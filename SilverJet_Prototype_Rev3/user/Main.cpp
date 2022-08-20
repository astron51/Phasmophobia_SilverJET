#include <Windows.h>
#include <iostream>
#include "../RendererRJ.h"
#include "../Cheats.h"

/*
   _____ _ _                    _ ______ _______
  / ____(_) |                  | |  ____|__   __|
 | (___  _| |_   _____ _ __    | | |__     | |
  \___ \| | \ \ / / _ \ '__|   | |  __|    | |
  ____) | | |\ V /  __/ | | |__| | |____   | |
 |_____/|_|_| \_/ \___|_|  \____/|______|  |_|

 Cheat for Phasmophobia Live Branch

*/

void Run()
{
	try {
		//loguru::add_file("D:\\SilverJET.txt", loguru::Append, loguru::Verbosity_MAX);
		auto uInstCheats = std::make_unique<Cheats>();
		auto uInstRenderer = std::make_unique<RendererRJ>();
		while (true) {
			if (g_Cheats) {
				if (g_Cheats->GetKey(VK_F5, FALSE)) {
					break;
				}
			}
			Sleep(100);
		}
	}
	catch (std::exception const& ex) {
		if (MessageBoxA(nullptr, ex.what(), nullptr, MB_OK | MB_ICONEXCLAMATION)) {
			ExitProcess(0);
		}
	}
	CloseHandle(g_MainThread);
	FreeLibraryAndExitThread(g_hModule, 0);
}