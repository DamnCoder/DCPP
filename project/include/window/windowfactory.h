//
//  CWindowFactory.hpp
//  dcpp
//
//  Created by Jorge López on 24/3/16.
//  Copyright © 2016 Jorge López. All rights reserved.
//

#ifndef CWindowFactory_hpp
#define CWindowFactory_hpp

namespace dc
{
    class IWindow;
    struct TDisplayInfo;
    
    enum EWindowType
    {
        SDL,
    };
    
    class CWindowFactory
    {
    public:
        static IWindow* Create(const TDisplayInfo& displayInfo, EWindowType type);
        
    };
}

#endif /* CWindowFactory_hpp */
