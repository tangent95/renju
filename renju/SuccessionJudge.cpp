#include "SuccessionJudge.hpp"

namespace renju
{
	constexpr UINT_64 MakeSuccession(const StoneType chess1, const StoneType chess2, const StoneType chess3, const StoneType chess4, const StoneType chess5, const StoneType chess6, const StoneType chess7, const StoneType chess8)
	{
		return ((UINT_64)chess1 << 8 * sizeof(UINT_8) * 7) | ((UINT_64)chess2 << 8 * sizeof(UINT_8) * 6) | ((UINT_64)chess3 << 8 * sizeof(UINT_8) * 5) | ((UINT_64)chess4 << 8 * sizeof(UINT_8) * 4) | ((UINT_64)chess5 << 8 * sizeof(UINT_8) * 3) | ((UINT_64)chess6 << 8 * sizeof(UINT_8) * 2) | ((UINT_64)chess7 << 8 * sizeof(UINT_8) * 1) | ((UINT_64)chess8 << 8 * sizeof(UINT_8) * 0);
	}

	const UINT_64 successionJudgeFiveOrMore = /*子子子子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::own, StoneType::own, StoneType::own);
	const UINT_64 successionJudgeLiveFour = /*空子子子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::own, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeRushFour1 = /*空子子子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::own, StoneType::own);
	const UINT_64 successionJudgeRushFour2 = /*子空子子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::none, StoneType::own, StoneType::own);
	const UINT_64 successionJudgeRushFour3 = /*子子空子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::own, StoneType::none, StoneType::own);
	const UINT_64 successionJudgeRushFour4 = /*子子子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::own, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeRushFour5 = /*堵子子子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::opponent, StoneType::own, StoneType::own, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeRushFour6 = /*空子子子堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::own, StoneType::own, StoneType::opponent);
	const UINT_64 successionJudgeLiveThree1 = /*空空子子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::own, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeLiveThree2 = /*空子子空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::own, StoneType::none, StoneType::none);
	const UINT_64 successionJudgeLiveThree3 = /*空子空子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::none, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeSleepThree1 = /*堵子子空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::opponent, StoneType::own, StoneType::own, StoneType::none, StoneType::none);
	const UINT_64 successionJudgeSleepThree2 = /*空空子子堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::own, StoneType::own, StoneType::opponent);
	const UINT_64 successionJudgeSleepThree3 = /*堵子空子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::opponent, StoneType::own, StoneType::none, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeSleepThree4 = /*空子空子堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::none, StoneType::own, StoneType::opponent);
	const UINT_64 successionJudgeSleepThree5 = /*堵空子子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::opponent, StoneType::none, StoneType::own, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeSleepThree6 = /*空子子空堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::own, StoneType::none, StoneType::opponent);
	const UINT_64 successionJudgeSleepThree7 = /*空空子子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::own, StoneType::own);
	const UINT_64 successionJudgeSleepThree8 = /*子空空子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::none, StoneType::none, StoneType::own);
	const UINT_64 successionJudgeSleepThree9 = /*子子空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::own, StoneType::none, StoneType::none);
	const UINT_64 successionJudgeSleepThree10 = /*空子空子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::none, StoneType::own);
	const UINT_64 successionJudgeSleepThree11 = /*子空子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::none, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeSleepThree12 = /*堵空子子空堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::opponent, StoneType::none, StoneType::own, StoneType::own, StoneType::none, StoneType::opponent);
	const UINT_64 successionJudgeLiveTwo1 = /*空空空子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::none, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeLiveTwo2 = /*空空子空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::own, StoneType::none, StoneType::none);
	const UINT_64 successionJudgeLiveTwo3 = /*空子空空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::none, StoneType::none, StoneType::none);
	const UINT_64 successionJudgeSleepTwo1 = /*堵空子空空堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::opponent, StoneType::none, StoneType::own, StoneType::none, StoneType::none, StoneType::opponent);
	const UINT_64 successionJudgeSleepTwo2 = /*堵空空子空堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::opponent, StoneType::none, StoneType::none, StoneType::own, StoneType::none, StoneType::opponent);
	const UINT_64 successionJudgeSleepTwo3 = /*堵空子空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::opponent, StoneType::none, StoneType::own, StoneType::none, StoneType::none);
	const UINT_64 successionJudgeSleepTwo4 = /*空空空子堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::none, StoneType::own, StoneType::opponent);
	const UINT_64 successionJudgeSleepTwo5 = /*空空子空堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::own, StoneType::none, StoneType::opponent);
	const UINT_64 successionJudgeSleepTwo6 = /*堵子空空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::opponent, StoneType::own, StoneType::none, StoneType::none, StoneType::none);
	const UINT_64 successionJudgeSleepTwo7 = /*堵空空子空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::opponent, StoneType::none, StoneType::none, StoneType::own, StoneType::none);
	const UINT_64 successionJudgeSleepTwo8 = /*空子空空堵*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::own, StoneType::none, StoneType::none, StoneType::opponent);
	const UINT_64 successionJudgeSleepTwo9 = /*空空空子*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::none, StoneType::none, StoneType::none, StoneType::own);
	const UINT_64 successionJudgeSleepTwo10 = /*子空空空*/MakeSuccession(StoneType::any, StoneType::any, StoneType::any, StoneType::any, StoneType::own, StoneType::none, StoneType::none, StoneType::none);


