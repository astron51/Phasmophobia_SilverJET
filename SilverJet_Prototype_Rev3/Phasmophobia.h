// Enum
enum class EGhostType : int64_t {
	Spirit = 0x00000000,
	Wraith = 0x00000001,
	Phantom = 0x00000002,
	Poltergeist = 0x00000003,
	Banshee = 0x00000004,
	Jinn = 0x00000005,
	Mare = 0x00000006,
	Revenant = 0x00000007,
	Shade = 0x00000008,
	Demon = 0x00000009,
	Yurei = 0x0000000a,
	Oni = 0x0000000b,
	Yokai = 0x0000000c,
	Hantu = 0x0000000d,
	Goryo = 0x0000000e,
	Myling = 0x0000000f,
	Onryo = 0x00000010,
	TheTwins = 0x00000011,
	Raiju = 0x00000012,
	Obake = 0x00000013,
};

enum class EMissionType : int32_t {
	none = 0x00000000,
	main = 0x00000001,
	side = 0x00000002,
};

enum class EGhostState : int32_t {
	idle = 0x00000000,
	wander = 0x00000001,
	hunting = 0x00000002,
	favouriteRoom = 0x00000003,
	light = 0x00000004,
	door = 0x00000005,
	throwing = 0x00000006,
	fusebox = 0x00000007,
	appear = 0x00000008,
	doorKnock = 0x00000009,
	windowKnock = 0x0000000a,
	carAlarm = 0x0000000b,
	radio = 0x0000000c,
	flicker = 0x0000000d,
	cctv = 0x0000000e,
	randomEvent = 0x0000000f,
	GhostAbility = 0x00000010,
	mannequin = 0x00000011,
	teleportObject = 0x00000012,
	interact = 0x00000013,
};

enum class EEMFType : int32_t {
	GhostInteraction = 0x00000000,
	GhostThrowing = 0x00000001,
	GhostAppeared = 0x00000002,
	GhostEvidence = 0x00000003,
};

enum class EFloorType : int32_t {
	basement = 0x00000000,
	firstFloor = 0x00000001,
	secondFloor = 0x00000002,
};

enum class ECursorLock : int32_t {
	None = 0x00000000,
	Locked = 0x00000001,
	Confined = 0x00000002,
};

enum class ERPCTarget {
	RpcTarget__Enum_All = 0x00000000,
	RpcTarget__Enum_Others = 0x00000001,
	RpcTarget__Enum_MasterClient = 0x00000002,
	RpcTarget__Enum_AllBuffered = 0x00000003,
	RpcTarget__Enum_OthersBuffered = 0x00000004,
	RpcTarget__Enum_AllViaServer = 0x00000005,
	RpcTarget__Enum_AllBufferedViaServer = 0x00000006,
};

enum class EEvidenceType : int32_t {
	emfSpot = 0x00000000,
	ouijaBoard = 0x00000001,
	fingerprint = 0x00000002,
	footstep = 0x00000003,
	DNA = 0x00000004,
	ghost = 0x00000005,
	deadBody = 0x00000006,
	dirtyWater = 0x00000007,
};

enum class ESelEvidence : int32_t {
	None = 0x00000000,
	EMF = 0x00000001,
	SpiritBox = 0x00000002,
	Fingerprints = 0x00000003,
	GhostOrb = 0x00000004,
	GhostWritingBook = 0x00000005,
	Temperature = 0x00000006,
	DotsProjector = 0x00000007,
};

// Struct
struct Vector3 {
	float x;
	float y;
	float z;

	Vector3() {
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
	}

	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3 operator+(const Vector3& V) const {
		return Vector3(x + V.x, y + V.y, z + V.z);
	}

	Vector3 operator-(const Vector3& V) const {
		return Vector3(x - V.x, y - V.y, z - V.z);
	}
};

