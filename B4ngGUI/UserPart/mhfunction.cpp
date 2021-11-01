#include "mhfunction.h"
#include <stdlib.h>
#include <time.h> 

#include "../misc/offsets/offsets.h"

void keyboard_input(WORD commond_key, WORD normal_key)
{
  if (commond_key == NULL)
  {
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));
    srand((unsigned int)time(NULL));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = normal_key;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

    uint32_t delay_time = rand() % 50 + 90;
    Sleep(delay_time);

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = normal_key;
    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
  }
  else
  {
    INPUT inputs[1] = {};
    ZeroMemory(inputs, sizeof(inputs));
    srand((unsigned int)time(NULL));

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = commond_key;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

    uint32_t delay_time = rand() % 20 + 5;
    Sleep(delay_time);

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = normal_key;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

    delay_time = rand() % 50 + 90;
    Sleep(delay_time);

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = normal_key;
    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));

    delay_time = rand() % 30 + 10;
    Sleep(delay_time);

    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = commond_key;
    inputs[0].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
  }
}

void initial_base_address(uint32_t process_id, HWND hwnd, PMH_BASE_ADDRESS base_address)
{
  if (base_address->player_IP_address == NULL)
  {
    uint32_t* address_list = (uint32_t*)malloc(2000 * sizeof(uint32_t));
    uint32_t address_list_length = 0;
    FindAddressByValue(process_id, 0, memory_start_address, memory_end_address, base_player_start_address, &address_list, &address_list_length);
    for (size_t i = 0; i < address_list_length; i++)
    {
      uint32_t feature_0x18 = Read<uint32_t>(process_id, address_list[i] + 0x18);
      uint32_t feature_0x1C = Read<uint32_t>(process_id, address_list[i] + 0x1C);
      uint32_t feature_0xDC = Read<uint32_t>(process_id, address_list[i] + 0xDC);
      if (feature_0x18 == player_IP_0x18_800x600 &&
        feature_0x1C == player_IP_0x1C_800x600 &&
        feature_0xDC == player_IP_0xDC_800x600)
      {
        base_address->player_IP_address = address_list[i];
        continue;
      }

      if (feature_0x18 == player_HP_0x18_800x600 &&
        feature_0x1C == player_HP_0x1C_800x600 &&
        feature_0xDC == player_HP_0xDC_800x600)
      {
        base_address->player_HP_address = address_list[i];
        continue;
      }

      if (feature_0x18 == player_MP_0x18_800x600 &&
          feature_0x1C == player_MP_0x1C_800x600)
      {
        base_address->player_MP_address = address_list[i];
        continue;
      }

      if (feature_0x18 == player_AP_0x18_800x600 &&
        feature_0x1C == player_AP_0x1C_800x600)
      {
        base_address->player_AP_address = address_list[i];
        continue;
      }

      if (feature_0x18 == player_EXP_0x18_800x600 &&
        feature_0x1C == player_EXP_0x1C_800x600)
      {
        base_address->player_EXP_address = address_list[i];
        continue;
      }

      if (feature_0x18 == pet_HP_0x18_800x600 &&
        feature_0x1C == pet_HP_0x1C_800x600)
      {
        base_address->pet_HP_address = address_list[i];
        continue;
      }

      if (feature_0x18 == pet_MP_0x18_800x600 &&
        feature_0x1C == pet_MP_0x1C_800x600)
      {
        base_address->pet_MP_address = address_list[i];
        continue;
      }

      if (feature_0x18 == pet_EXP_0x18_800x600 &&
        feature_0x1C == pet_EXP_0x1C_800x600)
      {
        base_address->pet_EXP_address = address_list[i];
        continue;
      }
    }
    free(address_list);
  }

  if (base_address->tab_address == NULL)
  {
    SetForegroundWindow(hwnd);
    keyboard_input(NULL, VK_TAB);

    uint32_t* address_list = (uint32_t*)malloc(2000 * sizeof(uint32_t));
    uint32_t address_list_length = 0;
    FindAddressByValue(process_id, 0, memory_start_address, memory_end_address, map_start_address, &address_list, &address_list_length);

    for (size_t i = 0; i < address_list_length; i++)
    {
      uint32_t feature_0x20 = Read<uint32_t>(process_id, address_list[i] + 0x20);
      uint32_t feature_0x24 = Read<uint32_t>(process_id, address_list[i] + 0x24);
      uint32_t feature_0x2C = Read<uint32_t>(process_id, address_list[i] + 0x2C);
      uint32_t feature_value = Read<uint32_t>(process_id, feature_0x2C);
      uint32_t feature_0x34 = Read<uint32_t>(process_id, address_list[i] + 0x34);

      if (feature_0x20 > 0 && feature_0x24 > 0 && feature_value == tab_0x2C_value_800x600 && feature_0x34 == 0)
      {
        base_address->tab_address = address_list[i];
        break;
      }
    }
    
    srand((unsigned int)time(NULL));
    uint32_t delay_time = rand() % 300 + 300;
    Sleep(delay_time);
    SetForegroundWindow(hwnd);
    keyboard_input(NULL, VK_TAB);

    free(address_list);
  }

  if (base_address->quick_mission_address == NULL)
  {
    SetForegroundWindow(hwnd);
    srand((unsigned int)time(NULL));
    keyboard_input(VK_MENU, 0x45); //ALT+E
    uint32_t delay_time = rand() % 50 + 50;
    Sleep(delay_time);
    keyboard_input(VK_MENU, 0x57); //ALT+W
    delay_time = rand() % 50 + 50;
    Sleep(delay_time);
    keyboard_input(VK_MENU, 0x51); //ALT+Q
    //delay_time = rand() % 50 + 50;
    //Sleep(delay_time);
    //keyboard_input(VK_MENU, 0x46); //ALT+F

    uint32_t* address_list = (uint32_t*)malloc(2000 * sizeof(uint32_t));
    uint32_t address_list_length = 0;
    FindAddressByValue(process_id, 0, memory_start_address, memory_end_address, alt_start_address, &address_list, &address_list_length);

    for (size_t i = 0; i < address_list_length; i++)
    {
      uint32_t feature_0x18 = Read<uint32_t>(process_id, address_list[i] + 0x18);
      uint32_t feature_0x1C = Read<uint32_t>(process_id, address_list[i] + 0x1C);
      uint32_t feature_0x20 = Read<uint32_t>(process_id, address_list[i] + 0x20);

      if (feature_0x18 == alt_e_ori_0x18_800x600 && feature_0x1C == alt_e_ori_0x1C_800x600)
      {
        base_address->alt_e_address = address_list[i];
        continue;
      }

      if (feature_0x18 == alt_w_0x18_800x600 && feature_0x1C == alt_w_0x1C_800x600 && feature_0x20 == alt_w_0x20_800x600)
      {
        base_address->alt_w_address = address_list[i];
        continue;
      }

      if (feature_0x18 == alt_q_new_0x18_800x600 && feature_0x20 == alt_q_new_0x20_800x600)
      {
        base_address->alt_q_new_address = address_list[i];
        continue;
      }

      if (feature_0x18 == alt_q_ori_0x18_800x600 && feature_0x20 == alt_q_ori_0x20_800x600)
      {
        base_address->alt_q_ori_address = address_list[i];
        continue;
      }

      if (feature_0x18 == quick_mission_0x18_800x600)
      {
        base_address->quick_mission_address = address_list[i];
        continue;
      }

      if (feature_0x18 == dialog_box_0x18_800x600)
      {
        base_address->dialog_box_address = address_list[i];
        continue;
      }

    }

    keyboard_input(VK_MENU, 0x45); //ALT+E
    delay_time = rand() % 50 + 50;
    Sleep(delay_time);
    keyboard_input(VK_MENU, 0x57); //ALT+W
    delay_time = rand() % 50 + 50;
    Sleep(delay_time);
    keyboard_input(VK_MENU, 0x51); //ALT+Q
    //delay_time = rand() % 50 + 50;
    //Sleep(delay_time);
    //keyboard_input(VK_MENU, 0x46); //ALT+F

    free(address_list);
  }
}

