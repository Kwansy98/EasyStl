# EasyStl
vector and string windows kernel implement

```C
#include <ntifs.h>
#include "EzVector.h"
#include "EzString.h"

VOID Unload(PDRIVER_OBJECT pDriver)
{
	UNREFERENCED_PARAMETER(pDriver);
}

EXTERN_C NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING pReg)
{
	UNREFERENCED_PARAMETER(pReg);
	pDriver->DriverUnload = Unload;

	ezvector<ezwstring> v;
	v.push_back(L"This");
	v.push_back(L"Is");
	v.push_back(L"The");
	v.push_back(L"Bug");
	v.push_back(L"Not");
	v.push_back(L"Feature");
	v.push_back(L".");

	if (v.exist(L"The"))
	{
		size_t index = v.find_first(L"The");
		v.erase(index);
	}

	v[v.size() - 1] = L"!";

	// print "THIS IS BUG NOT FEATURE ! "
	for (size_t i = 0; i < v.size(); i++)
	{
		ezwstring s = v[i].toupper();
		s += L" ";
		DbgPrintEx(77, 0, "%S", s.c_str());
	}

	return STATUS_SUCCESS;
}
```