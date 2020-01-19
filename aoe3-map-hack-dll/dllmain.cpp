#include "pch.h"

#include "../aoe3-map-hack-common/socketserver.h"
#include <Windows.h>
#include <stdio.h>
#include "hack.h"
#include <stdlib.h>
#include "dllserver.h"

using namespace std;
HMODULE dllHModule;

ServerReceiveResult onReceiveData(const char* data) {
	if (strcmp(data, "deject") == 0) {
		socketServer.socketSend(loggingCallback, "dejecting!");
		return ServerReceiveResultEnd;
	}

	if (strcmp(data, "test") == 0) {
		socketServer.socketSend(loggingCallback, "test success!");
	}

	if (strcmp(data, "fog-off") == 0) {
		toggleFogOfWar(false);
	}

	if (strcmp(data, "fog-on") == 0) {
		toggleFogOfWar(true);
	}


	return ServerReceiveResultContinue;
}

DWORD WINAPI runSocketServer(LPVOID) {
	socketServer.listenAndReceive("6666", loggingCallback, onReceiveData);
	Sleep(500);
	FreeLibraryAndExitThread(dllHModule, 0);
	return 0;
}

DWORD WINAPI initBot(LPVOID) {
	CreateThread(NULL, 0, runSocketServer, NULL, 0, NULL);
	return NULL;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	DisableThreadLibraryCalls(hModule);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		dllHModule = hModule;
		CreateThread(NULL, 0, initBot, NULL, 0, NULL);
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;

}
