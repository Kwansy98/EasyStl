#pragma once

#include "EzStl.h"
#include "EzVector.h"

class ezstring
{
private:
	ezvector<char> *v;

public:
	ezstring()
	{
		v = new(NonPagedPool) ezvector<char>(NonPagedPool);
		v->push_back('\0');
	}

	ezstring(const char *str)
	{
		v = new(NonPagedPool) ezvector<char>(NonPagedPool);

		size_t len = strlen(str);
		for (size_t i = 0; i < len; i++)
		{
			v->push_back(str[i]);
		}
		v->push_back('\0');
	}

	ezstring(const ezstring& rhs)
	{
		v = new(NonPagedPool) ezvector<char>(NonPagedPool);

		for (size_t i = 0; i < rhs.size(); i++)
		{
			v->push_back(rhs[i]);
		}
		v->push_back('\0');
	}

	~ezstring()
	{
		delete v;
	}

	size_t size() const
	{
		return v->size() - 1;
	}

	ezstring& operator=(const ezstring &rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		if (v!=nullptr)
		{
			delete v;
		}
		v = new(NonPagedPool) ezvector<char>(NonPagedPool);

		for (size_t i = 0; i < rhs.size(); i++)
		{
			v->push_back(rhs[i]);
		}
		v->push_back('\0');

		return *this;
	}

	const char* c_str() const
	{
		return v->data();
	}

	char& operator[](size_t index)
	{
		EZ_ASSERT(index < size() + 1);
		return (*v)[index];
	}

	const char& operator[](size_t index) const
	{
		EZ_ASSERT(index < size() + 1);
		return (*v)[index];
	}

	ezstring& operator+=(const char *str)
	{
		v->pop_back(); // 0

		size_t len = strlen(str);
		for (size_t i = 0; i < len; i++)
		{
			v->push_back(str[i]);
		}

		v->push_back('\0');

		return *this;
	}

	bool operator==(const ezstring& rhs) const
	{
		if (this->size() != rhs.size())
		{
			return false;
		}

		size_t len = size();
		for (size_t i = 0; i < len; i++)
		{
			if ((*v)[i] != rhs[i])
			{
				return false;
			}
		}
		return true;
	}

	ezstring tolower()
	{
		ezstring lower = *this;
		for (size_t i = 0; i < size(); i++)
		{
			if (lower[i] >= 'A' && lower[i] <= 'Z')
			{
				lower[i] += 0x20;
			}
		}
		return lower;
	}

	ezstring toupper()
	{
		ezstring upper = *this;
		for (size_t i = 0; i < size(); i++)
		{
			if (upper[i] >= 'a' && upper[i] <= 'z')
			{
				upper[i] -= 0x20;
			}
		}
		return upper;
	}
};

class ezwstring
{
private:
	ezvector<wchar_t> *v;

public:
	ezwstring()
	{
		v = new(NonPagedPool) ezvector<wchar_t>(NonPagedPool);
		v->push_back(L'\0');
	}

	ezwstring(const wchar_t *str)
	{
		v = new(NonPagedPool) ezvector<wchar_t>(NonPagedPool);

		size_t len = wcslen(str);
		for (size_t i = 0; i < len; i++)
		{
			v->push_back(str[i]);
		}
		v->push_back(L'\0');
	}

	ezwstring(const ezwstring& rhs)
	{
		v = new(NonPagedPool) ezvector<wchar_t>(NonPagedPool);

		for (size_t i = 0; i < rhs.size(); i++)
		{
			v->push_back(rhs[i]);
		}
		v->push_back(L'\0');
	}

	~ezwstring()
	{
		delete v;
	}

	size_t size() const
	{
		return v->size() - 1;
	}

	ezwstring& operator=(const ezwstring &rhs)
	{
		if (this == &rhs)
		{
			return *this;
		}
		if (v != nullptr)
		{
			delete v;
		}
		v = new(NonPagedPool) ezvector<wchar_t>(NonPagedPool);

		for (size_t i = 0; i < rhs.size(); i++)
		{
			v->push_back(rhs[i]);
		}
		v->push_back(L'\0');

		return *this;
	}

	const wchar_t* c_str() const
	{
		return v->data();
	}

	wchar_t& operator[](size_t index)
	{
		EZ_ASSERT(index < size() + 1);
		return (*v)[index];
	}

	const wchar_t& operator[](size_t index) const
	{
		EZ_ASSERT(index < size() + 1);
		return (*v)[index];
	}

	ezwstring& operator+=(const wchar_t *str)
	{
		v->pop_back(); // 0

		size_t len = wcslen(str);
		for (size_t i = 0; i < len; i++)
		{
			v->push_back(str[i]);
		}

		v->push_back(L'\0');

		return *this;
	}

	bool operator==(const ezwstring& rhs) const
	{
		if (this->size() != rhs.size())
		{
			return false;
		}

		size_t len = size();
		for (size_t i = 0; i < len; i++)
		{
			if ((*v)[i] != rhs[i])
			{
				return false;
			}
		}
		return true;
	}

	ezwstring tolower()
	{
		ezwstring lower = *this;
		for (size_t i = 0; i < size(); i++)
		{
			if (lower[i] >= L'A' && lower[i] <= L'Z')
			{
				lower[i] += (L'a' - L'A');
			}
		}
		return lower;
	}

	ezwstring toupper()
	{
		ezwstring upper = *this;
		for (size_t i = 0; i < size(); i++)
		{
			if (upper[i] >= L'a' && upper[i] <= L'z')
			{
				upper[i] -= (L'a' - L'A');
			}
		}
		return upper;
	}
};



