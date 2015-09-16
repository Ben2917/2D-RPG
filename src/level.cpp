

#include "level.h"


Level::Level(){}


Level::Level(SDL_Renderer* ren, std::string resource_dir, 
    int &level_w, int &level_h)
{

    std::vector<std::string> filenames;

    try
    {

        d_handler.ReadDirectory(resource_dir, filenames);

        FindLevelMapFile(filenames);

        LoadTiles(ren, filenames);

        LoadMap(resource_dir, level_w, level_h);

        player = GameObject(std::string("scripts/player.lua"),
            std::string("player"), std::string("save_file.txt"),
            new AnimatedGraphicsComponent(ren, "resources/player"),
            new PhysicsComponent(), new ControlComponent());

    }
    catch(int e)
    {

        HandleExceptions(e, resource_dir);

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


void Level::FindLevelMapFile(std::vector<std::string> &filenames)
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

        throw MAP_FIND_ERROR;

    }

}


int Level::LoadTiles(SDL_Renderer* ren, std::vector<std::string> filenames)
{

    for(unsigned int i = 0; i < filenames.size(); ++i)
    {

        // needs testing, may not work.
        tiles.insert(std::pair<std::string, GameTexture>
            (filenames[i], GameTexture(0, 0, ren, filenames[i])));

        // need to find a way to check for null textures in game texture
        // and throw tile error in this case.               
    }

    return 0;

}


void Level::LoadMap(std::string file_dir, int &level_w, int &level_h)
{

    std::string c_map_str;

    if(d_handler.ReadFile(file_dir, "map.txt", c_map_str) < 0)
    {

        throw MAP_LOAD_ERROR;

    }

    // parse the string to get data on tiles (locations 
    // and which assets to load) and level objects including their
    // locations, assets and collision boxes. Should also read level 
    // width and height.
    // should return negative numbers for each of the errors that could occur.
    // enemies should also be loaded here.
    //
    // maybe parse the string into modules and pass each module into the
    // function that it has information on.

}


void Level::HandleExceptions(int e, std::string resource_dir)
{

    switch(e)
    {

        case DIR_ERROR:
            ErrorPrinter::PrintError("Error opening directory " +
                resource_dir);
            break;
        case MAP_FIND_ERROR:
            ErrorPrinter::PrintError("Map file absent from directory " +
                resource_dir);
            break;
        case TILE_ERROR:
            ErrorPrinter::PrintError("Error lodaing one or more tiles.");
            break;
        case MAP_LOAD_ERROR:
            ErrorPrinter::PrintError(
                "Error parsing map file. It may have become corrupted.");
            break;
        default: 
            ErrorPrinter::PrintError(
                "An unexpected exception has occurred.");
            break;

    }

}
