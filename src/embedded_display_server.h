// C-compatible wrapper API for DisplayServerEmbedded
// This header exposes a minimal C ABI so that non-C++ code can drive
// the libgodot fork's embedded DisplayServer from external code.
//
// All functions are no-ops if the embedded display server singleton
// is not yet available.

#ifndef EMBEDDED_DISPLAY_SERVER_C_API_H
#define EMBEDDED_DISPLAY_SERVER_C_API_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Returns 1 if DisplayServerEmbedded singleton is available, 0 otherwise.
int embedded_display_server_is_available(void);

// Resize a window (0 = main window unless multi-window is supported).
void embedded_display_server_resize_window(int32_t width, int32_t height, int32_t window_id);

// Set content scale (for high DPI rendering etc.).
void embedded_display_server_set_content_scale(float content_scale);

// Touch press / release / double click.
void embedded_display_server_touch_press(int32_t idx, int32_t x, int32_t y, bool pressed, bool double_click, int32_t window_id);

// Touch drag / motion with pressure and tilt values (tilt in degrees or radians as provided by caller).
void embedded_display_server_touch_drag(int32_t idx,
		int32_t prev_x,
		int32_t prev_y,
		int32_t x,
		int32_t y,
		float pressure,
		float tilt_x,
		float tilt_y,
		int32_t window_id);

// Notify that touches were canceled (e.g. system gesture took over).
void embedded_display_server_touches_canceled(int32_t idx, int32_t window_id);

// Key event. key / unshifted / physical correspond to DisplayServer::Key values.
// modifiers is a bitfield of KeyModifierMask. unicode_char is a UTF-32 codepoint.
void embedded_display_server_key(int32_t key,
		uint32_t unicode_char,
		int32_t unshifted,
		int32_t physical,
		uint32_t modifiers,
		bool pressed,
		int32_t window_id);

#ifdef __cplusplus
}
#endif

#endif // EMBEDDED_DISPLAY_SERVER_C_API_H
