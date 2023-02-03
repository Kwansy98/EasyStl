#include "EzStl.h"

void* __cdecl operator new(size_t size, POOL_TYPE pool, ULONG tag)
{
	void* p = ExAllocatePoolWithTag(pool, size, tag);
	return p;
}

void __cdecl operator delete(void* p, size_t)
{
	ExFreePool(p);
}

void* __cdecl operator new[](size_t size, POOL_TYPE pool, ULONG tag)
{
	void* p = ExAllocatePoolWithTag(pool, size, tag);
	return p;
}

void __cdecl operator delete[](void* p, size_t)
{
	ExFreePool(p);
}

void __cdecl operator delete[](void* p)
{
	ExFreePool(p);
}
