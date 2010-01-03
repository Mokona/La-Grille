#define BOOST_TEST_DYN_LINK 1
// #define BOOST_TEST_NO_LIB
#include <boost/test/unit_test.hpp>

#include "wordgrid/Assert.h"

#ifdef ASSERT_ON

#define CHECK_ASSERT(CODE) \
    { \
        bool frameworkAssertCatched = false; \
        try \
        { \
            CODE; \
        } \
        catch(Wordgrid::Exception::Assert exception) \
        { \
            frameworkAssertCatched = true; \
        } \
        BOOST_CHECK( frameworkAssertCatched ); \
    } \
    while(0)

#else

#define CHECK_ASSERT(CODE)

#endif
