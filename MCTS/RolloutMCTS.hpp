#ifndef HEADER_RENJU_ROLLOUT_MCTS
#define HEADER_RENJU_ROLLOUT_MCTS

#include "renju\Renju.hpp"
#include "Limitation.hpp"
#include "BasicMCTS.hpp"
#include "ResultValueArray.hpp"

namespace renju
{
	const SuccessionScore m_defaultBasis = {20000, 5000, 1000, 100, 20, 5, 1};
	class RolloutMCTS : public BasicMCTS
	{
	private:
		class Node;
	public:
		class CheckResult;
	private:
		using SelectArray = ResultValueArray<Node*, double, Board::boardSize * Board::boardSize>;
		using GetBestArray = ResultValueArray<StonePosition, UINT_32, Board::boardSize* Board::boardSize>;
		//using GetBestArray = ResultValueArray<StonePosition, double, Board::boardSize* Board::boardSize>;
		using BestScoreArray = ResultValueArray<StonePosition, UINT_64, Board::boardSize * Board::boardSize>;
		SelectArray m_selectArray;
		GetBestArray m_getBestArray;
		BestScoreArray m_bestScoreArray;
		CheckResult *m_checkResult;
		Node* m_root;
		//static SuccessionScore m_defaultBasis;
	private:
		double Evaluate(const Board& board, Board& buffer, const WinnerType nodeWinner, UINT_32 simulateCount);
	public:
		static void PositionCheckFunction(const Board& board, CheckResult& task, bool getScore);
		static INT_64 GetSuccessionScore(const UINT_64& input, const SuccessionScore& basis);
		static INT_64 GetPositionScore(const Board& board, const StonePosition& position, const SuccessionScore& basis);
		void RandomPlace(Board& board, const UINT_32& random);
		void ScorePlace(Board& board, const UINT_32& random);
		WinnerType RolloutPolicy(Board& board, bool runType);
	protected:
		void IterationFunction(Board& board, const double& c_puct = 5) override;
		StonePosition GetBestMove() override;
	public:
		RolloutMCTS();
		~RolloutMCTS();
		void UpdateWithMove(const renju::StonePosition& position) override;
		std::tuple<double, std::vector<renju::StonePosition>, std::vector<UINT_32>> GetStatistic() const override;
	};
}

#endif