//
//  SDLWindow.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef SDLWindow_hpp
#define SDLWindow_hpp

#include "window.h"

#include <SDL2/SDL.h>

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
		
		void SwapBuffers() override;
        
    private:
        //The window we'll be rendering to
        SDL_Window*		m_window;
		
		SDL_GLContext	m_context;
    };
}

#endif /* SDLWindow_hpp */
