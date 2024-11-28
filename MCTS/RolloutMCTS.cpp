#include "RolloutMCTS.hpp"

#include <cmath>
#include <set>
#include <cstdio>

#define MAX_CHILD_COUNT (30)

/*
作为现在的我去看这个文件：
设计加入了禁手规则，以及棋盘过大，导致评估函数速度过慢，进一步拉跨MCTS
*/
namespace renju
{
	class RolloutMCTS::CheckResult
	{
	public:
		bool isFinish;
		StonePosition position;
		INT_64 score;
		bool isBanned;
		bool haveAround;
		void Initialize(const StonePosition& input)
		{
			isFinish = false;
			position = input;
		}
	};
	class RolloutMCTS::Node
	{
	private:
		class PositionScore
		{
		public:
			StonePosition m_position;
			INT_64 m_score;
			PositionScore(const StonePosition& position, const INT_64& score)
			{
				m_position = position;
				m_score = score;
			}
			bool operator < (const PositionScore& input) const
			{
				if (m_score < input.m_score)
				{
					return true;
				}
				else if (m_score == input.m_score)
				{
					return (m_position.x * (Board::boardSize + 1) + m_position.y) < (input.m_position.x * (Board::boardSize + 1) + input.m_position.y);
				}
				return false;
			}
			bool operator == (const PositionScore& input) const
			{
				return false;
			}
			bool operator > (const PositionScore& input) const
			{
				if (m_score > input.m_score)
				{
					return true;
				}
				else if (m_score == input.m_score)
				{
					return (m_position.x * (Board::boardSize + 1) + m_position.y) > (input.m_position.x * (Board::boardSize + 1) + input.m_position.y);
				}
				return false;
			}
		};
		static double Sigmoid(const double& input)
		{
			return 1 / (1 + exp(-input));
		}
		static double CalculateProbability(const UINT_32& index)
		{
			return Sigmoid(-(1.0 / 2.5 * index - 5));
		}
	private:
		Node* m_parent;
		UINT_32 N;
		double P;
		double W, Q;
		WinnerType m_winner;
		StonePosition m_position;
		Node* m_child[MAX_CHILD_COUNT];
		UINT_32 m_childCount;
	public:
		Node() = delete;
		Node(Node* parent, const StonePosition& position, const WinnerType& winner, const double& probability = 1)
		{
			m_parent = parent;
			N = 0;
			W = 0;
			Q = 0;
			P = probability;
			m_winner = winner;
			m_position = position;
			m_childCount = 0;
		}
		~Node()
		{
			for (UINT_32 position(0); position < m_childCount; ++position)
			{
				delete m_child[position];
			}
		}
		Node* Select(const UINT_32 random, SelectArray& array, const double& c_puct = 5) //请注意:叶子节点不能调用它
		{
			double sqrtN(sqrt(N));
			double value;
			array.Clear();
			for (UINT_32 position(0); position < m_childCount; ++position)
			{
				value = m_child[position]->Q + c_puct * m_child[position]->P * sqrtN / (1.0 * m_child[position]->N + 1);
				array.Push(m_child[position], value);
			}
			return array[random % array.Count()];
		}
		StonePosition GetBestMove(const UINT_32 random, GetBestArray& array) const
		{
			printf("get best:\n");
			array.Clear();
			for (UINT_32 position(0); position < m_childCount; ++position)
			{
				printf("position:%d,%d N:%d P:%lf Q:%lf\n", m_child[position]->m_position.x, m_child[position]->m_position.y, m_child[position]->N, m_child[position]->P, m_child[position]->Q);
				array.Push(m_child[position]->m_position, m_child[position]->N);
			}
			return array[random % array.Count()];
		}
		void Expand(const Board& board, RolloutMCTS::CheckResult* checkResult)
		{
			StoneRegion searchRegion(board);
			if (board.GetCurrentOrder() == 1)
			{
				searchRegion.Expand1();
			}
			else
			{
				searchRegion.Expand2();
			}
			UINT_32 searchX, searchY;
			bool runStep(false);
			m_childCount = 0;
			UINT_32 totalCount(0);
			for (searchX = searchRegion.left; searchX <= searchRegion.right; ++searchX)
			{
				for (searchY = searchRegion.top; searchY <= searchRegion.bottom; ++searchY)
				{
					if (board.GetStoneType(StonePosition(searchX, searchY)) == StoneType::none)
					{
						checkResult[totalCount].Initialize(StonePosition(searchX, searchY));
						RolloutMCTS::PositionCheckFunction(board, checkResult[totalCount], true);
						++totalCount;
					}
				}
			}
			StonePosition banned;
			std::set<PositionScore> position;
			for (UINT_32 i(0); i < totalCount; ++i)
			{
				while (!checkResult[i].isFinish);
				if (!checkResult[i].haveAround)
				{
					continue;
				}
				if (checkResult[i].isBanned)
				{
					banned = checkResult[i].position;
					continue;
				}
				position.insert(PositionScore(checkResult[i].position, checkResult[i].score));
			}
			if (position.empty())
			{
				m_child[m_childCount] = new Node(this, banned, board.GetWinnerAfterMove(banned));
				++m_childCount;
				return;
			}
			for (std::set<PositionScore>::reverse_iterator it(position.rbegin()); it != position.rend(); ++it)
			{
				m_child[m_childCount] = new Node(this, (*it).m_position, board.GetWinnerAfterMove((*it).m_position) , CalculateProbability(m_childCount + 1));
				++m_childCount;
				if (m_childCount >= MAX_CHILD_COUNT)
				{
					break;
				}
			}
		}
		void UpdateStatistic(const double& value)
		{
			N += 1;
			W += value;
			Q = W / N;
		}
		bool IsLeaf() const
		{
			return m_childCount == 0;
		}
		WinnerType GetWinner()
		{
			return m_winner;
		}
		const StonePosition& GetMove()
		{
			return m_position;
		}
		Node* GetParent()
		{
			return m_parent;
		}
	};
	RolloutMCTS::RolloutMCTS() : BasicMCTS()
	{
		m_root = new Node(nullptr, StonePosition(0, 0), WinnerType::none);
		m_checkResult = new CheckResult [Board::boardSize * Board::boardSize];
	}
	RolloutMCTS::~RolloutMCTS()
	{
		delete m_root;
		delete [] m_checkResult;
	}
	void RolloutMCTS::PositionCheckFunction(const Board& board, CheckResult& task, bool getScore)
	{
		StoneRegion searchRegion(task.position);
		searchRegion.Expand2();
		UINT_32 searchX, searchY;
		task.haveAround = false;
		for (searchX = searchRegion.left; searchX <= searchRegion.right; ++searchX)
		{
			for (searchY = searchRegion.top; searchY <= searchRegion.bottom; ++searchY)
			{
				if (board.GetStoneType(StonePosition(searchX, searchY)) != StoneType::none)
				{
					if (searchX != task.position.x || searchY != task.position.y)
					{
						task.haveAround = true;
					}
				}
			}
		}
		task.isBanned = false;
		if (!board.IsBoardEmpty()) //禁手
		{
			if (!board.IsMoveVaild(task.position, board.GetCurrentType() == StoneType::black ? StoneType::white : StoneType::black))
			{
				task.isBanned = true;
			}
		}
		if (getScore)
		{
			task.score = GetPositionScore(board, task.position, m_defaultBasis);
		}
		else
		{
			task.score = 0;
		}
		task.isFinish = true;
	}
	INT_64 RolloutMCTS::GetSuccessionScore(const UINT_64& input, const SuccessionScore& basis)
	{
		INT_64 score(0);
		if (IsSuccessionFiveOrMore(input))
		{
			score += basis.fiveOrMore;
		}
		else if (IsSuccessionLiveFour(input))
		{
			score += basis.liveFour;
		}
		else if (IsSuccessionRushFour(input))
		{
			score += basis.rushFour;
		}
		else if (IsSuccessionLiveThree(input))
		{
			score += basis.liveThree;
		}
		else if (IsSuccessionSleepThree(input))
		{
			score += basis.sleepThree;
		}
		else if (IsSuccessionLiveTwo(input))
		{
			score += basis.liveTwo;
		}
		else if (IsSuccessionSleepTwo(input))
		{
			score += basis.sleepTwo;
		}
		return score;
	}
	INT_64 RolloutMCTS::GetPositionScore(const Board& board, const StonePosition& position, const SuccessionScore& basis)
	{
		INT_64 ownScore(0), opponentScore(0);
		UINT_64 succession;
		StoneType opponent(board.GetCurrentType());
		StoneType own(opponent == StoneType::black ? StoneType::white : StoneType::black);
		
		succession = board.GetSuccession(position, own, Direction::horizontal);
		ownScore += GetSuccessionScore(succession, basis);
		succession = board.GetSuccession(position, own, Direction::vertical);
		ownScore += GetSuccessionScore(succession, basis);
		succession = board.GetSuccession(position, own, Direction::leftDiagonal);
		ownScore += GetSuccessionScore(succession, basis);
		succession = board.GetSuccession(position, own, Direction::rightDiagonal);
		ownScore += GetSuccessionScore(succession, basis);
		
		succession = board.GetSuccession(position, opponent, Direction::horizontal);
		opponentScore += GetSuccessionScore(succession, basis);
		succession = board.GetSuccession(position, opponent, Direction::vertical);
		opponentScore += GetSuccessionScore(succession, basis);
		succession = board.GetSuccession(position, opponent, Direction::leftDiagonal);
		opponentScore += GetSuccessionScore(succession, basis);
		succession = board.GetSuccession(position, opponent, Direction::rightDiagonal);
		opponentScore += GetSuccessionScore(succession, basis);
		
		return ownScore * 2 + opponentScore;
	}
	void RolloutMCTS::RandomPlace(Board& board, const UINT_32& random)
	{
		if (board.IsGameEnd())
		{
			return;
		}
		if (board.IsBoardEmpty())
		{
			board.DoMove(StonePosition((Board::boardSize + 1) >> 1, (Board::boardSize + 1) >> 1));
			return;
		}
		StoneRegion searchRegion(board);
		if (board.GetCurrentOrder() == 1)
		{
			searchRegion.Expand1();
		}
		else
		{
			searchRegion.Expand2();
		}
		UINT_32 totalResult(0);
		UINT_32 searchX, searchY;
		for (searchX = searchRegion.left; searchX <= searchRegion.right; ++searchX)
		{
			for (searchY = searchRegion.top; searchY <= searchRegion.bottom; ++searchY)
			{
				if (board.GetStoneType(StonePosition(searchX, searchY)) == StoneType::none)
				{
					m_checkResult[totalResult].Initialize(StonePosition(searchX, searchY));
					PositionCheckFunction(board, m_checkResult[totalResult], false);
					++totalResult;
				}
			}
		}
		m_bestScoreArray.Clear();
		StonePosition banned;
		for (UINT_32 i(0); i < totalResult; ++i)
		{
			while (!m_checkResult[i].isFinish);
			if (m_checkResult[i].isBanned)
			{
				banned = m_checkResult[i].position;
				continue;
			}
			m_bestScoreArray.Push(m_checkResult[i].position, m_checkResult[i].score);
		}
		if (!m_bestScoreArray.Count())
		{
			board.DoMove(banned);
		}
		board.DoMove(m_bestScoreArray[random % m_bestScoreArray.Count()]);
	}
	void RolloutMCTS::ScorePlace(Board& board, const UINT_32& random)
	{
		if (board.IsGameEnd())
		{
			return;
		}
		if (board.IsBoardEmpty())
		{
			board.DoMove(StonePosition((Board::boardSize + 1) >> 1, (Board::boardSize + 1) >> 1));
			return;
		}
		StoneRegion searchRegion(board);
		if (board.GetCurrentOrder() == 1)
		{
			searchRegion.Expand1();
		}
		else
		{
			searchRegion.Expand2();
		}
		UINT_32 totalResult(0);
		UINT_32 searchX, searchY;
		for (searchX = searchRegion.left; searchX <= searchRegion.right; ++searchX)
		{
			for (searchY = searchRegion.top; searchY <= searchRegion.bottom; ++searchY)
			{
				if (board.GetStoneType(StonePosition(searchX, searchY)) == StoneType::none)
				{
					m_checkResult[totalResult].Initialize(StonePosition(searchX, searchY));
					PositionCheckFunction(board, m_checkResult[totalResult], true);
					++totalResult;
				}
			}
		}
		m_bestScoreArray.Clear();
		StonePosition banned;
		for (UINT_32 i(0); i < totalResult; ++i)
		{
			while (!m_checkResult[i].isFinish);
			if (m_checkResult[i].isBanned)
			{
				banned = m_checkResult[i].position;
				continue;
			}
			m_bestScoreArray.Push(m_checkResult[i].position, m_checkResult[i].score);
		}
		if (!m_bestScoreArray.Count())
		{
			board.DoMove(banned);
		}
		board.DoMove(m_bestScoreArray[random % m_bestScoreArray.Count()]);
	}
	WinnerType RolloutMCTS::RolloutPolicy(Board& board, bool runType)
	{
		if (board.IsGameEnd())
		{
			return board.GetWinner();
		}
		do
		{
			if (runType)
			{
				ScorePlace(board, RunRandomEngine());
			}
			else
			{
				RandomPlace(board, RunRandomEngine());
			}
		} while (!board.IsGameEnd());
		return board.GetWinner();
	}
	double RolloutMCTS::Evaluate(const Board& board, Board& buffer, const WinnerType nodeWinner, const UINT_32 simulateCount)
	{
		double value(0);
		WinnerType currentType = board.GetCurrentType() == StoneType::black ? WinnerType::black : WinnerType::white;
		WinnerType simulateWinner;
		if (nodeWinner != WinnerType::none)
		{
			if (nodeWinner == currentType)
			{
				value = 1;
			}
			else if (nodeWinner == WinnerType::none)
			{
				value = 0;
			}
			else
			{
				value = -1;
			}
			return value;
		}
		for (UINT_32 i(simulateCount); i; --i)
		{
			simulateWinner = RolloutPolicy(buffer, i % 3);
			while (buffer.GetCurrentPosition() != board.GetCurrentPosition())
			{
				buffer.RetractMove();
			}
			if (simulateWinner == currentType)
			{
				value = 1;
			}
			else if (simulateWinner == WinnerType::none)
			{
				value = 0;
			}
			else
			{
				value = -1;
			}
		}
		return value / simulateCount;
	}
	void RolloutMCTS::IterationFunction(Board& board, const double& c_puct)
	{
		Node* node = m_root;
		while (!node->IsLeaf())
		{
			node = node->Select(RunRandomEngine(), m_selectArray, c_puct);
			board.DoMove(node->GetMove());
		}
		double value;
		Board buffer(board);
		value = Evaluate(board, buffer, node->GetWinner(), 5);
		if (node->GetWinner() == WinnerType::none)
		{
			node->Expand(board, m_checkResult);
		}
		do
		{
			node->UpdateStatistic(value);
			value = -value;
			node = node->GetParent();
		} while (node != nullptr);
	}
	StonePosition RolloutMCTS::GetBestMove()
	{
		return m_root->GetBestMove(RunRandomEngine(), m_getBestArray);
	}
	void RolloutMCTS::UpdateWithMove(const renju::StonePosition& position)
	{
		
	}
	std::tuple<double, std::vector<renju::StonePosition>, std::vector<UINT_32>> RolloutMCTS::GetStatistic() const
	{
		return std::make_tuple(0, std::vector<renju::StonePosition>(), std::vector<UINT_32>());
	}
}