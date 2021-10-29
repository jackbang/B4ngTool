#pragma once
#include <iostream>
#include <Windows.h>
#include <memory>
#include <cstdint>
#include <string>
#include <tlhelp32.h>
#include <vector>
#include <thread>

typedef struct _B4NG_MEMORY
{
  void* buffer_address;
  UINT_PTR address;
  ULONGLONG size;
  ULONG pid;
  BOOLEAN write;
  BOOLEAN read;
  BOOLEAN req_base;
  BOOLEAN query;
  BOOLEAN cursor;
  UINT32 cursor_x;
  UINT32 cursor_y;
  void* output;
  const char* module_name;
  ULONG64 base_address;
}B4NG_MEMORY;

typedef struct _CHARACTER_INFO
{
  INT32 screen_pos_x;
  INT32 screen_pos_y;
  INT32 world_pos_x;
  INT32 world_pos_y;
  INT32 character_id;
  char character_name[20];
}CHARACTER_INFO, * PCHARACTER_INFO;

typedef struct _WINDOWS_HANDLE
{
  uint32_t main_process_id_list[10];
  std::string main_process_title[10];
  HWND main_hwnd_list[10];
  RECT windows_rect[10];
  uint32_t size;
}WINDOWS_HANDLE, * PWINDOWS_HANDLE;

template<typename ... Arg>
uint64_t call_hook(const Arg ... args)
{
  void* user_32 = LoadLibrary("user32.dll");

  void* hooked_func = GetProcAddress(LoadLibrary("win32u.dll"), "NtGdiDdDDIGetProcessDeviceRemovalSupport");// Use GetModuleHandleA to call the driver function

  auto func = static_cast<uint64_t(_stdcall*)(Arg...)>(hooked_func);

  return func(args ...);
}

std::uint32_t get_process_id(const char* process_name);

void get_all_process_id(const char* process_name, uint32_t* procees_id);

void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND>& vhWnds);

uint64_t get_module_base_address(uint32_t process_id, const char* module_name);

template <class T>
T Read(uint32_t process_id, UINT_PTR read_address)
{
  T response;
  B4NG_MEMORY instruction;
  instruction.pid = process_id;
  instruction.size = sizeof(T);
  instruction.address = read_address;
  instruction.req_base = FALSE;
  instruction.read = TRUE;
  instruction.write = FALSE;
  instruction.query = FALSE;
  instruction.cursor = FALSE;
  instruction.output = &response;
  call_hook(instruction);

  return response;
}

bool Read_block(uint32_t process_id, UINT_PTR read_address, uint32_t* response_ptr, size_t size);

bool write_memory(uint32_t process_id, UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size);

template <class S>
bool Write(uint32_t process_id, UINT_PTR write_address, const S& value)
{
  return write_memory(process_id, write_address, (UINT_PTR)&value, sizeof(S));
}


template <class M>
M query_memory(uint32_t process_id, UINT_PTR start_address)
{
  M response;
  B4NG_MEMORY instruction;
  instruction.pid = process_id;
  instruction.size = sizeof(M);
  instruction.address = NULL;
  instruction.req_base = FALSE;
  instruction.read = FALSE;
  instruction.write = FALSE;
  instruction.query = TRUE;
  instruction.cursor = FALSE;
  instruction.buffer_address = NULL;
  instruction.base_address = start_address;
  instruction.output = &response;
  call_hook(&instruction);

  return response;
}

bool set_cursor(uint32_t process_id, uint32_t cursor_x, uint32_t cursor_y);

void scan_memory(uint32_t process_id, UINT_PTR base_address, uint32_t start_address, uint32_t region_size, uint32_t target_address, uint32_t* address_list, uint32_t* list_length);

void thread_scan_memory(uint32_t process_id, PMEMORY_BASIC_INFORMATION memory_info_ptr, uint32_t memory_info_length, UINT_PTR base_address, uint32_t target_address, uint32_t* address_list, uint32_t* list_length);

void generate_memory_map(uint32_t process_id, UINT_PTR base_address, UINT_PTR start_address, UINT_PTR end_address, PMEMORY_BASIC_INFORMATION memory_map, PSIZE_T map_size);

void FindAddressByValue(uint32_t procees_id, uint32_t base_address, uint32_t start_address, uint32_t end_address, uint32_t value, uint32_t** return_list, uint32_t* return_list_size);
