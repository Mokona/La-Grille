#include "Framework.h"
#include "wordgrid/Assert.h"

BOOST_AUTO_TEST_SUITE(Assert)

BOOST_AUTO_TEST_CASE( condition_ok_does_nothing )
{
    ASSERT( true, "Nothing" );
}

#ifdef ASSERT_ON

BOOST_AUTO_TEST_CASE( condition_failed_sends_exception )
{
    BOOST_CHECK_THROW( ASSERT( false, "Message" ), Wordgrid::Exception::Assert );
}

BOOST_AUTO_TEST_CASE( condition_failed_sends_exception_with_correct_message )
{
    try
    {
        ASSERT( false, "Message" );
    }
    catch ( Wordgrid::Exception::Assert exception )
    {
        BOOST_CHECK( strncmp("Message", exception.what(), 8) == 0 ) ;
    }
}

#else

BOOST_AUTO_TEST_CASE( condition_failed_does_nothing )
{
    // Will simply fail if an exception is thrown due to the assert.
    ASSERT( false, "Nothing" );
}

#endif

BOOST_AUTO_TEST_SUITE_END()

