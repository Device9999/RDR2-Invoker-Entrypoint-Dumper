#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <algorithm>
#include <vector>
#include <Psapi.h>
#include <map>
#include "../invoker/hash_to_address_table.hpp"
#include "../invoker/invoker.hpp"
#include "../invoker/natives.hpp"
#include "../renderer/renderer.hpp"
#include "../libs/Minhook/include/MinHook.h"
#include "../memory/memory.hpp"

typedef int(__fastcall* is_dlc_present_fn)(__int64 a1, DWORD dlchash);

namespace hooks
{
	namespace globals
	{
		extern RECT resolution;
		extern uintptr_t  base_address;
	}

	namespace original
	{
		extern is_dlc_present_fn o_is_dlc_present;
	}

	extern int __fastcall is_dlc_present_hook(__int64 a1, DWORD dlcHash);

	extern void initialize();

}