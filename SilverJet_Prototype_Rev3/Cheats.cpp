#include "RendererRJ.h"
#include "Cheats.h"

#define DO_API(r, n, p) r (*n) p
#include "il2cpp-api-functions.h"
#undef DO_API

#include "il2cpp-helpers.h"

#define DO_APP_FUNC(r, n, p, s) r (*n) p
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

String* odUnityFunction::CreateNETStringFromANSI(const char* string)
{
	return Marshal_PtrToStringAnsi((void*)string, NULL);
}

std::string odUnityFunction::GetUTF8StringFromNETString(String* netString)
{
	if (netString == NULL)
		return NULL;

	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10FFFF,
		std::codecvt_mode::little_endian>, char16_t> UTF16_TO_UTF8;

	uint16_t* buffer = new uint16_t[netString->Fields.Length + 1];
	memcpy(buffer, &netString->Fields.m_firstChar, netString->Fields.Length * sizeof(uint16_t));
	buffer[netString->Fields.Length] = L'\0';
	std::string newString = UTF16_TO_UTF8.to_bytes((const char16_t*)buffer);

	delete[] buffer;

	return newString;
}

void odUnityFunction::hksMissionComplete(Mission* _this) {
	__try {
		auto ClassName = _this->klass->ClassName;
		if (0 == _stricmp(ClassName, "MissionGhostEvent")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedGhostEventMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionCapturePhoto")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedCapturePhotoMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionCrucifix")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedCrucifixMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionBurnSage")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedBurnSageMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionMotionSensor")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedMotionMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionEMFEvidence")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedEMFMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionSalt")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedSaltMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionAverageSanity")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedAverageSanityMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionCandle")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedCandleMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionEscapeGhost")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedEscapeGhostMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionHuntSmudge")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedMissionHuntSmudgeMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else if (0 == _stricmp(ClassName, "MissionParabolic")) {
			return PhotonView_RPC(_this->Fields.View, odUnityFunction::CreateNETStringFromANSI("CompletedParabolicMissionSync"), ERPCTarget::RpcTarget__Enum_AllBuffered, NULL, NULL);
		}
		else {
			LogInstance.AddLog("Class Mismatch : %p\n", ClassName);
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		LogInstance.AddLog("Backend MC : %p\n", GetExceptionCode());
	}
}

void odUnityFunction::hkGhostAI_StartGhost(GhostAI* thisAI, void* thisInfo) {
	g_Cheats->oGhostAI_StartGhost(thisAI, thisInfo);
	g_Cheats->thisGhost = thisAI;
	LogInstance.AddLog("GhostAI : %p\n", thisAI);
	g_Cheats->bSafeToRun = true;
}

void odUnityFunction::hkGhostAI_Hunting(GhostAI* thisAI, bool isHunting, void* PhotonMsg, void* thisInfo) {
	g_Cheats->oGhostAI_Hunting(thisAI, isHunting, PhotonMsg, thisInfo);
	g_Cheats->bHunting = isHunting;
}

void odUnityFunction::hkGhostAI_Update(GhostAI* thisAI, void* thisInfo) {
	g_Cheats->oGhostAI_Update(thisAI, thisInfo);
	g_Cheats->thisGhost = thisAI;
}

void odUnityFunction::hkExitLevel_Exit(void* thisExit, void* thisInfo) {
	g_Cheats->oExitLevel_Exit(thisExit, thisInfo);
	g_Cheats->CleanUp();
}

void odUnityFunction::hkGameController_Exit(void* thisController, void* thisInfo) {
	g_Cheats->oGameController_Exit(thisController, thisInfo);
	g_Cheats->CleanUp();
}

void odUnityFunction::hkPauseMenuController_Leave(void* thisController, void* thisInfo) {
	g_Cheats->oPauseMenuController_Leave(thisController, thisInfo);
	g_Cheats->CleanUp();
}

void odUnityFunction::hkEMFData_Start(EMFData* _this, void* Method) {
	g_Cheats->oEMFData_Start(_this, Method);
	g_Cheats->thisEMF = _this;
}

void odUnityFunction::hkMissionManager_Start(MissionManager* _this, void* Method) {
	g_Cheats->oMissionManager_Start(_this, Method);
	g_Cheats->thisMission = _this;
}

