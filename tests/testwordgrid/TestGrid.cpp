#include "Framework.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"

BOOST_AUTO_TEST_SUITE(TestGrid)

using namespace Wordgrid;

BOOST_AUTO_TEST_CASE( grid_instantiation )
{
    Grid grid;
    // No check. Should just not crash
}

BOOST_AUTO_TEST_CASE( grid_init_with_size )
{
    Grid grid;
    grid.Init(Vector2(3,4));

    BOOST_CHECK_EQUAL(3, grid.GetWidth());
    BOOST_CHECK_EQUAL(4, grid.GetHeight());
}

BOOST_AUTO_TEST_CASE( grid_too_big_throws )
{
    Grid grid;
    BOOST_CHECK_THROW(grid.Init(Vector2(400, 400)), Exception::WrongSize);
}

BOOST_AUTO_TEST_CASE ( gets_size_in_vector2 )
{
    Grid grid;
    grid.Init(Vector2(3,4));

    BOOST_CHECK(Vector2(3,4) == grid.GetSize());
}

BOOST_AUTO_TEST_CASE( grid_init_width_cannot_be_negative )
{
    Grid grid;
    BOOST_CHECK_THROW(grid.Init(Vector2(-3,4)), Exception::WrongSize);
}

BOOST_AUTO_TEST_CASE( grid_init_height_cannot_be_negative )
{
    Grid grid;
    BOOST_CHECK_THROW(grid.Init(Vector2(3,-4)), Exception::WrongSize);
}

BOOST_AUTO_TEST_CASE( grid_no_init_cannot_get_content )
{
    Grid grid;
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(0,0)), Exception::Uninitialized);
}

BOOST_AUTO_TEST_CASE( grid_cannot_get_content_outside_the_grid )
{
    Grid grid;
    grid.Init(Vector2(3, 5));

    BOOST_CHECK_THROW(grid.GetSquare(Vector2(-1 ,-5)), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(-1 ,3)), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(1 ,-3)), Exception::WrongPosition);

    BOOST_CHECK_THROW(grid.GetSquare(Vector2(1 ,13)), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(16 ,3)), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(16 ,30)), Exception::WrongPosition);

    // Limits
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(3 ,5)), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(0 ,5)), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.GetSquare(Vector2(3 ,0)), Exception::WrongPosition);
}

BOOST_AUTO_TEST_CASE( grid_no_init_cannot_set_content )
{
    Square content;
    Grid grid;
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(0,0), content), Exception::Uninitialized);
}

BOOST_AUTO_TEST_CASE( grid_cannot_set_content_outside_the_grid )
{
    Square content;

    Grid grid;
    grid.Init(Vector2(3, 5));


    BOOST_CHECK_THROW(grid.SetSquare(Vector2(-1 ,-5), content), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(-1 ,3), content), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(1 ,-3), content), Exception::WrongPosition);

    BOOST_CHECK_THROW(grid.SetSquare(Vector2(1 ,13), content), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(16 ,3), content), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(16 ,30), content), Exception::WrongPosition);

    // Limits
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(3 ,5), content), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(0 ,5), content), Exception::WrongPosition);
    BOOST_CHECK_THROW(grid.SetSquare(Vector2(3 ,0), content), Exception::WrongPosition);
}

BOOST_AUTO_TEST_CASE ( setting_content_and_getting_it_gives_equal_object )
{
    Square contentOrig;
    Square contentDest;

    Grid grid;
    grid.Init(Vector2(3, 5));

    grid.SetSquare(Vector2(0,1), contentOrig);
    contentDest = grid.GetSquare(Vector2(0, 1));

    BOOST_CHECK( contentOrig == contentDest );
}

// Iterator on squares
BOOST_AUTO_TEST_CASE( grid_distance_is_grid_size )
{
    Grid grid;
    grid.Init(Vector2(4,6));

    BOOST_CHECK_EQUAL(grid.GetWidth() * grid.GetHeight(), std::distance(grid.begin(), grid.end()));
}

BOOST_AUTO_TEST_CASE( test_grid_not_full )
{
    Grid grid;
    grid.Init(Vector2(4,6));

    BOOST_CHECK_EQUAL( false, grid.IsFull());
}

BOOST_AUTO_TEST_CASE( test_grid_full )
{
    Grid grid;
    grid.Init(Vector2(2,1));

    grid.SetSquare(Vector2(0,0),Square('A'));
    grid.SetSquare(Vector2(1,0),Square('B'));

    BOOST_CHECK_EQUAL( true, grid.IsFull());
}

BOOST_AUTO_TEST_CASE( test_grid_full_with_several_write_at_the_same_place )
{
    Grid grid;
    grid.Init(Vector2(2,1));

    grid.SetSquare(Vector2(0,0),Square('A'));
    grid.SetSquare(Vector2(1,0),Square('B'));
    grid.SetSquare(Vector2(1,0),Square('C'));
    grid.SetSquare(Vector2(0,0),Square::EmptySquare());
    grid.SetSquare(Vector2(0,0),Square('D'));

    BOOST_CHECK(grid.IsFull());
}

BOOST_AUTO_TEST_CASE( test_grid_full_with_several_write_at_the_same_place_and_an_empty_square )
{
    Grid grid;
    grid.Init(Vector2(2,1));

    grid.SetSquare(Vector2(0,0),Square('A'));
    grid.SetSquare(Vector2(1,0),Square('B'));
    grid.SetSquare(Vector2(1,0),Square('C'));
    grid.SetSquare(Vector2(0,0),Square::EmptySquare());

    BOOST_CHECK(!grid.IsFull());
}

BOOST_AUTO_TEST_CASE(grid_equality)
{
    Grid grid;
    grid.Init(Vector2(3,4));

    grid.SetSquare(Vector2(1,2), Square('A'));

    Grid grid2(grid);

    BOOST_CHECK(grid == grid2);
}

BOOST_AUTO_TEST_CASE(grid_inequality_by_size)
{
    Grid grid;
    grid.Init(Vector2(3,4));

    grid.SetSquare(Vector2(1,2), Square('A'));

    Grid grid2;
    grid2.Init(Vector2(4,4));

    grid.SetSquare(Vector2(1,2), Square('A'));

    BOOST_CHECK(grid != grid2);
}

BOOST_AUTO_TEST_CASE(grid_inequality_by_content)
{
    Grid grid;
    grid.Init(Vector2(3,4));

    grid.SetSquare(Vector2(1,2), Square('A'));

    Grid grid2;
    grid2.Init(Vector2(3,4));

    grid.SetSquare(Vector2(2,2), Square('B'));

    BOOST_CHECK(grid != grid2);
}

BOOST_AUTO_TEST_SUITE_END()

