/*
 * This file contains the base classes that each of
 * the components for the game objects will be based off of
 */

#ifndef OBJECTBASE_H_
#define OBJECTBASE_H_


#include <SDL.h>


#include <vector>


class GameObject;


class GraphicsBase
{


    public:


        virtual void Update(SDL_Rect cam, SDL_Renderer* ren, GameObject &obj)
            = 0;

        virtual SDL_Rect GetDest() = 0;


        virtual ~GraphicsBase(){}


};


class PhysicsBase
{


    public:


        virtual void Update(GameObject &obj,
            std::vector<SDL_Rect> collision_rects);


        virtual ~PhysicsBase(){}


};


class ControlBase
{


    public:


        virtual void Update(float frame_time, GameObject &obj) = 0;


        virtual ~ControlBase(){}


};


#endif // OBJECTBASE_H_
