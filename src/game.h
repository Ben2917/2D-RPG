

#ifndef GAME_H_
#define GAME_H_


#include <SDL.h>
#include <SDL_image.h>


#include "gamewindow.h"
#include "timer.h"
#include "menu.h"
#include "gametexture.h"
#include "level.h"
#include "dirhandler.h"


#include <vector>
#include <iostream>


class Game
{

    
    public:


        Game(int w, int h, int target_update);


        ~Game();


        void Run();


    private:


        bool app_quit;


        DirectoryHandler d;


        GameWindow main_window;


        Timer game_timer;


        float frame_time_ms;


        Uint32 frame_time_s; 
 

        Level current_level;
       

        void LoadGame();

        
        void EventLoop();


        void Events(SDL_Event e);


        void MainLoop();


};


#endif // GAME_H_
