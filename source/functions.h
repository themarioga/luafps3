//Lua
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
// normal includes
#include <ppu-lv2.h>
#include <sysutil/sysutil.h>
#include <sysmodule/sysmodule.h>
#include <io/pad.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <malloc.h>
#include <math.h>
#include <filebrowser.h>
// SDL includes
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_draw.h>

#define toPush(HANDLE, DATATYPE) \
DATATYPE *to##HANDLE (lua_State *l, int index) { \
  DATATYPE* handle  = (DATATYPE*)lua_touserdata(l, index); \
  return handle; \
} \
DATATYPE* push##HANDLE(lua_State *l) { \
	DATATYPE * newvalue = (DATATYPE*)lua_newuserdata(l, sizeof(DATATYPE)); \
	return newvalue; \
}

SDL_Surface *screen;
lua_State *l;
TTF_Font *errorfont;
SDL_Surface *error_text_surface;
SDL_Color errorcolor;

void InitSDL();
void free_surf(SDL_Surface* surf);
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
void fontPrintf(int x, int y, const char *format, ...);
padData getPadData() ;
