//
//  SDLWindow.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef SDLWindow_hpp
#define SDLWindow_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "window.h"

namespace dc
{
    class CSDLWindow : public IWindow
    {
    public:
        CSDLWindow(const TDisplayInfo& displayInfo) : IWindow(displayInfo) {}
        
    protected:
            ~CSDLWindow() {}

    public:
        void Initialize() override;
        void Terminate() override;
        
    private:
        //The window we'll be rendering to
        SDL_Window* window = NULL;
        
        //The surface contained by the window
        SDL_Surface* screenSurface = NULL;
    };
}

#endif /* SDLWindow_hpp */
