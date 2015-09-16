

#include "frameset.h"


FrameSet::FrameSet() : tex(nullptr, SDL_DestroyTexture) {}


void FrameSet::Render(int x, int y, SDL_Renderer *renderer)
{

	SDL_Rect dest =
	{ x, y, 64, 64};

	SDL_RenderCopy(renderer, tex.get(), 
            &clips[current_clip], &dest);
	        	
}


int FrameSet::SetClip(Uint32 clip_num)
{
    
    if(clip_num >= clips.size())
    {

        return -1;

    }

    current_clip = clip_num;
    return 0;
}


int FrameSet::GetClip()
{

	return current_clip;

}


int FrameSet::LoadSpriteSheet(SDL_Renderer *ren,
     std::string filename, float update_interval)
{
        
    this->update_interval = update_interval;

    tex.reset(IMG_LoadTexture(ren, filename.c_str()));

    if (tex.get() == nullptr)
    {

        return -1;

    }

    if(SetupClips() < 0)
    {

        return -2;

    }	

    return 0;

}


void FrameSet::UpdateFrame(float frame_time)
{

    if (frame_time > update_cache + update_interval)
    {

        ++current_clip;

        if (current_clip >= clips.size())
        {

            current_clip = 0;

        }

        update_cache = frame_time;

    } 

}


int FrameSet::SetupClips()
{


    int w, h;

    SDL_QueryTexture(tex.get(), NULL, NULL, &w, &h);

    if (w % 64 != 0 || h % 64 != 0)
    {

        return -1;

    }

    for (int i = 0; i < w / 64; ++i)
    {

        clips.push_back({i*64, 0, i*64 + 64, 64});

    }

    return 0;

}


