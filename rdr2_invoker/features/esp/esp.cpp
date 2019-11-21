#include "esp.hpp"

namespace features
{

	void c_esp::draw_players() {
		static auto w2s = reinterpret_cast<bool(*)(Vector3 world, float* x, float* y)>(memory::find_signature(0, "\x48\x89\x5C\x24\x00\x56\x57\x41\x56\x48\x83\xEC\x60", "xxxx?xxxxxxxx"));
		for (int i = 0; i < 32; i++) {
			auto ped = PLAYER::GET_PLAYER_PED_SCRIPT_INDEX(i);
			if (!ped || !ENTITY::DOES_ENTITY_EXIST(ped))
				continue;

			auto position = ENTITY::GET_ENTITY_COORDS(ped, false, false);
			float screen_x = 0.f, screen_y = 0.f;
			if (w2s(position, &screen_x, &screen_y)) {
				screen_x *= hooks::globals::resolution.right;
				screen_y *= hooks::globals::resolution.bottom;

				auto name = PLAYER::GET_PLAYER_NAME(i);
				rendering::c_renderer::get()->draw_text(screen_x, screen_y, 14.f, name, 255, 0, 255, 255);
			}
		}
	}

}