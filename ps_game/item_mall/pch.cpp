//https://github.com/zidane168/Shaiya-Projects
#include "pch.h"

BOOL Init() {
	_ConnectionPtr pConnect;
	char cUid[32];
	char cPwd[32];

	if (FAILED(CoInitialize(NULL))) {
		return FALSE;
	}

	HRESULT hr = pConnect.CreateInstance("ADODB.Connection");
	if (FAILED(hr)) {
		return FALSE;
	}

	Sleep(500);

	GetPrivateProfileStringA("SQL", "Uid", "", cUid, 32, ".\\db.ini");
	GetPrivateProfileStringA("SQL", "Pwd", "", cPwd, 32, ".\\db.ini");

	//LPCSTR szConnectionString = "Provider=SQLNCLI11;Server=127.0.0.1;Database=master;";
	LPCSTR szConnectionString = "Provider=SQLOLEDB;Server=127.0.0.1;Database=master;";
	pConnect->Open(szConnectionString, cUid, cPwd, adModeUnknown);

	CoUninitialize();
	return TRUE;
}

DWORD SConsoleAddCommand = 0x4F5BE0;
LPCSTR szNoticeCharName = "/ntcn";
LPCSTR szNoticeCharId = "/ntcid";
//hooks CServerApp::InitConsoleCommand
void __declspec(naked) CMDHook() {
	__asm {
		push 0x0
		push -0x1
		push 0x2 //args
		push szNoticeCharName
		push 0x45 //case
		mov ecx,esi
		call SConsoleAddCommand
		push 0x0
		push -0x1
		push 0x2 //args
		push szNoticeCharId
		push 0x46 //case
		mov ecx,esi
		call SConsoleAddCommand
		//original code
		pop esi
		retn
	}
}

DWORD dwUserRetn = 0x47D163;
//hooks CUser::PacketUserDBPoint
void __declspec(naked) UserHook() {
	__asm {
		xor ebp,ebp
		add ebx,0x5998
		mov eax,[esi+0x6]
		mov [ecx+0x5AC0],eax //point
		jmp dwUserRetn
	}
}

DWORD CClientToMgrOnRecv = 0x406960;
DWORD WINAPI MallProc(LPVOID lpUid) {
	PBYTE pPacket[96];

	__asm {
		lea eax,[pPacket+0x12]
		mov [pPacket+0x4],eax

		mov [pPacket+0x12],0x0
		mov [pPacket+0x13],0x0
		mov [pPacket+0x14],0x2
		mov [pPacket+0x15],0x1B

		mov ecx,lpUid
		mov [pPacket+0x16],ecx

		lea eax,[pPacket]
		push eax
		mov ecx,0x0
		call CClientToMgrOnRecv
	}

	return 0;
}

void MallFunc(LPVOID& lpUid) {
	CreateThread(0, 0, MallProc, lpUid, 0, 0);
}

DWORD dwMallRetn = 0x488D5F;
//hooks CUser::PacketShop
void __declspec(naked) MallHook() {
	__asm {
		pushad
		lea eax,[edi+0x582C]
		push eax //lpUid           
		call MallFunc
		add esp,0x4
		popad
		jmp dwMallRetn
	}
}

void MainFunc() {
	Init();
	Hook((LPVOID)0x409459, CMDHook, 5);
	Hook((LPVOID)0x47D151, UserHook, 18);
	Hook((LPVOID)0x48876F, MallHook, 5);
}
