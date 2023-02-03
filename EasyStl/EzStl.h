#pragma once
#include <ntifs.h>

#define POOLTAG 'ipae'

#define EZLOG(...) DbgPrintEx ( DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "[EZLOG] " __VA_ARGS__)
#define EZ_ASSERT(x) if(!(x)){ EZLOG("EZ_ASSERT at %s line: %d\r\n", __FUNCTION__, __LINE__); DbgBreakPoint();}

template <class T> void swap(T& a, T& b)
{
	T c(a); a = b; b = c;
}


// new delete 重载，用于初始化/释放全局指针变量
void* __cdecl operator new(size_t size, POOL_TYPE pool, ULONG tag = POOLTAG);
void __cdecl  operator delete(void* p, size_t);
void* __cdecl operator new[](size_t size, POOL_TYPE pool, ULONG tag = POOLTAG);
void __cdecl  operator delete[](void* p, size_t);
void __cdecl  operator delete[](void* p);

