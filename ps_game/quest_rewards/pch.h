#pragma once
#include <windows.h>
#include <string>

BOOL Hook(LPVOID lpAddress, LPVOID lpfn, SIZE_T dwSize);
void Init();
