

#include "level.h"


DirectoryError::DirectoryError(std::string dir_name)
{

    message = std::string("Error finding directory ") + dir_name;

}


const char* DirectoryError::what()
{

    return message.c_str();

}


MapFindError::MapFindError(std::string dir_name)
{

    message = std::string("Couldn't find map file in directory ") +
        dir_name;

}


const char* MapFindError::what()
{

    return message.c_str();

}


MapLoadError::MapLoadError()
{

    message = std::string("Error loading map file. It may be corrupted");

}


const char* MapLoadError::what()
{

    return message.c_str();

}


LevelChunk::LevelChunk(SDL_Renderer* ren, int x, int y)
    : tex(SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
    SDL_TEXTUREACCESS_TARGET, 640, 640), SDL_DestroyTexture)
{

    dest = {x, y, 640, 640};

}


void LevelChunk::Update(SDL_Renderer* ren, SDL_Rect camera)
{

    // Draw chunk texture relative to camera
    
    // Draw objects in chunk relative to camera

}


void LevelChunk::AddTile(SDL_Renderer* ren, GameTexture tex, bool collidable)
{

    SDL_SetRenderTarget(ren, this->tex.get()); // render to chunk texture

    SDL_RenderCopy(ren, tex.Tex(), NULL, tex.Rect());

    SDL_SetRenderTarget(ren, NULL);

    if(collidable)
    {

        collision_rects.push_back(tex.Rect());

    }

}


void LevelChunk::AddObject(GameObject obj)
{

    objects.push_back(obj);

}


std::vector<SDL_Rect> LevelChunk::GetCollisionRects()
{

    return collision_rects;

}


Level::Level(){}


Level::Level(SDL_Renderer* ren, std::string resource_dir, 
    int &level_w, int &level_h)
{

    std::vector<std::string> filenames;

    try
    {

        // d_handler.ReadDirectory(resource_dir, filenames);

        // FindLevelMapFile(resource_dir, filenames);

        if(d_handler.SearchDirectory("map.txt", resource_dir))
        {

            LoadMap(resource_dir, level_w, level_h);
        // load map must load the tile key. The tiles must then
        // be loaded by searching the directory and confirming
        // that the files are there before loading.

        LoadTiles(ren, filenames);

        player = GameObject(std::string("scripts/player.lua"),
            std::string("player"), std::string("save_file.txt"),
            new AnimatedGraphicsComponent(ren, "resources/player"),
            new PhysicsComponent(), new ControlComponent());

        }
        else
        {

            std::cout << "No valid map file was found in this directory.";

        }

    }
    catch(std::exception e)
    {

        ErrorPrinter::PrintError(e.what());

    }
    catch(...)
    {

        ErrorPrinter::PrintError
            ("Unexpected error occurred constructing level");

    }


}


Level::~Level(){}


void Level::Update(SDL_Renderer* ren, SDL_Rect camera, float frame_time)
{

    // calculate which tile/s the player is in. 

    // create a vector of the objects in those tiles.

    // send that vector instead of all level objects

    // encapsulate this in it's own function.

    player.Update(camera, ren, frame_time, level_objects);
 
    // Maybe only draw tiles that are in the camera range.
    // Didn't seem to provide a huge performance boost, however.
   
    for(auto itr = tiles.begin(); itr != tiles.end(); ++itr)
    {
     
        SDL_Rect temp = itr->second.Rect();
   
        SDL_RenderCopy(ren, itr->second.Tex(), NULL, &temp); 

    }

}


void Level::FindLevelMapFile(std::string dir_name, 
    std::vector<std::string> &filenames)
{

    bool file_found = false;

    for(unsigned int i = 0; i < filenames.size(); ++i)
    {

        if(filenames[i] == "map.txt")
        {
                       
            filenames.erase(filenames.begin() + i); 
            file_found = true;

        }

    }
    if (!file_found)
    {

        throw MapFindError(dir_name);

    }

}


int Level::LoadTiles(SDL_Renderer* ren, std::vector<std::string> filenames)
{

    for(unsigned int i = 0; i < filenames.size(); ++i)
    {

        tiles.insert(std::pair<std::string, GameTexture>
            (filenames[i], GameTexture(0, 0, ren, filenames[i])));
                      
    }

    return 0;

}


void Level::LoadMap(std::string file_dir, int &level_w, int &level_h)
{

    std::string c_map_str;

    if(d_handler.ReadFile(file_dir, "map.txt", c_map_str) < 0)
    {

        throw MapLoadError();

    }

    // find marker that marks where the level map begins
    // load map into two dimensional array

    // need to load each level into 640 by 640 tiles and load a collision
    // rectangle for each collidable part.

    std::array<std::array<int, 50>, 50> map;


    // maybe parse the string into modules and pass each module into the
    // function that it has information on.

}