// Class
class GhostAI;
class GhostAI_Fields;
class MonoBehavior_Fields;
class GhostInfo;
class GhostInfo_Fields;
class List_1_Fingerprint;
class List_1_SelEvidence;
class List_1_SelEvidence_Fields;
class SelEvidence_Array;
class GhostTraits;
class LevelRoom;
class LevelRoom_Fields;
class EMFData_Class;
class EMFData_StaticFields;
class EMFData;
class EMFData_Fields;
class MissionManager_Class;
class MissionManager_StaticFields;
class MissionManager;
class MissionManager_Fields;
class List_1_Mission;
class List_1_Mission_Fields;
class Mission_Array;
class Mission_Class;
class Mission;
class Mission_Fields;
class String;
class String_Fields;
class Text;
class Transform;
class List_1_Evidence;
class List_1_Evidence_Fields;
class Evidence_Array;
class Evidence;
class Evidence_Fields;
class EvidenceController_Class;
class EvidenceController_StaticFields;
class EvidenceController;
class EvidenceController_Fields;
class DNAEvidence;
class DNAEvidence_Fields;
class LevelController_Class;
class LevelController_StaticFields;
class LevelController;
class LevelController_Fields;
class FuseBox;
class FuseBox_Fields;
class OuijaBoard;
class OuijaBoard_Fields;
class List_1_EMF;
class List_1_EMF_Fields;
class EMF_Array;
class EMF;
class EMF_Fields;
class GameController;
class GameController_Fields;
class PlayerData;
class PlayerData_Fields;
class FirstPersonController;
class FirstPersonController_Fields;
class PlayerStamina;
class PlayerStamina_Fields;
class PlayerStats;
class PlayerStats_Fields;
class Player_1;
class Player_1_Fields;
class PlayerSanity;
class PlayerSanity_Fields;
class PCFlashLight;
class PCFlashLight_Fields;
class List_1_Player_1;
class List_1_Player_1_Fields;
class Player_1_Array;

class String_Fields
{
public:
	int32_t Length; //0x0000 
	uint16_t m_firstChar; //0x0004 

}; //Size=0x0006

class String
{
public:
	unsigned char Head[0x10]; //0x0000 
	String_Fields Fields; //0x0010 

}; //Size=0x0016

class Text
{
public:
	unsigned char Head[0x10]; //0x0000 
	unsigned char UnknownData00[0xC0]; //0x0010 
	String* m_Text; //0x00D0 

}; //Size=0x00D8

class Object_1_Fields
{
public:
	void* m_CachedPtr; //0x0000 

}; //Size=0x0008

class Component_1_Fields : public Object_1_Fields
{
public:
}; //Size=0x0008

class Transform
{
public:
	unsigned char Head[0x10]; //0x0000 
	unsigned char Fields[0x4]; //0x0010 ( I am quite lazy to find out the correct Size for this )

}; //Size=0x0018

class MonoBehavior_Fields
{
public:
	char _[0x8]; //0x0000

}; //Size=0x0008

class GhostAI_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* stateMachine; //0x0008 
	EGhostState GhostState; //0x0010 
	void* View; //0x0018 
	void* Anim; //0x0020 
	GhostInfo* CurrentGhostInfo; //0x0028 
	void* Agent; //0x0030 
	unsigned char UnusedData00[0x38]; //0x0038 
	__int32 LayerMask; //0x0070
	unsigned char UnusedData01[0x4]; //0x0074 
	Transform* Location; //0x0078
	Transform* raycastPoint; //0x0080
	unsigned char UnusedData02[0x28]; //0x0088 
	Player_1* bansheeTarget; //0x00B0
}; //Size=0x00B8

class GhostAI
{
public:
	unsigned char Head[0x10]; //0x0000  
	GhostAI_Fields Fields; //0x0010 

}; //Size=0x0048

class SelEvidence_Array
{
public:
	unsigned char Head[0x10]; //0x0000 
	void* Bounds; //0x0010 
	__int64 MaxLength; //0x0018 
	ESelEvidence ListOfEvidence[0x20]; //0x0020 

}; //Size=0x0024

class List_1_SelEvidence_Fields
{
public:
	SelEvidence_Array* Items; //0x0000 
	__int32 Size; //0x0008 

}; //Size=0x000C

class List_1_SelEvidence
{
public:
	unsigned char Head[0x10]; //0x0000 
	List_1_SelEvidence_Fields Fields; //0x0010 

}; //Size=0x001C

class GhostTraits
{
public:
	EGhostType GhostType; //0x0000 
	List_1_SelEvidence* EvidenceList;
	__int32 GhostAge; //0x0010 
	bool Gender; //0x0014 
	String* GhostName; //0x0018 
	__int32 ghostFirstNameID; //0x0020 
	__int32 ghostLastNameID; //0x0024 
	__int32 isShy; //0x0028 
	__int32 deathLength; //0x002C 
	__int32 favouriteRoomID; //0x0030 
	__int32 UnknownData01; //0x0034 

}; //Size=0x0038

class GhostInfo_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* View; //0x0008 
	GhostTraits curGhostTraits; //0x0010 
	GhostAI* CurrentGhost; //0x0040 
	LevelRoom* CurrentLevelRoom; //0x0048 
	double activityMultiplier; //0x0050 

}; //Size=0x0058

