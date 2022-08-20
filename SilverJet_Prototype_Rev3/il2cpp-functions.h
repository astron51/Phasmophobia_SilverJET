// Unity Support Functions
DO_APP_FUNC(String*, Marshal_PtrToStringAnsi, (void* _this, void* MethodInfo), "mscorlib, System.String System.Runtime.InteropServices.Marshal::PtrToStringAnsi(System.IntPtr)");
DO_APP_FUNC(void*, Camera_Get_Main, (void* MethodInfo), "UnityEngine.CoreModule, UnityEngine.Camera UnityEngine.Camera::get_main()");
DO_APP_FUNC(Vector3, Camera_WorldToScreenPoint, (void* Camera, Vector3 Position, void* MethodInfo), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Camera::WorldToScreenPoint(UnityEngine.Vector3)");
DO_APP_FUNC(void, Cursor_set_lockState, (ECursorLock State, void* MethodInfo), "UnityEngine.CoreModule, System.Void UnityEngine.Cursor::set_lockState(UnityEngine.CursorLockMode)");
DO_APP_FUNC(bool, Cursor_get_visible, (void* MethodInfo), "UnityEngine.CoreModule, System.Boolean UnityEngine.Cursor::get_visible()");
DO_APP_FUNC(void, Light_Set_Intensity, (void* LightPtr, float fIntensity, void* MethodInfo), "UnityEngine.CoreModule, System.Void UnityEngine.Light::set_intensity(System.Single)");
DO_APP_FUNC(void, Light_set_spotAngle, (void* LightPtr, float fAngle, void* MethodInfo), "UnityEngine.CoreModule, System.Void UnityEngine.Light::set_spotAngle(System.Single)");
DO_APP_FUNC(void, PhotonView_RPC, (void* PhontonView, String* MethodName, ERPCTarget Target, void* Parameters, void* MethodInfo), "PhotonUnityNetworking, System.Void Photon.Pun.PhotonView::RPC(System.String, Photon.Pun.RpcTarget, System.Object[])");
DO_APP_FUNC(Vector3, LineRenderer_GetPosition, (void* Line, int32_t Index, void* MethodInfo), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.LineRenderer::GetPosition(System.Int32)");
DO_APP_FUNC(Vector3, Transform_get_position, (Transform* _this, void* MethodInfo), "UnityEngine.CoreModule, UnityEngine.Vector3 UnityEngine.Transform::get_position()");
DO_APP_FUNC(Transform*, Component_1_get_transform, (void* _this, void* MethodInfo), "UnityEngine.CoreModule, UnityEngine.Transform UnityEngine.Component::get_transform()");

// GhostAI Functions
DO_APP_FUNC(void, GhostAI_Hunting, (GhostAI*, bool, void*, void*), "Assembly-CSharp, System.Void GhostAI::Hunting(System.Boolean, Photon.Pun.PhotonMessageInfo)");
DO_APP_FUNC(void, GhostAI_StartGhost, (GhostAI*, void*), "Assembly-CSharp, System.Void GhostAI::StartGhost()");
DO_APP_FUNC(void, GhostAI_Update, (GhostAI*, void*), "Assembly-CSharp, System.Void GhostAI::Update()");

// Exit Functions
DO_APP_FUNC(void, ExitLevel_Exit, (void*, void*), "Assembly-CSharp, System.Void ExitLevel::Exit(Photon.Pun.PhotonMessageInfo)");
DO_APP_FUNC(void, GameController_Exit, (void*, void*), "Assembly-CSharp, System.Void GameController::Exit()");
DO_APP_FUNC(void, PauseMenuController_Leave, (void*, void*), "Assembly-CSharp, System.Void PauseMenuController::Leave()");
DO_APP_FUNC(void, EMFData_Start, (EMFData*, void*), "Assembly-CSharp, System.Void EMFData::Start()");
DO_APP_FUNC(void, MissionManager_Start, (MissionManager*, void*), "Assembly-CSharp, System.Void MissionManager::Start()");
DO_APP_FUNC(void, EvidenceController_Start, (EvidenceController*, void*), "Assembly-CSharp, System.Void EvidenceController::Start()");
DO_APP_FUNC(void, LevelController_Start, (LevelController*, void*), "Assembly-CSharp, System.Void LevelController::Start()");