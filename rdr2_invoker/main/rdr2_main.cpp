#include "rdr2_main.hpp"

namespace hooks
{
	namespace original
	{
		is_dlc_present_fn o_is_dlc_present;
	}

	int __fastcall is_dlc_present_hook(__int64 a1, DWORD dlcHash) {
		auto playerid = PLAYER::PLAYER_ID();

		if (NETWORK::NETWORK_IS_PLAYER_CONNECTED(playerid) && !PLAYER::GET_PLAYER_INVINCIBLE(playerid)) { // Simple godmode
			PLAYER::SET_PLAYER_INVINCIBLE(playerid, true);
		}
		return original::o_is_dlc_present(a1, dlcHash);
	}

	void initialize() {

		if (AllocConsole()) {
			freopen("CONIN$", "r", stdin);
			freopen("CONOUT$", "w", stdout);
			freopen("CONOUT$", "w", stderr);
		}
		printf("Cheat loaded!\n\n");

		auto status = MH_Initialize();
		printf("init_status : %s\n", std::string(MH_StatusToString(status)).c_str());

		auto is_dlc_present = memory::find_signature(0, "\x81\xFA\x00\x00\x00\x00\x75\x0B\x8A", "xx????xxx") - 0x1E; // thx to @a60276468 for the sig
		printf("is_dlc_present: %I64X\n", is_dlc_present);

		status = MH_CreateHook((PVOID)is_dlc_present, is_dlc_present_hook, reinterpret_cast<void**>(&original::o_is_dlc_present));
		printf("create_status : %s\n", std::string(MH_StatusToString(status)).c_str());

		status = MH_EnableHook((PVOID)is_dlc_present);
		printf("enable_status : %s\n\n", std::string(MH_StatusToString(status)).c_str());
		
	}
}