class GhostInfo
{
public:
	unsigned char Head[0x10]; //0x0000  
	GhostInfo_Fields Fields; //0x0010 

}; //Size=0x0068

class LevelRoom_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* PlayersInRoom; //0x0008 
	void* lightSwitches; //0x0010 
	void* doorsInLevel; //0x0018 
	void* ColliderList; //0x0020 
	unsigned char UnusedData00[0x10]; //0x0020
	EFloorType FloorType; //0x0038 
	String* roomName; //0x0040 
	float temperature; //0x0048 
	float startingTemperature; //0x004C 
	float currentPlayerInRoomTimer; //0x0050 
	float N0000016E; //0x0054 
	float N00000156; //0x0058 
	float N00000171; //0x005C 
	bool isBasementOrAttic; //0x0060

}; //Size=0x0064

class LevelRoom
{
public:
	unsigned char Head[0x10]; //0x0000  
	LevelRoom_Fields Fields; //0x0010 

}; //Size=0x0068

class EMFData_Class
{
public:
	unsigned char UnknownData00[0xB8]; //0x0000 
	EMFData_StaticFields* Static_Fields; //0x00B8 

}; //Size=0x00C0

class EMFData_StaticFields
{
public:
	EMFData* Instance; //0x0000 

}; //Size=0x0008

class EMF_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* UnusedData; //0x0008 
	__int32 UnknownData00; //0x0010 
	__int32 UnknownData01; //0x0014 
	EEMFType EMFType; //0x0018 
	float Tick; //0x001C 

}; //Size=0x0020

class EMF
{
public:
	unsigned char Head[0x10]; //0x0000 
	EMF_Fields Fields; //0x0010 

}; //Size=0x0018

class EMF_Array
{
public:
	unsigned char Head[0x10]; //0x0000 
	void* Bounds; //0x0010 
	__int64 MaxLength; //0x0018 
	EMF* Vector[0x20]; //0x0020 

}; //Size=0x0040

class List_1_EMF_Fields
{
public:
	EMF_Array* Items; //0x0000 
	__int32 Size; //0x0008 
	__int32 Version; //0x000C 
	void* _syncRoot; //0x0010 

}; //Size=0x0018

class List_1_EMF
{
public:
	unsigned char Head[0x10]; //0x0000 
	List_1_EMF_Fields Fields; //0x0010 

}; //Size=0x0028

class EMFData_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* rend; //0x0008 
	List_1_EMF* EMFArray; //0x0010 
	void* startingPos; //0x0018 
	float Tick; //0x0020 

}; //Size=0x0024

class EMFData
{
public:
	unsigned char Head[0x10]; //0x0000  
	EMFData_Fields Fields; //0x0010 

}; //Size=0x0034

class MissionManager_StaticFields
{
public:
	MissionManager* Instance; //0x0000 

}; //Size=0x0008

class MissionManager_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnusedData00[0x38]; //0x0008 
	List_1_Mission* MissionInfo; //0x0040 

}; //Size=0x0048

class MissionManager
{
public:
	unsigned char Head[0x10]; //0x0000  
	MissionManager_Fields Fields; //0x0010 

}; //Size=0x0058

class List_1_Mission_Fields
{
public:
	Mission_Array* Items; //0x0000 
	__int32 Size; //0x0008 

}; //Size=0x000C

class List_1_Mission
{
public:
	unsigned char Head[0x10]; //0x0000  
	List_1_Mission_Fields Fields; //0x0010 

}; //Size=0x001C

class Mission_Array
{
public:
	unsigned char Head[0x10]; //0x0000  
	void* Bound; //0x0010 
	__int64 MaxLength; //0x0018 
	Mission* ListOfMission[0x20]; //0x0020 

}; //Size=0x0048

class Mission_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* View; //0x0008 
	EMissionType MissionType; //0x0010 
	bool isComplete; //0x0014 
	String* MissionName; //0x0018 
	Text* MissionDetails; //0x0020 

}; //Size=0x0020

class Mission_Class
{
public:
	unsigned char UnusedData00[0x10]; //0x0000 
	const char* ClassName; //0x0010 

}; //Size=0x0018

class Mission
{
public:
	Mission_Class* klass; //0x0000 
	void* Monitor; //0x0008 
	Mission_Fields Fields; //0x0010 

}; //Size=0x0030

class EvidenceController_StaticFields
{
public:
	EvidenceController* curInstance; //0x0000 

}; //Size=0x0008

class DNAEvidence_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnknownData00[0x18]; //0x0008 

}; //Size=0x0020

