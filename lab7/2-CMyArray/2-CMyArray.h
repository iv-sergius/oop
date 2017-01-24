#pragma once

#include <new>
#include <algorithm>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;

	CMyArray(const CMyArray& arr)
	{
		const auto size = arr.GetSize();
		if (size != 0)
		{
			m_begin = RawAlloc(size);
			CopyItems(arr.m_begin, arr.m_end, m_begin, m_end);
			m_endOfCapacity = m_end;
		}
	}

	CMyArray(CMyArray && arr)
	{
		m_begin = arr.m_begin;
		m_end = arr.m_end;
		m_endOfCapacity = arr.m_endOfCapacity;
		arr.m_begin = nullptr;
		arr.m_end = nullptr;
		arr.m_endOfCapacity = nullptr;
	}

	void Append(const T & value)
	{
		if (m_end == m_endOfCapacity) // no free space
		{
			size_t newCapacity = std::max(1u, GetCapacity() * 2);

			auto newBegin = RawAlloc(newCapacity);
			T *newEnd = newBegin;
			CopyItems(m_begin, m_end, newBegin, newEnd);
			// Конструируем копию value по адресу newItemLocation
			new (newEnd)T(value);	
			++newEnd;
			DeleteItems(m_begin, m_end);

			// Переключаемся на использование нового хранилища элементов
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = m_begin + newCapacity;
		}
		else // has free space
		{
			new (m_end) T (value);
			++m_end;
		}
	}

	T & GetBack()
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	const T & GetBack()const
	{
		assert(GetSize() != 0u);
		return m_end[-1];
	}

	size_t GetSize()const
	{
		return m_end - m_begin;
	}

	size_t GetCapacity()const
	{
		return m_endOfCapacity - m_begin;
	}

	T& operator[](size_t index)
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Index out of range");
		}
		return m_begin[index];
	}

	const T& operator[](size_t index) const
	{
		if (index >= GetSize())
		{
			throw std::out_of_range("Index out of range");
		}
		return m_begin[index];
	}

	CMyArray& operator = (CMyArray && rhs)
	{
		if (std::addressof(rhs) != this)
		{
			DeleteItems(m_begin, m_end);
			m_begin = rhs.m_begin;
			m_end = rhs.m_end;
			m_endOfCapacity = rhs.m_endOfCapacity;
			rhs.m_begin = nullptr;
			rhs.m_end = nullptr;
			rhs.m_endOfCapacity = nullptr;
		}
		return *this;
	}

	CMyArray& operator = (const CMyArray & rhs)
	{
		if (std::addressof(rhs) != this)
		{
			CMyArray rhsCopy(rhs);
			DeleteItems(m_begin, m_end);

			std::swap(rhsCopy.m_begin, this->m_begin);
			std::swap(rhsCopy.m_end, this->m_end);
			std::swap(rhsCopy.m_endOfCapacity, this->m_endOfCapacity);

			return *this;
		}
	}

	void Resize(size_t newSize)
	{
		if (newSize > GetCapacity()) // need realloc
		{
			auto newBegin = RawAlloc(newSize);
			T *transitEnd = newBegin;
			CopyItems(m_begin, m_end, newBegin, transitEnd);
			T *newEnd = newBegin + newSize;
			FillDefaultItems(transitEnd, newEnd);
			// switch to new place
			DeleteItems(m_begin, m_end);
			m_begin = newBegin;
			m_end = newEnd;
			m_endOfCapacity = newEnd;
		} 
		else if (newSize >= GetSize()) // without realloc
		{
			T *newEnd = m_begin + newSize;
			FillDefaultItems(m_end, newEnd); 
			m_end = newEnd;
		}
		else if (newSize < GetSize()) // destroy excess elements
		{
			T *newEnd = m_begin + newSize;
			DestroyItems(newEnd, m_end);
			m_end = newEnd;
		}
	}

	void Clear()
	{
		DestroyItems(m_begin, m_end);
		m_end = m_begin;
	}

	~CMyArray()
	{
		DeleteItems(m_begin, m_end);
	}
private:
	static void DeleteItems(T *begin, T *end)
	{
		// Разрушаем старые элементы
		DestroyItems(begin, end);
		// Освобождаем область памяти для их хранения
		RawDealloc(begin);
	}

	// Копирует элементы из текущего вектора в to, возвращает newEnd
	static void CopyItems(const T *srcBegin, const T *srcEnd, T * dstBegin, T * & dstEnd)
	{
		try
		{
			for (dstEnd = dstBegin; srcBegin != srcEnd; ++srcBegin, ++dstEnd)
			{
				// Construct "T" at "dstEnd" as a copy of "*begin"
				new (dstEnd)T(*srcBegin);
			}
		}
		catch (...)
		{
			DeleteItems(dstBegin, dstEnd);
			throw;
		}
	}

	static void FillDefaultItems(T *from, T *to)
	{
		T *copyItemPtr;
		try 
		{
			for (copyItemPtr = from; copyItemPtr < to; ++copyItemPtr) //or   from != to 
			{
				new (copyItemPtr)T(); // безопасен ли констуктор по умолчанию к исключениям??
			}
		}
		catch (...)
		{
			DeleteItems(from, copyItemPtr);
			throw;
		}
	}

	static void DestroyItems(T *from, T *to)
	{
		// from - адрес объекта, при конструирование которого было выброшено исключение
		// to - первый скорнструированный объект
		while (to != from)
		{
			--to;
			// явно вызываем деструктор для шаблонного типа T
			to->~T();
		}
	}

	static T *RawAlloc(size_t n)
	{
		size_t memSize = n * sizeof(T);
		T *p = static_cast<T*>(malloc(memSize));
		if (!p)
		{
			throw std::bad_alloc();
		}
		return p;
	}

	static void RawDealloc(T *p)
	{
		free(p);
	}

	//<template T>
	//class 

private:
	T *m_begin = nullptr;
	T *m_end = nullptr;
	T *m_endOfCapacity = nullptr;
};