std::string string_to_utf8(std::string input)
{
  int size = MultiByteToWideChar(CP_ACP, MB_COMPOSITE, input.c_str(),
    input.length(), nullptr, 0);
  std::wstring utf16_str(size, '\0');
  MultiByteToWideChar(CP_ACP, MB_COMPOSITE, input.c_str(),
    input.length(), &utf16_str[0], size);

  int utf8_size = WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
    utf16_str.length(), nullptr, 0,
    nullptr, nullptr);
  std::string utf8_str(utf8_size, '\0');
  WideCharToMultiByte(CP_UTF8, 0, utf16_str.c_str(),
    utf16_str.length(), &utf8_str[0], utf8_size,
    nullptr, nullptr);

  return utf8_str;
}

bool mhmain_window_detection(PWINDOWS_HANDLE windows_handle)
{
  windows_handle->size = 0;
  for (size_t i = 0; i < 10; i++)
  {
    if (windows_handle->main_process_id_list[i])
    {
      std::vector <HWND> hwnd_list;
      GetAllWindowsFromProcessID(windows_handle->main_process_id_list[i], hwnd_list);
      for (size_t j = 0; j < hwnd_list.size(); j++)
      {
        PWINDOWINFO pwi = new WINDOWINFO();
        GetWindowInfo(hwnd_list[j], pwi);
        if (pwi->dwStyle < 0x80000000 && pwi->dwStyle >= 0x10000000)
        {
          windows_handle->main_hwnd_list[i] = hwnd_list[j];
          char window_title[100];
          GetWindowTextA(hwnd_list[j], window_title, 100);
          windows_handle->windows_rect[i].left = pwi->rcWindow.left;
          windows_handle->windows_rect[i].top = pwi->rcWindow.top;
          std::string window_title_utf8;
          window_title_utf8 = string_to_utf8(window_title);
          //windows_handle->main_process_title[i] = window_title_utf8;
          //windows_handle->main_process_title[i].resize(100);
          //windows_handle->main_process_title[i].reserve(100);
          windows_handle->main_process_title[i] = window_title_utf8;
          //memcpy(&(windows_handle->main_process_title[i]), window_title_utf8.c_str(), 100);
          //printf("%d %s\r\n", i, windows_handle->main_process_title+i);
          break;
        }
      }
      hwnd_list.clear();
      windows_handle->size += 1;
    }
  }
  return true;
}

