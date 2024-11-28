#ifndef HEADER_RENJU_DEFINATION
#define HEADER_RENJU_DEFINATION

#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>

//for dbg
#include <cstdio>

namespace renju
{
	template <typename T>
	inline T Min(T a, T b)
	{
		return a < b ? a : b;
	}
	template <typename T>
	inline T Max(T a, T b)
	{
		return a > b ? a : b;
	}

	using INT_8 = std::int8_t;
	using UINT_8 = std::uint8_t;
	using INT_32 = std::int32_t;
	using UINT_32 = std::uint32_t;
	using INT_64 = std::int64_t;
	using UINT_64 = std::uint64_t;
	
	enum class PlayerType
	{
		none,
		human,
		ai
	};
	enum class WinnerType
	{
		none, //无
		draw, //平局
		black, //黑方(先手)胜
		white, //白方(后手)胜
		error
	};
	enum class StoneType
	{
		//注在棋盘上只会出现black,white,none(未落子的空位置)
		//any,own,opponent以及none用于位运算棋型判断中
		black = 1,
		white = 2,
		any = 0, //any必须为0,其余只要赋2^n保证二进制位不重合即可
		none = 4,
		own = 8,
		opponent = 16,
		//保留
		chose = 32,
		error = 64
	};
	enum class SuccessionType
	{
		fiveOrMore,
		liveFour,
		rushFour,
		liveThree,
		sleepThree,
		liveTwo,
		sleepTwo
	};
	enum class Direction
	{
		horizontal, //水平
		vertical, //竖直
		leftDiagonal,
		rightDiagonal
	};
	class StonePosition
	{
	public:
		UINT_32 x;
		UINT_32 y;
		StonePosition() = default;
		StonePosition(const UINT_32& inputX, const UINT_32& inputY)
		{
			x = inputX;
			y = inputY;
		}
		void SetZero()
		{
			x = 0;
			y = 0;
		}
		void operator = (const StonePosition& input)
		{
			x = input.x;
			y = input.y;
		}
		bool operator != (const StonePosition& input) const
		{
			return x == input.x && y == input.y;
		}
	};
	class Stone
	{
	public:
		StoneType type;
		StonePosition previous;
		StonePosition next;
		UINT_32 order;
	};
	class SuccessionScore
	{
	public:
		INT_64 fiveOrMore;
		INT_64 liveFour;
		INT_64 rushFour;
		INT_64 liveThree;
		INT_64 sleepThree;
		INT_64 liveTwo;
		INT_64 sleepTwo;
		SuccessionScore(const INT_64& _fiveOrMore, const INT_64& _liveFour, const INT_64& _rushFour, const INT_64& _liveThree, const INT_64& _sleepThree, const INT_64& _liveTwo, const INT_64& _sleepTwo)
		{
			fiveOrMore = _fiveOrMore;
			liveFour = _liveFour;
			rushFour = _rushFour;
			liveThree = _liveThree;
			sleepThree = _sleepThree;
			liveTwo = _liveTwo;
			sleepTwo = _sleepTwo;
		}
	};
}
#endif