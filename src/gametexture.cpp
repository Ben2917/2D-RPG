

#include "gametexture.h"


GameTexture::GameTexture()
    : tex(nullptr, SDL_DestroyTexture){}


GameTexture::GameTexture(int x, int y, SDL_Renderer* ren, std::string filename)
    : tex(IMG_LoadTexture(ren, filename.c_str()), SDL_DestroyTexture)
{

    rect.x = x;
    rect.y = y;

    if(tex.get() == nullptr)
    {

        // Log error.

    }

    SDL_QueryTexture(tex.get(), NULL, NULL, &rect.w, &rect.h);

    // add some error checking

}


SDL_Texture* GameTexture::Tex()
{

    return tex.get();

}


SDL_Rect GameTexture::Rect()
{

    return rect;

}
