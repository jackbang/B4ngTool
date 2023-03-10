// dear imgui: "null" example application
// (compile and link imgui, create context, run headless with NO INPUTS, NO GRAPHICS OUTPUT)
// This is useful to test building, but you cannot interact with anything here!
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <stdio.h>
#include <d3d11.h>
#include <tchar.h>

#include <iostream>
#include <Windows.h>
#include <winuser.h>
#include <memory>
#include <cstdint>
#include <string>
#include <tlhelp32.h>
#include <vector>
#include <thread>
#include <mutex>
#include <time.h>
#include <math.h>

#include "UserPart/instruction.h"
#include "UserPart/mhfunction.h"
#include "UserPart/mhui_func.h"

// Data
static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Main code
int main(int, char**)
{
  // Create application window
  //ImGui_ImplWin32_EnableDpiAwareness();
  WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("B4ngGUI"), NULL };
  ::RegisterClassEx(&wc);
  HWND hwnd = ::CreateWindow(wc.lpszClassName, _T("B4ngTool"), WS_OVERLAPPEDWINDOW, 100, 100, 600, 800, NULL, NULL, wc.hInstance, NULL);

  // Initialize Direct3D
  if (!CreateDeviceD3D(hwnd))
  {
    CleanupDeviceD3D();
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 1;
  }

  // Show the window
  ::ShowWindow(hwnd, SW_SHOWDEFAULT);
  ::UpdateWindow(hwnd);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer backends
  ImGui_ImplWin32_Init(hwnd);
  ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

  // Load Fonts
  // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
  // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
  // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
  // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
  // - Read 'docs/FONTS.md' for more instructions and details.
  // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
  //io.Fonts->AddFontDefault();
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
  //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
  //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
  //IM_ASSERT(font != NULL);
  io.Fonts->AddFontFromFileTTF("../../misc/fonts/hkyt.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());

  // Our state
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // windows set
  std::string name_list[6] = { "window1", "window2", "window3", "window4", "window5", "window6" };
  bool bring_to_front[6] = { false, false, false, false, false, false };
  MH_BASE_ADDRESS base_address_list[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
  MHMAIN_TEMP_DATA temp_data[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
  uint32_t target_x[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
  uint32_t target_y[6] = { NULL, NULL, NULL, NULL, NULL, NULL };
  std::vector<CHARACTER_INFO> NPC_list_1;
  std::vector<CHARACTER_INFO> NPC_list_2;
  std::vector<CHARACTER_INFO> NPC_list_3;
  std::vector<CHARACTER_INFO> NPC_list_4;
  std::vector<CHARACTER_INFO> NPC_list_5;
  std::vector<CHARACTER_INFO> NPC_list_6;
  // Main loop
  bool done = false;
  while (!done)
  {
    // Poll and handle messages (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    MSG msg;
    while (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
    {
      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
      if (msg.message == WM_QUIT)
        done = true;
    }
    if (done)
      break;

    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    //if (show_demo_window)
    //  ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.

    static float f = 0.0f;
    static int counter = 0;

    // main page

    PWINDOWS_HANDLE mhtab_windows_handle = new WINDOWS_HANDLE();
    get_all_process_id("mhmain.exe", mhtab_windows_handle->main_process_id_list);
    mhmain_window_detection(mhtab_windows_handle);
    for (size_t i = 0; i < mhtab_windows_handle->size; i++)
    {
      ImGui::Begin(name_list[i].c_str());
      ImGui::Text(u8"%s", mhtab_windows_handle->main_process_title[i].c_str());
      ImGui::Text("PID:%d", mhtab_windows_handle->main_process_id_list[i]);
      if (ImGui::Button(u8"????????", ImVec2(100, 20)))
      {
        SetForegroundWindow(mhtab_windows_handle->main_hwnd_list[i]);
      }

      ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 200);
      ImGui::InputScalar(u8"X????", ImGuiDataType_U32, &target_x[i], NULL, NULL, "%u");
      ImGui::InputScalar(u8"Y????", ImGuiDataType_U32, &target_y[i], NULL, NULL, "%u");
      ImGui::PopTextWrapPos();

      tagPOINT mouse_p;
      char quick_mission_content[1000];
      char click_NPC_name[20];
      std::vector<CHARACTER_INFO>* temp_npc_list_ptr = NULL;

      get_game_mouse_pos(mhtab_windows_handle->main_process_id_list[i], &(temp_data[i].game_mouse_x), &(temp_data[i].game_mouse_y));
      get_map_info(mhtab_windows_handle->main_process_id_list[i],  
                &(temp_data[i].map_index), &(temp_data[i].map_size_x), &(temp_data[i].map_size_y), 
                &(temp_data[i].windows_size_x), &(temp_data[i].windows_size_y), 
                &(temp_data[i].windows_pos_x), &(temp_data[i].windows_pos_y));
      get_player_pos(mhtab_windows_handle->main_process_id_list[i], &(temp_data[i].player_x), &(temp_data[i].player_y), &(temp_data[i].windows_moving));
      get_click_NPC_name(mhtab_windows_handle->main_process_id_list[i], click_NPC_name);
      initial_base_address(mhtab_windows_handle->main_process_id_list[i], mhtab_windows_handle->main_hwnd_list[i], &base_address_list[i]);
      GetCursorPos(&mouse_p);
      if (temp_data[i].game_mouse_x < 0 || temp_data[i].game_mouse_x > 1200)
      {
        temp_data[i].game_mouse_x = mouse_p.x - mhtab_windows_handle->windows_rect[i].left;
      }

      if (temp_data[i].game_mouse_y < 0 || temp_data[i].game_mouse_y > 1200)
      {
        temp_data[i].game_mouse_y = mouse_p.y - mhtab_windows_handle->windows_rect[i].top - 25;
      }

      if (ImGui::Button(u8"????????", ImVec2(100, 20)))
      {
        std::thread mouse_move_thread(mouse_move, &target_x[i], &target_y[i], &temp_data[i], mhtab_windows_handle->main_hwnd_list[i], mhtab_windows_handle->windows_rect[i]);
        mouse_move_thread.detach();
      }

      uint32_t distance = sqrt(pow((int32_t)temp_data[i].player_x - (int32_t)temp_data[i].temp_player_x, 2) +
                               pow((int32_t)temp_data[i].player_y - (int32_t)temp_data[i].temp_player_y, 2));

      switch (i)
      {
      case 0:
        temp_npc_list_ptr = &NPC_list_1;
        break;
      case 1:
        temp_npc_list_ptr = &NPC_list_2;
        break;
      case 2:
        temp_npc_list_ptr = &NPC_list_3;
        break;
      case 3:
        temp_npc_list_ptr = &NPC_list_4;
        break;
      case 4:
        temp_npc_list_ptr = &NPC_list_5;
        break;
      case 5:
        temp_npc_list_ptr = &NPC_list_6;
        break;
      default:
        break;
      }

      if (distance > 100)
      {
        temp_data[i].temp_player_x = temp_data[i].player_x;
        temp_data[i].temp_player_y = temp_data[i].player_y;
        get_nearby_NPC(mhtab_windows_handle->main_process_id_list[i], temp_npc_list_ptr);
        
      }
      else
      {
        update_nearby_NPC(mhtab_windows_handle->main_process_id_list[i], temp_npc_list_ptr);
      }
      


      ImGui::Text(u8"(%d, %d) ????????(%d, %d)", mhtab_windows_handle->windows_rect[i].left, mhtab_windows_handle->windows_rect[i].top, temp_data[i].windows_size_x, temp_data[i].windows_size_y);
      ImGui::Text(u8"??????????(%d, %d) ??????????????(%d, %d)", 
            temp_data[i].game_mouse_x, temp_data[i].game_mouse_y, 
            mouse_p.x - mhtab_windows_handle->windows_rect[i].left, mouse_p.y - mhtab_windows_handle->windows_rect[i].top - 25);
      ImGui::Text(u8"??????%d, ??????????(%d, %d)", temp_data[i].map_index, temp_data[i].map_size_x, temp_data[i].map_size_y);
      ImGui::Text(u8"??????????(%d, %d) ??????????(%d, %d) ????????????%d", 
        (uint32_t)temp_data[i].player_x/20, (uint32_t)(temp_data[i].map_size_y - 10 - temp_data[i].player_y)/20,
        (uint32_t)temp_data[i].windows_pos_x / 20, (uint32_t)(temp_data[i].map_size_y - 10 - temp_data[i].windows_pos_y) / 20, temp_data[i].windows_moving);
      ImGui::Text(u8"??????NPC????%s", click_NPC_name);
      ImGui::Text(u8"??????????????????????????????????????????????????????????????????");
      
      for (size_t idx = 0; idx < temp_npc_list_ptr->size(); idx++)
      {
        ImGui::Text(u8"%s ??????(%d, %d) ??????(%d, %d)", 
          (*temp_npc_list_ptr)[idx].character_name, 
          (*temp_npc_list_ptr)[idx].screen_pos_x, (*temp_npc_list_ptr)[idx].screen_pos_y, 
          (*temp_npc_list_ptr)[idx].world_pos_x, (*temp_npc_list_ptr)[idx].world_pos_y);
      }

      ImGui::Text(u8"??????????????????????????????????????????????????????????????????");
      mhmain_base_address_table(mhtab_windows_handle->main_process_id_list[i], &base_address_list[i]);
      ImGui::Text(u8"??????????????????????????????????????????????????????????????????");
      get_quick_mission_content(mhtab_windows_handle->main_process_id_list[i], base_address_list[i].quick_mission_address, quick_mission_content);
      ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + 450);
      ImGui::Text(u8"??????????");
      ImGui::Text(u8"%s", quick_mission_content);
      ImGui::PopTextWrapPos();
      ImGui::End();

      //free memory
      //free(quick_mission_content);
    }


    // 3. Show another simple window.

    // Rendering
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
    g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    g_pSwapChain->Present(1, 0); // Present with vsync
    //g_pSwapChain->Present(0, 0); // Present without vsync
  }

  // Cleanup
  ImGui_ImplDX11_Shutdown();
  ImGui_ImplWin32_Shutdown();
  ImGui::DestroyContext();

  CleanupDeviceD3D();
  ::DestroyWindow(hwnd);
  ::UnregisterClass(wc.lpszClassName, wc.hInstance);

  return 0;
}

// Helper functions


bool CreateDeviceD3D(HWND hWnd)
{
  // Setup swap chain
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 2;
  sd.BufferDesc.Width = 0;
  sd.BufferDesc.Height = 0;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hWnd;
  sd.SampleDesc.Count = 1;
  sd.SampleDesc.Quality = 0;
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  UINT createDeviceFlags = 0;
  //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
  D3D_FEATURE_LEVEL featureLevel;
  const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
  if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
    return false;

  CreateRenderTarget();
  return true;
}

void CleanupDeviceD3D()
{
  CleanupRenderTarget();
  if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
  if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
  if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

void CreateRenderTarget()
{
  ID3D11Texture2D* pBackBuffer;
  g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
  pBackBuffer->Release();
}

void CleanupRenderTarget()
{
  if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    return true;

  switch (msg)
  {
  case WM_SIZE:
    if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
    {
      CleanupRenderTarget();
      g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
      CreateRenderTarget();
    }
    return 0;
  case WM_SYSCOMMAND:
    if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
      return 0;
    break;
  case WM_DESTROY:
    ::PostQuitMessage(0);
    return 0;
  }
  return ::DefWindowProc(hWnd, msg, wParam, lParam);
}