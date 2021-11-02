#pragma once
#include <vector>

const uint32_t memory_start_address = 0x01F14000;
const uint32_t memory_end_address = 0x4AD00000;

//static address
const uint32_t mouse_base_address = 0x1B787A4 + 0x2020 + 0x24FF8;
const uint32_t map_base_address = 0x01A19050;
const uint32_t windows_moving_base_address = 0x01A19050 + 0x14;
const uint32_t player_base_address = 0x01B9F900;
const uint32_t click_NPC_base_address = 0x01BBB1E4;

//
const uint32_t NPC_start_address = 0x11F4A610;
const uint32_t NPC_screen_pos_offset_x = 0x7C;
const uint32_t NPC_screen_pos_offset_y = 0x80;
const uint32_t NPC_map_pos_offset_x = 0x84;
const uint32_t NPC_map_pos_offset_y = 0x88;
const uint32_t NPC_id_offset = 0x8C;
const std::vector<uint32_t> NPC_name_offsets = { 0x24, 0xC, 0x14, 0x50 };



//
const uint32_t alt_start_address = 0x11F383E8;

//800x600
const uint32_t alt_e_ori_0x18_800x600 = 0;
const uint32_t alt_e_ori_0x1C_800x600 = 74;

const uint32_t alt_w_0x18_800x600 = 496;
const uint32_t alt_w_0x1C_800x600 = 60;
const uint32_t alt_w_0x20_800x600 = 304;

const uint32_t alt_q_new_0x18_800x600 = 185;
const uint32_t alt_q_new_0x20_800x600 = 430;

const uint32_t alt_q_ori_0x18_800x600 = 110;
const uint32_t alt_q_ori_0x20_800x600 = 555;

const uint32_t alt_f_0x18_800x600 = 598;
const uint32_t alt_f_0x20_800x600 = 200;

const uint32_t dialog_box_0x18_800x600 = 130;

const uint32_t quick_mission_0x18_800x600 = 639;

//
const uint32_t base_player_start_address = 0x11F42DAC;

//800x600
const uint32_t player_IP_0x18_800x600 = 742;
const uint32_t player_IP_0x1C_800x600 = 5;
const uint32_t player_IP_0xDC_800x600 = 15;

const uint32_t player_HP_0x18_800x600 = 742;
const uint32_t player_HP_0x1C_800x600 = 5;
const uint32_t player_HP_0xDC_800x600 = 11;

const uint32_t player_MP_0x18_800x600 = 742;
const uint32_t player_MP_0x1C_800x600 = 17;

const uint32_t player_AP_0x18_800x600 = 742;
const uint32_t player_AP_0x1C_800x600 = 29;

const uint32_t player_EXP_0x18_800x600 = 742;
const uint32_t player_EXP_0x1C_800x600 = 41;

const uint32_t pet_HP_0x18_800x600 = 622;
const uint32_t pet_HP_0x1C_800x600 = 5;

const uint32_t pet_MP_0x18_800x600 = 622;
const uint32_t pet_MP_0x1C_800x600 = 17;

const uint32_t pet_EXP_0x18_800x600 = 622;
const uint32_t pet_EXP_0x1C_800x600 = 29;

//
const uint32_t map_start_address = 0x11F42C0C;

//800x600
const uint32_t tab_0x18_800x600 = 107;
const uint32_t tab_0x20_800x600 = 586;
const uint32_t tab_0x2C_value_800x600 = 0x11F4367C;

//
const uint32_t ui_pos_offset_x = 0x18;
const uint32_t ui_pos_offset_y = 0x1C;
const uint32_t ui_size_offset_x = 0x20;
const uint32_t ui_size_offset_y = 0x24;
const uint32_t ui_is_active_offset = 0x34;
const uint32_t ui_dynamic_length_offset = 0x114;






//offset
const std::vector<uint32_t> windows_moving_offset = { 0x94 };

const std::vector<uint32_t> mouse_position_offset_x = { 0x80 };
const std::vector<uint32_t> mouse_position_offset_y = { 0x84 };

const std::vector<uint32_t> map_index_offset = { 0x88 + 0x04 };
const std::vector<uint32_t> windows_size_offset_x = { 0xB8 };
const std::vector<uint32_t> windows_size_offset_y = { 0xBC };
const std::vector<uint32_t> map_size_offset_x = { 0x58, 0x10 };
const std::vector<uint32_t> map_size_offset_y = { 0x58, 0x14 };
const std::vector<uint32_t> windows_pos_offset_x = { 0xC8 };
const std::vector<uint32_t> windows_pos_offset_y = { 0xCC };

const std::vector<uint32_t> click_NPC_offset = { 0x2C, 0x6C, 0x0, 0x78, 0xC, 0x60 };

