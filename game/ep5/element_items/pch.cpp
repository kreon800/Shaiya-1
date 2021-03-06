#include "pch.h"

BOOL isElementalGem(ULONG_PTR& pVector) {
	auto itFire = std::find(std::begin(vFireGems), std::end(vFireGems), pVector);
	if (itFire != std::end(vFireGems)) {
		return FIRE;
	}
	auto itWater = std::find(std::begin(vWaterGems), std::end(vWaterGems), pVector);
	if (itWater != std::end(vWaterGems)) {
		return WATER;
	}
	auto itEarth = std::find(std::begin(vEarthGems), std::end(vEarthGems), pVector);
	if (itEarth != std::end(vEarthGems)) {
		return EARTH;
	}
	auto itWind = std::find(std::begin(vWindGems), std::end(vWindGems), pVector);
	if (itWind != std::end(vWindGems)) {
		return WIND;
	}
	return FALSE;
}

BOOL isElementalItem(ULONG_PTR& pArray) {
	auto itFire = std::find(std::begin(aFireItems), std::end(aFireItems), pArray);
	if (itFire != std::end(aFireItems)) {
		return FIRE;
	}
	auto itWater = std::find(std::begin(aWaterItems), std::end(aWaterItems), pArray);
	if (itWater != std::end(aWaterItems)) {
		return WATER;
	}
	auto itEarth = std::find(std::begin(aEarthItems), std::end(aEarthItems), pArray);
	if (itEarth != std::end(aEarthItems)) {
		return EARTH;
	}
	auto itWind = std::find(std::begin(aWindItems), std::end(aWindItems), pArray);
	if (itWind != std::end(aWindItems)) {
		return WIND;
	}
	return FALSE;
}

void __declspec(naked) BagHook() {
	__asm {
		pushad
		//first slot
		lea edx,[eax+0x8666E2]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind
		
		//second slot
		lea edx,[eax+0x8666E3]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//third slot
		lea edx,[eax+0x8666E4]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fourth slot
		lea edx,[eax+0x8666E5]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fifth slot
		lea edx,[eax+0x8666E6]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//sixth slot
		lea edx,[eax+0x8666E7]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

    	//ecx = types 
		//edx = typeids
		movzx ecx,byte ptr[eax+0x8666DD]
		imul ecx,0x3E8
		movzx edx,byte ptr[eax+0x8666DE]
		add ecx,edx
		//save itemids
		mov[eax+aBagItems],ecx
		//ebx = pArray
		lea ebx,[eax+aBagItems]
		push ebx
		call isElementalItem
		add esp,0x4
		mov ebx,eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		popad
		//original code
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		jmp dwBagRetn

		_fire:
		popad
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		lea ebp,dword ptr ds:[edi+0x2C]
		push edx
		mov edx,dword ptr ss:[esp+0x20]
		push ebx
		push esi
		push eax
		push edx
		push ecx
		mov ecx,ebp
		call dwIconPos
	  	mov ecx,dword ptr ss:[esp+0x10]
		mov esi,dword ptr ss:[esp+0x14]
		push 0x20
		push 0x20
		push ecx
		push esi
		push 0x50FF0000
		call dwOverlay
		add esp,0x14
		jmp dwBagJump

		_water:
		popad
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		lea ebp,dword ptr ds:[edi+0x2C]
		push edx
		mov edx,dword ptr ss:[esp+0x20]
		push ebx
		push esi
		push eax
		push edx
		push ecx
		mov ecx,ebp
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x10]
		mov esi,dword ptr ss:[esp+0x14]
		push 0x20
		push 0x20
		push ecx
		push esi
		push 0x5000FFFF
		call dwOverlay
		add esp,0x14
		jmp dwBagJump

		_earth:
		popad
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		lea ebp,dword ptr ds:[edi+0x2C]
		push edx
		mov edx,dword ptr ss:[esp+0x20]
		push ebx
		push esi
		push eax
		push edx
		push ecx
		mov ecx,ebp
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x10]
		mov esi,dword ptr ss:[esp+0x14]
		push 0x20
		push 0x20
		push ecx
		push esi
		push 0x5000FF00
		call dwOverlay
		add esp,0x14
		jmp dwBagJump

		_wind:
		popad
		mov eax,dword ptr ss:[esp+0x10]
		push 0x1
		push 0x0
		lea ebp,dword ptr ds:[edi+0x2C]
		push edx
		mov edx,dword ptr ss:[esp+0x20]
		push ebx
		push esi
		push eax
		push edx
		push ecx
		mov ecx,ebp
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x10]
		mov esi,dword ptr ss:[esp+0x14]
		push 0x20
		push 0x20
		push ecx
		push esi
		push 0x50FFFFFF
		call dwOverlay
		add esp,0x14
		jmp dwBagJump
	}
}

void __declspec(naked) BarHook() {
	__asm {
		pushad
		//first slot
		lea edx,[esi+0x8666E2]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//second slot
		lea edx,[esi+0x8666E3]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//third slot
		lea edx,[esi+0x8666E4]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fourth slot
		lea edx,[esi+0x8666E5]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//fifth slot
		lea edx,[esi+0x8666E6]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//sixth slot
		lea edx,[esi+0x8666E7]
		push eax
		push edx
		call isElementalGem
		add esp,0x4
		mov ebx,eax
		pop eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		//ecx = types 
		//edx = typeids
		movzx ecx,byte ptr[esi+0x8666DD]
		imul ecx,0x3E8
		movzx edx,byte ptr[esi+0x8666DE]
		add ecx,edx
		//save itemids
		mov[esi+aBarItems],ecx
		//ebx = pArray
		lea ebx,[esi+aBarItems]
		push ebx
		call isElementalItem
		add esp,0x4
		mov ebx,eax
		cmp ebx,0x1
		je _fire
		cmp ebx,0x2
		je _water
		cmp ebx,0x3
		je _earth
		cmp ebx,0x4
		je _wind

		popad
		//original code
		push 0x0
		push edx
		push ebx
		push edi
		jmp dwBarRetn

		_fire:
		popad
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ecx
		mov ecx,dword ptr ss:[esp+0x2C]
		push -0x1
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x18]
		mov eax,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push ecx
		push eax
		push 0x50FF0000
		call dwOverlay
		add esp,0x14
		jmp dwBarJump

		_water:
		popad
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ecx
		mov ecx,dword ptr ss:[esp+0x2C]
		push -0x1
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x18]
		mov eax,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push ecx
		push eax
		push 0x5000FFFF
		call dwOverlay
		add esp,0x14
		jmp dwBarJump

		_earth:
		popad
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ecx
		mov ecx,dword ptr ss:[esp+0x2C]
		push -0x1
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x18]
		mov eax,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push ecx
		push eax
		push 0x5000FF00
		call dwOverlay
		add esp,0x14
		jmp dwBarJump

		_wind:
		popad
		push 0x0
		push edx
		push ebx
		push edi
		push eax
		push ecx
		mov ecx,dword ptr ss:[esp+0x2C]
		push -0x1
		call dwIconPos
		mov ecx,dword ptr ss:[esp+0x18]
		mov eax,dword ptr ss:[esp+0x1C]
		push 0x20
		push 0x20
		push ecx
		push eax
		push 0x50FFFFFF
		call dwOverlay
		add esp,0x14
		jmp dwBarJump
	}
}

void Init() {
	Hook((LPVOID)0x4F6896, BagHook, 6);
	Hook((LPVOID)0x4E0395, BarHook, 5);
}
