#include "Framework.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/GridOutputStream.h"

#include <sstream>
#include <ostream>

/* In these tests, we use Grid directly, without a mock. Due to the simplicity
 * of the Grid (it's basically a container), we can consider it's a unit test.
 *
 * Implementing a mock object for this seems overkill.
 *
 * If grid turns to be more complicated, a mock object should be created.
 */

BOOST_AUTO_TEST_CASE( outputgrid_empty_grid )
{
    Wordgrid::Grid grid;
    grid.Init(Wordgrid::Vector2(4,4));

    std::stringstream strStream;

    Wordgrid::GridOutputStream outputStream(strStream);
    outputStream(grid);

    std::string waited("------\n|    |\n|    |\n|    |\n|    |\n------");
    BOOST_CHECK_EQUAL(waited, strStream.str());
}

BOOST_AUTO_TEST_CASE( outputgrid_grid_with_content )
{
    Wordgrid::Square square;

    Wordgrid::Grid grid;
    grid.Init(Wordgrid::Vector2(4,4));

    square.SetChar('A');
    grid.SetSquare(Wordgrid::Vector2(1,1),square);
    square.SetChar('B');
    grid.SetSquare(Wordgrid::Vector2(0,3),square);

    std::stringstream strStream;

    Wordgrid::GridOutputStream outputStream(strStream);
    outputStream(grid);

    std::string waited("------\n|    |\n| A  |\n|    |\n|B   |\n------");
    BOOST_CHECK_EQUAL(waited, strStream.str());
}

BOOST_AUTO_TEST_CASE( write_grid_with_ouptut_operator )
{
    Wordgrid::Grid grid;
    grid.Init(Wordgrid::Vector2(4,4));

    std::stringstream strStream;

    strStream << grid;

    std::string waited("------\n|    |\n|    |\n|    |\n|    |\n------");
    BOOST_CHECK_EQUAL(waited, strStream.str());
}

