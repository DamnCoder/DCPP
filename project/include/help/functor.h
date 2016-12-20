#ifndef FUNCTIONOID_H
#define FUNCTIONOID_H

#include <iostream> 

namespace molo
{
namespace functor
{
    //------------------------------------------------------------//
    // FUNCTOR BASE CLASSES, WITHOUT RETURN VALUE
    //------------------------------------------------------------//
    struct CFunctor0
    {
    public:
        virtual ~CFunctor0(){}
        
    public:
        virtual void operator()()
        {
            std::cout<<"[CFunctor0] NOT IMPLEMENTED\n";
        }
    };
    
    //------------------------------------------------------------//

    template<class T1>
    struct CFunctor1
    {
    public:
        virtual ~CFunctor1(){}
        
    public:
        virtual void operator()(const T1& value1)
        {
            std::cout<<"[CFunctor1] NOT IMPLEMENTED\n";
        }
    };
    
    //------------------------------------------------------------//

    template<class T1, class T2>
    struct CFunctor2
    {
    public:
        virtual ~CFunctor2(){}
        
    public:
        virtual void operator()(const T1& value1, const T2& value2)
        {
            std::cout<<"[CFunctor2] NOT IMPLEMENTED\n";
        }
    };
    
    //------------------------------------------------------------//

    template<class T1, class T2, class T3>
    struct CFunctor3
    {
    public:
        virtual ~CFunctor3(){}
        
    public:
        virtual void operator()(const T1& value1, const T2& value2, const T3& value3)
        {
            std::cout<<"[CFunctor3] NOT IMPLEMENTED\n";
        }
    };
    
    //------------------------------------------------------------//

    template<class T1, class T2, class T3, class T4>
    struct CFunctor4
    {
    public:
        virtual ~CFunctor4(){}
        
    public:
        virtual void operator()(const T1& value1, const T2& value2, const T3& value3, const T4& value4)
        {
            std::cout<<"[CFunctor4] NOT IMPLEMENTED\n";
        }
        
    };
    
    //------------------------------------------------------------//

    template<class T1,class T2,class T3,class T4,class T5>
    struct CFunctor5
    {
    public:
        virtual ~CFunctor5(){}
        
    public:
        virtual void operator()(const T1& value1, const T2& value2, const T3& value3, const T4& value4, const T5& value5)
        {
            std::cout<<"[CFunctor5] NOT IMPLEMENTED\n";
        }
    };

    //------------------------------------------------------------//
    // FUNCTOR BASE CLASSES, WITH RETURN VALUE
    //------------------------------------------------------------//
    
    template<class R>
    struct CFunctor0R
    {
    public:
        virtual ~CFunctor0R(){}
        
    public:
        virtual R operator()()
        {
            std::cout<<"[CFunctor0R] NOT IMPLEMENTED\n";
            return R();
        }
    };
    //------------------------------------------------------------//

    template<class R, class T1>
    struct CFunctor1R
    {
    public:
        virtual ~CFunctor1R(){}
        
    public:
        /*
        virtual R operator()(const T1& value1)
        {
            std::cout<<"[CFunctor1R] NOT IMPLEMENTED\n";
            return R();
        }
        */
        virtual R operator()(const T1& value1)
        {
            std::cout<<"[CFunctor1R] NOT IMPLEMENTED\n";
            return R();
        }
    };
            
    //------------------------------------------------------------//
    
    template<class R, class T1, class T2>
    struct CFunctor2R
    {
    public:
        virtual ~CFunctor2R(){};
        
    public:
        virtual R operator()(const T1& value1, const T2& value2)
        {
            std::cout<<"[CFunctor2R] NOT IMPLEMENTED\n";
            return R();
        }
    };

    //------------------------------------------------------------//
            
    template<class R, class T1, class T2, class T3>
    struct CFunctor3R
    {
    public:
        virtual ~CFunctor3R(){};
        
    public:
        virtual R operator()(const T1& value1, const T2& value2, const T3& value3)
        {
            std::cout<<"[CFunctor3R] NOT IMPLEMENTED\n";
            return R();
        }
    };

    //------------------------------------------------------------//
    
    template<class R, class T1, class T2, class T3, class T4>
    struct CFunctor4R
    {
    public:
        virtual ~CFunctor4R(){};
        
    public:
        virtual R operator()(const T1& value1, const T2& value2, const T3& value3, const T4& value4)
        {
            std::cout<<"[CFunctor4R] NOT IMPLEMENTED\n";
            return R();
        }
    };

    //------------------------------------------------------------//

    template<class R, class T1, class T2, class T3, class T4, class T5>
    struct CFunctor5R
    {
    public:
        virtual ~CFunctor5R(){};
        
    public:
        virtual R operator()(const T1& value1, const T2& value2, const T3& value3, const T4& value4, const T5& value5)
        {
            std::cout<<"[CFunctor5R] NOT IMPLEMENTED\n";
            return R();
        }
    };
}
}

#endif
