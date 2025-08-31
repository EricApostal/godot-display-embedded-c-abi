#include "embedded_display_server.h"

#include <godot_cpp/classes/display_server_embedded.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/rendering_native_surface.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector2i.hpp>

using namespace godot;

extern "C" {

int embedded_display_server_is_available(void) {
	return DisplayServerEmbedded::get_singleton() != nullptr ? 1 : 0;
}

static inline DisplayServerEmbedded *eds() { return DisplayServerEmbedded::get_singleton(); }

void embedded_display_server_set_native_surface(void *native_surface_object) {
	Ref<RenderingNativeSurface> surf;
	if (native_surface_object) {
		Object *obj = reinterpret_cast<Object *>(native_surface_object);
		if (auto *typed = Object::cast_to<RenderingNativeSurface>(obj)) {
			surf = Ref<RenderingNativeSurface>(typed);
		}
	}
	DisplayServerEmbedded::set_native_surface(surf);
}

void embedded_display_server_resize_window(int32_t width, int32_t height, int32_t window_id) {
	if (auto *d = eds()) {
		d->resize_window(Vector2i(width, height), window_id);
	}
}

void embedded_display_server_set_content_scale(float content_scale) {
	if (auto *d = eds()) {
		d->set_content_scale(content_scale);
	}
}

void embedded_display_server_touch_press(int32_t idx, int32_t x, int32_t y, bool pressed, bool double_click, int32_t window_id) {
	if (auto *d = eds()) {
		d->touch_press(idx, x, y, pressed, double_click, window_id);
	}
}

void embedded_display_server_touch_drag(int32_t idx,
		int32_t prev_x,
		int32_t prev_y,
		int32_t x,
		int32_t y,
		float pressure,
		float tilt_x,
		float tilt_y,
		int32_t window_id) {
	if (auto *d = eds()) {
		d->touch_drag(idx, prev_x, prev_y, x, y, pressure, Vector2(tilt_x, tilt_y), window_id);
	}
}

void embedded_display_server_touches_canceled(int32_t idx, int32_t window_id) {
	if (auto *d = eds()) {
		d->touches_canceled(idx, window_id);
	}
}

void embedded_display_server_key(int32_t key,
		uint32_t unicode_char,
		int32_t unshifted,
		int32_t physical,
		uint32_t modifiers,
		bool pressed,
		int32_t window_id) {
	if (auto *d = eds()) {
		// The generated binding exposes DisplayServerEmbedded::key with parameter types matching these casts.
		d->key(static_cast<Key>(key),
				static_cast<char32_t>(unicode_char),
				static_cast<Key>(unshifted),
				static_cast<Key>(physical),
				BitField<KeyModifierMask>(modifiers),
				pressed,
				window_id);
	}
}

} // extern "C"
