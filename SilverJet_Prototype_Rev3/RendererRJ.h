#pragma once
#include "Common.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

struct odDirectX {
	static HRESULT __fastcall Present(IDXGISwapChain*, UINT, UINT);
	static LRESULT CALLBACK hWndProc(HWND, UINT, WPARAM, LPARAM);
};

struct LogWindow
{
	ImGuiTextBuffer     Buf;
	ImGuiTextFilter     Filter;
	ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
	bool                AutoScroll;  // Keep scrolling if already at the bottom.

	LogWindow()
	{
		AutoScroll = true;
		Clear();
	}

	void Clear()
	{
		Buf.clear();
		LineOffsets.clear();
		LineOffsets.push_back(0);
	}

	void AddLog(const char* fmt, ...) IM_FMTARGS(2)
	{
		int old_size = Buf.size();
		va_list args;
		va_start(args, fmt);
		Buf.appendfv(fmt, args);
		va_end(args);
		for (int new_size = Buf.size(); old_size < new_size; old_size++)
			if (Buf[old_size] == '\n')
				LineOffsets.push_back(old_size + 1);
	}

	void    Draw(const char* title, bool* p_open = NULL)
	{
		if (!ImGui::Begin(title, p_open))
		{
			ImGui::End();
			return;
		}

		// Options menu
		if (ImGui::BeginPopup("Options"))
		{
			ImGui::Checkbox("Auto-scroll", &AutoScroll);
			ImGui::EndPopup();
		}

		// Main window
		if (ImGui::Button("Options"))
			ImGui::OpenPopup("Options");
		ImGui::SameLine();
		bool clear = ImGui::Button("Clear");
		ImGui::SameLine();
		bool copy = ImGui::Button("Copy");
		ImGui::SameLine();
		Filter.Draw("Filter", -100.0f);

		ImGui::Separator();
		ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

		if (clear)
			Clear();
		if (copy)
			ImGui::LogToClipboard();

		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
		const char* buf = Buf.begin();
		const char* buf_end = Buf.end();
		if (Filter.IsActive())
		{
			for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
			{
				const char* line_start = buf + LineOffsets[line_no];
				const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
				if (Filter.PassFilter(line_start, line_end))
					ImGui::TextUnformatted(line_start, line_end);
			}
		}
		else
		{
			ImGuiListClipper clipper;
			clipper.Begin(LineOffsets.Size);
			while (clipper.Step())
			{
				for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
				{
					const char* line_start = buf + LineOffsets[line_no];
					const char* line_end = (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
					ImGui::TextUnformatted(line_start, line_end);
				}
			}
			clipper.End();
		}
		ImGui::PopStyleVar();

		if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
			ImGui::SetScrollHereY(1.0f);

		ImGui::EndChild();
		ImGui::End();
	}
};

struct EngineDebug {
	static void DebugOverlay(bool*);
	static void ShowLogWindow(bool*, LogWindow);
};

class RendererRJ
{
	friend odDirectX;
	friend EngineDebug;
public:
	RendererRJ();
	bool bShowDemo = false;
	void PreReset();
	void PostReset();
	bool bInitBaseSet = false;
	static IDXGISwapChain* pSwapChain;
	void InitImGui(DXGI_SWAP_CHAIN_DESC);
	void OnPresent(ID3D11DeviceContext*);
	void BeginScene();
	void DrawScene();
	void EndScene();
	float DrawTextExc(ImFont*, const std::string&, const ImVec2&, float, bool, ImVec4 & = ImVec4(255, 255, 255, 255));
	void DrawLine(const ImVec2&, const ImVec2&, uint32_t, float);
	void DrawBox(ImVec2, float, float, ImVec4, float);
	bool bOpenMenu = false;
	bool bReady = false;
	ImFont* fDefault;
	ImFont* fJpnGlyph;
	ImFont* fSeguiEmoji;
	ImFont* fskeet;
	ImFont* fguns;
	DWORD dwVTable[4] = { 0 };
	DXGI_SWAP_CHAIN_DESC SwapChainDescription;
	ID3D11Texture2D* pBackBuffer;
	ID3D11DeviceContext* g_pContext;
	ID3D11Device* g_pDevice;
	ID3D11RenderTargetView* g_pTargetView;
	tIDXGISwapChainPresent oIDXGISwapChainPresent;
	DWORD* pSwapChainVTable;
	WNDPROC DefaultProc;
private:
};

inline LogWindow LogInstance;

inline RendererRJ* g_Renderer;