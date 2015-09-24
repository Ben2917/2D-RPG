

#include "game.h"


Game::Game(int w, int h, int update_target)
    : main_window("Strategy game", 0, 0, w, h, 0, update_target)
{

    app_quit = false;

    LoadGame(); // loads the save file 

}


Game::~Game(){}


void Game::Run()
{
    
    MainLoop();

}


void Game::LoadGame()
{

    std::string save_file;

    d.ReadFile("player", "save_file.txt", save_file);

    if(ParseSaveFile(save_file)) // returns true if it has loaded a level
    {

        

    }
    else
    {

        // load default level

    }

    // each level will need a string key to differentiate them.
    
    int w = 0, h = 0; // variables to be filled with level width and height.

    main_window.SetLevelDimensions(w, h);

}


bool Game::ParseSaveFile(std::string save_file_str)
{

    

}


void Game::EventLoop()
{

    SDL_Event e;

    while(SDL_PollEvent(&e))
    {

        Events(e);

    }

}


void Game::Events(SDL_Event e)
{

    app_quit = main_window.HandleEvent(e);

    // other event handler functions

}


void Game::MainLoop()
{

    frame_time_ms = 0.0;

    frame_time_s = 0;

    while(!app_quit)
    {

        // neaten up

        game_timer.StartTimer();

        EventLoop();

        main_window.ClearRenderer({127, 127, 127, 255});

        // adapt to be based on player not mouse
        main_window.MoveCamera(frame_time_ms);

        main_window.PresentRenderer();

        game_timer.PauseTimer();

        frame_time_s = game_timer.GetTimeMs();

        game_timer.RestartTimer();

        main_window.PerformDelay(frame_time_s);

        game_timer.StopTimer();

        frame_time_ms = game_timer.GetTimeSeconds();

    }

}
