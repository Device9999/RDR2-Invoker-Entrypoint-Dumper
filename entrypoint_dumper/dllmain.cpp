/*

YOU WILL NEED TO USE SCRIPTHOOK FOR THIS.

*/
#include <Windows.h>
#include <iostream>
#include <fstream>
#define DLL_EXPORT __declspec(dllexport)
#include "native_engine.hpp"


extern "C" {
	DLL_EXPORT void Init(GetNativeAddressFunc getAddress)
	{
		Native::SetEssentialFunction(getAddress);
		printf("Handler(%I64X)\n", (uintptr_t)(getAddress));
	}

	DLL_EXPORT void Tick()
	{
		static auto is_dumped = false;
		if (!is_dumped) {
			std::ofstream file;
			file.open("RDR2_HASH_TO_ENTRYPOINTS.txt");
			if (!file.is_open() || !file.good()) {
				MessageBoxA(0, "Failed to open file!", "ERROR", MB_OK);
				return;
			}
			static auto baseaddr = (uintptr_t)(GetModuleHandleA(0));
			file << "static std::map<uintptr_t, uintptr_t> nativehash_to_address_table = {" << std::endl;
			for (auto native : native_dump_list) {
				auto addr = (uint64_t)Native::GetHandler(native.hash);
				file << "{" << std::hex << "0x" << native.hash << ", " << std::hex << "0x" << (addr - baseaddr) << " }, // " << native.name.c_str() << std::endl;
			}
			file << "};" << std::endl;
			file.close();
			is_dumped = true;
			MessageBoxA(0, "Dumped entrypoints to game folder, Press OK to exit.", "SUCCESS", MB_OK);
			exit(0);
		}

	}
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		if (AllocConsole()) {
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		}
	}
	return TRUE;
}

