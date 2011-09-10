#include "../functions.h"

toPush(CB, padData)

static int Controls_read(lua_State *l) {
	if(lua_gettop(l) != 1) return luaL_error(l, "Wrong number of elements.");
	int pad = luaL_checkint(l, 1);
	padData cb = getPadData(pad);
	padData* CB = pushCB(l);
	*CB = cb;
	return 1;
}
static int Controls_setSixaxis(lua_State *L) {
    int pad = luaL_checkint(L, 1);
    int enable = luaL_checkint(L, 2);
    ioPadSetSensorMode(pad, enable);
    return 0;
}

//BUTTONS
#define ControlsConv(NAMEFUN, NAMEBUT) \
	static int Controls_##NAMEFUN (lua_State *l) { \
		if(lua_gettop(l) != 1) return luaL_error(l, "Wrong number of elements."); \
		padData cb = *toCB(l, 1);\
		lua_pushnumber(l, cb.NAMEBUT); \
		return 1; \
	} 
ControlsConv(up, BTN_UP);
ControlsConv(down, BTN_DOWN);
ControlsConv(right, BTN_RIGHT);
ControlsConv(left, BTN_LEFT);
ControlsConv(cross, BTN_CROSS);
ControlsConv(square, BTN_SQUARE);
ControlsConv(circle, BTN_CIRCLE);
ControlsConv(triangle, BTN_TRIANGLE);
ControlsConv(r1, BTN_R1);
ControlsConv(r2, BTN_R2);
ControlsConv(r3, BTN_R3);
ControlsConv(l1, BTN_L1);
ControlsConv(l2, BTN_L2);
ControlsConv(l3, BTN_L3);
ControlsConv(start, BTN_START);
ControlsConv(select, BTN_SELECT);
ControlsConv(analogL_X, ANA_L_H);
ControlsConv(analogL_Y, ANA_L_V);
ControlsConv(analogR_X, ANA_R_H);
ControlsConv(analogR_Y, ANA_R_V);
ControlsConv(axisX, SENSOR_X);
ControlsConv(axisY, SENSOR_Y);
ControlsConv(axisZ, SENSOR_Z);
ControlsConv(axisG, SENSOR_G);

static const luaL_reg Controls[] = {
	{"read", Controls_read},
	{"setSixaxis", Controls_setSixaxis},
	{"up", Controls_up },
	{"down", Controls_down },
	{"right", Controls_right },
	{"left", Controls_left },
	{"cross", Controls_cross },
	{"circle", Controls_circle },
	{"square", Controls_square },
	{"triangle", Controls_triangle },
	{"l1", Controls_l1 },
	{"l2", Controls_l2 },
	{"l3", Controls_l3 },
	{"r1", Controls_r1 },
	{"r2", Controls_r2 },
	{"r3", Controls_r3 },
	{"analogLX", Controls_analogL_X },
	{"analogLY", Controls_analogL_Y },
	{"analogRX", Controls_analogR_X },
	{"analogRY", Controls_analogR_Y },
	{"axisX", Controls_axisX },
	{"axisY", Controls_axisY },
	{"axisZ", Controls_axisZ },
	{"axisG", Controls_axisG },
	{"start", Controls_start },
	{"select", Controls_select },
	{NULL, NULL}
};

int luaopen_Controls(lua_State *l) {
	luaL_register(l, "Controls", Controls);
	return 1;
}
