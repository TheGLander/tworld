/* oshwbind.h: Binds the generic module to the SDL OS/hardware layer.
 * 
 * Copyright (C) 2001-2010 by Brian Raiter and Madhav Shanbhag,
 * under the GNU General Public License. No warranty. See COPYING for details.
 */

#ifndef	HEADER_sdl_oshwbind_h_
#define	HEADER_sdl_oshwbind_h_

#include	"SDL.h"
#include	<stdint.h>

/* Constants
 */
enum {
	TW_ALPHA_TRANSPARENT	= SDL_ALPHA_TRANSPARENT,
	TW_ALPHA_OPAQUE		= SDL_ALPHA_OPAQUE
};

enum {
	TWK_BACKSPACE	= SDL_SCANCODE_BACKSPACE,
	TWK_TAB		= SDL_SCANCODE_TAB,
	TWK_RETURN	= SDL_SCANCODE_RETURN,
	TWK_KP_ENTER	= SDL_SCANCODE_KP_ENTER,
	TWK_ESCAPE	= SDL_SCANCODE_ESCAPE,

	TWK_UP		= SDL_SCANCODE_UP,
	TWK_LEFT	= SDL_SCANCODE_LEFT,
	TWK_DOWN	= SDL_SCANCODE_DOWN,
	TWK_RIGHT	= SDL_SCANCODE_RIGHT,

	TWK_KP8		= SDL_SCANCODE_KP_8,
	TWK_KP4		= SDL_SCANCODE_KP_4,
	TWK_KP2		= SDL_SCANCODE_KP_2,
	TWK_KP6		= SDL_SCANCODE_KP_6,

	TWK_INSERT	= SDL_SCANCODE_INSERT,
	TWK_DELETE	= SDL_SCANCODE_DELETE,
	TWK_HOME	= SDL_SCANCODE_HOME,
	TWK_END		= SDL_SCANCODE_END,
	TWK_PAGEUP	= SDL_SCANCODE_PAGEUP,
	TWK_PAGEDOWN	= SDL_SCANCODE_PAGEDOWN,

	TWK_F1		= SDL_SCANCODE_F1,
	TWK_F2		= SDL_SCANCODE_F2,
	TWK_F3		= SDL_SCANCODE_F3,
	TWK_F4		= SDL_SCANCODE_F4,
	TWK_F5		= SDL_SCANCODE_F5,
	TWK_F6		= SDL_SCANCODE_F6,
	TWK_F7		= SDL_SCANCODE_F7,
	TWK_F8		= SDL_SCANCODE_F8,
	TWK_F9		= SDL_SCANCODE_F9,
	TWK_F10		= SDL_SCANCODE_F10,

	TWK_LSHIFT	= SDL_SCANCODE_LSHIFT,
	TWK_RSHIFT	= SDL_SCANCODE_RSHIFT,
	TWK_LCTRL	= SDL_SCANCODE_LCTRL,
	TWK_RCTRL	= SDL_SCANCODE_RCTRL,
	TWK_LALT	= SDL_SCANCODE_LALT,
	TWK_RALT	= SDL_SCANCODE_RALT,
	TWK_LMETA	= SDL_SCANCODE_LGUI,
	TWK_RMETA	= SDL_SCANCODE_RGUI,
	TWK_CAPSLOCK	= SDL_SCANCODE_CAPSLOCK,
	TWK_NUMLOCK	= SDL_SCANCODE_NUMLOCKCLEAR,
	TWK_SCROLLLOCK	= SDL_SCANCODE_SCROLLLOCK,
	TWK_MODE	= SDL_SCANCODE_MODE,

	TWK_1 = SDL_SCANCODE_1,
	TWK_2 = SDL_SCANCODE_2,
	TWK_3 = SDL_SCANCODE_3,
	TWK_4 = SDL_SCANCODE_4,
	TWK_5 = SDL_SCANCODE_5,
	TWK_6 = SDL_SCANCODE_6,
	TWK_7 = SDL_SCANCODE_7,
	TWK_8 = SDL_SCANCODE_8,
	TWK_9 = SDL_SCANCODE_9,
	TWK_0 = SDL_SCANCODE_0,

