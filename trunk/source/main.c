#include "functions.h"

extern int luaopen_Screen(lua_State *l);
extern int luaopen_Controls(lua_State *l);
extern int luaopen_Timer(lua_State *l);
extern int luaopen_System(lua_State *l);

int main(int argc, char *argv[]) {
	InitSDL();
	l = lua_open();
	luaL_openlibs(l);
	luaopen_Screen(l);
	luaopen_Controls(l);
	luaopen_Timer(l);
	luaopen_System(l);
	SDL_Surface *image = IMG_Load("/dev_hdd0/game/LUAFPS310/USRDIR/contest_splash.png");
	if (image) {
		apply_surface(0,0, image, screen, NULL);
		SDL_Flip(screen);
		SDL_Delay(10000);
	}
	int s = luaL_loadfile(l, "/dev_usb000/script.lua");
	if (s) {
		s = luaL_loadfile(l, "/dev_hdd0/game/LUAFPS310/USRDIR/script.lua");
	}
	while(1) {
		if (!s) {
			s = lua_pcall(l, 0, 0, 0);
		}
		if (s) {
			if (lua_tostring(l, -1)) {
				SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0,0,0));
				fontPrintf(30, 30, "Error: %s", lua_tostring(l, -1));
				fontPrintf(30, 45, "Pulsa Home para salir.");
				lua_pop(l, 1);
			}
			getPadData(0);
			SDL_Flip(screen);
			sysUtilCheckCallback();
		}
	}
	lua_close(l);
	return 0;
}

