#include "SuccessionJudge.hpp"
#include "Renju.hpp"


//变动:Board中不再去实现region功能,另起一个StoneRegion并提供Clear,Update,Retract(可以采用栈)机制
namespace renju
{
	inline WinnerType StoneToWinner(const StoneType& input)
	{
		if (input == StoneType::black)
		{
			return WinnerType::black;
		}
		if (input == StoneType::white)
		{
			return WinnerType::white;
		}
		return WinnerType::error;
	}
	inline StoneType GetOpponentType(const StoneType& input)
	{
		if (input == StoneType::black)
		{
			return StoneType::white;
		}
		else
		{
			return StoneType::black;
		}
	}
	void Board::DoMove(const StonePosition& input)
	{
		//可选:加入对不合法走子的判断
		if (IsGameEnd() || GetStoneType(input) != StoneType::none)
		{
			return;
		}
		if (input.x == 0 || input.y == 0 || input.x > Board::boardSize || input.y > Board::boardSize)
		{
			return;
		}
		if (IsBoardEmpty())
		{
			At(input).order = 1;
			At(input).type = StoneType::black;
			At(input).previous.SetZero();
			At(input).next.SetZero();
			m_positionFirst = input;
			m_positionCurrent = input;
			return;
		}
		At(input).order = At(m_positionCurrent).order + 1;
		At(input).type = GetOpponentType(At(m_positionCurrent).type);
		At(input).previous = m_positionCurrent;
		At(input).next.SetZero();
		At(m_positionCurrent).next = input;
		m_positionCurrent = input;
		m_winner = CheckWinner();
	}
	void Board::RetractMove()
	{
		if (IsBoardEmpty())
		{
			return;
		}
		if (At(m_positionCurrent).order == 1)
		{
			At(m_positionCurrent).order = 0;
			At(m_positionCurrent).type = StoneType::none;
			m_positionCurrent.SetZero();
			m_positionFirst.SetZero();
			return;
		}
		if (m_winner != WinnerType::none)
		{
			m_winner = WinnerType::none;
		}
		At(m_positionCurrent).order = 0;
		At(m_positionCurrent).type = StoneType::none;
		//current的next一定为(0, 0)
		m_positionCurrent = At(m_positionCurrent).previous;
		At(At(m_positionCurrent).next).previous.SetZero();
		At(m_positionCurrent).next.SetZero();
	}
	inline UINT_8 StoneTypeToValue(const StoneType& ownType, const StoneType& checkType)
	{
		if (checkType == StoneType::none)
		{
			return (UINT_8)StoneType::none;
		}
		else if (checkType == ownType)
		{
			return (UINT_8)StoneType::own;
		}
		else
		{
			return (UINT_8)StoneType::opponent;
		}
	}
	//返回棋盘以ownType的视野下,在position位置并在direction方向下左右的棋子类型(own,opponent,none)
	//返回的顺序由高位至低位排列,建议使用位运算操作返回值
	UINT_64 Board::GetSuccession(const StonePosition& position, const StoneType& ownType, const Direction& direction) const
	{
		UINT_64 result(0);
		StoneType type;
		UINT_32 resultPosition(0);
		//注:以下的代码中涉及减的操作一定不能出现负号(position为无符号数),可以先加再减,在判断中也可以移动减
		switch (direction)
		{
		case Direction::horizontal: //水平方向
			while (resultPosition < 4)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.x + resultPosition < 5) //(position.x - 4) + resultPosition < 1
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x + resultPosition - 4, position.y)); //(position.x - 4) + resultPosition
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			while (resultPosition < 8)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.x + resultPosition > Board::boardSize + 3) //(position.x + 1) + (resultPosition - 4) > Board::boardSize
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x + resultPosition - 3, position.y)); //(position.x + 1) + (resultPosition - 4)
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			break;
		case Direction::vertical: //竖直方向
			while (resultPosition < 4)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.y + resultPosition < 5) //(position.y - 4) + resultPosition < 1
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x , position.y + resultPosition - 4)); //(position.y - 4) + resultPosition
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			while (resultPosition < 8)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.y + resultPosition > Board::boardSize + 3) //(position.y + 1) + (resultPosition - 4) > Board::boardSize
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x, position.y + resultPosition - 3)); //(position.y + 1) + (resultPosition - 4)
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			break;
		case Direction::leftDiagonal: //左对角线
			while (resultPosition < 4)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.x + resultPosition < 5 || position.y + resultPosition < 5) //(position.x - 4) + resultPosition < 1 || (position.y - 4) + resultPosition < 1
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x + resultPosition - 4, position.y + resultPosition - 4)); //x:(position.x - 4) + resultPosition y:(position.y - 4) + resultPosition
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			while (resultPosition < 8)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.x + resultPosition > Board::boardSize + 3 || position.y + resultPosition > Board::boardSize + 3) //(position.x + 1) + (resultPosition - 4) > Board::boardSize || (position.y + 1) + (resultPosition - 4) > Board::boardSize
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x + resultPosition - 3, position.y + resultPosition - 3)); //x:(position.x + 1) + (resultPosition - 4) y:(position.y + 1) + (resultPosition - 4)
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			break;
		case Direction::rightDiagonal: //右对角线方向
			while (resultPosition < 4)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.x + resultPosition < 5 || position.y + 4 > resultPosition + Board::boardSize) //(position.x - 4) + resultPosition < 1 || (position.y + 4) - resultPosition > Board::boardSize
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x + resultPosition - 4, position.y + 4 - resultPosition)); //x:(position.x - 4) + resultPosition y:(position.y + 4) - resultPosition
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			while (resultPosition < 8)
			{
				result <<= (8 * sizeof(UINT_8));
				if (position.x + resultPosition > Board::boardSize + 3 || position.y + 2 < resultPosition) //(position.x + 1) + (resultPosition - 4) > Board::boardSize || (position.y - 1) - (resultPosition - 4) < 1
				{
					result |= (UINT_8)StoneType::opponent;
				}
				else
				{
					type = GetStoneType(StonePosition(position.x + resultPosition - 3, position.y + 3 - resultPosition)); //x:(position.x + 1) + (resultPosition - 4) y:(position.y - 1) - (resultPosition - 4)
					result |= StoneTypeToValue(ownType, type);
				}
				++resultPosition;
			}
			break;
		}
		return result;
	}
	
	//position位置本身被视作为有ownType的棋子
	UINT_32 Board::GetNInRow(const StonePosition& position, const StoneType& ownType, const Direction& direction) const
	{
		UINT_32 result(1); //position位置本身
		StonePosition searchPosition;
		switch (direction)
		{
		case Direction::horizontal: //水平方向
			searchPosition.x = position.x - 1;
			searchPosition.y = position.y;
			while (searchPosition.x/*>=1*/ && GetStoneType(searchPosition) == ownType)
			{
				--searchPosition.x;
				++result;
			}
			searchPosition.x = position.x + 1;
			while (searchPosition.x <= Board::boardSize && GetStoneType(searchPosition) == ownType)
			{
				++searchPosition.x;
				++result;
			}
			break;
		case Direction::vertical: //竖直方向
			searchPosition.x = position.x;
			searchPosition.y = position.y - 1;
			while (searchPosition.y/*>=1*/ && GetStoneType(searchPosition) == ownType)
			{
				--searchPosition.y;
				++result;
			}
			searchPosition.y = position.y + 1;
			while (searchPosition.y <= Board::boardSize && GetStoneType(searchPosition) == ownType)
			{
				++searchPosition.y;
				++result;
			}
			break;
		case Direction::leftDiagonal: //左对角线
			searchPosition.x = position.x - 1;
			searchPosition.y = position.y - 1;
			while (searchPosition.x/*>=1*/ && searchPosition.y/*>=1*/ && GetStoneType(searchPosition) == ownType)
			{
				--searchPosition.x;
				--searchPosition.y;
				++result;
			}
			searchPosition.x = position.x + 1;
			searchPosition.y = position.y + 1;
			while (searchPosition.x <= Board::boardSize && searchPosition.y <= Board::boardSize && GetStoneType(searchPosition) == ownType)
			{
				++searchPosition.x;
				++searchPosition.y;
				++result;
			}
			break;
		case Direction::rightDiagonal: //右对角线方向
			searchPosition.x = position.x - 1;
			searchPosition.y = position.y + 1;
			while (searchPosition.x/*>=1*/ && searchPosition.y <= Board::boardSize && GetStoneType(searchPosition) == ownType)
			{
				--searchPosition.x;
				++searchPosition.y;
				++result;
			}
			searchPosition.x = position.x + 1;
			searchPosition.y = position.y - 1;
			while (searchPosition.x <= Board::boardSize && searchPosition.y/*>=1*/ && GetStoneType(searchPosition) == ownType)
			{
				++searchPosition.x;
				--searchPosition.y;
				++result;
			}
			break;
		}
		return result;
	}
	
	//黑棋一子落下，同时形成三三(这里一定要两个都是 “活”三才能算)、或者四四(只要是两个“四”即为禁手，无论是活四、冲四都算)、或者长连，且没有形成五连。那么，这个点就是禁手点，黑棋判负。白棋没有禁手。
	//在禁手规则下，除非一方出现不堵冲四或活三的低级错误，黑方仅能通过“四三”一种方法来获胜
	//而白方可以通过“四三”“三三”“四四”“抓禁手”等方法取胜，长连也算胜利。
	
	//返回当前位置对于某玩家是否是禁手(将position视作ownType),哪怕position上的不是自己的子或为空
	bool Board::IsMoveVaild(const StonePosition& position, const StoneType& ownType) const
	{
		if (ownType == StoneType::white) //白方无禁手
		{
			return true;
		}
		UINT_32 numberFour(0), numberLiveThree(0);
		UINT_32 nInRow;
		UINT_64 succession;
		bool haveMore(false);
		
		nInRow = GetNInRow(position, ownType, Direction::horizontal); //水平
		if (nInRow == 5)
		{
			return true;
		}
		if (nInRow > 5)
		{
			haveMore = true;
		}
		succession = GetSuccession(position, ownType, Direction::horizontal);
		if (IsSuccessionLiveFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionRushFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionLiveThree(succession))
		{
			++numberLiveThree;
		}
		
		nInRow = GetNInRow(position, ownType, Direction::vertical); //竖直
		if (nInRow == 5)
		{
			return true;
		}
		if (nInRow > 5)
		{
			haveMore = true;
		}
		succession = GetSuccession(position, ownType, Direction::vertical);
		if (IsSuccessionLiveFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionRushFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionLiveThree(succession))
		{
			++numberLiveThree;
		}
		
		nInRow = GetNInRow(position, ownType, Direction::leftDiagonal); //左斜对角线
		if (nInRow == 5)
		{
			return true;
		}
		if (nInRow > 5)
		{
			haveMore = true;
		}
		succession = GetSuccession(position, ownType, Direction::leftDiagonal);
		if (IsSuccessionLiveFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionRushFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionLiveThree(succession))
		{
			++numberLiveThree;
		}
		
		nInRow = GetNInRow(position, ownType, Direction::rightDiagonal); //右斜对角线
		if (nInRow == 5)
		{
			return true;
		}
		if (nInRow > 5)
		{
			haveMore = true;
		}
		succession = GetSuccession(position, ownType, Direction::rightDiagonal);
		if (IsSuccessionLiveFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionRushFour(succession))
		{
			++numberFour;
		}
		else if (IsSuccessionLiveThree(succession))
		{
			++numberLiveThree;
		}
		//((活三>=2||活四+冲四>=2||长连>=1)&&五连==0) && 黑子
		
		//五连(不包括长连)已在前面排除了
		if (numberFour >= 2 || numberLiveThree >=2 || haveMore)
		{
			return false;
		}
		return true;
	}
	WinnerType Board::CheckWinner()
	{
		WinnerType winner(WinnerType::none);
		if (!IsMoveVaild(GetCurrentPosition(), GetCurrentType()))
		{
			winner = StoneToWinner(GetOpponentType(GetCurrentType()));
		}
		UINT_32 nInRow;
		StoneType ownType = GetCurrentType();
		StonePosition position = GetCurrentPosition();
		
		nInRow = GetNInRow(position, ownType, Direction::horizontal); //水平
		if (nInRow == 5)
		{
			winner = StoneToWinner(ownType);
		}
		
		nInRow = GetNInRow(position, ownType, Direction::vertical); //竖直
		if (nInRow == 5)
		{
			winner = StoneToWinner(ownType);
		}
		
		nInRow = GetNInRow(position, ownType, Direction::leftDiagonal); //左斜对角线
		if (nInRow == 5)
		{
			winner = StoneToWinner(ownType);
		}
		
		nInRow = GetNInRow(position, ownType, Direction::rightDiagonal); //右斜对角线
		if (nInRow == 5)
		{
			winner = StoneToWinner(ownType);
		}
		
		if (GetCurrentOrder() == Board::boardSize * Board::boardSize)
		{
			winner = WinnerType::draw;
		}
		return winner;
	}
	WinnerType Board::GetWinnerAfterMove(const StonePosition& position) const
	{
		WinnerType winner(WinnerType::none);
		StoneType futureType = GetOpponentType(GetCurrentType());
		if (!IsMoveVaild(position, futureType))
		{
			winner = StoneToWinner(GetCurrentType());
		}
		UINT_32 nInRow;
		
		nInRow = GetNInRow(position, futureType, Direction::horizontal); //水平
		if (nInRow == 5)
		{
			winner = StoneToWinner(futureType);
		}
		
		nInRow = GetNInRow(position, futureType, Direction::vertical); //竖直
		if (nInRow == 5)
		{
			winner = StoneToWinner(futureType);
		}
		
		nInRow = GetNInRow(position, futureType, Direction::leftDiagonal); //左斜对角线
		if (nInRow == 5)
		{
			winner = StoneToWinner(futureType);
		}
		
		nInRow = GetNInRow(position, futureType, Direction::rightDiagonal); //右斜对角线
		if (nInRow == 5)
		{
			winner = StoneToWinner(futureType);
		}
		
		if (GetCurrentOrder() == Board::boardSize * Board::boardSize - 1)
		{
			winner = WinnerType::draw;
		}
		return winner;
	}
}




