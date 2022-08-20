#include "Common.h"
#include "RendererRJ.h"

HRESULT GetDeviceAndCtxFromSwapchain(IDXGISwapChain* pSwapChain, ID3D11Device** ppDevice, ID3D11DeviceContext** ppContext)
{
	HRESULT ret = pSwapChain->GetDevice(__uuidof(ID3D11Device), (PVOID*)ppDevice);

	if (SUCCEEDED(ret))
		(*ppDevice)->GetImmediateContext(ppContext);

	return ret;
}

tIDXGISwapChainPresent CreateDummy()
{
	WNDCLASSEXA wc = { sizeof(WNDCLASSEX), CS_CLASSDC, dWndProc, 0L, 0L, GetModuleHandleA(NULL), NULL, NULL, NULL, NULL, "DX", NULL };
	RegisterClassExA(&wc);
	HWND hWnd = CreateWindowA("DX", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = 2;
	sd.BufferDesc.Height = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	D3D_FEATURE_LEVEL FeatureLevelsRequested = D3D_FEATURE_LEVEL_11_0;
	UINT numFeatureLevelsRequested = 1;
	D3D_FEATURE_LEVEL FeatureLevelsSupported;
	HRESULT hr;
	IDXGISwapChain* g_pSwapChain = 0;
	ID3D11Device* dev = 0;
	ID3D11DeviceContext* devcon = 0;
	if (FAILED(hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &FeatureLevelsRequested, numFeatureLevelsRequested, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &dev, &FeatureLevelsSupported, &devcon)))
	{
		LOG_F(ERROR,"Device Creation Failure");
		return NULL;
	}
	DWORD_PTR* pSwapChainVtable = NULL;
	pSwapChainVtable = (DWORD_PTR*)g_pSwapChain;
	pSwapChainVtable = (DWORD_PTR*)pSwapChainVtable[0];
	g_pSwapChain->Release();
	dev->Release();
	return (tIDXGISwapChainPresent)(DWORD_PTR)pSwapChainVtable[8];
}

HRESULT RetrieveFromModule(tIDXGISwapChainPresent oSwapChain)
{
	DWORD_PTR hDxgi = (DWORD_PTR)GetModuleHandle("dxgi.dll");
#if defined(ENV64BIT)
	oSwapChain = (tIDXGISwapChainPresent)((DWORD_PTR)hDxgi + 0x5070);
#elif defined (ENV32BIT)
	oSwapChain = (tIDXGISwapChainPresent)((DWORD_PTR)hDxgi + 0x10230);
#endif
	return S_OK;
}

LRESULT CALLBACK dWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

BOOL bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

uintptr_t  FindPattern(uintptr_t  dwAddress, DWORD dwLen, BYTE* bMask, char* szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
	{
		if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
		{
			return (uintptr_t)(dwAddress + i);
		}
	}
	return 0;
}

std::vector<uintptr_t> FindPatternVector(uintptr_t dwAddress, int32_t iLimit, DWORD dwLen, BYTE* bMask, char* szMask) {
	std::vector<uintptr_t> tempResult;
	int CCount = NULL;
	tempResult.clear();
	for (DWORD i = NULL; i <= dwLen; i++) {
		if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
		{
			if (CCount <= iLimit)
				CCount++;
			else
				break;
			tempResult.push_back((uintptr_t)(dwAddress + i));
		}
	}
	return tempResult;
}