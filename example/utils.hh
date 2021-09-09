#include <Windows.h>
#include <string>
#include <vector>
#include <Psapi.h>

#include <d3d11.h>
#pragma comment (lib, "d3d11.lib")

#include "settings.hh"
#include "spoofer.hh"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_internal.h"

#include "minhook/minhook.h"
#pragma comment (lib, "minhook.lib")

bool is_inital_release = false;
#define rva(addr, size) ((uintptr_t)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))

ID3D11Device* device = nullptr;
ID3D11DeviceContext* context = nullptr;
ID3D11RenderTargetView* render_target_view = nullptr;

HRESULT(*present_og)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
WNDPROC wndproc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT wndprocc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
        return true;
    return CallWindowProc(wndproc, hWnd, uMsg, wParam, lParam);
}

float width = 0;
float height = 0;

namespace utils
{
	uintptr_t uworld;
	uintptr_t worldtoscreen;
	uintptr_t local_pawn;
	uintptr_t player_controller;

	ImGuiWindow& begin_scene();
	void end_scene(ImGuiWindow& window);
}

namespace offsets
{
	uint64_t game_instance = 0x180;
	uint64_t local_players = 0x38;
	uint64_t player_controller = 0x30;
	uint64_t acknowledged_pawn = 0x2A0;
	uint64_t levels = 0x138;
	uint64_t persistent_level = 0x30;
	uint64_t aactors = 0x98;
	uint64_t actor_count = 0xA0;
	uint64_t root_component = 0x130;
	uint64_t relative_loc = 0x11c;
	uint64_t mesh = 0x280;
	uint64_t player_state = 0x240;
	uint64_t cam_manager = 0x2B8;
	uint64_t team_index = 0xED0;
	uint64_t current_weapon = 0x600;
	uint64_t weapon_data = 0x378;
	uint64_t static_mesh = 0x480;
}

namespace color
{
	ImColor black = { 0, 0, 0 };
	ImColor blue = { 100, 100, 255 };
	ImColor white = { 255, 255, 255 };
	ImColor green = { 0, 255, 0 };
	ImColor red = { 255, 0, 0 };
}

namespace Scanners
{
    uintptr_t PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex = 0);
    uintptr_t PatternScan(const char* sSignature, size_t nSelectResultIndex = 0);
}

uintptr_t Scanners::PatternScan(uintptr_t pModuleBaseAddress, const char* sSignature, size_t nSelectResultIndex)
{
    static auto patternToByte = [](const char* pattern)
    {
        auto       bytes = std::vector<int>{};
        const auto start = const_cast<char*>(pattern);
        const auto end = const_cast<char*>(pattern) + strlen(pattern);

        for (auto current = start; current < end; ++current)
        {
            if (*current == '?')
            {
                ++current;
                if (*current == '?')
                    ++current;
                bytes.push_back(-1);
            }
            else {
                bytes.push_back(strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    const auto dosHeader = (PIMAGE_DOS_HEADER)pModuleBaseAddress;
    const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)pModuleBaseAddress + dosHeader->e_lfanew);

    const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
    auto       patternBytes = patternToByte(sSignature);
    const auto scanBytes = reinterpret_cast<std::uint8_t*>(pModuleBaseAddress);

    const auto s = patternBytes.size();
    const auto d = patternBytes.data();

    size_t nFoundResults = 0;

    for (auto i = 0ul; i < sizeOfImage - s; ++i)
    {
        bool found = true;

        for (auto j = 0ul; j < s; ++j)
        {
            if (scanBytes[i + j] != d[j] && d[j] != -1)
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            if (nSelectResultIndex != 0)
            {
                if (nFoundResults < nSelectResultIndex)
                {
                    nFoundResults++;
                    found = false;
                }
                else
                {
                    return reinterpret_cast<uintptr_t>(&scanBytes[i]);
                }
            }
            else
            {
                return reinterpret_cast<uintptr_t>(&scanBytes[i]);
            }
        }
    }

    return NULL;
}

uintptr_t Scanners::PatternScan(const char* sSignature, size_t nSelectResultIndex)
{
    static bool bIsSetted = false;

    static MODULEINFO info = { 0 };

    if (!bIsSetted)
    {
        GetModuleInformation(GetCurrentProcess(), GetModuleHandle(0), &info, sizeof(info));
        bIsSetted = true;
    }
    return PatternScan((uintptr_t)info.lpBaseOfDll, sSignature, nSelectResultIndex);
}

namespace SteamHelper
{
    uintptr_t GetSteamdModule()
    {
        std::string module = ("GameOverlayRenderer64.dll");
        return (uintptr_t)GetModuleHandleA(module.c_str());
    }

    void InsertHook(__int64 addr, __int64 func, __int64* orig)
    {
        static uintptr_t hook_addr;
        if (!hook_addr)
            hook_addr = Scanners::PatternScan(GetSteamdModule(), ("48 ? ? ? ? 57 48 83 EC 30 33 C0"));

        auto hook = ((__int64(__fastcall*)(__int64 addr, __int64 func, __int64* orig, __int64 smthng))(hook_addr));
        hook((__int64)addr, (__int64)func, orig, (__int64)1);
    }
}

namespace f_
{
    bool aim_key()
    {
        return GetAsyncKeyState(VK_RBUTTON);
    }

    void draw_line(float x, float y, float xx, float yy, ImColor color, int thickness)
    {ImGui::GetOverlayDrawList()->AddLine(ImVec2(x, y), ImVec2(xx, yy), color, thickness);}

    void draw_outlined_text(float x, float y, const char* text, ImColor color)
    {   
        ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y + 1), color::black, text);
        ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y - 1), color::black, text);
        ImGui::GetOverlayDrawList()->AddText(ImVec2(x + 1, y - 1), color::black, text);
        ImGui::GetOverlayDrawList()->AddText(ImVec2(x - 1, y + 1), color::black, text);
        ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), color, text); 
    }

    void mousemove(float tarx, float tary, float X, float Y, int smooth)
    {
        float ScreenCenterX = (X / 2);
        float ScreenCenterY = (Y / 2);
        float TargetX = 0;
        float TargetY = 0;

        if (tarx != 0)
        {
            if (tarx > ScreenCenterX)
            {
                TargetX = -(ScreenCenterX - tarx);
                TargetX /= smooth;
                if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
            }

            if (tarx < ScreenCenterX)
            {
                TargetX = tarx - ScreenCenterX;
                TargetX /= smooth;
                if (TargetX + ScreenCenterX < 0) TargetX = 0;
            }
        }

        if (tary != 0)
        {
            if (tary > ScreenCenterY)
            {
                TargetY = -(ScreenCenterY - tary);
                TargetY /= smooth;
                if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
            }

            if (tary < ScreenCenterY)
            {
                TargetY = tary - ScreenCenterY;
                TargetY /= smooth;
                if (TargetY + ScreenCenterY < 0) TargetY = 0;
            }
        }

        (mouse_event)(MOUSEEVENTF_MOVE, static_cast<DWORD>(TargetX), static_cast<DWORD>(TargetY), 0, 0);
    }
}