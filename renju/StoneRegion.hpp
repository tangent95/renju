#ifndef HEADER_RENJU_STONE_REGION
#define HEADER_RENJU_STONE_REGION

#include "RenjuDefination.hpp"
#include "Board.hpp"

namespace renju
{
	class StoneRegion
	{
	public:
		UINT_32 left;
		UINT_32 right;
		UINT_32 top;
		UINT_32 bottom;
	private:
		inline bool __IsEmpty()
		{
			return left == 0;
		}
		inline void __Clear()
		{
			left = 0;
			right = 0;
			top = 0;
			bottom = 0;
		}
		inline void __Initialize(const StonePosition& input)
		{
			left = input.x;
			right = input.x;
			top = input.y;
			bottom = input.y;
		}
		inline void __Update(const StonePosition& input)
		{
			if (input.x < left && input.x) left = input.x;
			if (right < input.x && input.x <= Board::boardSize) right = input.x;
			if (input.y < top && input.y) top = input.y;
			if (bottom < input.y && input.y <= Board::boardSize) bottom = input.y;
		}
	public:
		StoneRegion()
		{
			__Clear();
		}
		StoneRegion(const StonePosition& input)
		{
			__Initialize(input);
		}
		StoneRegion(const Board& input)
		{
			if (input.IsBoardEmpty())
			{
				__Initialize(StonePosition((Board::boardSize + 1) >> 1, (Board::boardSize + 1) >> 1));
				return;
			}
			StonePosition buffer = input.GetFirstPosition();
			__Initialize(buffer);
			buffer = input.GetStoneNextPosition(buffer);
			while (buffer.x != 0)
			{
				__Update(buffer);
				buffer = input.GetStoneNextPosition(buffer);
			}
		}
	public:
		void Clear()
		{
			__Clear();
		}
		void UpdateWithMove(const StonePosition& input)
		{
			if (__IsEmpty())
			{
				__Initialize(input);
				return;
			}
			__Update(input);
		}
		/*void FitBoard(const Board& input)
		{
			
		}*/
		void Expand1()
		{
			if (left > 1) left -= 1;
			if (right + 1 <= Board::boardSize) right += 1;
			if (top > 1) top -= 1;
			if (bottom + 1 <= Board::boardSize) bottom += 1;
		}
		void Expand2()
		{
			if (left > 2) left -= 2; else left = 1;
			if (right + 2 <= Board::boardSize) right += 2; else right = Board::boardSize;
			if (top > 2) top -= 2; else top = 1;
			if (bottom + 2 <= Board::boardSize) bottom += 2; else bottom = Board::boardSize;
		}
	};
}
#endif