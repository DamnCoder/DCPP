//
//  SDLWindow.cpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#include "window/sdlwindow.h"
#include <cassert>

namespace dc
{
    void CSDLWindow::Initialize()
    {
        const int opCode = SDL_Init( SDL_INIT_VIDEO );
        
        assert(-1 < opCode && "SDL could not be initialized");
        
        //Create window
        window = SDL_CreateWindow(m_displayInfo.name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_displayInfo.width, m_displayInfo.height, SDL_WINDOW_SHOWN);
        
        assert(window && "SDL Window could not be created");
        
        //Get window surface
        screenSurface = SDL_GetWindowSurface( window );
        
        //Fill the surface white
        SDL_FillRect(screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF));
    }
    
    void CSDLWindow::Terminate()
    {
        //Destroy window
        SDL_DestroyWindow(window);
        
        window = 0;
        screenSurface = 0;
        
        //Quit SDL subsystems
        SDL_Quit();
    }
}
