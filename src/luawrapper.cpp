

#include "luawrapper.h"


LuaWrapper::LuaWrapper()
    : L(luaL_newstate(), lua_close)
{

    luaL_openlibs(L.get());

}


LuaWrapper::LuaWrapper(const LuaWrapper &l)
    : L(l.L)
{

    

}


int LuaWrapper::LoadFile(std::string filename)
{

    if(luaL_loadfile(L.get(), filename.c_str()))
    {

        // pass error info to global error function
        return -1;

    }

    return 0;

}


int LuaWrapper::ExecuteChunk()
{

    if(lua_pcall(L.get(), 0, LUA_MULTRET, 0))
    {

        // add error info to global function.
        return -1;

    }
  
    return 0;

}


int LuaWrapper::RunFunction(std::string func_name, int num)
{

    lua_getglobal(L.get(), func_name.c_str());

    lua_pushnumber(L.get(), num);

    lua_pcall(L.get(), 1, 1, 0);

    int return_val = lua_tonumber(L.get(), -1);

    lua_pop(L.get(), 1);

    return return_val;

}


// Back end functions
int LuaWrapper::SendVariable(int num, std::string name)
{

    lua_pushnumber(L.get(), num);
    lua_setglobal(L.get(), name.c_str());

}


int LuaWrapper::SendVariable(float num, std::string name)
{

    lua_pushnumber(L.get(), num);
    lua_setglobal(L.get(), name.c_str());

}


int LuaWrapper::SendVariable(bool val, std::string name)
{

    lua_pushboolean(L.get(), val);
    lua_setglobal(L.get(), name.c_str());

}


int LuaWrapper::SendVariable(const char* val, std::string name)
{

    lua_pushstring(L.get(), val);
    lua_setglobal(L.get(), name.c_str());

}


int LuaWrapper::SendVariable(std::string val, std::string name)
{

    lua_pushstring(L.get(), val.c_str());
    lua_setglobal(L.get(), name.c_str());

}


int LuaWrapper::GetVariable(int &val, std::string name)
{

    lua_getglobal(L.get(), name.c_str());
    val = lua_tonumber(L.get(), -1);
    lua_pop(L.get(), 1);

}


int LuaWrapper::GetVariable(float &val, std::string name)
{

    lua_getglobal(L.get(), name.c_str());
    val = lua_tonumber(L.get(), -1);
    lua_pop(L.get(), 1);

}


int LuaWrapper::GetVariable(bool &val, std::string name)
{

    lua_getglobal(L.get(), name.c_str());
    val = lua_toboolean(L.get(), -1);
    lua_pop(L.get(), 1);

}


int LuaWrapper::GetVariable(std::string &val, std::string name)
{

    lua_getglobal(L.get(), name.c_str());
    val = lua_tostring(L.get(), -1);
    lua_pop(L.get(), 1);

}



