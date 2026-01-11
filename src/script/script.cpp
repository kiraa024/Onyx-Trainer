// Onyx-Trainer-Legacy (expansion from GTA5-ASI-MenuBase)
// © 2026 kiraa024
// MIT License

#define _CRT_SECURE_NO_WARNINGS

#include "script.h"

// MinHook
#include "../../ext/MinHook/MinHook.h"

// ImGui impl
#include "../../ext/ImGui/imgui_impl_win32.h"
#include "../../ext/ImGui/imgui_impl_dx11.h"

// Theme
#include "../theme/themes.h"

// Features
#include "../features/Player/player.h"

#pragma comment(lib, "d3d11.lib")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

namespace Overlay
{
    ImFont* verdanaFont = nullptr;
    HWND hwnd = nullptr;
    WNDPROC originalWndProc = nullptr;

    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    ID3D11RenderTargetView* rtv = nullptr;

    PresentFn originalPresent = nullptr;

    bool initialized = false;
    bool menuVisible = false;
    bool g_ShowWatermark = true;

    // Init Fonts
    void InitImGuiFonts()
    {
        ImGuiIO& io = ImGui::GetIO();
        verdanaFont = io.Fonts->AddFontFromFileTTF(
            "C:/Windows/Fonts/verdana.ttf", 15.0f
        );
        if (!verdanaFont)
            verdanaFont = io.Fonts->AddFontDefault();
    }

    // Blocking Input so you cant Move Player around with Mouse. (optional, just makes it more UX Friendly.)
    void BlockMouseInput()
    {
        invoke<Void>(0xFE99B66D079CF6BC, 0, 1, true);
        invoke<Void>(0xFE99B66D079CF6BC, 0, 2, true);
        invoke<Void>(0xFE99B66D079CF6BC, 0, 24, true);
        invoke<Void>(0xFE99B66D079CF6BC, 0, 25, true);
        invoke<Void>(0xFE99B66D079CF6BC, 0, 68, true);
        invoke<Void>(0xFE99B66D079CF6BC, 0, 69, true);
    }

    LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        if (menuVisible &&
            ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;

        return CallWindowProc(originalWndProc, hWnd, msg, wParam, lParam);
    }

    void SetupRenderTarget(IDXGISwapChain* swapChain)
    {
        ID3D11Texture2D* backBuffer = nullptr;
        swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
            (void**)&backBuffer);

        device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
        backBuffer->Release();
    }

    // HK Present
    long __stdcall HookedPresent(
        IDXGISwapChain* swapChain,
        UINT interval,
        UINT flags)
    {
        if (!initialized)
        {
            if (SUCCEEDED(swapChain->GetDevice(
                __uuidof(ID3D11Device),
                (void**)&device)))
            {
                device->GetImmediateContext(&context);

                DXGI_SWAP_CHAIN_DESC desc;
                swapChain->GetDesc(&desc);
                hwnd = desc.OutputWindow;

                SetupRenderTarget(swapChain);
                originalWndProc = (WNDPROC)SetWindowLongPtr(
                    hwnd, GWLP_WNDPROC, (LONG_PTR)WindowProc
                );

                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                DefaultTheme();

                ImGuiIO& io = ImGui::GetIO();
                io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

                ImGui_ImplWin32_Init(hwnd);
                ImGui_ImplDX11_Init(device, context);

                InitImGuiFonts();
                initialized = true;
            }
        }

        // Initialize Tabs/Features
        Features::PlayerUpdate();
        //Features::VehicleUpdate(); // possible expansion
        //Features::WeaponUpdate();  // possible expansion
        //Features::WorldUpdate();   // possible expansion

        if (GetAsyncKeyState(VK_F4) & 1)
            menuVisible = !menuVisible;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        if (menuVisible)
            BlockMouseInput();

        ImGuiIO& io = ImGui::GetIO();
        io.WantCaptureMouse = menuVisible;
        io.WantCaptureKeyboard = menuVisible;
        io.MouseDrawCursor = menuVisible;

        // Menu
        if (menuVisible)
        {
            ImGui::PushFont(verdanaFont);
            ImGui::SetNextWindowSize(ImVec2(650, 550), ImGuiCond_Once);
            ImGui::Begin("Onyx Trainer", nullptr,
                ImGuiWindowFlags_NoCollapse);

            // Player
            ImGui::Separator();

            ImGui::Checkbox("God Mode", &Features::g_GodMode);
            ImGui::Checkbox("Invisible Player (Local)", &Features::g_InvisiblePlayer);
            ImGui::TextDisabled("You could add Categories or more Functions/Features here.");

            ImGui::Separator();

            // Settings
            ImGui::Checkbox("Show Menu Watermark", &g_ShowWatermark);
            if (ImGui::Button("Unload DLL"))
            {
                CreateThread(nullptr, 0, [](LPVOID) -> DWORD
                    {
                        MH_DisableHook(originalPresent);
                        MH_Uninitialize();

                        ImGui_ImplDX11_Shutdown();
                        ImGui_ImplWin32_Shutdown();
                        ImGui::DestroyContext();

                        if (rtv) rtv->Release();
                        if (context) context->Release();
                        if (device) device->Release();

                        SetWindowLongPtr(hwnd, GWLP_WNDPROC,
                            (LONG_PTR)originalWndProc);

                        FreeLibraryAndExitThread(
                            GetModuleHandle(nullptr), 0);
                        return 0;
                    }, nullptr, 0, nullptr);
            }
            ImGui::Separator();

            ImGui::End();
            ImGui::PopFont();
        }

        // Watermark
        if (g_ShowWatermark)
        {
            ImGui::SetNextWindowPos({ 15,15 }, ImGuiCond_Always);
            ImGui::Begin("##wm", nullptr,
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoInputs |
                ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::Text("Onyx Trainer Base | v1.00");
            ImGui::End();
        }

        ImGui::Render();
        context->OMSetRenderTargets(1, &rtv, nullptr);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        return originalPresent(swapChain, interval, flags);
    }
}
