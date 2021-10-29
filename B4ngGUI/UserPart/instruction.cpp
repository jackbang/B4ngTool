#include "instruction.h"

struct HandleDisposer
{
  using pointere = HANDLE;
  void operator()(HANDLE handle) const
  {
	if (handle != NULL || handle != INVALID_HANDLE_VALUE)
	{
	  CloseHandle(handle);
	  printf("UM part: Can not open handle. (HandleDisposer)");
	}
  }
};

std::uint32_t get_process_id(const char* process_name)
{
  std::uint32_t procees_id = 0;
  HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
  if (ss)
  {
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(ss, &pe))
	{
	  do
	  {
		if (!strcmp(pe.szExeFile, process_name))
		{
		  procees_id = pe.th32ProcessID;
		  break;
		}
	  } while (Process32Next(ss, &pe));
	}
	CloseHandle(ss);
  }
  //printf("the process id is: %d", procees_id);
  return procees_id;
};

void get_all_process_id(const char* process_name, uint32_t * procees_id)
{
  uint32_t length = 0;
  HANDLE ss = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
  if (ss)
  {
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (Process32First(ss, &pe))
	{
	  do
	  {
		if (!strcmp(pe.szExeFile, process_name))
		{
		  procees_id[length] = pe.th32ProcessID;
		  length += 1;
		}
	  } while (Process32Next(ss, &pe));
	}
	CloseHandle(ss);
  }
  //printf("the process id is: %d", procees_id);
};

void GetAllWindowsFromProcessID(DWORD dwProcessID, std::vector <HWND>& vhWnds)
{
  // find all hWnds (vhWnds) associated with a process id (dwProcessID)
  HWND hCurWnd = nullptr;
  do
  {
	hCurWnd = FindWindowEx(nullptr, hCurWnd, nullptr, nullptr);
	DWORD checkProcessID = 0;
	GetWindowThreadProcessId(hCurWnd, &checkProcessID);
	if (checkProcessID == dwProcessID)
	{
	  vhWnds.push_back(hCurWnd);  // add the found hCurWnd to the vector
	  //wprintf(L"Found hWnd %d\n", hCurWnd);
	}
  } while (hCurWnd != nullptr);
}

uint64_t get_module_base_address(uint32_t process_id, const char* module_name)
{
  B4NG_MEMORY instruction = { 0 };
  instruction.pid = process_id;
  instruction.req_base = TRUE;
  instruction.read = FALSE;
  instruction.write = FALSE;
  instruction.query = FALSE;
  instruction.cursor = FALSE;
  instruction.module_name = module_name;
  call_hook(&instruction);

  ULONG base = NULL;
  base = instruction.base_address;
  return base;
};

bool Read_block(uint32_t process_id, UINT_PTR read_address, uint32_t* response_ptr, size_t size)
{
  B4NG_MEMORY instruction;
  instruction.pid = process_id;
  instruction.size = size;
  instruction.address = read_address;
  instruction.req_base = FALSE;
  instruction.read = TRUE;
  instruction.write = FALSE;
  instruction.query = FALSE;
  instruction.cursor = FALSE;
  instruction.output = response_ptr;
  call_hook(instruction);

  return true;
}

bool write_memory(uint32_t process_id, UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size)
{
  B4NG_MEMORY instruction;
  instruction.pid = process_id;
  instruction.size = write_size;
  instruction.address = write_address;
  instruction.req_base = FALSE;
  instruction.read = FALSE;
  instruction.write = TRUE;
  instruction.query = FALSE;
  instruction.cursor = FALSE;
  instruction.buffer_address = (void*)source_address;

  call_hook(&instruction);

  return true;
}

bool set_cursor(uint32_t process_id, uint32_t cursor_x, uint32_t cursor_y)
{
  B4NG_MEMORY instruction;
  instruction.pid = process_id;
  instruction.size = NULL;
  instruction.address = NULL;
  instruction.req_base = FALSE;
  instruction.read = FALSE;
  instruction.write = FALSE;
  instruction.query = FALSE;
  instruction.cursor = TRUE;
  instruction.buffer_address = NULL;
  instruction.cursor_x = cursor_x;
  instruction.cursor_y = cursor_y;

  call_hook(&instruction);

  return true;
}

