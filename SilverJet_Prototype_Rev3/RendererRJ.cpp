#include "RendererRJ.h"
#include "Cheats.h"

#define DO_APP_FUNC(r, n, p, s) extern r (*n) p
#include "il2cpp-functions.h"
#undef DO_APP_FUNC

HRESULT __fastcall odDirectX::Present(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags)
{
	__try {
		if (!g_Renderer->g_pDevice) {
			if (FAILED(GetDeviceAndCtxFromSwapchain(pThis, &g_Renderer->g_pDevice, &g_Renderer->g_pContext))) {
				return g_Renderer->oIDXGISwapChainPresent(pThis, SyncInterval, Flags);
			}
			if (FAILED(pThis->GetDesc(&g_Renderer->SwapChainDescription))) {
				return g_Renderer->oIDXGISwapChainPresent(pThis, SyncInterval, Flags);
			}
			do {
				g_Renderer->DefaultProc = (WNDPROC)SetWindowLongPtr(g_Renderer->SwapChainDescription.OutputWindow, GWLP_WNDPROC, (LONG_PTR)odDirectX::hWndProc);
			} while (g_Renderer->SwapChainDescription.OutputWindow && !g_Renderer->DefaultProc);
			pThis->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&g_Renderer->pBackBuffer);
			if (FAILED(g_Renderer->g_pDevice->CreateRenderTargetView(g_Renderer->pBackBuffer, NULL, &g_Renderer->g_pTargetView))) {
				return g_Renderer->oIDXGISwapChainPresent(pThis, SyncInterval, Flags);
			}
			g_Renderer->pBackBuffer->Release();
			g_Renderer->bInitBaseSet = true;
		}

		if (g_Renderer->bReady) {
			if (g_Renderer->bReady && g_Renderer->g_pContext) {
				g_Renderer->OnPresent(g_Renderer->g_pContext);
			}
			else {
				g_Renderer->g_pContext->OMSetRenderTargets(1, &g_Renderer->g_pTargetView, NULL);
			}
			if (g_Cheats)
				g_Cheats->CheatThread();
		}
		return g_Renderer->oIDXGISwapChainPresent(pThis, SyncInterval, Flags);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		LogInstance.AddLog("Error while rendering : %p\n", GetExceptionCode());
		return g_Renderer->oIDXGISwapChainPresent(pThis, SyncInterval, Flags);
	}
}

LRESULT CALLBACK odDirectX::hWndProc(HWND hHwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_ACTIVATEAPP:
		g_Cheats->bAllowInput = (bool)wParam;
		break;
	case WM_SIZE:
		g_Renderer->PreReset();
		g_Renderer->PostReset();
		break;
	case WM_KEYDOWN:
		if (wParam == VK_INSERT) {
			g_Renderer->bOpenMenu = !g_Renderer->bOpenMenu;
			Cursor_set_lockState(ECursorLock::None, NULL);
		}
		break;
	default:
		break;
	}
	if (g_Renderer->bOpenMenu && g_Renderer->bReady)
	{
		ImGui_ImplWin32_WndProcHandler(hHwnd, uMsg, wParam, lParam);
		return true;
	}
	return CallWindowProc(g_Renderer->DefaultProc, hHwnd, uMsg, wParam, lParam);
}

void RendererRJ::PreReset() {
	ImGui_ImplDX11_InvalidateDeviceObjects();
}

void RendererRJ::PostReset() {
	ImGui_ImplDX11_CreateDeviceObjects();
}

RendererRJ::RendererRJ() {
	g_Renderer = this;
	if (MH_CreateHook((DWORD*)CreateDummy(), &odDirectX::Present, reinterpret_cast<LPVOID*>(&this->oIDXGISwapChainPresent)) != MH_OK) {
		throw std::exception(_c("Fault while attempting to create hook for IDXGISwapChain::Present."));
	}

	if (MH_EnableHook((DWORD*)CreateDummy()) != MH_OK) {
		throw std::exception(_c("Fault while attempting to enable Renderer hook."));
	}

	do { Sleep(100); } while (!this->g_pDevice || !DefaultProc);

	do { Sleep(100); } while (!g_Renderer->bInitBaseSet || !g_Renderer->SwapChainDescription.OutputWindow); // Safe check, wait for Present to Setup
	InitImGui(g_Renderer->SwapChainDescription);
}

