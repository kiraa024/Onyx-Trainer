// Onyx-Trainer-Legacy (expansion from GTA5-ASI-MenuBase)
// © 2026 kiraa024
// MIT License

#pragma once
#include <Windows.h>
#include <d3d11.h>

// ImGui
#include "../../ext/ImGui/imgui.h"

// Forward declare ImFont
struct ImFont;

// ScriptHookV
#include "../../ext/ScriptHookV/script.h"
#include "../../ext/ScriptHookV/natives.h"

namespace Overlay
{
    // Globals (render / window)
    extern ImFont* verdanaFont;
    extern HWND hwnd;
    extern WNDPROC originalWndProc;

    extern ID3D11Device* device;
    extern ID3D11DeviceContext* context;
    extern ID3D11RenderTargetView* rtv;

    // State
    extern bool initialized;
    extern bool menuVisible;
    extern bool g_ShowWatermark;
    extern bool g_ShowInjectMessage;
    extern DWORD g_InjectMessageStartTime;

    // DX hook typedef
    using PresentFn = long(__stdcall*)(IDXGISwapChain*, UINT, UINT);
    extern PresentFn originalPresent;

    // Functions
    void InitImGuiFonts();
    void BlockMouseInput();
    void SetupRenderTarget(IDXGISwapChain* swapChain);

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    long __stdcall HookedPresent(IDXGISwapChain* swapChain, UINT interval, UINT flags);
}