

#include <iostream>


#include "gamewindow.h"


GameWindow::GameWindow()
    : win(nullptr, SDL_DestroyWindow)
    , ren(nullptr, SDL_DestroyRenderer)
{}

// neaten up
GameWindow::GameWindow(std::string title, int x, int y, int w, int h,
    Uint32 window_flag, int update_target)
    : win(SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_SHOWN), 
        SDL_DestroyWindow)
    , ren(SDL_CreateRenderer(win.get(), -1, SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC), SDL_DestroyRenderer)
{

    float temp = 1.0 / update_target * 1000;

    update_delay = Uint32(temp);

    // level needs access to write width and height for the camera bounds.

    // this->level_w

    // this->level_h

    fullscreen = false;

    if(SetWindow(window_flag) < 0)
    {

       // report error 

    }

    // Camera is set to be the same size as the window
    camera = {x, y, w, h};    


}


GameWindow::~GameWindow(){}


void GameWindow::ClearRenderer(SDL_Color colour)
{

    SDL_SetRenderDrawColor(ren.get(), colour.r, colour.g, colour.b, colour.a);

    SDL_RenderClear(ren.get());

}


SDL_Renderer* GameWindow::GetRenderer()
{

    return ren.get();

}


void GameWindow::PerformDelay(Uint32 frame_time)
{

    if(frame_time <= update_delay)
    {

        Uint32 delay_time = update_delay - frame_time;

        if(delay_time >= overflow && overflow > 0)
        {

            --delay_time;
            --overflow;

        }

        SDL_Delay(delay_time);

    }
    else
    {

        overflow = frame_time - update_delay;       

    }

}


void GameWindow::PresentRenderer()
{

    SDL_RenderPresent(ren.get());

}


int GameWindow::SetWindow(Uint32 window_flag)
{

    int result;

    result =  SDL_SetWindowFullscreen(win.get(), window_flag);

    if(result == 0)
    {

        if(window_flag == SDL_WINDOW_FULLSCREEN)
        {

            fullscreen = true;

        }
        else if(window_flag == 0)
        {

            fullscreen = false;

        }

    }

    return result;

}


void GameWindow::MoveCamera(float frame_time)
{
    
    // need to update this so that the camera sticks to the player 
    // keeping them central on the screen.
    int mouse_x, mouse_y;

    SDL_GetMouseState(&mouse_x, &mouse_y);

    if (mouse_x > 0 && mouse_x < 40)
    {

        camera.x -= 320 * frame_time;

    }

    if (mouse_x > (camera.w - 40) && mouse_x < camera.w)
    {
        
        camera.x += 320 * frame_time;

    }

    if (mouse_y > 0 && mouse_y < 40)
    {

        camera.y -= 320 * frame_time;

    }

    if (mouse_y > (camera.h - 40) && mouse_y < camera.h)
    {

        camera.y += 320 * frame_time;

    }

    CheckCameraInBounds();    

}


SDL_Rect GameWindow::GetCamera()
{

    return camera;

}


bool GameWindow::HandleEvent(SDL_Event e)
{

    if(e.type == SDL_QUIT)
    {

        return true;

    }
    if(e.type == SDL_KEYDOWN)
    {

        if(e.key.keysym.sym == SDLK_f)
        {

            if(!fullscreen)
            {

                SetWindow(SDL_WINDOW_FULLSCREEN);

            }
            else
            {

                SetWindow(0);

            }

        }

    
        else if(e.key.keysym.sym == SDLK_ESCAPE)
        {

            return true;

        }

    }

    return false;

}


void GameWindow::GetLevelDimensions(int &w, int &h)
{

    w = level_w;

    h = level_h;

}


void GameWindow::SetLevelDimensions(int w, int h)
{

    level_w = w;

    level_h = h;

}


void GameWindow::CheckCameraInBounds()
{

    if (camera.x < 0)
    {

        camera.x = 0;

    }

    if (camera.x + camera.w > level_w)
    {

        camera.x = level_w - camera.w;

    }

    if (camera.y < 0)
    {

        camera.y = 0;

    }

    if (camera.y + camera.h > level_h)
    {

        camera.y = level_h - camera.h;

    }

}


