#include "renderer.hpp"

namespace rendering
{
	void c_renderer::draw_filled_rect(int x, int y, int w, int h, int r, int g, int b, int a) {
		auto width = hooks::globals::resolution.right,
			height = hooks::globals::resolution.bottom;
		x /= width; w /= width;
		y /= height; h /= height;

		GRAPHICS::DRAW_RECT(x, y, w, h, r, g, b, a, 0, 0); // doesn't draw for some reason
	}

	void c_renderer::draw_text(float x, float y, float font_size, std::string text, int r, int g, int b, int a) {
		x /= hooks::globals::resolution.right; y /= hooks::globals::resolution.bottom;
		font_size /= 100.f;
		HUD::SET_TEXT_SCALE(font_size, font_size);
		HUD::_SET_TEXT_COLOR(r, g, b, a);
		auto str = MISC::_CREATE_VAR_STRING(10, "LITERAL_STRING", text.c_str());
		HUD::_DRAW_TEXT(str, x, y);
	}


}