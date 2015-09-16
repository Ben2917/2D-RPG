

#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_


#include <SDL.h>


#include <memory>
#include <string>


class GameWindow
{


    public:
  
        
        bool fullscreen;


        GameWindow();


        GameWindow(std::string title, int x, int y,
            int w, int h, Uint32 window_flag, int update_target);


        ~GameWindow();


        void ClearRenderer(SDL_Color colour);
    

        SDL_Renderer* GetRenderer();

        
        void PerformDelay(Uint32 frame_time);


        void PresentRenderer();


        int SetWindow(Uint32 window_flag);


        void MoveCamera(float frame_time);


        bool HandleEvent(SDL_Event e);


        // Move to level
        void GetLevelDimensions(int &w, int &h);


        void SetLevelDimensions(int w, int h);


        SDL_Rect GetCamera();


    private:


        int width;


        int height;

        
        int level_w;


        int level_h;


        Uint32 update_delay;


        Uint32 overflow;


        SDL_Rect camera;

        
        std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> win;


        std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> ren;


        void CheckCameraInBounds();

};


#endif // GAMEWINDOW_H_
