#include "functions.h"

SDL_Color errorcolor = {255,255,255};
TTF_Font *errorfont;
SDL_Surface *error_text_surface;
const SDL_VideoInfo *dispinfo;

void writeToLog(const char *text, ...) {
    va_list opt;
	FILE *pFile;
    char buff[2048];
    va_start(opt, text);
    vsnprintf(buff, sizeof(buff), text, opt);
    va_end(opt);
	pFile = fopen("/dev_usb000/log.txt","a+");
	fputs(buff,pFile);
    fclose(pFile);
}

static void sys_callback(uint64_t status, uint64_t param, void* userdata) {
	switch (status) {
		case SYSUTIL_EXIT_GAME:
			exit(0);
			break;
	default:
		break;
	}
}

void InitSDL() {
	sysModuleLoad(SYSMODULE_FS);
	sysModuleLoad(SYSMODULE_IO);
	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	TTF_Init();
	dispinfo = SDL_GetVideoInfo();
	screen = SDL_SetVideoMode(dispinfo->current_w, dispinfo->current_h,32,SDL_DOUBLEBUF);
	sysUtilRegisterCallback(SYSUTIL_EVENT_SLOT0, sys_callback, NULL);
	ioPadInit(7);
	atexit(SDL_Quit);
	SDL_ShowCursor(SDL_DISABLE);
	errorfont=TTF_OpenFont("/dev_hdd0/game/LUAFPS310/USRDIR/error.ttf", dispinfo->current_h/50);
	if (!errorfont) {
		exit(0);
	}
}
void free_surf(SDL_Surface* surf){
	if(surf) SDL_FreeSurface(surf);
}
void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip) {
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface( source, clip, destination, &offset );
}
void fontWrite(int x, int y, const char* text) {
	if (text != NULL) {
		error_text_surface=TTF_RenderText_Solid(errorfont, text, errorcolor);
		apply_surface(x, y, error_text_surface, screen, NULL);
		free_surf(error_text_surface);
	} else {
		exit(0);
	}
}
void fontPrintf(int x, int y, const char *format, ...) {
    va_list opt;
    char buff[2048];
    va_start(opt, format);
    vsnprintf(buff, sizeof(buff), format, opt);
    va_end(opt);
	fontWrite(x, y, buff);
}

padData getPadData(int i) {
	padInfo padinfo;
	padData paddata;
	ioPadGetInfo(&padinfo);
	if(padinfo.status[i]){
		ioPadGetData(i, &paddata);
	}
	return paddata;
}
