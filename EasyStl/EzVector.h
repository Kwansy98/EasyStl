#pragma once

#include "EzStl.h"

//*********************************************************************************************
// ���ͱ䳤����
//
// �̲߳���ȫ��ȫ��ʹ�������
//
// Ĭ��ʹ�÷�ҳ�ڴ�
//
// 
// ȫ�ֶ���ֻ��ʹ��ָ�룬�����ص� new �������ʼ������ʹ��ʱ�����ص� delete �ͷ�
//
// 
//*********************************************************************************************

template <typename T>
class ezvector
{
private:
	T* buffer;
	size_t length;
	size_t max_length;
	POOL_TYPE pool_type;

public:
	ezvector(POOL_TYPE poolType = PagedPool);
	ezvector(const ezvector<T>& other);
	~ezvector();
	//ezvector& operator=(const ezvector& other);
	ezvector& operator=(ezvector other);
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	size_t size() const;
	size_t capacity() const;
	void push_back(const T& val);
	void pop_back();
	void reserve(size_t n);
	void erase(size_t index);
	void clear();
	T* data();
	bool exist(const T& val);
	size_t find_first(const T& val);
};


// Ĭ�Ϲ��캯��
template <typename T>
ezvector<T>::ezvector(POOL_TYPE poolType)
{
	this->length = 0;				// ��ʼ����Ϊ0
	this->max_length = 0;			// ����Ϊ0
	this->pool_type = poolType;		// Ĭ��ʹ�÷�ҳ�ڴ�

	// �����ڴ�
	reserve(8);
}

// �������캯��
template <typename T>
ezvector<T>::ezvector(const ezvector<T>& other)
{
	this->length = 0;
	this->max_length = 0;
	this->buffer = nullptr;
	this->pool_type = other.pool_type;

	reserve(other.capacity());
	for (size_t i = 0; i < other.size(); i++)
	{
		push_back(other[i]);
	}
}

// �����������ͷ��ڴ�
template <typename T>
ezvector<T>::~ezvector()
{
	if (this->buffer)
	{
		delete[] this->buffer;
		this->buffer = nullptr;
	}
}

// ���ݺ���
template <typename T>
void ezvector<T>::reserve(size_t n)
{
	if (n > capacity())
	{
		//  ����һ���㹻��С���ڴ棬��0��ʼ��
		T* tmp = nullptr;
		while (tmp == nullptr)
		{
			tmp = new(this->pool_type) T[n];
		}

		if (size() == 0)
		{
			// ��һ�η����ڴ�
			this->buffer = tmp;
		}
		else
		{
			// ���ݳ���

			// ���ƾ�ֵ
			for (size_t i = 0; i < size(); i++)
			{
				tmp[i] = buffer[i];
			}

			// �ͷ� buffer ����������Ԫ�أ��������ǵ����������������ͷ� this->buffer
			delete[] this->buffer;

			this->buffer = tmp;
		}
		this->max_length = n;
	}
}

// =��ֵ����
template <typename T>
ezvector<T>& ezvector<T>::operator=(ezvector<T> other)
{
	this->length = 0;				// ��ʼ����Ϊ0
	this->max_length = 0;
	reserve(8);
	
	for (size_t i = 0; i < other.size(); i++)
	{
		push_back(other[i]);
	}
	return *this;
}

// �±���������������
template <typename T>
T& ezvector<T>::operator[](size_t index)
{
	EZ_ASSERT(index < size());
	return *(this->buffer + index);
}

template <typename T>
const T& ezvector<T>::operator[](size_t index) const
{
	EZ_ASSERT(index < size());
	return *(this->buffer + index);
}

// ��ȡʵ�ʳ���
template <typename T>
size_t ezvector<T>::size() const
{
	return this->length;
}

// ��ȡ��󳤶�
template <typename T>
size_t ezvector<T>::capacity() const
{

	return this->max_length;
}

// β��׷��Ԫ�أ�׷�ӳɹ�����true
template <typename T>
void ezvector<T>::push_back(const T& val)
{
	// �Ƿ���Ҫ����
	if (size() == capacity())
	{
		size_t new_capacity = size() == 0 ? 8 : capacity() * 2;
		reserve(new_capacity);
	}

	// ��������������=������
	*(this->buffer + size()) = val;
	this->length += 1;
}

// ����β��Ԫ��
template <typename T>
void ezvector<T>::pop_back()
{
	this->length -= 1;
}

// ɾ��ָ���±��Ԫ��
template <typename T>
void ezvector<T>::erase(size_t index)
{
	EZ_ASSERT(index < size());

	for (size_t i = index; i < size() - 1; i++)
	{
		buffer[i] = buffer[i + 1];
	}

	this->length -= 1;
}

// �������
template <typename T>
void ezvector<T>::clear()
{
	ezvector<T> emptyVector(this->pool_type);
	swap(*this, emptyVector);
}

// ��ȡ����
template <typename T>
T* ezvector<T>::data()
{
	return this->buffer;
}

// �ж�Ԫ���Ƿ����
template <typename T>
bool ezvector<T>::exist(const T& val)
{
	for (size_t i = 0; i < size(); i++)
	{
		if (buffer[i] == val)
		{
			return true;
		}
	}
	return false;
}

// ��ȡԪ�ص�һ�γ��ֵ�λ�ã���������ڣ����� size_t(~0)
template <typename T>
size_t ezvector<T>::find_first(const T& val)
{
	for (size_t i = 0; i < size(); i++)
	{
		if (buffer[i] == val)
		{
			return i;
		}
	}
	return size_t(~0);
}

