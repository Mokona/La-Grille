#include "Framework.h"
#include "wordgrid/Vector2.h"

using namespace Wordgrid;

BOOST_AUTO_TEST_SUITE(TestVector2)

BOOST_AUTO_TEST_CASE( vector2_instantiation )
{
    Vector2 vec(2,8);

    BOOST_CHECK_EQUAL(2, vec[0]);
    BOOST_CHECK_EQUAL(8, vec[1]);
}

BOOST_AUTO_TEST_CASE( vector2_set_values )
{
    Vector2 vec;

    vec.Set(-5, 1);

    BOOST_CHECK_EQUAL(-5, vec[0]);
    BOOST_CHECK_EQUAL(1, vec[1]);
}

BOOST_AUTO_TEST_CASE( vector2_equality )
{
    Vector2 vec1(8,9);
    Vector2 vec2(8,9);

    BOOST_CHECK(vec1 == vec2);
}

BOOST_AUTO_TEST_CASE( vector2_addition_assign )
{
    Vector2 result(1, 4);

    result += Vector2(4, -2);

    BOOST_CHECK(result == Vector2(5, 2));
}

BOOST_AUTO_TEST_CASE( vector2_scalar_multiply_assitn )
{
    Vector2 result(1, 4);

    result *= 2;

    BOOST_CHECK(result == Vector2(2, 8));
}

BOOST_AUTO_TEST_CASE(vector2_ostream)
{
    std::stringstream strStream;
    Vector2 vector(3,4);
    strStream << vector;
    
    BOOST_CHECK_EQUAL("(3,4)", strStream.str());
}

BOOST_AUTO_TEST_SUITE_END()

