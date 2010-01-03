#ifndef WORDGRID_ASSERT
#define WORDGRID_ASSERT

#ifdef ASSERT_ON
#include <exception>

namespace Wordgrid
{
    namespace Exception
    {
        /** Assert exception, raised by ASSERT macro
         */
        class Assert : public std::exception
        {
            public:
                Assert(const char * message);
                virtual const char* what() const throw();

            private:
                const char * m_message;
        };
    }
}

#define ASSERT(Condition, Message) \
    { \
        if (!(Condition)) \
        { \
            throw Wordgrid::Exception::Assert(Message); \
        } \
    } \
    while(0)

#else

#define ASSERT(Condition, Message) \
    while(0)

#endif

#endif // guard

