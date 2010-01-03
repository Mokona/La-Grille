#include "Framework.h"
#include "wordgrid/ScopedTimer.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(TestScopedTimer)

using namespace Wordgrid;

BOOST_AUTO_TEST_CASE(instantiation_without_output)
{
    std::stringstream outputStream;
    ScopedTimer timer("Name", outputStream);
}

BOOST_AUTO_TEST_CASE(instantiation_with_output)
{
    std::stringstream outputStream;
    ScopedTimer timer("Name", outputStream);
}

BOOST_AUTO_TEST_CASE(output_starts_with_name)
{
    std::stringstream outputStream;
    BOOST_CHECK_EQUAL(0, outputStream.str().size());
    {
        ScopedTimer timer("Name", outputStream);
    }
    BOOST_CHECK(0 < outputStream.str().size());
    BOOST_CHECK_EQUAL(0, outputStream.str().find("Name : "));
}

BOOST_AUTO_TEST_SUITE_END()