class DNAEvidence
{
public:
	unsigned char Head[0x10]; //0x0000 
	DNAEvidence_Fields Fields; //0x0010 

}; //Size=0x0030

class OuijaBoard_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnusedData00[0x58]; //0x0008 
	Transform* evidenceTransform; //0x0060

}; //Size=0x0068

class OuijaBoard
{
public:
	unsigned char Head[0x10]; //0x0000 
	OuijaBoard_Fields Fields; //0x0010 

}; //Size=0x0098

class Evidence_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnknownData00[0x1C]; //0x0008 
	EEvidenceType EvidenceType; //0x0024 
	String* EvidenceName; //0x0028 

}; //Size=0x0030

class Evidence
{
public:
	unsigned char Head[0x10]; //0x0000 
	Evidence_Fields Fields; //0x0010 

}; //Size=0x0040

class Evidence_Array
{
public:
	unsigned char Head[0x10]; //0x0000 
	void* Bounds; //0x0010 
	__int64 MaxLength; //0x0018 
	Evidence* ListOfEvidence[0x20]; //0x0020 

}; //Size=0x0028

class List_1_Evidence_Fields
{
public:
	Evidence_Array* Items; //0x0000 
	__int32 Size; //0x0008 

}; //Size=0x000C

class List_1_Evidence
{
public:
	unsigned char Head[0x10]; //0x0000 
	List_1_Evidence_Fields Fields; //0x0010 

}; //Size=0x001C

class EvidenceController_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnusedData00[0x10]; //0x0008 
	List_1_Evidence* EvidenceList; //0x0018 
	unsigned char UnusedData01[0x10]; //0x0020 
	DNAEvidence* bone; //0x0030 
	Transform* ghostOrb; //0x0038 
	void* ParticleRenderer; //0x0040 
	OuijaBoard* OuijaBoard; //0x0048 
	unsigned char UnusedData02[0x20]; //0x0050 
	void* FingerprintList; //0x0070 

}; //Size=0x0050

class EvidenceController
{
public:
	unsigned char Head[0x10]; //0x0000 
	EvidenceController_Fields Fields; //0x0010 

}; //Size=0x0058

class EvidenceController_Class
{
public:
	unsigned char UnknownData00[0xB8]; //0x0000 
	EvidenceController_StaticFields* Static_Fields; //0x00B8 

}; //Size=0x00C0

class FuseBox_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnusedData00[0x38]; //0x0008 
	Transform* Location; //0x0038 
	unsigned char UnusedData01[0x10]; //0x0048
	bool isTurnedOn; //0x0058
	unsigned char UnusedData02[0x30]; //0x0060

}; //Size=0x0090

class FuseBox
{
public:
	unsigned char Head[0x10]; //0x0000 
	FuseBox_Fields Fields; //0x0010 

}; //Size=0x0050

class GameController_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	PlayerData* myPlayer; //0x0008 
	unsigned char UnityEvent[0x40]; //0x0010 
	List_1_Player_1* playerList; //0x0050 
	unsigned char UnknownData00[0x20]; //0x0058
	LevelController* curLevelController; //0x0078
	unsigned char UnknownData01[0x28]; //0x0080

}; //Size=0x00A8

class GameController
{
public:
	unsigned char Head[0x10]; //0x0000 
	GameController_Fields Fields; //0x0010 

}; //Size=0x0078

class LevelController_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* View; //0x0008 
	LevelRoom* UnknownLevel00; //0x0010 
	LevelRoom* curLevelRoom; //0x0018 
	GhostAI* curGhost; //0x0020 
	unsigned char UnusedData00[0x30]; //0x0028 
	FuseBox* Breaker; //0x0058
	unsigned char UnusedData01[0x8]; //0x0060
	GameController* curGameController; //0x0068 

}; //Size=0x0058

class LevelController
{
public:
	unsigned char Head[0x10]; //0x0000 
	LevelController_Fields Fields; //0x0010 

}; //Size=0x0068

class LevelController_StaticFields
{
public:
	LevelController* Instance; //0x0000 

}; //Size=0x0008

class LevelController_Class
{
public:
	unsigned char UnknownData00[0xB8]; //0x0000 
	LevelController_StaticFields* Static_Fields; //0x00B8 

}; //Size=0x00C0

class FirstPersonController_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	char pad_0x0008[0x98]; //0x0008

}; //Size=0x00A0

class FirstPersonController
{
public:
	unsigned char UnusedData00[0x10]; //0x0000 
	FirstPersonController_Fields Fields; //0x0010 

}; //Size=0x0018

