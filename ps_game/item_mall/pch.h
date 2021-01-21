#pragma once
#import "msado15.dll" no_namespace rename("EOF", "adoEOF")
#include <windows.h>

BOOL Hook(LPVOID lpAddress, LPVOID lpfn, SIZE_T dwSize);
void MainFunc();
