#pragma once


#include <Windows.h>
#include "mainwindow.h"
#include "dllserver.h"

typedef void(cdecl* _setFogAndBlackMap)(DWORD isFog, DWORD isBlackMap);
_setFogAndBlackMap setFogAndBlackmap = (_setFogAndBlackMap)0x0098074E;


void toggleFogOfWar(bool isFog)
{
	logFromBot("set fog and blackmap %d", isFog);
	setFogAndBlackmap(isFog, isFog);
}

