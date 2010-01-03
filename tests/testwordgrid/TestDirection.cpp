#include "Framework.h"
#include "wordgrid/Direction.h"
#include "wordgrid/Vector2.h"

BOOST_AUTO_TEST_SUITE(TestDirection)

using namespace Wordgrid;

BOOST_AUTO_TEST_CASE(wrong_value_asserts)
{
    CHECK_ASSERT(SpeedFromDirectionEnum(static_cast<EDirection>(3)));
}

BOOST_AUTO_TEST_CASE(test_horizontal_vector)
{
    const Vector2 & vector = SpeedFromDirectionEnum(EDirection_Horizontal);
    BOOST_CHECK(vector == Vector2(1,0));
}

BOOST_AUTO_TEST_CASE(test_vertical_vector)
{
    const Vector2 & vector = SpeedFromDirectionEnum(EDirection_Vertical);
    BOOST_CHECK(vector == Vector2(0,1));
}

BOOST_AUTO_TEST_CASE(test_other_direction)
{
    BOOST_CHECK_EQUAL(EDirection_Vertical, OtherDirection(EDirection_Horizontal));
    BOOST_CHECK_EQUAL(EDirection_Horizontal, OtherDirection(EDirection_Vertical));
}

BOOST_AUTO_TEST_CASE(horizontal_letter)
{
    BOOST_CHECK_EQUAL('H', GetOutputCharForDirection(EDirection_Horizontal));
}

BOOST_AUTO_TEST_CASE(verical_letter)
{
    BOOST_CHECK_EQUAL('V', GetOutputCharForDirection(EDirection_Vertical));
}

BOOST_AUTO_TEST_SUITE_END()