	TWK_A = SDL_SCANCODE_A,
	TWK_B = SDL_SCANCODE_B,
	TWK_C = SDL_SCANCODE_C,
	TWK_D = SDL_SCANCODE_D,
	TWK_E = SDL_SCANCODE_E,
	TWK_F = SDL_SCANCODE_F,
	TWK_G = SDL_SCANCODE_G,
	TWK_H = SDL_SCANCODE_H,
	TWK_I = SDL_SCANCODE_I,
	TWK_J = SDL_SCANCODE_J,
	TWK_K = SDL_SCANCODE_K,
	TWK_L = SDL_SCANCODE_L,
	TWK_M = SDL_SCANCODE_M,
	TWK_N = SDL_SCANCODE_N,
	TWK_O = SDL_SCANCODE_O,
	TWK_P = SDL_SCANCODE_P,
	TWK_Q = SDL_SCANCODE_Q,
	TWK_R = SDL_SCANCODE_R,
	TWK_S = SDL_SCANCODE_S,
	TWK_T = SDL_SCANCODE_T,
	TWK_U = SDL_SCANCODE_U,
	TWK_V = SDL_SCANCODE_V,
	TWK_W = SDL_SCANCODE_W,
	TWK_X = SDL_SCANCODE_X,
	TWK_Y = SDL_SCANCODE_Y,
	TWK_Z = SDL_SCANCODE_Z,
	TWK_SLASH = SDL_SCANCODE_SLASH,
	TWK_SPACE	= SDL_SCANCODE_SPACE,

	TWK_CTRL_C	= '\003',
	
	TWK_LAST	= SDL_NUM_SCANCODES
};

enum {
	TW_BUTTON_LEFT		= SDL_BUTTON_LEFT,
	TW_BUTTON_RIGHT		= SDL_BUTTON_RIGHT,
	TW_BUTTON_MIDDLE	= SDL_BUTTON_MIDDLE,
	TW_BUTTON_WHEELUP	= SDL_MOUSEWHEEL_NORMAL,
	TW_BUTTON_WHEELDOWN	= SDL_MOUSEWHEEL_FLIPPED
};

/* Types
 */
typedef  SDL_Rect	TW_Rect;
typedef  SDL_Surface	TW_Surface;
typedef  SDL_Window	TW_Window;
typedef  SDL_Renderer	TW_Renderer;
typedef  SDL_Texture	TW_Texture;
 
/* Functions
 */
extern TW_Surface *TW_NewSurface(int w, int h, int transparency);
#define  TW_FreeSurface  SDL_FreeSurface
#define  TW_MUSTLOCK  SDL_MUSTLOCK
#define  TW_LockSurface  SDL_LockSurface
#define  TW_UnlockSurface  SDL_UnlockSurface
#define  TW_FillRect  SDL_FillRect
#define  TW_BlitSurface  SDL_BlitSurface
#define  TW_SetColorKey(s, c)  SDL_SetColorKey(s, SDL_TRUE, c)
#define  TW_ResetColorKey(s)  SDL_SetColorKey(s, SDL_FALSE, 0)
#define  TW_EnableAlpha(s)  SDL_SetSurfaceAlphaMod(s, 255)
#define  TW_DisplayFormat(s)  SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_RGB888, 0)
#define  TW_DisplayFormatAlpha(s)  SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_ARGB8888, 0)
#define  TW_BytesPerPixel(s)  ((s)->format->BytesPerPixel)
extern uint32_t TW_PixelAt(TW_Surface *s, int x, int y);
#define  TW_MapRGB(s, r, g, b)  SDL_MapRGB((s)->format, r, g, b)
#define  TW_MapRGBA(s, r, g, b, a)  SDL_MapRGBA((s)->format, r, g, b, a)
extern TW_Surface *TW_LoadBMP(char const *filename, int setscreenpalette);

#define  TW_GetKeyState  SDL_GetKeyboardState

#define  TW_GetTicks  SDL_GetTicks
#define  TW_Delay  SDL_Delay

#define  TW_GetError  SDL_GetError

#endif
