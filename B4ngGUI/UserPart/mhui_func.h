#pragma once
#include <iostream>
#include <Windows.h>
#include <memory>
#include <cstdint>
#include <string>
#include <tlhelp32.h>
#include <vector>
#include <thread>
#include "mhfunction.h"

void mhmain_base_address_table_row(uint32_t process_id, uint32_t address, std::string title);

void mhmain_base_address_table(uint32_t process_id, PMH_BASE_ADDRESS base_address);


