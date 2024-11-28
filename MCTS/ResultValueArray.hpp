#ifndef HEADER_RENJU_RESULT_VALUE_ARRAY
#define HEADER_RENJU_RESULT_VALUE_ARRAY

namespace renju
{
template <typename ResultType, typename ValueType, UINT_32 maxSize>
class ResultValueArray
{
private:
	ResultType m_result[maxSize];
	ValueType m_value;
	UINT_32 m_count;
public:
	ResultValueArray()
	{
		m_count = 0;
	}
	~ResultValueArray()
	{
		
	}
	void Push(const ResultType& result, const ValueType& value) //注意:ValueType中最好不要有含有指针的东西,否则将出现内存泄漏
	{
		if (m_count == 0)
		{
			m_result[m_count] = result;
			m_value = value;
			++m_count;
		}
		else
		{
			if (value < m_value)
			{
				return;
			}
			else if (value == m_value)
			{
				m_result[m_count] = result;
				++m_count;
			}
			else
			{
				m_count = 0;
				m_result[m_count] = result;
				m_value = value;
				++m_count;
			}
		}
	}
	UINT_32 Count() const
	{
		return m_count;
	}
	void Clear()
	{
		m_count = 0;
	}
	const ResultType& operator [] (const UINT_32& arrayPosition) const
	{
		return m_result[arrayPosition];
	}
};
}
#endif