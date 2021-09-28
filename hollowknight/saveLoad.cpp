#include "stdafx.h"
#include "saveLoad.h"

void saveLoad::update()
{
}

void saveLoad::save(int hp, int geo)
{
	HANDLE file;
	DWORD write;

	char str[128] = "";

	file = CreateFile("save file.txt", GENERIC_WRITE, FALSE,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);
}

void saveLoad::load()
{
	HANDLE file;
	DWORD read;

	char str[128];

	file = CreateFile("save file.txt", GENERIC_READ, FALSE,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);
}
