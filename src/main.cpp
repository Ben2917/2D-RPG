
#include <iostream>

#include <string>

#include <sstream>

#include "game.h"


int CharPointerToInt(char* arg)
{

    int temp;

    std::stringstream stream;

    stream << arg;

    stream >> temp;

    return temp;

}


int ArgParser(int argc, char* argv[])
{

    if(argc == 1)
    {

        // Run main menu
        return 0;

    }
    else
    {

        if(argc < 3)
        {

            std::cout << "Too few arguments.\n"
                << "Usage:\n./<name>\n./<name> x y updates\n";
            return -1;

        }
        else
        {

            int x = CharPointerToInt(argv[1]);
 
            int y = CharPointerToInt(argv[2]);

            int updates = CharPointerToInt(argv[3]);

            Game game(x, y, updates);

            game.Run();

            return 0;

        }

    }

}


int main (int argc, char* argv[])
{

    if(ArgParser(argc, argv) < 0)
    {

        return -1;

    } 
    
    SDL_Quit();

    return 0;

}
