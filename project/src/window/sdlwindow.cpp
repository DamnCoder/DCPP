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
        int opCode = SDL_Init( SDL_INIT_VIDEO );
        
        assert(-1 < opCode && "[CSDLWindow::Initialize] SDL could not be initialized");
		
        // Create window
        m_window = SDL_CreateWindow(m_displayInfo.name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_displayInfo.width, m_displayInfo.height, SDL_WINDOW_SHOWN);
        
        assert(m_window && "[CSDLWindow::Initialize] SDL Window could not be created");
		
		// Set our OpenGL version.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		
		// Use OpenGL 3.1 core
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		
		// Create context
		m_context = SDL_GL_CreateContext( m_window );
		assert(m_window && "[CSDLWindow::Initialize] OpenGL context could not be created");
		
		// Use Vsync
		opCode = SDL_GL_SetSwapInterval( 1 );
		assert(-1 < opCode && "[CSDLWindow::Initialize] Unable to set VSync!");
		
        //Get window surface
        //m_screenSurface = SDL_GetWindowSurface( m_window );
        
        //Fill the surface white
        //SDL_FillRect(m_screenSurface, NULL, SDL_MapRGB(m_screenSurface->format, 0xFF, 0xFF, 0xFF));
    }
    
    void CSDLWindow::Terminate()
    {
		// Delete our OpengL context
		SDL_GL_DeleteContext(m_context);
		
        //Destroy window
        SDL_DestroyWindow(m_window);
		
		m_context = 0;
        m_window = 0;
        m_screenSurface = 0;
        
        //Quit SDL subsystems
        SDL_Quit();
    }
	
	void CSDLWindow::SwapBuffers()
	{
		SDL_GL_SwapWindow( m_window );
	}
}
