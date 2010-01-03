#include "Framework.h"
#include "wordgrid/Assert.h"
#include "wordgrid/Array2D/WalkerCommon.h"

using namespace Wordgrid;

namespace TestArray2D
{
BOOST_AUTO_TEST_SUITE(WalkerCommon)

    struct TestWalkerCommon : public Array2D::WalkerCommon
    {
        TestWalkerCommon(const Vector2 & size) :
            Array2D::WalkerCommon(size)
        {
        }

        TestWalkerCommon(const Walker & walker) :
            Array2D::WalkerCommon(walker)
        {
        }

        Walker & operator ++ ()
        {
            return *this;
        }
        Walker & operator -- ()
        {
            return *this;
        }

        void SetPosition(const Vector2 & vector)
        {
            SetInternalPosition(vector);
        }

        const Vector2 & TestGetPosition() const
        {
            return GetPosition();
        }
    };


    BOOST_AUTO_TEST_CASE(position_is_0_when_initialized)
    {
        std::auto_ptr<Array2D::Walker> walker(new TestWalkerCommon(Vector2(3,2)));
        BOOST_CHECK(Vector2(0,0) == walker->GetPosition());
    }

    BOOST_AUTO_TEST_CASE(TestWalkerCommon_knowns_its_size)
    {
        std::auto_ptr<Array2D::Walker> walker(new TestWalkerCommon(Vector2(3,2)));
        BOOST_CHECK(Vector2(3,2) == walker->GetSize());
    }

    BOOST_AUTO_TEST_CASE(TestWalkerCommon_is_copy_constructible_via_interface)
    {
        std::auto_ptr<Array2D::Walker> walker(new TestWalkerCommon(Vector2(3,2)));
        const TestWalkerCommon copiedWalker(*walker);

        BOOST_CHECK(walker->GetSize() == copiedWalker.GetSize());
    }

    BOOST_AUTO_TEST_CASE(if_either_dimension_is_zero_assertion_is_raised)
    {
        CHECK_ASSERT(TestWalkerCommon walker(Vector2(0,1)));
        CHECK_ASSERT(TestWalkerCommon walker(Vector2(1,0)));
    }

    struct CreateWalkerAndSetAtCenter
    {
        CreateWalkerAndSetAtCenter() :
            walker(Vector2(9,9))
        {
            walker.SetPosition(Vector2(4,4));
            ASSERT(walker.TestGetPosition() == Vector2(4,4), "Fixture can't set position");
        }

        TestWalkerCommon walker;
    };

    BOOST_FIXTURE_TEST_CASE(go_right, CreateWalkerAndSetAtCenter)
    {
        walker.GoRight();
        BOOST_CHECK(Vector2(5,4) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_left, CreateWalkerAndSetAtCenter)
    {
        walker.GoLeft();
        BOOST_CHECK(Vector2(3,4) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_up, CreateWalkerAndSetAtCenter)
    {
        walker.GoUp();
        BOOST_CHECK(Vector2(4,3) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_down, CreateWalkerAndSetAtCenter)
    {
        walker.GoDown();
        BOOST_CHECK(Vector2(4,5) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_right_several_times, CreateWalkerAndSetAtCenter)
    {
        walker.GoRight(4);
        BOOST_CHECK(Vector2(8,4) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_left_several_times, CreateWalkerAndSetAtCenter)
    {
        walker.GoLeft(4);
        BOOST_CHECK(Vector2(0,4) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_up_several_times, CreateWalkerAndSetAtCenter)
    {
        walker.GoUp(4);
        BOOST_CHECK(Vector2(4,0) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_down_several_times, CreateWalkerAndSetAtCenter)
    {
        walker.GoDown(4);
        BOOST_CHECK(Vector2(4,8) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_right_outside_the_array_adjusts_coordinates, CreateWalkerAndSetAtCenter)
    {
        walker.GoRight(5);
        BOOST_CHECK(Vector2(0,5) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_left_outside_the_array_adjusts_coordinates, CreateWalkerAndSetAtCenter)
    {
        walker.GoLeft(5);
        BOOST_CHECK(Vector2(8,3) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_up_outside_the_array_adjusts_coordinates, CreateWalkerAndSetAtCenter)
    {
        walker.GoUp(5);
        BOOST_CHECK(Vector2(3,8) == walker.TestGetPosition());
    }

    BOOST_FIXTURE_TEST_CASE(go_down_outside_the_array_adjusts_coordinates, CreateWalkerAndSetAtCenter)
    {
        walker.GoDown(5);
        BOOST_CHECK(Vector2(5,0) == walker.TestGetPosition());
    }

    BOOST_AUTO_TEST_CASE(if_after_last_position_going_right_is_at_end)
    {
        TestWalkerCommon walker(Vector2(1,1));

        walker.GoRight();
        BOOST_CHECK(walker.IsAtEnd());
    }

    BOOST_AUTO_TEST_CASE(if_after_last_position_going_down_is_at_end)
    {
        TestWalkerCommon walker(Vector2(1,1));

        BOOST_CHECK(!walker.IsAtEnd());
        walker.GoDown();
        BOOST_CHECK(walker.IsAtEnd());
    }

    // TODO : checks when trying to set position outside the grid

BOOST_AUTO_TEST_SUITE_END()
}

