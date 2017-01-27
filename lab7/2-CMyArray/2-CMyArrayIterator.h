#pragma once

#include "2-CMyArray.h"

template<typename T>
class CMyArrayIterator : public std::iterator<std::input_iterator_tag, T>
{
	template <typename T> friend class CMyArray;

public:
	CMyArrayIterator() = delete;
	CMyArrayIterator(const CMyArrayIterator &it) = default;
	bool operator == (const CMyArrayIterator & rhs) const;
	bool operator != (const CMyArrayIterator & rhs) const;
	CMyArrayIterator<T> & operator ++();
	CMyArrayIterator<T> const operator ++(int);
	T operator *() const;
	T* operator ->() const;
protected:
	explicit CMyArrayIterator(T * ptr, T * beginPtr, T * endPtr)
		: m_ptr(ptr)
		, m_beginPtr(beginPtr)
		, m_endPtr(endPtr)
	{
		if (m_beginPtr < m_endPtr)
		{
			m_step = 1;
		} 
		else if (m_beginPtr > m_endPtr)
		{
			m_step = -1;
		}
		else
		{
			m_step = 0;
		}
	}
private:
	T * m_ptr;
	T * m_beginPtr;
	T * m_endPtr;
	int m_step;
};

template<typename T>
inline bool CMyArrayIterator<T>::operator==(const CMyArrayIterator & rhs) const
{
	return m_ptr == rhs.m_ptr;
}

template<typename T>
inline bool CMyArrayIterator<T>::operator!=(const CMyArrayIterator & rhs) const
{
	return m_ptr != rhs.m_ptr;
}

template<typename T>
inline CMyArrayIterator<T>& CMyArrayIterator<T>::operator++()
{
	assert(m_ptr != m_endPtr);
	m_ptr += m_step;
	return *this;
}

template<typename T>
inline CMyArrayIterator<T> const CMyArrayIterator<T>::operator++(int)
{
//	assert(m_ptr != m_endPtr);
	auto tmpCopy(*this);
	++*this;
	return tmpCopy;
}

template<typename T>
inline T CMyArrayIterator<T>::operator*() const
{
	assert((m_beginPtr < m_endPtr && m_beginPtr <= m_ptr && m_ptr < m_endPtr)
		|| (m_beginPtr > m_endPtr && m_beginPtr >= m_ptr && m_ptr > m_endPtr));
	return *m_ptr;
}

template<typename T>
inline T * CMyArrayIterator<T>::operator->() const
{
	assert((m_beginPtr < m_endPtr && m_beginPtr <= m_ptr && m_ptr < m_endPtr)
		|| (m_beginPtr > m_endPtr && m_beginPtr >= m_ptr && m_ptr > m_endPtr));
	return m_ptr;
}
