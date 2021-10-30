#pragma once

#include <vector>

uint32_t memory_start_address = 0x01F14000;
uint32_t memory_end_address = 0x4AD00000;

//static address
uint32_t mouse_base_address = 0x1B787A4 + 0x2020;
uint32_t map_base_address = 0x19F2030 + 0x2020;
uint32_t player_base_address = 0x1B788E8 + 0x2020;
uint32_t click_NPC_base_address = 0x01B941D4 + 0x2020;

//
uint32_t alt_start_address = 0x1F383E8;

//800x600
uint32_t alt_e_ori_0x18_800x600 = 0;
uint32_t alt_e_ori_0x1C_800x600 = 74;

uint32_t alt_w_0x18_800x600 = 409;

uint32_t alt_q_new_0x18_800x600 = 187;
uint32_t alt_q_new_0x20_800x600 = 425;

uint32_t alt_q_ori_0x18_800x600 = 110;
uint32_t alt_q_ori_0x20_800x600 = 555;

uint32_t alt_f_0x18_800x600 = 598;
uint32_t alt_f_0x20_800x600 = 200;

uint32_t dialog_box_0x18_800x600 = 130;

uint32_t quick_mission_0x18_800x600 = 639;

//
uint32_t base_player_start_address = 0x11F42DAC;

//800x600
uint32_t player_IP_0x18_800x600 = 742;
uint32_t player_IP_0x1C_800x600 = 5;
uint32_t player_IP_0xDC_800x600 = 15;

uint32_t player_HP_0x18_800x600 = 742;
uint32_t player_HP_0x1C_800x600 = 5;
uint32_t player_HP_0xDC_800x600 = 11;

uint32_t player_MP_0x18_800x600 = 742;
uint32_t player_MP_0x1C_800x600 = 17;

uint32_t player_AP_0x18_800x600 = 742;
uint32_t player_AP_0x1C_800x600 = 29;

uint32_t player_EXP_0x18_800x600 = 742;
uint32_t player_EXP_0x1C_800x600 = 41;

uint32_t pet_HP_0x18_800x600 = 622;
uint32_t pet_HP_0x1C_800x600 = 5;

uint32_t pet_MP_0x18_800x600 = 622;
uint32_t pet_MP_0x1C_800x600 = 17;

uint32_t pet_EXP_0x18_800x600 = 622;
uint32_t pet_EXP_0x1C_800x600 = 29;

//
uint32_t map_start_address = 0x11F42C0C;

//800x600
uint32_t tab_0x18_800x600 = 107;
uint32_t tab_0x20_800x600 = 586;

//
uint32_t ui_pos_offset_x = 0x18;
uint32_t ui_pos_offset_y = 0x1C;
uint32_t ui_size_offset_x = 0x20;
uint32_t ui_size_offset_y = 0x24;
uint32_t ui_is_active_offset = 0x34;
uint32_t ui_dynamic_length_offset = 0x114;






//offset
std::vector<uint32_t> mouse_position_offset_x = { 0x80 };
std::vector<uint32_t> mouse_position_offset_y = { 0x84 };

std::vector<uint32_t> map_index_offset = { 0x88 + 0x04 };
std::vector<uint32_t> windows_size_offset_x = { 0xB8 };
std::vector<uint32_t> windows_size_offset_y = { 0xBC };
std::vector<uint32_t> map_size_offset_x = { 0x58, 0x10 };
std::vector<uint32_t> map_size_offset_y = { 0x58, 0x14 };

std::vector<uint32_t> click_NPC_offset = { 0x2C, 0x78, 0x0, 0x64, 0xC, 0x50, 0x8, 0x20 };

