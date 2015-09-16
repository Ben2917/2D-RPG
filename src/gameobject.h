

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_


#include <SDL.h>
#include <SDL_image.h>


#include "objectbase.h"
#include "luawrapper.h"
#include "dirhandler.h"
#include "gametexture.h"
#include "frameset.h"


#include <string>
#include <memory>
#include <vector>
#include <map>


class GraphicsComponent : public GraphicsBase
{


    public:


        GraphicsComponent(SDL_Renderer *ren, std::string filename);


        virtual ~GraphicsComponent();

        
        // Change all update functions to return integers so that exception
        // checking in the game object is much easier.
        // Should update the graphics for the menu.
        virtual void Update(SDL_Renderer *ren, GameObject &obj);


        virtual SDL_Rect GetDest();


    private:


        GameTexture tex;


};


class AnimatedGraphicsComponent : public GraphicsBase
{


    public:


        AnimatedGraphicsComponent(SDL_Renderer* ren, std::string dir_name);


        virtual ~AnimatedGraphicsComponent();


        virtual void Update(SDL_Rect camera, SDL_Renderer* ren, 
            GameObject &obj);


        virtual SDL_Rect GetDest();


    private:


        std::vector<FrameSet> frame_sets;


        enum directions {UP, DOWN, LEFT, RIGHT};


        DirectoryHandler d;


        void LoadFramesets(SDL_Renderer* ren, std::string dir_name);


};


class PhysicsComponent : public PhysicsBase
{


    public:


        PhysicsComponent();


        virtual ~PhysicsComponent();


        virtual void Update(GameObject &obj,
            std::vector<GameObject> objects);


    private:
       

        // function required to check if any of the player collision boxes
        // intersect with the given collision boxes.

};


class ControlComponent : public ControlBase
{


    public:


        ControlComponent();


        virtual ~ControlComponent();


        // Should contain the update function for the menu.
        virtual void Update(float frame_time, GameObject &obj);


    private:

        
        void HandleKeys(float frame_time, GameObject &obj);


};


/*
 * This class is a little bloated, may need to create player
 * class to inherit this one and add it's own features.
 * */
class GameObject
{


    public:


        GameObject();


        GameObject(const GameObject &g);


        GameObject(std::string script_filename, GraphicsBase* g,
            PhysicsBase* p);

        // constructor is only needed for players.
        GameObject(std::string script_filename, std::string data_dir,
            std::string data_file, GraphicsBase* g, PhysicsBase* p, 
            ControlBase* c);

        
        ~GameObject();

        
        // GameObjects don't need to perform the collision check,
        // only the player does.
        void Update(SDL_Rect camera, SDL_Renderer* ren, float frame_time,
            std::vector<GameObject> objects);


        LuaWrapper lua;


    private:


        std::shared_ptr<GraphicsBase> graphics;


        std::shared_ptr<PhysicsBase> physics;


        // control component only needed for players.
        std::shared_ptr<ControlBase> control;

        // shouldn't need more than one collision box
        // std::vector<SDL_Rect> collision_boxes;

        SDL_Rect collision_box;


        // used to index the collision box vector.
        enum directions {UP, DOWN, LEFT, RIGHT};


        int LoadBaseScript(std::string script_name);


        int LoadScriptWithData(std::string data_dir, 
            std::string data_file, std::string script_name);


};


#endif // GAMEOBJECT_H_
