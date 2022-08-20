#pragma once
#include <SDKDDKVer.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <thread>
#include <time.h>
#include <ctime>
#include <Psapi.h>
#include <string>
#include <locale>
#include <sstream>
#include <iomanip>
#include <codecvt>
#include <optional>
#include <list>
#include <DirectXMath.h>
#include <commdlg.h>
#include "D3D_VMT.h" // DX11 Index
#include "MoonMan.h" // Font Data
#include "Crypt.h"
#include "loguru.hpp"

// RapidJSON
#include <..\rapidjson\document.h>
#include <..\rapidjson\stringbuffer.h>
#include <..\rapidjson\filewritestream.h>
#include <..\rapidjson\filereadstream.h>
#include <..\rapidjson\writer.h>

using namespace rapidjson;

//MinHook Imports
#include <MinHook.h>
#if defined _M_X64
#pragma comment(lib, "libMinHook.x64.lib")
#elif defined _M_IX86
#pragma comment(lib, "libMinHook.lib")
#endif

//Detours
#include "detours.h"
#pragma comment(lib, "detours.lib")

//DirectX 11 Imports
#include <d3d11.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "D3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")

//ImGui Imports
#include <imgui.h>
#include <misc/freetype/imgui_freetype.h>
#include <imgui_internal.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#pragma comment (lib, "ImGui.lib")

//ImPlot Imports
#include <implot.h>
#include <implot_internal.h>
#pragma comment (lib, "ImPlot.lib")

using namespace std;
using namespace DirectX;

//Defining type in upper class ( Lazy to shift it )
typedef HRESULT(__fastcall* tIDXGISwapChainPresent)(IDXGISwapChain*, UINT, UINT);

HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain*, ID3D11Device**, ID3D11DeviceContext**);
HRESULT RetrieveFromModule(tIDXGISwapChainPresent);
LRESULT CALLBACK dWndProc(HWND, UINT, WPARAM, LPARAM);
tIDXGISwapChainPresent CreateDummy();
BOOL bCompare(const BYTE*, const BYTE*, const char*);
uintptr_t FindPattern(uintptr_t, DWORD, BYTE*, char*);
std::vector<uintptr_t> FindPatternVector(uintptr_t, int32_t, DWORD, BYTE*, char*);

inline HMODULE g_hModule{};
inline HANDLE g_MainThread{};

// Support Class
struct PHMAddress {
	DWORD dwCamera_get_main = 0x0;
	DWORD dwCursor_set_lockState = 0x0;
	DWORD dwLight_set_intensity = 0x0;
	DWORD dwLight_set_spotAngle = 0x0;
	DWORD dwPhotonView_RPC = 0x0;
	DWORD dwMission_Completed = 0x0;
	DWORD dwCursor_get_visible = 0x0;
	DWORD dwMarshal_PtrToStringAnsi = 0x0;
	DWORD dwLineRenderer_GetPosition = 0x0;
	DWORD dwCamera_WorldToScreenPoint_1 = 0x0;
	DWORD dwTransform_get_position = 0x0;
	DWORD dwComponent_1_get_transform = 0x0;
	DWORD dwGhostAI_StartGhost = 0x0;
	DWORD dwGhostAI_Hunting = 0x0;
	DWORD dwGhostAI_Update = 0x0;
	DWORD dwGhostAI_ChangeState = 0x0;
	DWORD dwExitLevel_Exit = 0x0;
	DWORD dwGameController_Exit = 0x0;
	DWORD dwPauseMenuController_Leave = 0x0;
	DWORD dwEMFData_Update = 0x0;
	DWORD dwMissionManager_Start = 0x0;
	DWORD dwEvidenceController_Start = 0x0;
	DWORD dwLevelController_Start = 0x0;
};

inline PHMAddress PH_Pools;

#include "il2cpp_translations.h"
#include "Phasmophobia.h"
#include "il2cpp-types.h"