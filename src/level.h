

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


        LevelChunk(SDL_Renderer* ren, int x, int y);

        // Draw the chunk texture and any objects in the chunk to the renderer
        // keeping them relative to the camera.
        void Update(SDL_Renderer* ren, SDL_Rect camera);


        // Draws a tile to the chunk texture
        // if collidable is true tex's rect will 
        // be pushed into the collision rects
        void AddTile(SDL_Renderer* ren, GameTexture tex, bool collidable);


        // Adds a game object 
        void AddObject(GameObject obj);


        // Returns the collision rects of the tile
        // so that they can be passed to player and
        // collision can be checked
        std::vector<SDL_Rect> GetCollisionRects();
        

    private:

        
        std::vector<SDL_Rect> collision_rects;


        // Stores game objects and level triggers that appear in the
        // chunk
        std::vector<GameObject> objects;

        // The main texture of the chunk
        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> tex;
 

        // The destination for the main chunk texture.
        SDL_Rect dest;
       
        
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


        // Chunks are the components that make up levels
        std::vector<LevelChunk> chunks;


        // Checks directory for level map file
        void FindLevelMapFile(std::string dir_name, 
            std::vector<std::string> &filenames);

      
        int LoadTiles(SDL_Renderer* ren, std::vector<std::string> filenames);


        void LoadMap(std::string file_dir, int &level_w, int &level_h);


};



#endif // LEVEL_H_
