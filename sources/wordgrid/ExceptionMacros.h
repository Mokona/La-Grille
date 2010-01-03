#ifndef WORDGRID_EXCEPTION_MACRO
#define WORDGRID_EXCEPTION_MACRO

#include <exception>

#define EXCEPTION_DECLARE(Name) \
    class Name : public std::exception \
    { \
        virtual const char* what() const throw(); \
    }

#define EXCEPTION_IMPLEMENT(Name, Message) \
    const char* Name::what() const throw() \
    { \
        return Message; \
    }

#endif // guard

