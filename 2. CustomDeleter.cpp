#include "stdafx.h"
#include <windows.h>
#include <memory>
#include <iostream>
#include <cassert>

void close_handle(HANDLE *hptr)
{
	if (*hptr != INVALID_HANDLE_VALUE)
	{
		std::cout << "Handle closed: " << *hptr << std::endl;
		CloseHandle(*hptr);
	}
}
typedef std::unique_ptr<HANDLE, decltype(&close_handle)> Uptr;

Uptr operate_file_unique(Uptr uFile)
{
	std::cout << "Something happens to file via unique ptr: " << *uFile << std::endl;
	return std::move(uFile);
}

void operate_file_shared(std::shared_ptr<HANDLE> sFile)
{
	std::cout << "Something happens to file via shared ptr: " << *sFile << std::endl;
}

int main()
{
	LPCWSTR file1 = L"test_file1";
	LPCWSTR file2 = L"test_file2";

	HANDLE hFile;
	hFile = CreateFile(file1,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		Uptr uFile(&hFile, &close_handle);
		std::cout << "Handle aquired: " << hFile << std::endl;
		Uptr uFile2 = operate_file_unique(std::move(uFile));
		assert(!uFile);
	}

	hFile = CreateFile(file2,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile != INVALID_HANDLE_VALUE)
	{
		std::shared_ptr<HANDLE> sFile(&hFile, &close_handle);
		std::cout << "Handle aquired: " << hFile << std::endl;
		operate_file_shared(sFile);
	}

	std::cin.ignore();
	return 0;
}
