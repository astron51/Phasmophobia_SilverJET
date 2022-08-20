#pragma once
#include "Common.h"

struct odUnityFunction {
	static String* CreateNETStringFromANSI(const char*);
	static std::string GetUTF8StringFromNETString(String*);
	static void hksMissionComplete(Mission*);
	static void hkGhostAI_StartGhost(GhostAI*, void*);
	static void hkGhostAI_Update(GhostAI*, void*);
	static void hkGhostAI_Hunting(GhostAI*, bool, void*, void*);
	static void hkExitLevel_Exit(void*, void*);
	static void hkGameController_Exit(void*, void*);
	static void hkPauseMenuController_Leave(void*, void*);
	static void hkEMFData_Start(EMFData*, void*);
	static void hkMissionManager_Start(MissionManager*, void*);
	static void hkEvidenceController_Start(EvidenceController*, void*);
	static void hkLevelController_Start(LevelController*, void*);
};

struct MinHook_KeepAlive {
	MinHook_KeepAlive();
	~MinHook_KeepAlive();
};

class Cheats
{
	friend odUnityFunction;
public:
	Cheats();
	String* PhraseRecognized;
	GhostAI* thisGhost;
	EMFData* thisEMF;
	MissionManager* thisMission;
	EvidenceController* thisEvidence;
	LevelController* thisLevel;
	std::vector<float> ActivityGraphs;
	float fFlashLightIntensity = 1.0f;
	float fFlashLightAngle = 60.0f;
	bool bEnableSpeechRec = false;
	bool bSpeechHooked = false;
	bool bAutoIncreaseFlash = false;
	bool bAllowInput = true;
	bool bShowDebug = false;
	bool bSafeToRun = false;
	bool bShowActivityGraph = false;
	bool bShowMissionDetails = false;
	bool bUnlimitedStamina = false;
	bool bESP = false;
	bool bSanity = false;
	bool bHunting = false;
	int iInfoType = 0; // 0 - Name and Mission Details , 1 - Name, Age, Gender, Responsive, Ghost Type, Evidence and Mission Details
	int	iESPType = 1; // 0 - Text and Box 1 - Normal Text only
	void CheatThread();
	bool OpenMeta(char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL);
	BOOL GetKey(UINT, bool);
	void CleanUp();
	void (*oGhostAI_StartGhost)(GhostAI*, void*);
	void (*oGhostAI_Hunting)(GhostAI*, bool, void*, void*);
	void (*oGhostAI_Update)(GhostAI*, void*);
	void (*oExitLevel_Exit)(void*, void*);
	void (*oGameController_Exit)(void*, void*);
	void (*oPauseMenuController_Leave)(void*, void*);
	void (*oEMFData_Start)(EMFData*, void*);
	void (*oMissionManager_Start)(MissionManager*, void*);
	void (*oEvidenceController_Start)(EvidenceController*, void*);
	void (*oLevelController_Start)(LevelController*, void*);
private:
	MinHook_KeepAlive MH_Instance;
};

inline Cheats* g_Cheats;