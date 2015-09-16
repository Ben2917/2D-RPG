

#ifndef GAMETEXTURE_H_
#define GAMETEXTURE_H_


#include <SDL.h>
#include <SDL_image.h>


#include <memory>
#include <string>


class GameTexture
{


    public:


        GameTexture();


        GameTexture(int x, int y, SDL_Renderer* ren, std::string filename);


        SDL_Texture* Tex();


        SDL_Rect Rect();


    private:


        std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> tex;


        SDL_Rect rect;
        


};


#endif // GAMETEXTURE_H_

