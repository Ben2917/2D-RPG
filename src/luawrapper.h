

#ifndef LUAWRAPPER_H_
#define LUAWRAPPER_H_


#include "lua/lua.hpp"
#include <string>
#include <cstdarg>
#include <memory>


class LuaWrapper
{


    public:


        LuaWrapper();


        LuaWrapper(const LuaWrapper &l);


        // loads a lua script file returns 0 for success
        int LoadFile(std::string filename);


        // Executes the loaded lua script chunk. returns -1
        // if no chunk has been loaded.
        int ExecuteChunk(); 
        

        int RunFunction(std::string func_name, int num);


        int SendVariable(int num, std::string name);


        int SendVariable(float num, std::string name);


        int SendVariable(bool val, std::string name);


        int SendVariable(const char* val, std::string name);


        int SendVariable(std::string val, std::string name);


        int GetVariable(int &val, std::string name);


        int GetVariable(float &val, std::string name);


        int GetVariable(bool &val, std::string name);


        int GetVariable(std::string &val, std::string name);


    private:


        std::shared_ptr<lua_State> L;


};


#endif // LUAWRAPPER_H_