void scan_memory(uint32_t process_id, UINT_PTR base_address, uint32_t start_address, uint32_t region_size, uint32_t target_address, uint32_t* address_list, uint32_t* list_length)
{
  uint32_t* memory_block = (uint32_t*)malloc(region_size / 4 * sizeof(uint32_t));
  //printf("start read block %X size: %X\r\n", start_address, region_size);
  Read_block(process_id, start_address, memory_block, region_size);
  //printf("done!!!!!!!!!!!!!!! read block %X\r\n", start_address);
  for (size_t i = 0; i < region_size / 4; i++)
  {
	uint32_t value = *(memory_block + i);

	//printf("Start Address: %X\n", start_address);
	if (value == (uint32_t)target_address)
	{

	  *(address_list + *list_length) = start_address + i * 4;
	  //printf("%X ----%X\r\n", *list_length, value);
	  //printf("2-Value: %X\n", value);
	  //printf("Address: %X\n", start_address + i * 4);
	  //std::lock_guard<std::mutex> guard(myMutex);
	  //printf("Founded! Start Address: %X\n", start_address);
	  //PCHARACTER_INFO character = charater_list + (uint32_t)(*list_length);
	  //character->screen_pos_x = Read<int32_t>(process_id, base_address + start_address + i*4 + 0x7C);
	  //character->screen_pos_y = Read<int32_t>(process_id, base_address + start_address + i*4 + 0x80);
	  //character->world_pos_x = Read<int32_t>(process_id, base_address + start_address + i*4 + 0x84);
	  //character->world_pos_y = Read<int32_t>(process_id, base_address + start_address + i*4 + 0x88);
	  //character->character_id = Read<int32_t>(process_id, base_address + start_address + i*4 + 0x8C);

	  //uint32_t bias_1_address = Read<uint32_t>(process_id, base_address + start_address + i * 4 + 0x24);
	  //uint32_t bias_2_address = Read<uint32_t>(process_id, base_address + bias_1_address + 0xC);
	  //uint32_t bias_3_address = Read<uint32_t>(process_id, base_address + bias_2_address + 0x14);\
	  //uint32_t bias_4_address = Read<uint32_t>(process_id, base_address + bias_3_address + 0x50);
// 
	  //uint32_t bias_5_address = Read<uint32_t>(process_id, base_address + bias_4_address + 0x14);

	  //for (size_t j = 0; j < 20; j++)
	  //{
		//*(character->character_name + j) = Read<char>(process_id, base_address + bias_4_address + 0x14 + j);
	  //}

	  * list_length += 1;
	}
  }
  //printf("for done!!!!!!!!!!!!!!! read block %X\r\n", start_address);
  free(memory_block);
}

void thread_scan_memory(uint32_t process_id, PMEMORY_BASIC_INFORMATION memory_info_ptr, uint32_t memory_info_length, UINT_PTR base_address, uint32_t target_address, uint32_t* address_list, uint32_t* list_length)
{
  for (size_t i = 0; i < memory_info_length; i++)
  {
	scan_memory(process_id, base_address, (uint32_t)(memory_info_ptr + i)->BaseAddress, (memory_info_ptr + i)->RegionSize, target_address, address_list, list_length);
	//printf("The Block Base Address: %X\n", (uint32_t)(memory_info_ptr + i)->BaseAddress);
  }
}

