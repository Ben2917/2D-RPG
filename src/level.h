

#ifndef LEVEL_H_
#define LEVEL_H_


#include <SDL.h>
#include <SDL_image.h>


#include <string>
#include <map>
#include <vector>
#include <memory>
#include <exception>
#include <sstream>


#include "dirhandler.h"
#include "gameobject.h"
#include "gametexture.h"


// levels need to include information on on what levels they are connected to
// so that when a player gets to the edge of the level the game knows which
// level to load next.


class DirectoryError : public std::exception
{


    public:


        DirectoryError(std::string dir_name);


        virtual const char* what();


    protected:


        std::string message;


};


class MapFindError : public std::exception
{


    public:


        MapFindError(std::string dir_name);


        virtual const char* what();


    protected:


        std::string message;


};


class MapLoadError : public std::exception
{


    public:


        MapLoadError();


        virtual const char* what();


    protected:


        std::string message;


};


// Level chunks store a 640 by 640 texture made up of tiles,
// a vector of game objects that appear in the chunk and
// a vector of rectangles to check the player's collision against.
class LevelChunk
{


    public:


        LevelTile(SDL_Renderer* ren);


        void Update(SDL_Renderer* ren);


        void AddTile(GameTexture tex, bool collidable);


        // collision is checked in player. This means this class
        // needs to return it's collision rects.


    private:


        std::vector<SDL_Rect> collision_rects;

        
        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> tex;
        
        
};


class Level
{


    public:


        Level();


        Level(SDL_Renderer* ren, std::string resource_dir, int &level_w,
            int &level_h); 


        ~Level();


        void HandleEvent(SDL_Event e);


        void Update(SDL_Renderer* ren, SDL_Rect camera, float frame_time);


    private:


        GameObject player;

        
        DirectoryHandler d_handler;


        std::vector<std::string> tile_key;


        std::vector<GameTexture> tiles;


        std::vector<LevelTile> level_tiles;
        

        // not sure if need map or vector
        // std::map<std::string, GameObject> level_objects;
        std::vector<GameObject> level_objects;


        void FindLevelMapFile(std::string dir_name, 
            std::vector<std::string> &filenames);


        int LoadTiles(SDL_Renderer* ren, std::vector<std::string> filenames);


        // Loads all tiles and level objects into their positions.
        void LoadMap(std::string file_dir, int &level_w, int &level_h);


};



#endif // LEVEL_H_
