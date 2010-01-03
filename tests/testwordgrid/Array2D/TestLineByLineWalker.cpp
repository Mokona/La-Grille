#include "Framework.h"
#include "wordgrid/Assert.h"
#include "wordgrid/Array2D/LineByLineWalker.h"
#include "wordgrid/Vector2.h"

using namespace Wordgrid;

namespace TestArray2D
{
BOOST_AUTO_TEST_SUITE(LineByLineWalker)

    BOOST_AUTO_TEST_CASE(position_is_0_when_initialized)
    {
        std::auto_ptr<Array2D::Walker> walker(new Array2D::LineByLineWalker(Vector2(3,2)));
        BOOST_CHECK(Vector2(0,0) == walker->GetPosition());
    }

    BOOST_AUTO_TEST_CASE(LineByLineWalker_knowns_its_size)
    {
        std::auto_ptr<Array2D::Walker> walker(new Array2D::LineByLineWalker(Vector2(3,2)));
        BOOST_CHECK(Vector2(3,2) == walker->GetSize());
    }

    BOOST_AUTO_TEST_CASE(LineByLineWalker_is_copy_constructible_via_interface)
    {
        std::auto_ptr<Array2D::Walker> walker(new Array2D::LineByLineWalker(Vector2(3,2)));
        const Array2D::LineByLineWalker copiedWalker(*walker);

        BOOST_CHECK(walker->GetSize() == copiedWalker.GetSize());
    }

    BOOST_AUTO_TEST_CASE(if_either_dimension_is_zero_assertion_is_raised)
    {
        CHECK_ASSERT(Array2D::LineByLineWalker walker(Vector2(0,1)));
        CHECK_ASSERT(Array2D::LineByLineWalker walker(Vector2(1,0)));
    }

    BOOST_AUTO_TEST_CASE(plus_plus_goes_to_the_right)
    {
        std::auto_ptr<Array2D::Walker> walker(new Array2D::LineByLineWalker(Vector2(3,2)));
        ++(*walker);
        BOOST_CHECK(Vector2(1,0) == walker->GetPosition());
    }

    BOOST_AUTO_TEST_CASE(plus_plus_at_rightmost_position_goes_beginning_of_next_line)
    {
        std::auto_ptr<Array2D::Walker> walker(new Array2D::LineByLineWalker(Vector2(3,2)));
        ++(*walker);
        ++(*walker);
        ++(*walker);
        BOOST_CHECK(Vector2(0,1) == walker->GetPosition());
    }

    BOOST_AUTO_TEST_CASE(plus_plus_at_leftmost_position_goes_to_end_of_previous_line)
    {
        std::auto_ptr<Array2D::Walker> walker(new Array2D::LineByLineWalker(Vector2(3,2)));
        ++(*walker);
        ++(*walker);
        ++(*walker);
        --(*walker);
        BOOST_CHECK(Vector2(2,0) == walker->GetPosition());
    }

    BOOST_AUTO_TEST_CASE(is_at_end_is_true_when_going_after_the_end_position)
    {
        Array2D::LineByLineWalker walker(Vector2(1,1));

        BOOST_CHECK(!walker.IsAtEnd());
        ++walker;
        BOOST_CHECK(walker.IsAtEnd());
    }

    BOOST_AUTO_TEST_CASE(is_at_end_is_true_when_going_after_the_end_position_width_rectangle)
    {
        Array2D::LineByLineWalker walker(Vector2(2,1));

        BOOST_CHECK(!walker.IsAtEnd());
        ++walker;
        ++walker;
        BOOST_CHECK(walker.IsAtEnd());
    }

    BOOST_AUTO_TEST_CASE(is_at_end_is_true_when_going_after_the_end_position_height_rectangle)
    {
        Array2D::LineByLineWalker walker(Vector2(1,2));

        BOOST_CHECK(!walker.IsAtEnd());
        ++walker;
        ++walker;
        BOOST_CHECK(walker.IsAtEnd());
    }
BOOST_AUTO_TEST_SUITE_END()
}

