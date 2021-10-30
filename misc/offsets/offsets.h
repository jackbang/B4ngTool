#pragma once

#include <vector>

//static address
uint32_t mouse_base_address = 0x1B787A4 + 0x2020;
uint32_t map_base_address = 0x19F2030 + 0x2020;
uint32_t player_base_address = 0x1B788E8 + 0x2020;

//offset
std::vector<uint32_t> mouse_position_offset_x = { 0x80 };
std::vector<uint32_t> mouse_position_offset_y = { 0x84 };

std::vector<uint32_t> map_index_offset = { 0x88 + 0x04 };
std::vector<uint32_t> windows_size_offset_x = { 0xB8 };
std::vector<uint32_t> windows_size_offset_y = { 0xBC };
std::vector<uint32_t> map_size_offset_x = { 0x58, 0x10 };
std::vector<uint32_t> map_size_offset_y = { 0x58, 0x14 };
