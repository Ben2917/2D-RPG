

#include "gametexture.h"


TextureError::TextureError(std::string tex_name)
{

    message = std::string("Error loading texture ") + tex_name;
    message += std::string
        ("\nYou may want to check the file exists in the correct path.");

}


const char* TextureError::what()
{

    return message.c_str();

}


GameTexture::GameTexture()
    : tex(nullptr, SDL_DestroyTexture){}


GameTexture::GameTexture(int x, int y, SDL_Renderer* ren, std::string filename)
    : tex(IMG_LoadTexture(ren, filename.c_str()), SDL_DestroyTexture)
{

    rect.x = x;
    rect.y = y;

    if(tex.get() == nullptr)
    {

         throw TextureError(filename);

    }

    SDL_QueryTexture(tex.get(), NULL, NULL, &rect.w, &rect.h);

    
}


SDL_Texture* GameTexture::Tex()
{

    return tex.get();

}


SDL_Rect GameTexture::Rect()
{

    return rect;

}
