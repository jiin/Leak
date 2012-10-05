// Bridge C++->C->Lua

#include <iostream>

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

#include "main.h"

using namespace std;

int API_move(lua_State *L) {
    int sx = lua_tonumber(L, 1),
        sy = lua_tonumber(L, 2),
        x  = lua_tonumber(L, 3),
        y  = lua_tonumber(L, 4);

    lua_getglobal(L, "player");
    Player *curr = (Player *) lua_topointer(L, -1);

    //cout << "MOVED" << endl;

    curr->move(sx, sy, x, y);
    return 0;
}

int API_getprop(lua_State *L) {
    int atk, def;
    string *color;

    lua_getglobal(L, "player");
    Player *curr = (Player *) lua_topointer(L, -1);

    if (lua_isnumber(L, 1) && lua_isnumber(L, 2)) {
        int x = lua_tonumber(L, 1),
            y = lua_tonumber(L, 2);

        if (curr->grid->gui->matrix[x][y].player)
            atk = curr->grid->gui->matrix[x][y].player->atk + curr->grid->gui->matrix[x][y].atk;
        else
            atk = 0;

        if (curr->grid->gui->matrix[x][y].player)
            def = curr->grid->gui->matrix[x][y].player->def + curr->grid->gui->matrix[x][y].def;
        else
            def = 0;
        if (curr->grid->gui->matrix[x][y].player)
            color = color_to_string(curr->grid->gui->matrix[x][y].player->color);
        else
            color = color_to_string(sf::Color::White);
        
    } else {
        atk = curr->atk;
        def = curr->def;
    }

    // Creating array [atk, def]
    lua_newtable(L);
    
    // t[atk] = atk
    lua_pushstring(L, "atk");
    lua_pushnumber(L, atk);
    lua_settable(L, -3);
    
    // t[def] = def
    lua_pushstring(L, "def");
    lua_pushnumber(L, def);
    lua_settable(L, -3);

    // t[color] = 
    lua_pushstring(L, "color");
    lua_pushstring(L, color->c_str());
    lua_settable(L, -3);

    return 1;
}

int API_getgridprops(lua_State *L) {
    lua_getglobal(L, "player");
    Player *curr = (Player *) lua_topointer(L, -1);

    //cout << "CALL'D" << endl;

    lua_newtable(L);

    // t[0] = width
    lua_pushinteger(L, 0);
    lua_pushinteger(L, curr->grid->w);
    lua_settable(L, -3);

    // t[0] = height
    lua_pushinteger(L, 1);
    lua_pushinteger(L, curr->grid->h);
    lua_settable(L, -3);

    return 1;
}