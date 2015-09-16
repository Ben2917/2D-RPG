
#ifndef BTEXTURE_H_
#define BTEXTURE_H_


#include <SDL.h>
#include <SDL_image.h>


#include <memory>
#include <vector>
#include <string>


#include "errorprinter.h"


/*
 * This class encapsulates sets of animation frames for sprites
 * It also handles the animation of frames by iterating through
 * sets based on the frame time.
 */
class FrameSet
{


    public:


        FrameSet();


	/*
        Renders the current clip of the sprite sheet.
	@param x - The x location to draw the texture at.
	@param y - The y location to draw the texture at.
	@param ren - The renderer to render the texture to.
	*/
	void Render(int x, int y, SDL_Renderer* ren);


        /*
         * Sets the current clip index to the number specified.
         * @param clip_num - The number to set the clip index to.
         * returns 0 for success
         * returns -1 for out of vector bounds
         */
        int SetClip(Uint32 clip_num);

        
        /*
         * Gets the index for the current clip and returns it.
         */
	int GetClip();


        /*
         * Loads a sprite sheet of any supported image format
         * and automatically loads clips for each of the sprites into
         * the clip vector.
         * returns 0 for success 
         * returns < 0 for failure
         * @param ren - The renderer to load the texture to.
         * @param filename - The filename for the sprite sheet.
         * @param update_interval - Sets how often the sprite
         * sheet frame should be updated.
         */
	int LoadSpriteSheet(SDL_Renderer *ren, std::string filename,
            float update_interval);


        /*
         * Updates the surrent sprite sheet clip based on the frame time
         * and the update interval set upon initialisation.
         * @param frame_time - The time taken to render the previous frame.
         */ 
        void UpdateFrame(float frame_time);

       
    private:

	
        // The main texture for the class
	std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> tex;

        
        // Stores a clip for each sprite on the sprite sheet.
	std::vector<SDL_Rect> clips;

 
        // Tracks the index of the current clip in the clip vector
        Uint32 current_clip;


        /*
         * Loads all of the clips for the sprite sheet.
         * returns 0 for success
         * returns -1 if sprite sheet w and h are not
         * divisible by 64
         */
        int SetupClips();


        float update_interval;

        
        float update_cache; // caches the previous
        //  time when the frame was updated

};


#endif // BTEXTURE_H_
