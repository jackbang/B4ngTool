#pragma once
#include "instruction.h"
#include <vector>
#include <string>

std::string string_to_utf8(std::string input);

bool mhmain_window_detection(PWINDOWS_HANDLE windows_handle);

void get_game_mouse_pos(uint32_t process_id, int32_t* mouse_x, int32_t* mouse_y);

void get_map_info(uint32_t process_id, int32_t* map_index, int32_t* map_size_x, int32_t* map_size_y, int32_t* windows_size_x, int32_t* windows_size_y);

void get_player_pos(uint32_t process_id, float* player_x, float* player_y);

void get_click_NPC_name(uint32_t process_id, char* clicked_name);

void get_quick_mission_content(uint32_t process_id, char* mission_content);