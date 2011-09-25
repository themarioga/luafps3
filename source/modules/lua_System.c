#include "../functions.h"
#include "../filebrowser.h"
#include <lv2/sysfs.h>

static int lua_systemSleep(lua_State *i) {
if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	int xm = luaL_checkint(l, 1);
	sleep(xm);
	return 1;
}
static int lua_systemExit(lua_State *l) {
	if (lua_gettop(l) != 0) return luaL_error(l, "wrong number of arguments");
	exit(0);
	return 1;
}
/**static int lua_getCurrentDirectory(lua_State *l) {
	if (lua_gettop(l) != 0) return luaL_error(l, "wrong number of arguments");
	char path[256];
	getcwd(path, 256);
	lua_pushstring(l, path);
	return 1;
}
static int lua_setCurrentDirectory(lua_State *l) {
	if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	const char *path = luaL_checkstring(l, 1);
	if(!path) return luaL_error(l, "Argument error: System.currentDirectory(file) takes a filename as string as argument.");
	lua_getCurrentDirectory(l);
	chdir(path);
	return 1;
}
static int lua_curdir(lua_State *l) {
	int argc = lua_gettop(l);
	if(argc == 0) return lua_getCurrentDirectory(l);
	if(argc == 1) return lua_setCurrentDirectory(l);
	return luaL_error(l, "Argument error: System.currentDirectory([file]) takes zero or one argument.");
}*/
static int lua_createDir(lua_State *l) {
	if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	const char *path = luaL_checkstring(l, 1);
	if(!path) return luaL_error(l, "Argument error: System.createDirectory(directory) takes a directory name as string as argument.");
	sysFsMkdir(path, 0777);
	return 1;
}
static int lua_chmod(lua_State *l) {
	if (lua_gettop(l) != 2) return luaL_error(l, "wrong number of arguments");
	const char *path = luaL_checkstring(l, 1);
	int mode = luaL_checknumber(l, 2);
	if(!path) return luaL_error(l, "Argument error: System.createDirectory(directory) takes a directory name as string as argument.");
	sysFsChmod(path, mode);
	return 1;
}
static int lua_removeDir(lua_State *l) {
if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	const char *path = luaL_checkstring(l, 1);
	if(!path) return luaL_error(l, "Argument error: System.createDirectory(directory) takes a directory name as string as argument.");
	sysFsRmdir(path);
	return 1;
}
static int lua_checkFile(lua_State *l) {
	if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	const char *path = luaL_checkstring(l, 1);
	FILE *fichero = fopen(path, "r");
	if(fichero){
		lua_pushnumber(l, 1);
 	}else{
		lua_pushnumber(l, 0);
 	}
 	fclose(fichero);
	return 1;
}
static int lua_removeFile(lua_State *l) {
	if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	const char *path = luaL_checkstring(l, 1);
	if(!path) return luaL_error(l, "Argument error: System.removeFile(filename) takes a filename as string as argument.");
	remove(path);
	return 0;
}
static int lua_renameFile(lua_State *l) {
	if (lua_gettop(l) != 2) return luaL_error(l, "wrong number of arguments");
	const char *path1 = luaL_checkstring(l, 1);
	const char *path2 = luaL_checkstring(l, 2);
	if(!path1) return luaL_error(l, "Argument error: System.removeFile(filename) takes a filename as string as argument.");
	rename(path1,path2);
	return 0;
}
static int lua_moveFile(lua_State *l) {
	if (lua_gettop(l) != 2) return luaL_error(l, "wrong number of arguments");
	const char *path1 = luaL_checkstring(l, 1);
	const char *path2 = luaL_checkstring(l, 2);
	if(!path1) return luaL_error(l, "Argument error: System.removeFile(filename) takes a filename as string as argument.");
	rename(path1,path2);
	return 0;
}
static int lua_getdir (lua_State *L) {
	if (lua_gettop(l) == 0) {
		if (!browser.numEntries) {
			BrowseDevice();
		}
	} else {
		int i = luaL_checkint(l, 1);
		browser.selIndex = i;
		BrowserChangeFolder();
	}
    return 1;
}
static int lua_getnumdir (lua_State *L) {
	if (lua_gettop(l) != 0) return luaL_error(l, "wrong number of arguments");
	lua_pushnumber(l, browser.numEntries);
    return 1;
}
static int lua_getname (lua_State *L) {
	if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	int i = luaL_checkint(l, 1);
	lua_pushstring(l, browserList[i].displayname);
    return 1;
}
static int lua_gettype (lua_State *L) {
	if (lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	int i = luaL_checkint(l, 1);
	lua_pushnumber(l, browserList[i].isdir);
    return 1;
}
static int lua_isext (lua_State *L) {
	if (lua_gettop(l) != 2) return luaL_error(l, "wrong number of arguments");
	const char *exten = luaL_checkstring(l, 1);
	int i = luaL_checkint(l, 2);
	char *res = strstr(browserList[i].filename, exten);
	if (res) {
		lua_pushnumber(l, 1);
	} else {
		lua_pushnumber(l, 0);
	}
    return 1;
}
/**static int lua_pathDir (lua_State *L) {
	if (lua_gettop(l) != 0 && lua_gettop(l) != 1) return luaL_error(l, "wrong number of arguments");
	if (lua_gettop(l) != 0) {
		lua_pushstring(l, browser.dir);
	} else {
		sprintf(browser.dir, lua_tostring(l, 1));
	}
    return 1;
}*/

static const struct luaL_reg System[] = {
	{"sleep",lua_systemSleep},
	{"getDir",lua_getdir},
	{"getName",lua_getname},
	{"getType",lua_gettype},
	{"isExt",lua_isext},
	{"getMaxDir",lua_getnumdir},
	//{"getPathDir",lua_pathDir},
	//{"currentDir",lua_curdir},
	{"setChmod",lua_chmod},
	{"createDir",lua_createDir},
	{"removeDir",lua_removeDir},
	{"checkFile",lua_checkFile}, 
	{"removeFile",lua_removeFile},
	{"renameFile",lua_renameFile},
	{"moveFile",lua_moveFile},
	{"exit",lua_systemExit},
	{NULL, NULL}
};

int luaopen_System(lua_State *l) {
	luaL_register(l, "System", System);
	return 1;
}