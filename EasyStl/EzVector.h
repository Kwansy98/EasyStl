#pragma once

#include "EzStl.h"

//*********************************************************************************************
// 泛型变长数组
//
// 线程不安全，全局使用需加锁
//
// 默认使用分页内存
//
// 
// 全局对象只能使用指针，用重载的 new 运算符初始化，不使用时用重载的 delete 释放
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


// 默认构造函数
template <typename T>
ezvector<T>::ezvector(POOL_TYPE poolType)
{
	this->length = 0;				// 初始长度为0
	this->max_length = 0;			// 容量为0
	this->pool_type = poolType;		// 默认使用分页内存

	// 分配内存
	reserve(8);
}

// 拷贝构造函数
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

// 析构函数，释放内存
template <typename T>
ezvector<T>::~ezvector()
{
	if (this->buffer)
	{
		delete[] this->buffer;
		this->buffer = nullptr;
	}
}

// 扩容函数
template <typename T>
void ezvector<T>::reserve(size_t n)
{
	if (n > capacity())
	{
		//  申请一段足够大小的内存，并0初始化
		T* tmp = nullptr;
		while (tmp == nullptr)
		{
			tmp = new(this->pool_type) T[n];
		}

		if (size() == 0)
		{
			// 第一次分配内存
			this->buffer = tmp;
		}
		else
		{
			// 扩容场景

			// 复制旧值
			for (size_t i = 0; i < size(); i++)
			{
				tmp[i] = buffer[i];
			}

			// 释放 buffer 数组中所有元素，调用他们的析构函数，并且释放 this->buffer
			delete[] this->buffer;

			this->buffer = tmp;
		}
		this->max_length = n;
	}
}

// =赋值操作
template <typename T>
ezvector<T>& ezvector<T>::operator=(ezvector<T> other)
{
	this->length = 0;				// 初始长度为0
	this->max_length = 0;
	reserve(8);
	
	for (size_t i = 0; i < other.size(); i++)
	{
		push_back(other[i]);
	}
	return *this;
}

// 下标索引，返回引用
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

// 获取实际长度
template <typename T>
size_t ezvector<T>::size() const
{
	return this->length;
}

// 获取最大长度
template <typename T>
size_t ezvector<T>::capacity() const
{

	return this->max_length;
}

// 尾部追加元素，追加成功返回true
template <typename T>
void ezvector<T>::push_back(const T& val)
{
	// 是否需要扩容
	if (size() == capacity())
	{
		size_t new_capacity = size() == 0 ? 8 : capacity() * 2;
		reserve(new_capacity);
	}

	// 插入对象必须重载=操作符
	*(this->buffer + size()) = val;
	this->length += 1;
}

// 弹出尾部元素
template <typename T>
void ezvector<T>::pop_back()
{
	this->length -= 1;
}

// 删除指定下标的元素
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

// 清空容器
template <typename T>
void ezvector<T>::clear()
{
	ezvector<T> emptyVector(this->pool_type);
	swap(*this, emptyVector);
}

// 获取缓存
template <typename T>
T* ezvector<T>::data()
{
	return this->buffer;
}

// 判断元素是否存在
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

// 获取元素第一次出现的位置，如果不存在，返回 size_t(~0)
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

