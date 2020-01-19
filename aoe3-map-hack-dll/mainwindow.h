#include <Windows.h>

HWND mainWindow = NULL;
HDC deviceContext = NULL;

BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		mainWindow = hwnd;
		deviceContext = GetDC(mainWindow);
		return FALSE;
	}
	return TRUE;
}

// use to find HWND and HDC for main window and device context
void updateMainWindow() {
	EnumWindows(enumWindowsProc, GetCurrentProcessId());
}