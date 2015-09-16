

#ifndef MENU_H_
#define MENU_H_


#include <SDL.h>
#include <SDL_image.h>


#include <vector>
#include <memory>
#include <iostream>
#include <string>


template<typename Func> class Button
{


    public:


        Button();


        Button(const Button<Func>& b);


        Button(int x, int y, Func func, SDL_Renderer* ren,
            std::string tex_name_one, std::string tex_name_two);


        template <typename Param> void Update(Param p);


        void Draw(SDL_Renderer* ren);


        void ModifyDest(int x, int y);


    private:


        Func function;


        SDL_Rect dest;


        SDL_Rect base_dest;


        std::shared_ptr<SDL_Texture> tex_one;


        std::shared_ptr<SDL_Texture> tex_two; 


        bool InButton();


        bool InRange(int check, int lower, int upper);


};


template<typename Func> class Menu
{


    public:


        Menu();


        Menu(const Menu<Func>& m);


        Menu(int x, int y, bool is_static, SDL_Renderer* ren, 
            std::string tex_name);


        void AddButton(int x, int y, Func func, SDL_Renderer* ren, 
            std::string b_tex_one, std::string b_tex_two);


        template <typename Param> void Update(SDL_Event e, Param p);


        void Draw(SDL_Renderer* ren);

        
        bool MouseInMenu();


    private:


        bool visible;


        bool is_static;


        SDL_Rect dest;


        std::vector<Button<Func>> buttons;


        std::shared_ptr<SDL_Texture> tex; 


};


#endif // MENU_H_
