#include "mhfunction.h"

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

void get_game_mouse_pos(uint32_t procees_id, int32_t* mouse_x, int32_t* mouse_y)
{
  uint32_t mouse_base = Read<uint32_t>(procees_id, 0x11000000 + 0x1B787A4 + 0x2020);
  *mouse_x = Read<int32_t>(procees_id, mouse_base + 0x80);
  *mouse_y = Read<int32_t>(procees_id, mouse_base + 0x84);
}

void get_map_info(uint32_t procees_id, int32_t* map_index, int32_t* map_size_x, int32_t* map_size_y, int32_t* windows_size_x, int32_t* windows_size_y)
{
  uint32_t map_base = Read<uint32_t>(procees_id, 0x11000000 + 0x19F2030 + 0x2020);
  *map_index = Read<int32_t>(procees_id, map_base + 0x88 + 0x04);
  int32_t map_size_ptr = Read<int32_t>(procees_id, map_base + 0x58);
  *map_size_x = Read<int32_t>(procees_id, map_size_ptr + 0x10);
  *map_size_y = Read<int32_t>(procees_id, map_size_ptr + 0x14);
  *windows_size_x = Read<int32_t>(procees_id, map_base + 0xB8);
  *windows_size_y = Read<int32_t>(procees_id, map_base + 0xBC);
}

void get_player_pos(uint32_t procees_id, float* player_x, float* player_y)
{
  int32_t map_size_Y = 0;
  get_map_info(procees_id, NULL, NULL, &map_size_Y, NULL, NULL);
  *player_x = Read<float_t>(procees_id, 0x11000000 + 0x1B788E8 + 0x2020) / 20;
  float_t player_Y = Read<float_t>(procees_id, 0x11000000 + 0x1B788E8 + 4 + 0x2020);
  *player_y = (map_size_Y - 10 - player_Y) / 20;
}

void get_click_NPC_name(uint32_t process_id, char* clicked_name)
{
  uint32_t clicked_name_base = Read<uint32_t>(process_id, 0x11000000 + 0x01B941D4 + 0x2020);
  uint32_t clicked_name_base_1 = Read<uint32_t>(process_id, clicked_name_base + 0x2C);
  uint32_t clicked_name_base_2 = Read<uint32_t>(process_id, clicked_name_base_1 + 0x78);
  uint32_t clicked_name_base_3 = Read<uint32_t>(process_id, clicked_name_base_2 + 0x0);
  uint32_t clicked_name_base_4 = Read<uint32_t>(process_id, clicked_name_base_3 + 0x64);
  uint32_t clicked_name_base_5 = Read<uint32_t>(process_id, clicked_name_base_4 + 0xC);
  uint32_t clicked_name_base_6 = Read<uint32_t>(process_id, clicked_name_base_5 + 0x50);
  uint32_t clicked_name_base_7 = Read<uint32_t>(process_id, clicked_name_base_6 + 0x8);
  uint32_t clicked_name_base_8 = Read<uint32_t>(process_id, clicked_name_base_7 + 0x20);
  for (size_t i = 0; i < 20; i++)
  {
    *(clicked_name + i) = Read<char>(process_id, clicked_name_base_8 + 0x14 + i);
  }
}

void get_quick_mission_content(uint32_t process_id, char* mission_content)
{
  const ULONG start_address = 0x01F14000;
  const ULONG end_address = 0x4AD00000;
  const ULONG MISSION_base_value = 0x11F383E8;
  const ULONG quick_mission_pos_x = 639;

  uint32_t* ui_address_list = (uint32_t*)malloc(2000 * sizeof(uint32_t));
  uint32_t ui_address_list_length = 0;
  FindAddressByValue(process_id, 0, start_address, end_address, MISSION_base_value, &ui_address_list, &ui_address_list_length);

  for (size_t i = 0; i < ui_address_list_length; i++)
  {
    uint32_t feature_value = Read<uint32_t>(process_id, ui_address_list[i] + 0x18);
    //printf("the id %d\r\n", feature_value);
    if (feature_value == quick_mission_pos_x)
    {
      uint32_t mission_content_base_0 = Read<uint32_t>(process_id, ui_address_list[i] + 0x60);
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
    }
  }
}

