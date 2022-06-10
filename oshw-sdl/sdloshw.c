/* sdloshw.c: Top-level SDL management functions.
 *
 * Copyright (C) 2001-2010 by Brian Raiter and Madhav Shanbhag,
 * under the GNU General Public License. No warranty. See COPYING for details.
 */

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	"SDL/SDL.h"
#include	"sdlgen.h"
#include	"sdlsfx.h"
#include	"../err.h"
#include <3ds/services/fs.h>
#include <3ds/archive.h>
#include <3ds/romfs.h>
#include <3ds/result.h>
#include <3ds/console.h>


/* Values global to this library.
 */
oshwglobals	sdlg;

/* This is an automatically-generated file, which contains a
 * representation of the program's icon.
 */
#include	"ccicon.c"

// START A B X Y L R SELECT ZL ZR
static int buttonMapping[] = { SDLK_QUESTION, SDLK_RETURN, SDLK_q, SDLK_n, SDLK_p, 0, 0, 0 };
int lastjoyhat = 0;

/* Dispatch all events sitting in the SDL event queue. 
 */
static void _eventupdate(int wait)
{
    static int	mouselastx = -1, mouselasty = -1;
    SDL_Event	event;
    if (wait)
	SDL_WaitEvent(NULL);
    SDL_PumpEvents();
    while (SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_ALLEVENTS)) {
	switch (event.type) {
		case SDL_JOYBUTTONDOWN:
			keyeventcallback(buttonMapping[event.jbutton.button], TRUE);
			break;
		case SDL_JOYBUTTONUP:
			keyeventcallback(buttonMapping[event.jbutton.button], FALSE);
			break;
		case SDL_JOYHATMOTION:
				if((event.jhat.value & SDL_HAT_UP) != (lastjoyhat & SDL_HAT_UP)) keyeventcallback(SDLK_UP, event.jhat.value & SDL_HAT_UP);
				if((event.jhat.value & SDL_HAT_RIGHT) != (lastjoyhat & SDL_HAT_RIGHT)) keyeventcallback(SDLK_RIGHT, event.jhat.value & SDL_HAT_RIGHT);
				if((event.jhat.value & SDL_HAT_DOWN) != (lastjoyhat & SDL_HAT_DOWN)) keyeventcallback(SDLK_DOWN, event.jhat.value & SDL_HAT_DOWN);
				if((event.jhat.value & SDL_HAT_LEFT) != (lastjoyhat & SDL_HAT_LEFT)) keyeventcallback(SDLK_LEFT, event.jhat.value & SDL_HAT_LEFT);
				lastjoyhat = event.jhat.value;
			break;
	  case SDL_MOUSEBUTTONDOWN:
	  case SDL_MOUSEBUTTONUP:
	    SDL_ShowCursor(SDL_ENABLE);
	    mouselastx = event.motion.x;
	    mouselasty = event.motion.y;
	    mouseeventcallback(event.button.x, event.button.y,
			       event.button.button,
			       event.type == SDL_MOUSEBUTTONDOWN);
	    break;
	  case SDL_MOUSEMOTION:
	    SDL_ShowCursor(SDL_ENABLE);
	    mouselastx = event.motion.x;
	    mouselasty = event.motion.y;
	    break;
	  case SDL_QUIT:
	    exit(EXIT_SUCCESS);
	}
    }
}

/* Alter the window decoration.
 */
void setsubtitle(char const *subtitle)
{
    char	buf[270];

    if (subtitle && *subtitle) {
	sprintf(buf, "Tile World - %.255s", subtitle);
	SDL_WM_SetCaption(buf, "Tile World");
    } else {
	SDL_WM_SetCaption("Tile World", "Tile World");
    }
}

/* Read any additional data for the series.
 */
void readextensions(struct gameseries *series)
{
    /* Not implemented. */
}

/* Get number of seconds to skip at start of playback.
 */
int getreplaysecondstoskip(void)
{
    /* Not implemented. */
    return -1;
}

void copytoclipboard(char const *text)
{
    /* Not implemented. */
}

/* Shut down SDL.
 */
static void shutdown(void)
{
    SDL_Quit();
}

/* Initialize SDL, create the program's icon, and then initialize
 * the other modules of the library.
 */
int oshwinitialize(int silence, int soundbufsize,
		   int showhistogram, int fullscreen)
{
    SDL_Surface	       *icon;

    geng.eventupdatefunc = _eventupdate;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
	errmsg(NULL, "Cannot initialize SDL system: %s\n", SDL_GetError());
	return FALSE;
    }
    atexit(shutdown);

    setsubtitle(NULL);

    icon = SDL_CreateRGBSurfaceFrom(cciconimage, CXCCICON, CYCCICON,
				    32, 4 * CXCCICON,
				    0x0000FF, 0x00FF00, 0xFF0000, 0);
    if (icon) {
	SDL_WM_SetIcon(icon, cciconmask);
	SDL_FreeSurface(icon);
    } else
	warn("couldn't create icon surface: %s", SDL_GetError());

    return _generictimerinitialize(showhistogram)
	&& _sdltextinitialize()
	&& _generictileinitialize()
	&& _sdlinputinitialize()
	&& _sdloutputinitialize(fullscreen)
	&& _sdlsfxinitialize(silence, soundbufsize);
}

static const FS_Path EMPTY_PATH = { PATH_EMPTY, 0, NULL };

void flush() {

		//Flush and swap framebuffers
		gfxFlushBuffers();
		gfxSwapBuffers();

		//Wait for VBlank
		gspWaitForVBlank();
}

/* The real main().
 */
int main(int argc, char *argv[])
{
		gfxInitDefault();
		fsInit();
	
		FS_Archive ar;
		Result rc;
		flush();
		rc = FSUSER_OpenArchive(&ar, ARCHIVE_SAVEDATA, EMPTY_PATH);
		if (R_FAILED(rc)) {
			// Okay looks like there's no archive, let's try to create it
			rc = FSUSER_FormatSaveData(ARCHIVE_SAVEDATA, EMPTY_PATH, 1024 * 5, 7, 7, 7, 7, false);
			if (R_FAILED(rc)) return 1;
			rc = FSUSER_OpenArchive(&ar, ARCHIVE_SAVEDATA, EMPTY_PATH);
			if (R_FAILED(rc)) return 2;
		}
		FSUSER_CloseArchive(ar);
		rc = archiveMount(ARCHIVE_SAVEDATA, EMPTY_PATH, "save");
		romfsMountSelf("romfs");
		if (R_FAILED(rc)) {
			return 3;
		}
    return tworld(argc, argv);
}
