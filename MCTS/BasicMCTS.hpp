#ifndef HEADER_RENJU_MCTS
#define HEADER_RENJU_MCTS

#include "renju\Renju.hpp"
#include "Limitation.hpp"
#include <chrono>
#include <tuple>
#include <vector>
#include <random>

namespace renju
{

class BasicMCTS
{
private:
	LimitationType m_limitation;
	double m_timeLimitation;
	UINT_32 m_iterationLimitation;
	UINT_32 m_checkTerm;
	UINT_32 m_searchIteration;
	std::random_device randomDevice;
	std::default_random_engine randomEngine;
private:
	void InitializeLimitation()
	{
		
	}
	bool IsReachLimitation() const
	{
		switch (m_limitation)
		{
		case LimitationType::time:
			throw("not support now");
			break;
		case LimitationType::iteration:
			if (m_searchIteration >= m_iterationLimitation)
			{
				return true;
			}
			break;
		}
		return false;
	}
protected:
	virtual void IterationFunction(Board& board, const double& c_puct = 5) = 0;
	virtual StonePosition GetBestMove() = 0;
	inline UINT_32 RunRandomDevice()
	{
		return randomDevice();
	}
	inline UINT_32 RunRandomEngine()
	{
		return randomEngine();
	}
public:
	BasicMCTS()
	{
		randomEngine.seed(randomDevice());
	}
	void ChangeSeed()
	{
		randomEngine.seed(randomDevice());
	}
	void SetSeed(UINT_32 seed)
	{
		randomEngine.seed(seed);
	}
	void SetLimitation(const LimitationType& limitation, const double& time, const UINT_32& iteration, const UINT_32& checkTerm)
	{
		m_limitation = limitation;
		m_timeLimitation = time;
		m_iterationLimitation = iteration;
		m_checkTerm = checkTerm;
	}
	StonePosition GetMove(const renju::Board& board, const double& c_puct = 5)
	{
		InitializeLimitation();
		m_searchIteration = 0;
		Board buffer(board);
		do
		{
			do
			{
				IterationFunction(buffer, c_puct);
				++m_searchIteration;
				while (buffer.GetCurrentPosition() != board.GetCurrentPosition())
				{
					buffer.RetractMove();
				}
			} while (m_searchIteration % m_checkTerm);
		} while (!IsReachLimitation());
		return GetBestMove();
	}
	
	virtual void UpdateWithMove(const renju::StonePosition& position) = 0;
	virtual std::tuple<double, std::vector<renju::StonePosition>, std::vector<UINT_32>> GetStatistic() const = 0;
};

}
#endif