void odUnityFunction::hkEvidenceController_Start(EvidenceController* _this, void* Method) {
	g_Cheats->oEvidenceController_Start(_this, Method);
	g_Cheats->thisEvidence = _this;
	LogInstance.AddLog("EvidenceController : %p\n", _this);
}

void odUnityFunction::hkLevelController_Start(LevelController* _this, void* Method) {
	g_Cheats->oLevelController_Start(_this, Method);
	g_Cheats->thisLevel = _this;
	LogInstance.AddLog("LevelController : %p\n", _this);
}

Cheats::Cheats() {
	g_Cheats = this;
	HMODULE moduleHandle = GetModuleHandleW(L"GameAssembly.dll");
#define DO_API(r, n, p) n = (r (*) p)(GetProcAddress(moduleHandle, #n))
#include "il2cpp-api-functions.h"
#undef DO_API

#define DO_APP_FUNC(r, n, p, s) n = reinterpret_cast<decltype(n)>(get_method(s))
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

	LogInstance.AddLog(_c("StartGhost : %p\n"), GhostAI_StartGhost);
	LogInstance.AddLog(_c("Hunting : %p\n"), GhostAI_Hunting);
	LogInstance.AddLog(_c("Update : %p\n"), GhostAI_Update);
	LogInstance.AddLog(_c("ExitLevel_Exit : %p\n"), ExitLevel_Exit);
	LogInstance.AddLog(_c("GameController_Exit : %p\n"), GameController_Exit);
	LogInstance.AddLog(_c("PauseMenuController_Leave : %p\n"), PauseMenuController_Leave);
	LogInstance.AddLog(_c("EMFData_Start : %p\n"), EMFData_Start);
	LogInstance.AddLog(_c("MissionManager_Start : %p\n"), MissionManager_Start);
	LogInstance.AddLog(_c("EvidenceController_Start : %p\n"), EvidenceController_Start);
	LogInstance.AddLog(_c("LevelController_Start : %p\n"), LevelController_Start);
	LogInstance.AddLog(_c("PhotonView_RPC : %p\n"), PhotonView_RPC);
	LogInstance.AddLog(_c("Marshal_PtrToStringAnsi : %p\n"), Marshal_PtrToStringAnsi);

	thisGhost = nullptr;
	thisEMF = nullptr;
	thisEvidence = nullptr;
	thisMission = nullptr;
	thisLevel = nullptr;
	PhraseRecognized = odUnityFunction::CreateNETStringFromANSI(_c("Disabled"));
	oGhostAI_StartGhost = (void(*)(GhostAI*, void*))(GhostAI_StartGhost);
	oGhostAI_Hunting = (void(*)(GhostAI*, bool, void*, void*))(GhostAI_Hunting);
	oGhostAI_Update = (void(*)(GhostAI*, void*))(GhostAI_Update);
	oExitLevel_Exit = (void(*)(void*, void*))(ExitLevel_Exit);
	oGameController_Exit = (void(*)(void*, void*))(GameController_Exit);
	oPauseMenuController_Leave = (void(*)(void*, void*))(PauseMenuController_Leave);
	oEMFData_Start = (void(*)(EMFData*, void*))(EMFData_Start);
	oMissionManager_Start = (void(*)(MissionManager*, void*))(MissionManager_Start);
	oEvidenceController_Start = (void(*)(EvidenceController*, void*))(EvidenceController_Start);
	oLevelController_Start = (void(*)(LevelController*, void*))(LevelController_Start);

	if (MH_CreateHook((DWORD_PTR*)oGhostAI_StartGhost, &odUnityFunction::hkGhostAI_StartGhost, reinterpret_cast<LPVOID*>(&(PVOID&)oGhostAI_StartGhost)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for GhostAI_StartGhost\n"));
	}
	else {
		LogInstance.AddLog(_c("GhostAI_StartGhost : %p\n"), (DWORD_PTR*)oGhostAI_StartGhost);
	}
	if (MH_CreateHook((DWORD_PTR*)oGhostAI_Hunting, &odUnityFunction::hkGhostAI_Hunting, reinterpret_cast<LPVOID*>(&(PVOID&)oGhostAI_Hunting)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for GhostAI_Hunting\n"));
	}
	else {
		LogInstance.AddLog(_c("GhostAI_Hunting : %p\n"), (DWORD_PTR*)oGhostAI_Hunting);
	}
	if (MH_CreateHook((DWORD_PTR*)oGhostAI_Update, &odUnityFunction::hkGhostAI_Update, reinterpret_cast<LPVOID*>(&(PVOID&)oGhostAI_Update)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for GhostAI_Update\n"));
	}
	else {
		LogInstance.AddLog(_c("GhostAI_Update : %p\n"), (DWORD_PTR*)oGhostAI_Update);
	}
	if (MH_CreateHook((DWORD_PTR*)oExitLevel_Exit, &odUnityFunction::hkExitLevel_Exit, reinterpret_cast<LPVOID*>(&(PVOID&)oExitLevel_Exit)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for ExitLevel_Exit\n"));
	}
	else {
		LogInstance.AddLog(_c("ExitLevel_Exit : %p\n"), (DWORD_PTR*)oExitLevel_Exit);
	}
	if (MH_CreateHook((DWORD_PTR*)oGameController_Exit, &odUnityFunction::hkGameController_Exit, reinterpret_cast<LPVOID*>(&(PVOID&)oGameController_Exit)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for GameController_Exit\n"));
	}
	else {
		LogInstance.AddLog(_c("GameController_Exit : %p\n"), (DWORD_PTR*)oGameController_Exit);
	}
	if (MH_CreateHook((DWORD_PTR*)oPauseMenuController_Leave, &odUnityFunction::hkPauseMenuController_Leave, reinterpret_cast<LPVOID*>(&(PVOID&)oPauseMenuController_Leave)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for PauseMenuController_Leave\n"));
	}
	else {
		LogInstance.AddLog(_c("PauseMenuController_Leave : %p\n"), (DWORD_PTR*)oPauseMenuController_Leave);
	}
	if (MH_CreateHook((DWORD_PTR*)oEMFData_Start, &odUnityFunction::hkEMFData_Start, reinterpret_cast<LPVOID*>(&(PVOID&)oEMFData_Start)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for EMFData_Start\n"));
	}
	else {
		LogInstance.AddLog(_c("EMFData_Start : %p\n"), (DWORD_PTR*)oEMFData_Start);
	}
	if (MH_CreateHook((DWORD_PTR*)oMissionManager_Start, &odUnityFunction::hkMissionManager_Start, reinterpret_cast<LPVOID*>(&(PVOID&)oMissionManager_Start)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for MissionManager_Start\n"));
	}
	else {
		LogInstance.AddLog(_c("MissionManager_Start : %p\n"), (DWORD_PTR*)oMissionManager_Start);
	}
	if (MH_CreateHook((DWORD_PTR*)oEvidenceController_Start, &odUnityFunction::hkEvidenceController_Start, reinterpret_cast<LPVOID*>(&(PVOID&)oEvidenceController_Start)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for EvidenceController_Start\n"));
	}
	else {
		LogInstance.AddLog(_c("EvidenceController_Start : %p\n"), (DWORD_PTR*)oEvidenceController_Start);
	}
	if (MH_CreateHook((DWORD_PTR*)oLevelController_Start, &odUnityFunction::hkLevelController_Start, reinterpret_cast<LPVOID*>(&(PVOID&)oLevelController_Start)) != MH_OK) {
		LogInstance.AddLog(_c("Hook Failure for LevelController_Start\n"));
	}
	else {
		LogInstance.AddLog(_c("LevelController_Start : %p\n"), (DWORD_PTR*)oLevelController_Start);
	}
	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		if (MessageBoxA(NULL, _c("Error while trying to enable hook"), _c("Critical Error"), MB_ICONERROR)) {
			ExitProcess(0);
		}
	}
	LOG_F(INFO, "Cheat Instance %p", this);
}

void Cheats::CheatThread() {
	// Extra Thread, this run with DirectX Hook
	__try {
		if (g_Cheats->bSafeToRun) {
			if (g_Cheats->bShowActivityGraph) {
				ActivityGraphs.clear();
				if (thisEMF) {
					void* lrActivityGraph = thisEMF->Fields.rend;
					if (lrActivityGraph) {
						for (int i = 0; i < 60; i++) {
							Vector3 pos = LineRenderer_GetPosition(lrActivityGraph, i, NULL);
							ActivityGraphs.push_back(pos.y / 50);
						}
					}
				}
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {

	}
}

bool Cheats::OpenMeta(char* filter, HWND owner)
{
	OPENFILENAME ofn;
	char fileName[MAX_PATH] = "";
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = owner;
	ofn.lpstrFilter = filter;
	ofn.lpstrFile = fileName;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = "";
	string fileNameStr;
	if (GetOpenFileName(&ofn))
		fileNameStr = fileName;

	string allFile;

	ifstream file(fileNameStr);
	copy(istream_iterator<char>{ file >> noskipws }, {}, back_inserter(allFile));
	file.close();

	Document d;
	d.Parse(allFile.c_str());
	for (Value::ConstValueIterator itr = d["addressMap"]["methodDefinitions"].Begin(); itr != d["addressMap"]["methodDefinitions"].End(); ++itr) {
		auto curMethod = itr->FindMember("name")->value.GetString();
		auto curvAddr = std::string(itr->FindMember("virtualAddress")->value.GetString());
		if (std::strcmp(curMethod, "Camera_get_main") == 0) {
			PH_Pools.dwCamera_get_main = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Cursor_set_lockState") == 0) {
			PH_Pools.dwCursor_set_lockState = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Light_set_intensity") == 0) {
			PH_Pools.dwLight_set_intensity = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Light_set_spotAngle") == 0) {
			PH_Pools.dwLight_set_spotAngle = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "PhotonView_RPC") == 0) {
			PH_Pools.dwPhotonView_RPC = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Mission_Completed") == 0) {
			PH_Pools.dwMission_Completed = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Cursor_get_visible") == 0) {
			PH_Pools.dwCursor_get_visible = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Marshal_PtrToStringAnsi") == 0) {
			PH_Pools.dwMarshal_PtrToStringAnsi = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "LineRenderer_GetPosition") == 0) {
			PH_Pools.dwLineRenderer_GetPosition = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Camera_WorldToScreenPoint_1") == 0) {
			PH_Pools.dwCamera_WorldToScreenPoint_1 = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Transform_get_position") == 0) {
			PH_Pools.dwTransform_get_position = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "Component_1_get_transform") == 0) {
			PH_Pools.dwComponent_1_get_transform = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "GhostAI_StartGhost") == 0) {
			PH_Pools.dwGhostAI_StartGhost = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "GhostAI_Hunting") == 0) {
			PH_Pools.dwGhostAI_Hunting = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "GhostAI_Update") == 0) {
			PH_Pools.dwGhostAI_Update = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "GhostAI_ChangeState") == 0) {
			PH_Pools.dwGhostAI_ChangeState = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "ExitLevel_Exit") == 0) {
			PH_Pools.dwExitLevel_Exit = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "GameController_Exit") == 0) {
			PH_Pools.dwGameController_Exit = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "PauseMenuController_Leave") == 0) {
			PH_Pools.dwPauseMenuController_Leave = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "EMFData_Update") == 0) {
			PH_Pools.dwEMFData_Update = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "MissionManager_Start") == 0) {
			PH_Pools.dwMissionManager_Start = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "EvidenceController_Start") == 0) {
			PH_Pools.dwEvidenceController_Start = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
		if (std::strcmp(curMethod, "LevelController_Start") == 0) {
			PH_Pools.dwLevelController_Start = std::strtoul(curvAddr.c_str(), NULL, 16);
		}
	}
	return true;
}

BOOL Cheats::GetKey(UINT key, bool Spam = false)
{
	if (!bAllowInput)return FALSE;
	if (Spam == true)
		return static_cast<BOOL>(GetAsyncKeyState(key) & 0x8000);
	else
		return static_cast<BOOL>(GetAsyncKeyState(key) & 1);
}

void Cheats::CleanUp() {
	bSafeToRun = false;
	thisGhost = nullptr;
	thisEMF = nullptr;
	thisEvidence = nullptr;
	thisMission = nullptr;
	thisLevel = nullptr;
	//PhraseRecognized = odUnityFunction::CreateNETStringFromANSI("Try say something.");
	ActivityGraphs.clear();
}

MinHook_KeepAlive::MinHook_KeepAlive() {
	if (MH_Initialize() != MH_STATUS::MH_OK)
	{
		throw std::exception("MinHook Fault");
	}
	else {
		LogInstance.AddLog("MH Instance : %p\n", this);
	}
}

MinHook_KeepAlive::~MinHook_KeepAlive() {
	MH_Uninitialize();
}