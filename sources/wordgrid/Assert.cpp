#ifdef ASSERT_ON

#include "Assert.h"

namespace Wordgrid
{
    namespace Exception {
        Assert::Assert(const char * message) :
            m_message(message)
        {
        }

        const char* Assert::what() const throw()
        {
            return m_message;
        }
    } /* Exception */
}

#endif

