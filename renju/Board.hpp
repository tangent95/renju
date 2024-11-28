#ifndef HEADER_RENJU_BOARD
#define HEADER_RENJU_BOARD

#include "RenjuDefination.hpp"

#include <cstdlib>

/*
//rules: https://www.zhihu.com/question/375400094/answer/2454295442?utm_id=0
// 
https://www.zhihu.com/question/375400094/answer/2454295442
*/
namespace renju
{
	//注:输入position的函数不检查position越界
	class Board
	{
	public:
		static const UINT_32 boardSize = 15;
	private:
		WinnerType m_winner; //是否有一方获胜
		Stone* m_stone; //棋盘数据储存
		StonePosition m_positionFirst; //棋盘首位置,初始为(0,0)
		StonePosition m_positionCurrent; //棋盘当前位置
	private:
		inline void Allocate()
		{
			m_stone = (Stone*)malloc(sizeof(Stone) * boardSize * boardSize);
		}
		inline void Free()
		{
			free(m_stone);
		}
		inline Stone& At(const StonePosition& input) const
		{
			return m_stone[(input.y - 1) * boardSize + input.x - 1];
		}
		inline Stone& At(const StonePosition& input)
		{
			return m_stone[(input.y - 1) * boardSize + input.x - 1];
		}
		inline void Clear()
		{
			m_winner = WinnerType::none;
			m_positionFirst.SetZero();
			m_positionCurrent.SetZero();
			for (INT_32 position(0); position < boardSize * boardSize ; ++position)
			{
				m_stone[position].previous.SetZero();
				m_stone[position].next.SetZero();
				m_stone[position].order = 0;
				m_stone[position].type = StoneType::none;
			}
		}
		WinnerType CheckWinner();
		
		UINT_32 GetNInRow(const StonePosition& position, const StoneType& ownType, const Direction& direction) const;
	public:
		Board()
		{
			Allocate();
			Clear();
		}
		Board(const Board& input)
		{
			m_winner = input.m_winner;
			Allocate();
			for (UINT_32 position(0); position < boardSize * boardSize; ++position)
			{
				m_stone[position].previous = input.m_stone[position].previous;
				m_stone[position].next = input.m_stone[position].next;
				m_stone[position].order = input.m_stone[position].order;
				m_stone[position].type = input.m_stone[position].type;
			}
			m_positionFirst.x = input.m_positionFirst.x;
			m_positionFirst.y = input.m_positionFirst.y;
			m_positionCurrent.x = input.m_positionCurrent.x;
			m_positionCurrent.y = input.m_positionCurrent.y;
		}
		~Board()
		{
			Free();
		}
	public:
		void Copy(const Board& input)
		{
			m_winner = input.m_winner;
			for (UINT_32 position(0); position < boardSize * boardSize; ++position)
			{
				m_stone[position].previous = input.m_stone[position].previous;
				m_stone[position].next = input.m_stone[position].next;
				m_stone[position].order = input.m_stone[position].order;
				m_stone[position].type = input.m_stone[position].type;
			}
			m_positionFirst.x = input.m_positionFirst.x;
			m_positionFirst.y = input.m_positionFirst.y;
			m_positionCurrent.x = input.m_positionCurrent.x;
			m_positionCurrent.y = input.m_positionCurrent.y;
		}
	public:
		bool IsBoardEmpty() const
		{
			if (!m_positionFirst.x)
			{
				return true;
			}
			return false;
		}
		bool IsGameEnd() const
		{
			return m_winner != WinnerType::none;
		}
		bool IsEndForBan() const
		{
			if (IsGameEnd() && m_winner != WinnerType::draw)
			{
				if (GetCurrentType() == (m_winner == WinnerType::white ? StoneType::black : StoneType::white))
				{
					return true;
				}
			}
			return false;
		}
		WinnerType GetWinner() const
		{
			return m_winner;
		}
		void Restart()
		{
			Clear();
		}
		const StonePosition& GetFirstPosition() const
		{
			return m_positionFirst;
		}
		const StonePosition& GetCurrentPosition() const
		{
			return m_positionCurrent;
		}
		UINT_32 GetStoneOrder(const StonePosition& input) const
		{
			return At(input).order;
		}
		StoneType GetStoneType(const StonePosition& input) const
		{
			return At(input).type;
		}
		const StonePosition& GetStoneNextPosition(const StonePosition& input) const
		{
			return At(input).next;
		}
		const StonePosition& GetStonePreviousPosition(const StonePosition& input) const
		{
			return At(input).previous;
		}
	public:
		StoneType GetCurrentType() const
		{
			return GetStoneType(GetCurrentPosition());
		}
		UINT_32 GetCurrentOrder() const
		{
			return GetStoneOrder(GetCurrentPosition());
		}
	public:
		void DoMove(const StonePosition& input);
		
		void RetractMove();

		UINT_64 GetSuccession(const StonePosition& position, const StoneType& ownType, const Direction& direction) const;
		//返回棋盘以ownType的视野下,在position位置并在direction方向下左右的棋子类型(own,opponent,none)
		//返回的顺序由高位至低位排列,建议使用位运算操作返回值
		
		bool IsMoveVaild(const StonePosition& position, const StoneType& ownType) const;
		
		WinnerType GetWinnerAfterMove(const StonePosition& position) const;
	};
}

#endif