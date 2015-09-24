

#include <iostream>


#include "game.h"


int main (int argc, char** argv)
{

    Game game(1280, 720, 60); 
 
    game.Run();
   
    SDL_Quit();

    return 0;

}