	UINT_8 IsSuccessionFiveOrMore(const UINT_64& input) //连五或长连
	{
		if ((input & successionJudgeFiveOrMore) == successionJudgeFiveOrMore)
		{
			return 1;
		}
		else if ((input & (successionJudgeFiveOrMore) << (8 * sizeof(UINT_8) * 1)) == (successionJudgeFiveOrMore << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeFiveOrMore) << (8 * sizeof(UINT_8) * 2)) == (successionJudgeFiveOrMore << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeFiveOrMore) << (8 * sizeof(UINT_8) * 3)) == (successionJudgeFiveOrMore << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		else if ((input & (successionJudgeFiveOrMore) << (8 * sizeof(UINT_8) * 4)) == (successionJudgeFiveOrMore << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		return 0;
	}
	UINT_8 IsSuccessionLiveFour(const UINT_64& input) //活四
	{
		if ((input & successionJudgeLiveFour) == successionJudgeLiveFour)
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveFour) << (8 * sizeof(UINT_8) * 1)) == (successionJudgeLiveFour << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveFour) << (8 * sizeof(UINT_8) * 2)) == (successionJudgeLiveFour << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveFour) << (8 * sizeof(UINT_8) * 3)) == (successionJudgeLiveFour << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		return 0;
	}
	UINT_8 IsSuccessionRushFour(const UINT_64& input) //冲四
	{
		//1.空子子子
		if ((input & successionJudgeRushFour1) == successionJudgeRushFour1)
		{
			return 1;
		}
		//2.子空子子
		else if ((input & (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 4))) == (successionJudgeRushFour2 << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		//3.子子空子
		else if ((input & (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 4))) == (successionJudgeRushFour3 << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		//4.子子子空
		else if ((input & (successionJudgeRushFour4 << (8 * sizeof(UINT_8) * 4))) == (successionJudgeRushFour4 << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		//5.堵子子子空
		else if ((input & (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeRushFour5 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//6.空子子子堵
		else if ((input & (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeRushFour6 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		return 0;
	}
	UINT_8 IsSuccessionLiveThree(const UINT_64& input) //活三
	{
		//1.空空子子空
		if ((input & (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeLiveThree1 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//2.空子子空空
		else if ((input & (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeLiveThree2 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//3.空子空子空
		else if ((input & (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeLiveThree3 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		return 0;
	}
	UINT_8 IsSuccessionSleepThree(const UINT_64& input) //眠三
	{
		//堵子子空空
		if ((input & (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepThree1 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//2.空空子子堵
		else if ((input & (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepThree2 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//3.堵子空子空
		else if ((input & (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepThree3 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//4.空子空子堵
		else if ((input & (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepThree4 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//5.堵空子子空
		else if ((input & (successionJudgeSleepThree5 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepThree5 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		//6.空子子空堵
		else if ((input & (successionJudgeSleepThree6 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepThree6 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//7.空空子子
		else if ((input & (successionJudgeSleepThree7 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree7 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		//8.子空空子
		else if ((input & (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 4))) == (successionJudgeSleepThree8 << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		//9.子子空空
		else if ((input & (successionJudgeSleepThree9 << (8 * sizeof(UINT_8) * 4))) == (successionJudgeSleepThree9 << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		//10.空子空子
		else if ((input & (successionJudgeSleepThree10 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree10 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		//11.子空子空
		else if ((input & (successionJudgeSleepThree11 << (8 * sizeof(UINT_8) * 4))) == (successionJudgeSleepThree11 << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		//12.堵空子子空堵
		else if ((input & (successionJudgeSleepThree12 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepThree12 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree12 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepThree12 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepThree12 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepThree12 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		return 0;
	}
	UINT_8 IsSuccessionLiveTwo(const UINT_64& input)
	{
		//1.空空空子空
		if ((input & (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeLiveTwo1 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//2.空空子空空
		else if ((input & (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeLiveTwo2 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//3.空子空空空
		else if ((input & (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeLiveTwo3 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		return 0;
	}
	UINT_8 IsSuccessionSleepTwo(const UINT_64& input)
	{
		//1.堵空子空空堵
		if ((input & (successionJudgeSleepTwo1 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepTwo1 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo1 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepTwo1 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo1 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepTwo1 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		//2.堵空空子空堵
		else if ((input & (successionJudgeSleepTwo2 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepTwo2 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo2 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepTwo2 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo2 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepTwo2 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		//3.堵空子空空
		else if ((input & (successionJudgeSleepTwo3 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepTwo3 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		//4.空空空子堵
		else if ((input & (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepTwo4 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//5.空空子空堵
		else if ((input & (successionJudgeSleepTwo5 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepTwo5 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//6.堵子空空空
		else if ((input & (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 1))) == (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 1)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 2))) == (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 2)))
		{
			return 1;
		}
		else if ((input & (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepTwo6 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//7.堵空空子空
		else if ((input & (successionJudgeSleepTwo7 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepTwo7 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		//8.空子空空堵
		else if ((input & (successionJudgeSleepTwo8 << (8 * sizeof(UINT_8) * 3))) == (successionJudgeSleepTwo8 << (8 * sizeof(UINT_8) * 3)))
		{
			return 1;
		}
		//9.空空空子
		else if ((input & (successionJudgeSleepTwo9 << (8 * sizeof(UINT_8) * 0))) == (successionJudgeSleepTwo9 << (8 * sizeof(UINT_8) * 0)))
		{
			return 1;
		}
		//10.子空空空
		else if ((input & (successionJudgeSleepTwo10 << (8 * sizeof(UINT_8) * 4))) == (successionJudgeSleepTwo10 << (8 * sizeof(UINT_8) * 4)))
		{
			return 1;
		}
		return 0;
	}
}