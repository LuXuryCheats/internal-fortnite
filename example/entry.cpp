#include "main.hh"

bool __stdcall DllMain(void* nigga, unsigned long niggas, void* niggahs)
{
	if (niggas == 1)
	{
		main();

		HWND game_window = FindWindow(L"UnrealWindow", L"Fortnite  ");
		auto address = Scanners::PatternScan(SteamHelper::GetSteamdModule(), ("48 89 6C 24 18 48 89 74 24 20 41 56 48 83 EC 20 41 8B E8"));
		SteamHelper::InsertHook(address, (uintptr_t)hook_present, (long long*)&present_og);
		wndproc = (WNDPROC)SetWindowLongPtr(game_window, GWLP_WNDPROC, (LONG_PTR)wndprocc);

		return TRUE;
	}
	return 1;
}