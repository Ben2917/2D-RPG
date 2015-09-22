

#include "gameobject.h"


GraphicsComponent::GraphicsComponent(SDL_Renderer* ren, std::string filename)
{

    tex = GameTexture(0, 0, ren, filename);    

}


GraphicsComponent::~GraphicsComponent() {}


void GraphicsComponent::Update(SDL_Renderer* ren, GameObject &obj)
{

   /*
    *
    * Get the new location of the player as calculated 
    * in the physics component.
    *
    * int x, y;
    *
    * obj->LuaWrapper.GetVariable(x, "Player.x");
    * obj->LuaWrapper.GetVariable(y, "Player.y");
    *
    * render at destination
    */  

}


SDL_Rect GraphicsComponent::GetDest()
{

    return tex.Rect();

}


AnimatedGraphicsComponent::AnimatedGraphicsComponent(
    SDL_Renderer* ren, std::string dir_name)
{

    LoadFramesets(ren, dir_name);

}


AnimatedGraphicsComponent::~AnimatedGraphicsComponent(){}


void AnimatedGraphicsComponent::Update(SDL_Rect camera, SDL_Renderer* ren, 
    GameObject &obj)
{

    int x, y;

    obj.lua.GetVariable(x, "Player.x");

    obj.lua.GetVariable(y, "Player.y");

    x -= camera.x;

    y -= camera.y;

    // get state
    // if player is moving call update, otherwise don't

    int player_direction;

    obj.lua.GetVariable(player_direction, "Player.direction");

    frame_sets[player_direction].Render(x, y, ren);

}


SDL_Rect AnimatedGraphicsComponent::GetDest(){}


void AnimatedGraphicsComponent::LoadFramesets(SDL_Renderer* ren, 
    std::string dir_name)
{

    std::vector<std::string> filenames;

    d.ReadDirectory(dir_name, filenames);

    // NOTE: check update interval.
    // NOTE: needs better error checking

    // needs fixing so that this is an automated process
    // and is not specific for player

    // probably needs to parse file names looking for directions
    // and set spritesheets accordingly.
    
    frame_sets[UP].LoadSpriteSheet(ren, 
        std::string("resources/link_up.png"), 0.125);

    frame_sets[DOWN].LoadSpriteSheet(ren,
        std::string("resources/link_down.png"), 0.125);

    frame_sets[LEFT].LoadSpriteSheet(ren,
        std::string("resources/link_left.png"), 0.125);

    frame_sets[RIGHT].LoadSpriteSheet(ren,
        std::string("resources/link_right.png"), 0.125);

}


PhysicsComponent::PhysicsComponent(){}


PhysicsComponent::~PhysicsComponent(){}


void PhysicsComponent::Update(GameObject &obj, 
    std::vector<SDL_Rect> collision_rects)
{

    // See if obj rect is within any of the objects' rectangles.
    // if it is, need to check the current direction and move back in the
    // opposite direction. Update will need to have the frame time passed to
    // it to do this.

}


ControlComponent::ControlComponent(){}


ControlComponent::~ControlComponent(){}


void ControlComponent::Update(float frame_time, GameObject &obj)
{

    HandleKeys(frame_time, obj);

}


void ControlComponent::HandleKeys(float frame_time, GameObject &obj)
{

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if(state[SDL_SCANCODE_UP])
    {

        obj.lua.RunFunction("Player.MoveUp", frame_time);

    }

    if(state[SDL_SCANCODE_DOWN])
    {

        obj.lua.RunFunction("Player.MoveDown", frame_time);

    }

    if(state[SDL_SCANCODE_LEFT])
    {

        obj.lua.RunFunction("Player.MoveLeft", frame_time);

    }

    if(state[SDL_SCANCODE_RIGHT])
    {

        obj.lua.RunFunction("Player.MoveRight", frame_time);

    }

    obj.lua.RunFunction("Player.SetIdle", 0.0);

}


GameObject::GameObject()
    : graphics(nullptr), physics(nullptr), control(nullptr){}


GameObject::GameObject(const GameObject &g)
    : graphics(g.graphics), physics(g.physics),
    control(g.control), lua(g.lua){}

// Constructor for non-player controlled objects
GameObject::GameObject(std::string script_filename, GraphicsBase* g,
    PhysicsBase* p) : graphics(g), physics(p), control(nullptr)
{

    lua.LoadFile(script_filename); // error check needed.

    lua.ExecuteChunk();

    collision_box = graphics.get()->GetDest();    

}


GameObject::GameObject(std::string script_filename, std::string data_dir,
    std::string data_file, GraphicsBase* g, PhysicsBase* p, ControlBase* c) 
    : graphics(g), physics(p), control(c)
{

    lua.LoadFile(script_filename);

    lua.ExecuteChunk(); // now data can be loaded into player class in script.

    // if datafile string isn't blank open and load the data
    // from the file into the corresponding variables in the script.

       

}


GameObject::~GameObject(){}


void GameObject::Update(SDL_Rect camera, SDL_Renderer* ren, float frame_time,
    std::vector<SDL_Rect> collision_rects)
{


    control.get()->Update(frame_time, *this);

    physics.get()->Update(*this, collision_rects);

    graphics.get()->Update(camera, ren, *this);


}


int GameObject::LoadBaseScript(std::string script_name)
{

    // return negative if file cannot be loaded or executed.

    lua.LoadFile(script_name);

    lua.ExecuteChunk();

}


int GameObject::LoadScriptWithData(std::string data_dir, 
    std::string data_file, std::string script_name)
{

    LoadBaseScript(script_name);

    DirectoryHandler d;

    std::string data;

    d.ReadFile(data_dir, data_file, data);

    // read in player stats and pass them into script.
    
    // read in globals and set them.

}




