// Onyx-Trainer-Legacy (expansion from GTA5-ASI-MenuBase)
// © 2026 kiraa024
// MIT License

#include <Windows.h>
#include <d3d11.h>

// MinHook
#include "../ext/MinHook/MinHook.h"

#include "script/script.h"

#if _WIN64
#pragma comment(lib, "ext/MinHook/libMinHook.x64.lib")
#else
#pragma comment(lib, "ext/MinHook/libMinHook.x86.lib")
#endif

namespace Overlay
{
    PresentFn GetPresentFunction()
    {
        DXGI_SWAP_CHAIN_DESC desc{};
        desc.BufferCount = 1;
        desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        desc.OutputWindow = GetDesktopWindow();
        desc.SampleDesc.Count = 1;
        desc.Windowed = TRUE;

        ID3D11Device* dev = nullptr;
        IDXGISwapChain* sc = nullptr;
        D3D_FEATURE_LEVEL lvl = D3D_FEATURE_LEVEL_11_0;

        if (D3D11CreateDeviceAndSwapChain(
            nullptr, D3D_DRIVER_TYPE_HARDWARE,
            nullptr, 0, &lvl, 1,
            D3D11_SDK_VERSION, &desc,
            &sc, &dev, nullptr, nullptr) == S_OK)
        {
            void** vt = *(void***)sc;
            PresentFn fn = (PresentFn)vt[8];

            sc->Release();
            dev->Release();
            return fn;
        }
        return nullptr;
    }

    DWORD WINAPI InitThread(LPVOID)
    {
        MH_Initialize();

        auto present = GetPresentFunction();
        if (present)
        {
            MH_CreateHook(present, &HookedPresent,
                (void**)&originalPresent);
            MH_EnableHook(present);
        }

        while (!(GetAsyncKeyState(VK_END) & 0x8000))
            Sleep(50);

        MH_DisableHook(present);
        MH_Uninitialize();

        FreeLibraryAndExitThread(
            GetModuleHandle(nullptr), 0);
    }
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0,
            Overlay::InitThread, nullptr, 0, nullptr);
    }
    return TRUE;
}
