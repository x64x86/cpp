#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <string>

class GFile
{
public:
	GFile(HANDLE handle) 
	{
		if (isValidHandle(handle))
		{
			hFile = handle;
			std::cout << "Guard init with handle: " << hFile << std::endl;
		}
		else
		{
			hFile = NULL;
		}
	}
	GFile& operator= (HANDLE handle)
	{
		if (hFile)
		{
			std::cout << "Handle closed: " << hFile << std::endl;
			CloseHandle(hFile);
		}
		if (isValidHandle(handle))
		{
			hFile = handle;
			std::cout << "New handle acquired: " << hFile << std::endl;
		}
		else
		{
			hFile = NULL;
		}
		return *this;
	}
	~GFile()
	{
		if (hFile)
		{
			std::cout << "Handle closed: " << hFile << std::endl;
			CloseHandle(hFile);
		}
	}
	bool isValidHandle(HANDLE handle)
	{
		if (handle == INVALID_HANDLE_VALUE)
		{
			std::cout << "Invalid file handle" << std::endl;
			return FALSE;
		}
		return TRUE;
	}
private:
	HANDLE hFile;
};

int main()
{
	LPCWSTR file1 = L"test_file_1";
	LPCWSTR file2 = L"test_file_2";
	HANDLE hFile1;
	hFile1 = CreateFile(file1,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	GFile gFile(hFile1);

	HANDLE hFile2;
	hFile2 = CreateFile(file2,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	gFile = hFile2;

	std::cin.ignore();
	return 0;
}
