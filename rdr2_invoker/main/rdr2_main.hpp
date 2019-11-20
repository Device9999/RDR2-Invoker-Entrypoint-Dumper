#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h> 
#include <algorithm>
#include <vector>
#include <Psapi.h>
#include "../invoker/hash_to_adress_table.hpp"
#include "../invoker/invoker.hpp"
#include "../invoker/natives.hpp"
#include "../libs/Minhook/include/MinHook.h"
#include "../memory/memory.hpp"

typedef int(__fastcall* is_dlc_present_fn)(__int64 a1, DWORD dlchash);

namespace hooks
{
	namespace original
	{
		extern is_dlc_present_fn o_is_dlc_present;
	}

	extern int __fastcall is_dlc_present_hook(__int64 a1, DWORD dlcHash);

	extern void initialize();

}