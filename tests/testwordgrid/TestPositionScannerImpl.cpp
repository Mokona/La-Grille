#include "Framework.h"
#include "wordgrid/Grid.h"
#include "wordgrid/PositionScannerImpl.h"
#include "wordgrid/Square.h"

using namespace Wordgrid;

BOOST_AUTO_TEST_CASE(on_empty_grid_returns_all_border_positions)
{
    Grid grid;
    grid.Init(Vector2(3,2));

    PositionScannerImpl scanner(grid);

    BOOST_CHECK_EQUAL(grid.GetHeight() * grid.GetWidth(), scanner.GetPositions().size());
}

BOOST_AUTO_TEST_CASE(check_positions_on_empty_grid)
{
    Grid grid;
    grid.Init(Vector2(2,2));

    PositionScannerImpl scanner(grid);
    PositionScanner::PositionList positions = scanner.GetPositions();

    BOOST_CHECK(find(positions.begin(), positions.end(), Vector2(0,0)) != positions.end());
    BOOST_CHECK(find(positions.begin(), positions.end(), Vector2(1,0)) != positions.end());
    BOOST_CHECK(find(positions.begin(), positions.end(), Vector2(0,1)) != positions.end());
    BOOST_CHECK(find(positions.begin(), positions.end(), Vector2(1,1)) != positions.end());
}

BOOST_AUTO_TEST_CASE(one_position_missing_with_one_black_square)
{
    Grid grid;
    grid.Init(Vector2(3,2));
    grid.SetSquare(Vector2(1,1), Square::BlackSquare());

    PositionScannerImpl scanner(grid);

    BOOST_CHECK_EQUAL(grid.GetHeight()*grid.GetWidth() - 1, scanner.GetPositions().size());
}

BOOST_AUTO_TEST_CASE(returns_no_position_on_full_grid)
{
    Grid grid;
    grid.Init(Vector2(2,2));
    grid.SetSquare(Vector2(0,0), Square::BlackSquare());
    grid.SetSquare(Vector2(1,0), Square::BlackSquare());
    grid.SetSquare(Vector2(0,1), Square::BlackSquare());
    grid.SetSquare(Vector2(1,1), Square::BlackSquare());

    PositionScannerImpl scanner(grid);

    BOOST_CHECK_EQUAL(0, scanner.GetPositions().size());
}

