//
//  IWindow.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef IWindow_hpp
#define IWindow_hpp

namespace dc
{
    struct TDisplayInfo
    {
	public:
        unsigned int 	width;
        unsigned int 	height;
        unsigned int	bpp;
        const char* 	name;
        bool			fullscreen;
		
	public:
		const float AR() { return width / (float)height; }
		
	public:
        TDisplayInfo():
        	width(0),
			height(0),
			bpp(0),
			name(0),
			fullscreen(false)
		{}

        TDisplayInfo(const unsigned int width,
                     const unsigned int height,
                     const unsigned int bpp,
                     const char* name,
                     const bool fullscreen) :
            width(width),
            height(height),
            bpp(bpp),
            name(name),
            fullscreen(fullscreen)
        {}
    };
    
    class IWindow
    {
        friend class CWindowFactory;
    public:
        const TDisplayInfo DisplayInfo() const { return m_displayInfo; }
        
    public:
        virtual ~IWindow() {}

    protected:
        IWindow(const TDisplayInfo& displayInfo) : m_displayInfo(displayInfo) {}
        
    public:
        virtual void Initialize() = 0;
        virtual void Terminate() = 0;
		
		virtual void SwapBuffers() = 0;
        
    protected:
        TDisplayInfo m_displayInfo;
    };
}

#endif /* IWindow_hpp */