void generate_memory_map(uint32_t process_id, UINT_PTR base_address, UINT_PTR start_address, UINT_PTR end_address, PMEMORY_BASIC_INFORMATION memory_map, PSIZE_T map_size)
{
  *(memory_map + *map_size) = query_memory<MEMORY_BASIC_INFORMATION>(process_id, base_address + start_address);
  UINT32 head_address = (UINT32)(memory_map + *map_size)->BaseAddress;
  UINT32 memory_size = (UINT32)(memory_map + *map_size)->RegionSize;
  while (head_address + memory_size <= end_address)
  {
	//printf("address: %X, Size: %X End: %X Protect: %X\n", head_address, memory_size, end_address, (memory_map + *map_size)->Protect);
	if ((memory_map + *map_size)->Type == MEM_PRIVATE &&
	  (memory_map + *map_size)->State == MEM_COMMIT &&
	  (((memory_map + *map_size)->Protect & PAGE_NOACCESS) == NULL))
	{
	  //Record the memory information
	  //printf("address: %X, Size: %X End: %X Protect: %X\n", head_address, memory_size, end_address, (memory_map + *map_size)->Protect);
	  *map_size += 1;
	}
	*(memory_map + *map_size) = query_memory<MEMORY_BASIC_INFORMATION>(process_id, base_address + head_address + memory_size);
	if ((UINT32)(memory_map + *map_size)->BaseAddress > head_address)
	{
	  head_address = (UINT32)(memory_map + *map_size)->BaseAddress;
	}
	else
	{
	  head_address = (UINT32)(memory_map + *map_size)->BaseAddress + (memory_map + *map_size)->RegionSize;
	}
	memory_size = (UINT32)(memory_map + *map_size)->RegionSize;
  }
}

void FindAddressByValue(uint32_t procees_id, uint32_t base_address, uint32_t start_address, uint32_t end_address, uint32_t value, uint32_t** return_list, uint32_t* return_list_size)
{
  PMEMORY_BASIC_INFORMATION memory_map_ptr = (PMEMORY_BASIC_INFORMATION)malloc(2000 * sizeof(MEMORY_BASIC_INFORMATION));
  SIZE_T memory_map_length = 0;

  printf("Loading...\n");
  generate_memory_map(procees_id, base_address, start_address, end_address, memory_map_ptr, &memory_map_length);
  printf("Length: %d\n", memory_map_length);

  const uint32_t threads_max = 20;
  std::thread threads[threads_max + 1];

  uint32_t* address_list_ptr[threads_max + 1]; //thread memory list;
  uint32_t address_list_ptr_size[threads_max + 1];

  uint32_t num_of_modules = memory_map_length / threads_max;

  for (size_t i = 0; i <= threads_max; i++)
  {
	*(address_list_ptr_size + i) = 0;
  }

  for (size_t i = 0; i < threads_max; i++)
  {
	//printf("start address: %X Region: %X\n", (memory_map_ptr + i)->BaseAddress, (memory_map_ptr + i)->RegionSize);
	uint32_t* address_list = (uint32_t*)malloc(3000 * sizeof(uint32_t));
	address_list_ptr[i] = address_list;
	threads[i] = std::thread(thread_scan_memory, procees_id, memory_map_ptr + i * num_of_modules, num_of_modules, base_address, value, address_list, (address_list_ptr_size + i));
  }

  uint32_t* address_list = (uint32_t*)malloc(3000 * sizeof(uint32_t));
  address_list_ptr[threads_max] = address_list;
  uint32_t left_modules = memory_map_length - num_of_modules * threads_max;
  threads[threads_max] = std::thread(thread_scan_memory, procees_id, memory_map_ptr + threads_max * num_of_modules, left_modules, base_address, value, address_list, (address_list_ptr_size + threads_max));

  for (size_t i = 0; i <= threads_max; i++)
  {
	threads[i].join();
  }
  //printf("DONE!");

  *return_list_size = 0;
  for (size_t i = 0; i <= threads_max; i++)
  {
	if (*(address_list_ptr_size + i) > 0)
	{// if this thread's address list is not zero
	  //printf("%d list length %d\r\n", i, *(address_list_ptr_size + i));
	  //memcpy((return_list + *return_list_size), *(address_list_ptr + i), *(address_list_ptr_size + i));
	  //*return_list_size += *(address_list_ptr_size + i);
	  for (size_t j = 0; j < *(address_list_ptr_size + i); j++)
	  {
		//printf("the value is %X\r\n", *(*(address_list_ptr + i) + j));
		*(*return_list + *return_list_size) = *(*(address_list_ptr + i) + j);
		*return_list_size += 1;
	  }
	}
	free(address_list_ptr[i]);
  }
  //printf("return list size %d\r\n", *return_list_size);
  free(memory_map_ptr);
  //printf("return list size %X\r\n", *(return_list+1000));
}
