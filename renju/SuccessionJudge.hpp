/*
文件类型:C++头文件(.hpp)
文件名:SuccessionJudge.hpp
功能:判断棋型
*/

#ifndef HEADER_RENJU_SUCCESSION_JUDGE
#define HEADER_RENJU_SUCCESSION_JUDGE

#include "RenjuDefination.hpp"

namespace renju
{
	UINT_8 IsSuccessionFiveOrMore(const UINT_64& input);
	UINT_8 IsSuccessionLiveFour(const UINT_64& input);
	UINT_8 IsSuccessionRushFour(const UINT_64& input);
	UINT_8 IsSuccessionLiveThree(const UINT_64& input);
	UINT_8 IsSuccessionSleepThree(const UINT_64& input);
	UINT_8 IsSuccessionLiveTwo(const UINT_64& input); //对于二的判断有时会与其它的冲突（对长连、五连、四、三的判断精准），不建议使用这个进行精准判断，可以用在评分落子上
	UINT_8 IsSuccessionSleepTwo(const UINT_64& input); //对于二的判断有时会与其它的冲突（对长连、五连、四、三的判断精准），不建议使用这个进行精准判断，可以用在评分落子上
}

#endif