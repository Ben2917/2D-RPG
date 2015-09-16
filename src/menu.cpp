

#include "menu.h"


template<typename Func> Button<Func>::Button()
    : tex_one(nullptr, SDL_DestroyTexture),
    tex_two(nullptr, SDL_DestroyTexture) {}


template<typename Func> Button<Func>::Button(const Button& b)
    : tex_one(b.tex_one), tex_two(b.tex_two),
    function(b.function), dest(b.dest), base_dest(b.base_dest) 
{

    if(tex_one.get() == nullptr || tex_two.get() == nullptr)
    {

        // to be changed to use debug file
        std::cout << "Problem copying tex one or two\n";

    }

    int w, h;

    SDL_QueryTexture(tex_one.get(), NULL, NULL, &w, &h);

}


template<typename Func> Button<Func>::Button(int x, int y, Func func,
    SDL_Renderer* ren, std::string tex_name_one, std::string tex_name_two) 
    : tex_one(IMG_LoadTexture(ren, tex_name_one.c_str()), SDL_DestroyTexture),
    tex_two(IMG_LoadTexture(ren, tex_name_two.c_str()), SDL_DestroyTexture)
{

    function = func;

    int w, h;

    if(tex_one.get() == nullptr || tex_two.get() == nullptr)
    {

        // to be changed to write to the debug file
        std::cout << "Error loading texture one or two\n";

    }

    SDL_QueryTexture(tex_one.get(), NULL, NULL, &w, &h);

    dest = {x, y, w, h}; 

    base_dest = dest;

}


template <typename Func> 
    template <class Param> void Button<Func>::Update(Param p)
{

    if(InButton())
    {

        function(p);

    }

}


template <typename Func> void Button<Func>::Draw(SDL_Renderer* ren)
{

    if(tex_one.get() == nullptr || tex_two.get() == nullptr)
    {

        std::cout << "Attempting to render null button texture.\n";

    }

    if(!InButton())
    {

        SDL_RenderCopy(ren, tex_one.get(), NULL, &dest);

    }
    else
    {

        SDL_RenderCopy(ren, tex_two.get(), NULL, &dest);                

    }

}


template <typename Func> bool Button<Func>::InButton()
{

    int x, y;

    SDL_GetMouseState(&x, &y);
 
    if(InRange(x, dest.x, dest.x + dest.w)
        && InRange(y, dest.y, dest.y + dest.h))
    {

        return true;

    }

   return false;

}


template <typename Func> bool Button<Func>::InRange(
    int check, int lower, int upper)
{

    if(check > lower && check < upper)
    {

        return true;

    }

    return false;        

}


template <typename Func> void Button<Func>::ModifyDest(int x, int y)
{

    dest.x = base_dest.x + x;

    dest.y = base_dest.y + y;

}


template <typename Func> Menu<Func>::Menu() 
    : tex(nullptr, SDL_DestroyTexture) {}


template <typename Func> Menu<Func>::Menu(const Menu<Func> &m)
    : tex(m.tex), dest(m.dest), buttons(m.buttons), visible(m.visible)
{

    if(tex.get() == nullptr)
    {

        // to be changed to write to the debug file
        std::cout << "error copying menu texture.\n";

    }

}


template <typename Func> Menu<Func>::Menu( int x, int y, bool is_static,            SDL_Renderer* ren, std::string tex_name) 
    : tex(IMG_LoadTexture(ren, tex_name.c_str()), SDL_DestroyTexture)
{

    this->is_static = is_static;

    if(this->is_static)
    {

        visible = true;
    }
    else
    {

        visible = false;

    }

    int w, h;

    if(tex.get() == nullptr)
    {

        // to be changed to write to the debug file
        std::cout << "Error loading menu texture.\n";

    }

    SDL_QueryTexture(tex.get(), NULL, NULL, &w, &h);

    dest = {x, y, w, h};

}


template<typename Func> void Menu<Func>::AddButton(int x, int y, Func func,
    SDL_Renderer* ren, std::string b_tex_one, std::string b_tex_two)
{

    buttons.push_back(Button<Func>(x, y, func, ren, b_tex_one, b_tex_two));

}


template <typename Func> 
    template <typename Param> void Menu<Func>::Update(SDL_Event e, Param p)
{

    if(e.type == SDL_MOUSEBUTTONDOWN)
    {
        
        if(e.button.button == SDL_BUTTON_RIGHT && !is_static)
        {

            visible = true;

            SDL_GetMouseState(&dest.x, &dest.y);

        }
        if(e.button.button == SDL_BUTTON_LEFT)
        {

            if(!MouseInMenu())
            {

                visible = false;

            }
            else
            {

                if(visible)
                {

                    for(auto itr = buttons.begin(); itr < buttons.end(); ++itr)
                    {

                        itr->Update(p);

                    }

                }

            }
       
        }

    }

}


template <typename Func> void Menu<Func>::Draw(SDL_Renderer* ren)
{

    if(visible)
    {

        SDL_RenderCopy(ren, tex.get(), NULL, &dest);

        if(tex.get() == nullptr)
        {

            std::cout << "Attempting to render null texture.\n";

        }

        for(auto itr = buttons.begin(); itr < buttons.end(); ++itr)
        {

            itr->ModifyDest(dest.x, dest.y);

            itr->Draw(ren);

        }

    }

}


bool InRange(int check, int lower, int upper)
{

    if(check > lower && check < upper)
    {

        return true;

    }

    return false;

}


template <typename Func> bool Menu<Func>::MouseInMenu()
{

    int x, y;

    SDL_GetMouseState(&x, &y);

    if(InRange(x, dest.x, dest.x + dest.w) &&
        InRange(y, dest.y, dest.y + dest.h))
    {

        return true;

    }

    return false;

}