void RendererRJ::InitImGui(DXGI_SWAP_CHAIN_DESC SwapChainDescription) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.DeltaTime = 1.0f / 60.0f;
	io.FontGlobalScale = 0.90f;
	io.ConfigWindowsMoveFromTitleBarOnly = TRUE;
	io.FontGlobalScale = 0.9f;
	static ImWchar ranges[] = { 0x1, 0x1FFFF, 0 };
	static ImFontConfig cfg;
	cfg.OversampleH = cfg.OversampleV = 1;
	cfg.MergeMode = true;
	cfg.FontBuilderFlags |= ImGuiFreeTypeBuilderFlags_LoadColor;
	fDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 15.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
	fSeguiEmoji = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\seguiemj.ttf", 15.0f, &cfg, ranges);
	fskeet = io.Fonts->AddFontFromMemoryCompressedBase85TTF(skrrtmenu_base85, 40.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	fguns = io.Fonts->AddFontFromMemoryCompressedBase85TTF(astriumwep_base85, 40.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
	ImGui::StyleColorsClassic();
	if (!ImGui_ImplWin32_Init(SwapChainDescription.OutputWindow)) {
	}
	if (!ImGui_ImplDX11_Init(g_Renderer->g_pDevice, g_Renderer->g_pContext)) {
	}
	ImGui::GetIO().ImeWindowHandle = SwapChainDescription.OutputWindow;
	ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
	ImGuiStyle& style = ImGui::GetStyle();
	style.AntiAliasedLines = TRUE;
	style.AntiAliasedFill = TRUE;
	style.AntiAliasedLinesUseTex = TRUE;
	style.WindowTitleAlign.x = 0.50f;
	style.WindowTitleAlign.y = 0.50f;
	style.FrameRounding = 2.0f;
	style.WindowRounding = 12.0f;
	bReady = true;
	LOG_F(INFO, "ImGui Ready");
}

void EngineDebug::DebugOverlay(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 2;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (corner != -1)
	{
		window_flags |= ImGuiWindowFlags_NoMove;
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("##Debug PCFlashLight", p_open, window_flags))
	{
		ImGui::Text("Player Stamina");
		ImGui::Separator();

		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

void EngineDebug::ShowLogWindow(bool* p_open, LogWindow log)
{
	ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
	ImGui::Begin(_c("SilverJET Prototype Log"), p_open);
	ImGui::End();

	log.Draw(_c("SilverJET Prototype Log"), p_open);
}

void ShowSanityDetails(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 2;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (corner != -1)
	{
		window_flags |= ImGuiWindowFlags_NoMove;
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Sanity", p_open, window_flags))
	{
		ImGui::Text("Sanity");
		ImGui::Separator();
		__try {
			if (g_Cheats->bSafeToRun && g_Cheats->thisGhost) {
				if (g_Cheats->bSanity) {
					List_1_Player_1* playerList = g_Cheats->thisLevel->Fields.curGameController->Fields.playerList;
					if (playerList != NULL) {
						float Average = 0.0f;
						for (int i = 0; i < playerList->Fields.Size; i++)
						{
							double curSanity = static_cast<double>(100.0f) - static_cast<double>(playerList->Fields.Items->ListOfPlayers[i]->Fields.player->Fields.mySanity->Fields.Insanity);
							Average += curSanity;
							ImGui::Text("%s : %.2f", odUnityFunction::GetUTF8StringFromNETString(playerList->Fields.Items->ListOfPlayers[i]->Fields.playerName).c_str(), curSanity);
						}
						Average = Average / playerList->Fields.Size;
						ImGui::Text("Average Sanity : %.2f", Average);
					}
				}
			}
			else {
				ImGui::Text("Waiting for game to start.");
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LogInstance.AddLog("Exception Caught : %p\n", GetExceptionCode());
		}
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

void ShowMissionDetails(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 0;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (corner != -1)
	{
		window_flags |= ImGuiWindowFlags_NoMove;
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Mission Details", p_open, window_flags))
	{
		ImGui::Text("Mission Details");
		ImGui::Separator();
		__try {
			if (g_Cheats->bSafeToRun && g_Cheats->thisGhost) {
				if (g_Cheats->bShowMissionDetails) {
					if (g_Cheats->iInfoType == 0) {
						ImGui::Text("Name of Ghost : %s", odUnityFunction::GetUTF8StringFromNETString(g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.curGhostTraits.GhostName).c_str());
						if (g_Cheats->thisMission) {
							List_1_Mission* missionList = g_Cheats->thisMission->Fields.MissionInfo;
							if (missionList != NULL) {
								for (int i = 0; i < missionList->Fields.Size; i++)
								{
									Text* missionText = missionList->Fields.Items->ListOfMission[i]->Fields.MissionDetails;
									std::string missionMessage = odUnityFunction::GetUTF8StringFromNETString(missionText->m_Text);
									missionMessage.erase(missionMessage.begin(), missionMessage.begin() + 13);
									ImGui::Text("Mission %d : %s", i + 1, missionList->Fields.Items->ListOfMission[i]->Fields.isComplete ? "Accomplished" : missionMessage.c_str());
								}
							}
						}
					}
					else {
						ImGui::Text("Name of Ghost : %s", odUnityFunction::GetUTF8StringFromNETString(g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.curGhostTraits.GhostName).c_str());
						ImGui::Text("Age : %d", g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.curGhostTraits.GhostAge);
						ImGui::Text("Gender : %s", g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.curGhostTraits.Gender ? "Male" : "Female");
						ImGui::Text("Is Shy : %s", g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.curGhostTraits.isShy ? "Yes" : "No");
						switch (g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.curGhostTraits.GhostType) {
						case EGhostType::Spirit:
							ImGui::Text("Ghost Type : Spirit");
							break;
						case EGhostType::Wraith:
							ImGui::Text("Ghost Type : Wraith");
							break;
						case EGhostType::Phantom:
							ImGui::Text("Ghost Type : Phantom");
							break;
						case EGhostType::Poltergeist:
							ImGui::Text("Ghost Type : Poltergeist");
							break;
						case EGhostType::Banshee:
							ImGui::Text("Ghost Type : Banshee");
							break;
						case EGhostType::Jinn:
							ImGui::Text("Ghost Type : Jinn");
							break;
						case EGhostType::Mare:
							ImGui::Text("Ghost Type : Mare");
							break;
						case EGhostType::Revenant:
							ImGui::Text("Ghost Type : Revenant");
							break;
						case EGhostType::Shade:
							ImGui::Text("Ghost Type : Shade");
							break;
						case EGhostType::Demon:
							ImGui::Text("Ghost Type : Demon");
							break;
						case EGhostType::Yurei:
							ImGui::Text("Ghost Type : Yurei");
							break;
						case EGhostType::Oni:
							ImGui::Text("Ghost Type : Oni");
							break;
						case EGhostType::Hantu:
							ImGui::Text("Ghost Type : Hantu");
							break;
						case EGhostType::Yokai:
							ImGui::Text("Ghost Type : Yokai");
							break;
						case EGhostType::Goryo:
							ImGui::Text("Ghost Type : Goryo");
							break;
						case EGhostType::Myling:
							ImGui::Text("Ghost Type : Myling");
							break;
						case EGhostType::Onryo:
							ImGui::Text("Ghost Type : Onryo");
							break;
						case EGhostType::TheTwins:
							ImGui::Text("Ghost Type : The Twins");
							break;
						case EGhostType::Raiju:
							ImGui::Text("Ghost Type : Raiju");
							break;
						case EGhostType::Obake:
							ImGui::Text("Ghost Type : Obake");
							break;
						default:
							ImGui::Text("Ghost Type : Unknown"); ImGui::SameLine();
							ImGui::Text("Evidence : Unknown");
							break;
						}
						ImGui::Text("Evidence : "); ImGui::SameLine();
						if (g_Cheats->thisEvidence) {
							List_1_SelEvidence* eList = g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.curGhostTraits.EvidenceList;
							if (eList != NULL) {
								for (int i = 0; i < eList->Fields.Size; i++) {
									switch (eList->Fields.Items->ListOfEvidence[i]) {
									case ESelEvidence::DotsProjector:
										ImGui::Text("DOTS Projector"); ImGui::SameLine();
										break;
									case ESelEvidence::EMF:
										ImGui::Text("EMF 5"); ImGui::SameLine();
										break;
									case ESelEvidence::Fingerprints:
										ImGui::Text("Fingerprints"); ImGui::SameLine();
										break;
									case ESelEvidence::GhostOrb:
										ImGui::Text("Ghost Orbs"); ImGui::SameLine();
										break;
									case ESelEvidence::GhostWritingBook:
										ImGui::Text("Ghost Writing"); ImGui::SameLine();
										break;
									case ESelEvidence::SpiritBox:
										ImGui::Text("Spirit Box"); ImGui::SameLine();
										break;
									case ESelEvidence::Temperature:
										ImGui::Text("Freezing Temperature"); ImGui::SameLine();
										break;
									default:
										break;
									}
								}
							}
						}
						ImGui::NewLine();
						switch (g_Cheats->thisGhost->Fields.GhostState) {
						case EGhostState::idle:
							ImGui::Text("Ghost State : %s", "Idle");
							break;
						case EGhostState::wander:
							ImGui::Text("Ghost State : %s", "Wandering around");
							break;
						case EGhostState::hunting:
							ImGui::Text("Ghost State : %s", "Hunting, you better hide bitch!");
							break;
						case EGhostState::favouriteRoom:
							ImGui::Text("Ghost State : %s", "In favourite room");
							break;
						case EGhostState::light:
							ImGui::Text("Ghost State : %s", "Interact with light");
							break;
						case EGhostState::door:
							ImGui::Text("Ghost State : %s", "Interact with door");
							break;
						case EGhostState::throwing:
							ImGui::Text("Ghost State : %s", "Throwing item");
							break;
						case EGhostState::fusebox:
							ImGui::Text("Ghost State : %s", "Tripping Fusebox");
							break;
						case EGhostState::appear:
							ImGui::Text("Ghost State : %s", "Appear");
							break;
						case EGhostState::doorKnock:
							ImGui::Text("Ghost State : %s", "Knocking door");
							break;
						case EGhostState::windowKnock:
							ImGui::Text("Ghost State : %s", "Knocking window");
							break;
						case EGhostState::carAlarm:
							ImGui::Text("Ghost State : %s", "Trigger car alarm");
							break;
						case EGhostState::radio:
							ImGui::Text("Ghost State : %s", "Playing with Radio");
							break;
						case EGhostState::flicker:
							ImGui::Text("Ghost State : %s", "Flickering Light");
							break;
						case EGhostState::cctv:
							ImGui::Text("Ghost State : %s", "CCTV");
							break;
						case EGhostState::randomEvent:
							ImGui::Text("Ghost State : %s", "Random Event");
							break;
						case EGhostState::GhostAbility:
							ImGui::Text("Ghost State : %s", "Using Ghost Ability");
							break;
						case EGhostState::mannequin:
							ImGui::Text("Ghost State : %s", "Playing with mannequin");
							break;
						case EGhostState::teleportObject:
							ImGui::Text("Ghost State : %s", "Teleport object");
							break;
						case EGhostState::interact:
							ImGui::Text("Ghost State : %s", "Interacting");
							break;
						default:
							ImGui::Text("Ghost State : %s", "Unknown");
							break;
						}
						ImGui::Text("Favourite Room : %s", odUnityFunction::GetUTF8StringFromNETString(g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.CurrentLevelRoom->Fields.roomName).c_str()); ImGui::SameLine();
						switch (g_Cheats->thisGhost->Fields.CurrentGhostInfo->Fields.CurrentLevelRoom->Fields.FloorType) {
						case EFloorType::basement:
							ImGui::Text("Floor : Basement");
							break;
						case EFloorType::firstFloor:
							ImGui::Text("Floor : First Floor");
							break;
						case EFloorType::secondFloor:
							ImGui::Text("Floor : Second Floor");
							break;
						default:
							ImGui::Text("Floor : Unknown Floor");
							break;
						}
						if (g_Cheats->thisMission) {
							List_1_Mission* missionList = g_Cheats->thisMission->Fields.MissionInfo;
							if (missionList != NULL) {
								for (int i = 0; i < missionList->Fields.Size; i++)
								{
									Text* missionText = missionList->Fields.Items->ListOfMission[i]->Fields.MissionDetails;
									std::string missionMessage = odUnityFunction::GetUTF8StringFromNETString(missionText->m_Text);
									missionMessage.erase(missionMessage.begin(), missionMessage.begin() + 13);
									ImGui::Text("Mission %d : %s", i + 1, missionList->Fields.Items->ListOfMission[i]->Fields.isComplete ? "Accomplished" : missionMessage.c_str());
								}
							}
						}
						if (g_Cheats->thisGhost->Fields.bansheeTarget) {
							if (g_Cheats->thisGhost->Fields.bansheeTarget->Fields.myStats) {
								if (g_Cheats->thisGhost->Fields.bansheeTarget->Fields.myStats->Fields.curLevelController) {
									GameController* thisControl = g_Cheats->thisGhost->Fields.bansheeTarget->Fields.myStats->Fields.curLevelController->Fields.curGameController;
									if (thisControl) {
										if (thisControl->Fields.myPlayer) {
											ImGui::Text("Banshee Target : %s", odUnityFunction::GetUTF8StringFromNETString(thisControl->Fields.myPlayer->Fields.playerName).c_str());
										}
									}
								}
							}
						}
					}
				}
			}
			else {
				ImGui::Text("Waiting for game to start.");
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LogInstance.AddLog("Exception Caught : %p\n", GetExceptionCode());
		}
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

void ShowGhostGraph(bool* p_open)
{
	const float DISTANCE = 10.0f;
	static int corner = 1;
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (corner != -1)
	{
		window_flags |= ImGuiWindowFlags_NoMove;
		ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
		ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
	}
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	ImGui::SetNextWindowSize(ImVec2(430, 315));
	if (ImGui::Begin("Ghost Graph", p_open, window_flags))
	{
		ImPlot::SetNextPlotLimits(-0.1, 60, 0, 10);
		if (ImPlot::BeginPlot("Ghost Activity Graph", "Seconds", "Strength", ImVec2(-1, 0), ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect | ImPlotFlags_NoLegend | ImPlotFlags_NoMousePos, ImPlotAxisFlags_Lock, ImPlotAxisFlags_Lock)) {
			__try {
				if (g_Cheats->bSafeToRun && !g_Cheats->ActivityGraphs.empty() && g_Cheats->thisGhost) {
					ImPlot::PlotLine("Ghost Activity", &g_Cheats->ActivityGraphs[0], g_Cheats->ActivityGraphs.size(), 1.0f, 1.0f);
				}
				else {
					static float arr[] = { 0.0f,0.0f };
					ImPlot::PlotLine("Ghost Activity", arr, IM_ARRAYSIZE(arr), 1.0f, 1.0f);
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {
				LogInstance.AddLog("Error in Graph : %p\n", GetExceptionCode());
			}
			ImPlot::EndPlot();
		}
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::MenuItem("Custom", NULL, corner == -1)) corner = -1;
			if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
			if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
			if (p_open && ImGui::MenuItem("Close")) *p_open = false;
			ImGui::EndPopup();
		}
	}
	ImGui::End();
}

void RendererRJ::OnPresent(ID3D11DeviceContext* pContext) {
	if (!bReady) return;
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (!Cursor_get_visible(NULL)) {
		ImGui::GetIO().MouseDrawCursor = g_Renderer->bOpenMenu;
	}
	if (g_Renderer->bShowDemo)
		ImGui::ShowDemoWindow(&g_Renderer->bOpenMenu);
	if (g_Renderer->bOpenMenu) {
		ImGui::Begin("SilverJET Prototype", &g_Renderer->bOpenMenu, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize); {
			if (ImGui::BeginTabBar("##tab", ImGuiTabBarFlags_None)) {
				if (ImGui::BeginTabItem("Visuals"))
				{
					ImGui::BeginChild("##Visual", ImVec2(538, 115), false); {
						ImGui::Checkbox("Mission Details", &g_Cheats->bShowMissionDetails); ImGui::SameLine(); ImGui::SetNextItemWidth(130.0f); ImGui::Combo("##DType", &g_Cheats->iInfoType, "Basic Information\0Extra Information\0");
						ImGui::Checkbox("Ghost Activity Graph", &g_Cheats->bShowActivityGraph);
						ImGui::Checkbox("Game ESP", &g_Cheats->bESP); ImGui::SameLine(); ImGui::SetNextItemWidth(130.0f); ImGui::Combo("##EType", &g_Cheats->iESPType, "Text and Box only\0Text Only\0");
						ImGui::Checkbox("Show Sanity", &g_Cheats->bSanity);
					}ImGui::EndChild();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Mission Completer"))
				{
					ImGui::BeginChild("##MC", ImVec2(538, 115), false); {
						static int curSelectedIndex = NULL;
						if (g_Cheats->bSafeToRun) {
							__try {
								List_1_Mission* missionList = g_Cheats->thisMission->Fields.MissionInfo;
								if (missionList != NULL) {
									if (missionList->Fields.Items->ListOfMission[1]->Fields.isComplete &&
										missionList->Fields.Items->ListOfMission[2]->Fields.isComplete &&
										missionList->Fields.Items->ListOfMission[3]->Fields.isComplete) {
										ImGui::Text("No mission available.");
									}
									else {
										if (ImGui::BeginListBox("Click to complete!", ImVec2(-FLT_MIN, 75)))
										{
											for (int i = 1; i < missionList->Fields.Size; i++)
											{
												const bool is_selected = (curSelectedIndex == i);
												if (missionList->Fields.Items->ListOfMission[i]->Fields.isComplete)
													continue;
												String* missionText = missionList->Fields.Items->ListOfMission[i]->Fields.MissionDetails->m_Text;
												std::string missionMessage = odUnityFunction::GetUTF8StringFromNETString(missionText);
												missionMessage.erase(missionMessage.begin(), missionMessage.begin() + 13);

												if (ImGui::Selectable(missionMessage.c_str(), is_selected)) {
													LogInstance.AddLog("%s\n", missionList->Fields.Items->ListOfMission[i]->klass->ClassName);
													odUnityFunction::hksMissionComplete(missionList->Fields.Items->ListOfMission[i]);
												}
											}
											ImGui::EndListBox();
										}
									}
								}
								else {
									ImGui::Text("No mission available.");
								}
							}
							__except (EXCEPTION_EXECUTE_HANDLER) {
								LogInstance.AddLog("MC : %p\n", GetExceptionCode());
							}
						}
						else {
							ImGui::Text("Waiting for game to start.");
						}
					}ImGui::EndChild();
					ImGui::EndTabItem();
				}
				if (ImGui::BeginTabItem("Extras"))
				{
					ImGui::BeginChild("##Extra", ImVec2(538, 115), false); {
						//ImGui::Checkbox("Enable Phrase Recognizer ( Warning : Unstable )", &g_Cheats->bEnableSpeechRec);
						__try {
							if (g_Cheats->bSafeToRun) {
								ImGui::Checkbox("Unlimited Stamina", &g_Cheats->bUnlimitedStamina);
								if (g_Cheats->thisLevel->Fields.curGameController->Fields.myPlayer->Fields.player->Fields.FlashLight) {
									ImGui::SetNextItemWidth(120.0f); ImGui::SliderFloat("FlashLight Intensity", &g_Cheats->fFlashLightIntensity, 0.100f, 15.0f); ImGui::SameLine(); ImGui::SetNextItemWidth(120.0f); ImGui::SliderFloat("FlashLight Angle", &g_Cheats->fFlashLightAngle, 50.0f, 105.0f);
									if (ImGui::Button("Set Flashlight Setting")) {
										if (g_Cheats->fFlashLightIntensity >= 16.0f) {
											g_Cheats->fFlashLightIntensity = 15.0f;
										}
										if (g_Cheats->fFlashLightAngle >= 106.0f) {
											g_Cheats->fFlashLightAngle = 105.0f;
										}
										Light_Set_Intensity(g_Cheats->thisLevel->Fields.curGameController->Fields.myPlayer->Fields.player->Fields.FlashLight->Fields.HeadLight, g_Cheats->fFlashLightIntensity, NULL);
										Light_Set_Intensity(g_Cheats->thisLevel->Fields.curGameController->Fields.myPlayer->Fields.player->Fields.FlashLight->Fields.inventoryLight, g_Cheats->fFlashLightIntensity, NULL);
										Light_set_spotAngle(g_Cheats->thisLevel->Fields.curGameController->Fields.myPlayer->Fields.player->Fields.FlashLight->Fields.HeadLight, g_Cheats->fFlashLightAngle, NULL);
										Light_set_spotAngle(g_Cheats->thisLevel->Fields.curGameController->Fields.myPlayer->Fields.player->Fields.FlashLight->Fields.inventoryLight, g_Cheats->fFlashLightAngle, NULL);
									}
								}
							}
							else {
								ImGui::Text("Waiting for game to start.");
							}
						}
						__except (EXCEPTION_EXECUTE_HANDLER) {
							LogInstance.AddLog("Error : %p \n", GetExceptionCode());
						}
					}ImGui::EndChild();
					ImGui::EndTabItem();
				}

				ImGui::EndTabBar();
			}
			ImGui::Checkbox("Show Debug", &g_Cheats->bShowDebug);
			ImGui::Spacing(); ImGui::Spacing();
			ImGui::Separator();
			ImGui::Text(_c("This is a freeware, if You pay for it demand a refund!"));
			ImGui::Text(_c(u8"这辅助器是免费分享的, 也只会在UnknownCheats.Me上分享. 如果你在其他地方下载我无法保证是否被安装了病毒!"));
			ImGui::Text(_c("UnknownCheats.Me@Astron51"));
		}ImGui::End();
	}

	if (g_Cheats->bShowMissionDetails) {
		ShowMissionDetails(&g_Cheats->bShowMissionDetails);
	}

	if (g_Cheats->bShowActivityGraph) {
		ShowGhostGraph(&g_Cheats->bShowActivityGraph);
	}

	if (g_Cheats->bSanity) {
		ShowSanityDetails(&g_Cheats->bSanity);
	}

	if (g_Cheats->bShowDebug) {
		__try {
			EngineDebug::ShowLogWindow(&g_Cheats->bShowDebug, LogInstance);
			//EngineDebug::DebugOverlay(&g_Cheats->bShowDebug);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LogInstance.AddLog("Error : %p \n", GetExceptionCode());
		}
	}

	BeginScene();
	DrawScene();
	EndScene();

	ImGui::EndFrame();
	ImGui::Render();
	g_Renderer->g_pContext->OMSetRenderTargets(1, &g_Renderer->g_pTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void RendererRJ::BeginScene() {
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::Begin("BackBuffer", reinterpret_cast<bool*>(true), ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);
}

void RendererRJ::DrawScene() {
	// Draw Text and Line using ImGui
	if (g_Cheats->bSafeToRun &&
		g_Cheats->thisGhost &&
		g_Cheats->thisLevel &&
		g_Cheats->thisEMF &&
		g_Cheats->thisEvidence) {
		__try {
			if (g_Cheats->bESP) {
				auto mGhostAIFields = g_Cheats->thisGhost->Fields;
				auto mGhostInfoFields = mGhostAIFields.CurrentGhostInfo->Fields;
				auto mGhostDetails = mGhostInfoFields.curGhostTraits;
				auto instEvidence = g_Cheats->thisEvidence->Fields;
				auto instBone = instEvidence.bone;
				auto instFuseBox = g_Cheats->thisLevel->Fields.Breaker;
				auto FuseBoxOnScreen = Camera_WorldToScreenPoint(Camera_Get_Main(NULL), Transform_get_position(instFuseBox->Fields.Location, NULL), NULL);
				auto BoneOnScreen = Camera_WorldToScreenPoint(Camera_Get_Main(NULL), Transform_get_position(Component_1_get_transform((void*)instBone, NULL), NULL), NULL);
				auto OuijaOnScreen = Camera_WorldToScreenPoint(Camera_Get_Main(NULL), Transform_get_position(instEvidence.OuijaBoard->Fields.evidenceTransform, NULL), NULL);
				auto GhostOnScreen = Camera_WorldToScreenPoint(Camera_Get_Main(NULL), Transform_get_position(mGhostAIFields.Location, NULL), NULL);
				auto GhostWorldPosition = Camera_WorldToScreenPoint(Camera_Get_Main(NULL), Transform_get_position(Component_1_get_transform((void*)g_Cheats->thisGhost, NULL), NULL), NULL);
				float ghostNeckMid = ImGui::GetIO().DisplaySize.y - GhostWorldPosition.y;
				float ghostBottomMid = ImGui::GetIO().DisplaySize.y - GhostOnScreen.y;
				float ghostTopMid = ghostNeckMid - (ghostBottomMid - ghostNeckMid) / 5;
				float boxHeight = (ghostBottomMid - ghostTopMid);
				float boxWidth = boxHeight / 1.8f;
				if (g_Cheats->bHunting)
				{
					DrawTextExc(g_Renderer->fDefault, std::string("Ghost is Hunting"), ImVec2(ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 1.5f), 30, true, ImVec4(255, 255, 000, 000));
				}
				switch (g_Cheats->iESPType) {
				case 0:
					// Box
					if (GhostOnScreen.z > 0.0f)
					{
						ImVec4 curColor = ImVec4(255, 000, 255, 255);
						if (g_Cheats->bHunting)
							curColor = ImVec4(255, 255, 000, 000);
						DrawBox(ImVec2(GhostOnScreen.x - (boxWidth / 2.0f), ghostNeckMid), boxWidth, boxHeight, curColor, 1.0);
					}
				case 1:
					// Object Name
					if (GhostOnScreen.z > 0.0f) {
						DrawTextExc(g_Renderer->fDefault, odUnityFunction::GetUTF8StringFromNETString(mGhostDetails.GhostName), ImVec2(GhostOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (GhostOnScreen.y + 1.0f)), 15, false);
					}
					if (FuseBoxOnScreen.z > 0.0f) {
						std::string fText = std::string("Fusebox : Off");
						if (g_Cheats->thisLevel->Fields.Breaker->Fields.isTurnedOn)
							fText = std::string("Fusebox : On");
						else
							fText = std::string("Fusebox : Off");
						DrawTextExc(g_Renderer->fDefault, fText, ImVec2(FuseBoxOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (FuseBoxOnScreen.y + 1.0f)), 15, false);
					}
					if (BoneOnScreen.z > 0.0f) {
						DrawTextExc(g_Renderer->fDefault, std::string("Bone"), ImVec2(BoneOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (BoneOnScreen.y + 1.0f)), 15, false);
					}
					if (OuijaOnScreen.z > 0.0f) {
						DrawTextExc(g_Renderer->fDefault, std::string("Ouija Board"), ImVec2(OuijaOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (OuijaOnScreen.y + 1.0f)), 15, false);
					}
					break;
				default:
					break;
				}
				auto ListEMF = g_Cheats->thisEMF->Fields.EMFArray->Fields;
				for (int i = NULL; i < ListEMF.Size; i++) {
					auto EMFOnScreen = Camera_WorldToScreenPoint(Camera_Get_Main(NULL), Transform_get_position(Component_1_get_transform((void*)ListEMF.Items->Vector[i], NULL), NULL), NULL);
					if (EMFOnScreen.z > 0.0f) {
						switch (ListEMF.Items->Vector[i]->Fields.EMFType) {
						case EEMFType::GhostAppeared:
							DrawTextExc(g_Renderer->fDefault, std::string("EMFs"), ImVec2(EMFOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (EMFOnScreen.y + 1.0f)), 15, false);
							break;
						case EEMFType::GhostEvidence:
							DrawTextExc(g_Renderer->fDefault, std::string("EMFs"), ImVec2(EMFOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (EMFOnScreen.y + 1.0f)), 15, false);
							break;
						case EEMFType::GhostInteraction:
							DrawTextExc(g_Renderer->fDefault, std::string("EMFs"), ImVec2(EMFOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (EMFOnScreen.y + 1.0f)), 15, false);
							break;
						case EEMFType::GhostThrowing:
							DrawTextExc(g_Renderer->fDefault, std::string("EMFs"), ImVec2(EMFOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (EMFOnScreen.y + 1.0f)), 15, false);
							break;
						default:
							DrawTextExc(g_Renderer->fDefault, std::string("EMFs"), ImVec2(EMFOnScreen.x, (int32_t)ImGui::GetIO().DisplaySize.y - (EMFOnScreen.y + 1.0f)), 15, false);
							break;
						}
					}
				}
			}
			if (g_Cheats->thisLevel->Fields.curGameController->Fields.myPlayer->Fields.player->Fields.myStamina && g_Cheats->bUnlimitedStamina) {
				g_Cheats->thisLevel->Fields.curGameController->Fields.myPlayer->Fields.player->Fields.myStamina->Fields.Stamina = 3.0f;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {
			LogInstance.AddLog("Error on Draw : %p\n", GetExceptionCode());
		}
	}
}

void RendererRJ::EndScene() {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	window->DrawList->PushClipRectFullScreen();
	ImGui::End();
	ImGui::PopStyleColor();
}

float RendererRJ::DrawTextExc(ImFont* pFont, const std::string& text, const ImVec2& pos, float size, bool center, ImVec4& Color)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = Color.x;
	float r = Color.y;
	float g = Color.z;
	float b = Color.w;

	std::stringstream steam(text);
	std::string line;

	float y = 0.0f;
	int i = 0;

	while (std::getline(steam, line))
	{
		ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, line.c_str());

		if (center)
		{
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());

			window->DrawList->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}
		else
		{
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());
			window->DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, a / 255)), line.c_str());

			window->DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), line.c_str());
		}

		y = pos.y + textSize.y * (i + 1);
		i++;
	}

	return y;
}

void RendererRJ::DrawLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	float a = (color >> 24) & 0xff;
	float r = (color >> 16) & 0xff;
	float g = (color >> 8) & 0xff;
	float b = (color) & 0xff;

	window->DrawList->AddLine(from, to, ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
}

void RendererRJ::DrawBox(ImVec2 Point, float width, float height, ImVec4 color, float thickness) {
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	float a = color.x;
	float r = color.y;
	float g = color.z;
	float b = color.w;

	window->DrawList->AddLine(Point, ImVec2(Point.x + width, Point.y), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
	window->DrawList->AddLine(Point, ImVec2(Point.x, Point.y + height), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
	window->DrawList->AddLine(ImVec2(Point.x + width, Point.y + height), ImVec2(Point.x + width, Point.y), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
	window->DrawList->AddLine(ImVec2(Point.x + width, Point.y + height), ImVec2(Point.x, Point.y + height), ImGui::GetColorU32(ImVec4(r / 255, g / 255, b / 255, a / 255)), thickness);
}