class PlayerStamina_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnusedData00[0x18]; //0x0008 
	Player_1* Owner; //0x0020 
	__int8 UnknownBoolean00; //0x0028 
	__int8 UnknownBoolean01; //0x0029 
	__int8 isRunning; //0x002A 
	__int8 isOutOfBreath; //0x002B 
	__int8 isRecharging; //0x002C 
	unsigned char UnusedByte00[0x3]; //0x002D 
	float StaminaMax; //0x0030 
	float RechargeMax; //0x0034 
	float RechargeTick; //0x0038 
	float Stamina; //0x003C 
	float CDRecharge; //0x0040 
	unsigned char UnityEvent[0x10]; //0x0044 

}; //Size=0x0054

class PlayerStamina
{
public:
	unsigned char UnusedData00[0x10]; //0x0000 
	PlayerStamina_Fields Fields; //0x0010 

}; //Size=0x0064

class PlayerStats_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char view[0x8]; //0x0008 
	Player_1* player; //0x0010 
	unsigned char UnusedData00[0x8]; //0x0018 
	LevelController* curLevelController; //0x0020 

}; //Size=0x0028

class PlayerStats
{
public:
	unsigned char Head[0x10]; //0x0000 
	PlayerStats_Fields Fields; //0x0010 

}; //Size=0x0038

class Player_1_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	unsigned char UnusedData00[0x98]; //0x0008 
	PlayerSanity* mySanity; //0x00C0 
	PlayerStats* myStats; //0x00A8 
	unsigned char UnusedData01[0x20]; //0x0008 
	PlayerStamina* myStamina; //0x00C0 
	unsigned char UnusedData02[0x10]; //0x00C8 
	FirstPersonController* myFirstPersonController; //0x00D8 
	unsigned char UnusedData03[0x38]; //0x00E0 
	PCFlashLight* FlashLight; //0x0118 

}; //Size=0x0120

class Player_1
{
public:
	unsigned char Head[0x10]; //0x0000
	Player_1_Fields Fields; //0x0010 

}; //Size=0x0248

class Player_1_Array
{
public:
	unsigned char Head[0x10]; //0x0000 
	void* Bounds; //0x0000 
	__int64 MaxLength; //0x0018 
	PlayerData* ListOfPlayers[0x20]; //0x0020 

}; //Size=0x0028

class List_1_Player_1_Fields
{
public:
	Player_1_Array* Items; //0x0000 
	__int32 Size; //0x0008 

}; //Size=0x000C

class List_1_Player_1
{
public:
	unsigned char Head[0x10]; //0x0000 
	List_1_Player_1_Fields Fields; //0x0010 

}; //Size=0x001C

class PlayerData_Fields
{
public:
	Player_1* player; //0x0000 
	void* photonPlayer; //0x0008 
	String* playerName; //0x0010 

}; //Size=0x0018

class PlayerData
{
public:
	unsigned char Head[0x10]; //0x0000 
	PlayerData_Fields Fields; //0x0010 

}; //Size=0x0028

class PlayerSanity_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* View; //0x0008 
	Player_1* Owner; //0x0010 
	float Insanity; //0x0018
	float UnknownFloat00; //0x001C
	float TimerRandomize; //0x0020
	unsigned char UnusedData00[0x10]; //0x0024
	float fDrainingRate; //0x0034
	unsigned char UnusedData01[0x40]; //0x0038

}; //Size=0x0078

class PlayerSanity
{
public:
	unsigned char Head[0x10]; //0x0000 
	PlayerSanity_Fields Fields; //0x0010 

}; //Size=0x0052

class PCFlashLight_Fields
{
public:
	MonoBehavior_Fields* _; //0x0000 
	void* HeadLight; //0x0008 
	void* VolumetricLight; //0x0008 
	void* PCPropGrab; //0x0010 
	Player_1* Owner; //0x0018 
	void* source; //0x0020 
	void* View; //0x0028 
	bool bIsOn; //0x0030 
	void* inventoryLight; //0x0038 
	bool bIsBlinking; //0x0040 
	unsigned char UnknownData[0x18]; //0x004C 

}; //Size=0x0050

class PCFlashLight
{
public:
	unsigned char Head[0x10]; //0x0000 
	PCFlashLight_Fields Fields; //0x0010 

}; //Size=0x0060

// Function Declaration, Static.
uintptr_t inline il2CPP_Get_Base() {
	return (uintptr_t)GetModuleHandleW(L"GameAssembly.dll");
}

uintptr_t inline il2CPP_Get_Base_Merge(DWORD p0) {
	return (uintptr_t)GetModuleHandleW(L"GameAssembly.dll") + p0;
}