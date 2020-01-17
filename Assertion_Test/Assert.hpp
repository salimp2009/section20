// this is a sample of ASSERT MACRO that can enble or disabled
// from  the book "Game Engine architecture 3rd edition" by Jason Gregory 

#ifdef _DEBUG

//#include <cassert>
//define inline assembly that cause a break
//into debugger -- this is different on each target CPU
#define debugBreak() asm (int 3)

//check the expression and fail if it is false
#define ASSERT(expr) \
    if(expr) { } \
    else \
    { \
        reportAssertionFailure(#expr,\
                __FILE__, __LINE__);\
       debugBreak();\ 
    }
    
    #else
    
    #define ASSERT(expr) // evaluates to nothing
    
    #endif