uint32_t get_address_value(uint32_t process_id, uint32_t base_address, std::vector<uint32_t> offsets)
{
  uint32_t base_address_ptr = Read<uint32_t>(process_id, 0x11000000 + base_address);
  uint32_t address_0 = base_address_ptr;
  for (size_t i = 0; i < offsets.size(); i++)
  {
    uint32_t address_1 = Read<uint32_t>(process_id, address_0 + offsets[i]);
    address_0 = address_1;
  }
  return address_0;
}

void get_game_mouse_pos(uint32_t procees_id, int32_t* mouse_x, int32_t* mouse_y)
{
  *mouse_x = get_address_value(procees_id, mouse_base_address, mouse_position_offset_x);
  *mouse_y = get_address_value(procees_id, mouse_base_address, mouse_position_offset_y);
}

void get_map_info(uint32_t procees_id, int32_t* map_index, int32_t* map_size_x, int32_t* map_size_y, int32_t* windows_size_x, int32_t* windows_size_y, float* windows_pos_x, float* windows_pos_y)
{
  *map_index = get_address_value(procees_id, map_base_address, map_index_offset);
  *map_size_x = get_address_value(procees_id, map_base_address, map_size_offset_x);
  *map_size_y = get_address_value(procees_id, map_base_address, map_size_offset_y);
  *windows_size_x = get_address_value(procees_id, map_base_address, windows_size_offset_x);
  *windows_size_y = get_address_value(procees_id, map_base_address, windows_size_offset_y);

  uint32_t base = Read<uint32_t>(procees_id, 0x11000000 + map_base_address);
  *windows_pos_x = Read<float_t>(procees_id, base + windows_pos_offset_x[0]);
  *windows_pos_y = Read<float_t>(procees_id, base + windows_pos_offset_y[0]);
  
}

void get_player_pos(uint32_t procees_id, float* player_x, float* player_y, uint32_t* moving)
{
  *player_x = Read<float_t>(procees_id, 0x11000000 + player_base_address);
  *player_y = Read<float_t>(procees_id, 0x11000000 + player_base_address + 0x04);
  uint32_t base = Read<uint32_t>(procees_id, 0x11000000 + windows_moving_base_address);
  *moving = Read<uint32_t>(procees_id, base + windows_moving_offset[0]);
}

void get_click_NPC_name(uint32_t process_id, char* clicked_name)
{
  uint32_t clicked_name_base = get_address_value(process_id, click_NPC_base_address, click_NPC_offset);
  for (size_t i = 0; i < 20; i++)
  {
    clicked_name[i] = Read<char>(process_id, clicked_name_base + 0x14 + i);
  }
  std::string utf8_name = string_to_utf8(clicked_name);
  memcpy(clicked_name, utf8_name.c_str(), 20);
}

void get_quick_mission_content(uint32_t process_id, uint32_t quick_mission_address, char* mission_content)
{
  if (quick_mission_address == NULL)
  {
    return;
  }

  uint32_t mission_content_base_0 = Read<uint32_t>(process_id, quick_mission_address + 0x60);
  uint32_t mission_content_base_1 = Read<uint32_t>(process_id, mission_content_base_0 + 0x24);
  uint32_t mission_content_base_2 = Read<uint32_t>(process_id, mission_content_base_1 + 0x60);
  uint32_t mission_content_base_3 = Read<uint32_t>(process_id, mission_content_base_2 + 0x0);
  uint32_t mission_content_base_4 = Read<uint32_t>(process_id, mission_content_base_3 + 0x60);
  uint32_t mission_content_base_5 = Read<uint32_t>(process_id, mission_content_base_4 + 0xC);
  uint32_t mission_content_base_6 = Read<uint32_t>(process_id, mission_content_base_5 + 0x60);
  uint32_t mission_content_base_7 = Read<uint32_t>(process_id, mission_content_base_6 + 0x0);
  uint32_t mission_content_base_8 = Read<uint32_t>(process_id, mission_content_base_7 + 0x60);
  uint32_t mission_content_base_9 = Read<uint32_t>(process_id, mission_content_base_8 + 0x74);
  uint32_t mission_content_base_10 = Read<uint32_t>(process_id, mission_content_base_9 + 0x0);
  for (size_t i = 0; i < 1000; i++)
  {
    mission_content[i] = Read<char>(process_id, mission_content_base_9 + i);
  }

  //printf("%s\r\n", mission_content);
  std::string utf8_content = string_to_utf8(mission_content);
  memcpy(mission_content, utf8_content.c_str(), 1000);
}

