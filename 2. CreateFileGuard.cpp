#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>

class CreateFileGuard
{
public:
	CreateFileGuard(HANDLE handle) : hFile(handle) {}
	~CreateFileGuard()
	{
		CloseHandle(hFile);
	}
private:
	HANDLE hFile;
};

int main()
{
	LPCWSTR fname = L"test_file";
	HANDLE hFile;
	hFile = CreateFile(fname,
		GENERIC_READ|GENERIC_WRITE,
		0, 
		NULL,
		CREATE_NEW|OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to open file" << std::endl;
		return 1;
	}

	CreateFileGuard gFile(hFile);

	std::cin.ignore();
	return 0;
}
