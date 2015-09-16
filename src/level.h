

#ifndef LEVEL_H_
#define LEVEL_H_


#include <SDL.h>
#include <SDL_image.h>


// Will need to include the exception system here.


#include <string>
#include <map>
#include <vector>
#include <memory>


#include "dirhandler.h"
#include "gameobject.h"
#include "gametexture.h"


// levels need to include information on on what levels they are connected to
// so that when a player gets to the edge of the level the game knows which
// level to load next.

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


        enum Exceptions {
            DIR_ERROR, MAP_FIND_ERROR, 
            TILE_ERROR, MAP_LOAD_ERROR };


        // Player exists as part of a level
        // need to have player load a file that
        // stores information on how it should look
        // and all of its stats, inventory etc.
        GameObject player;

        
        DirectoryHandler d_handler;


        std::map<std::string, GameTexture> tiles;
        

        // not sure if need map or vector
        // std::map<std::string, GameObject> level_objects;
        std::vector<GameObject> level_objects;


        void FindLevelMapFile(std::vector<std::string> &filenames);


        int LoadTiles(SDL_Renderer* ren, std::vector<std::string> filenames);


        // Loads all tiles and level objects into their positions.
        void LoadMap(std::string file_dir, int &level_w, int &level_h);


        void HandleExceptions(int e, std::string resource_dir);


};



#endif // LEVEL_H_
