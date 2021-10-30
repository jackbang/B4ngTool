#pragma once
#include "instruction.h"
#include <vector>
#include <string>

typedef struct _MH_BASE_ADDRESS
{
  uint32_t player_IP_address = NULL;
  uint32_t player_HP_address = NULL;
  uint32_t player_MP_address = NULL;
  uint32_t player_AP_address = NULL;
  uint32_t player_EXP_address = NULL;

  uint32_t pet_HP_address = NULL;
  uint32_t pet_MP_address = NULL;
  uint32_t pet_EXP_address = NULL;

  uint32_t tab_address = NULL;

  uint32_t alt_e_address = NULL;
  uint32_t alt_w_address = NULL;
  uint32_t alt_q_new_address = NULL;
  uint32_t alt_q_ori_address = NULL;
  uint32_t alt_f_address = NULL;

  uint32_t quick_mission_address = NULL;

  uint32_t dialog_box_address = NULL;

}MH_BASE_ADDRESS, * PMH_BASE_ADDRESS;

void initial_base_address(uint32_t process_id, PMH_BASE_ADDRESS base_address);

std::string string_to_utf8(std::string input);

bool mhmain_window_detection(PWINDOWS_HANDLE windows_handle);

uint32_t get_address_value(uint32_t process_id, uint32_t base_address, std::vector<uint32_t> offsets);

void get_game_mouse_pos(uint32_t process_id, int32_t* mouse_x, int32_t* mouse_y);

void get_map_info(uint32_t process_id, int32_t* map_index, int32_t* map_size_x, int32_t* map_size_y, int32_t* windows_size_x, int32_t* windows_size_y);

void get_player_pos(uint32_t process_id, float* player_x, float* player_y);

void get_click_NPC_name(uint32_t process_id, char* clicked_name);

void get_quick_mission_content(uint32_t process_id, char* mission_content);