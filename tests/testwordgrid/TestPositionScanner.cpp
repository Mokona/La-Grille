#include "Framework.h"
#include "wordgrid/PositionScanner.h"
#include "wordgrid/Grid.h"

struct MockPositionScanner : public Wordgrid::PositionScanner
{
    MockPositionScanner(const Wordgrid::Grid & grid) :
        m_grid(grid)
    {
    }

    const Wordgrid::Grid & CheckGrid() const
    {
        return m_grid;
    }

    Wordgrid::PositionScanner::PositionList GetPositions() const
    {
        Wordgrid::PositionScanner::PositionList positionList;
        positionList.push_back(Wordgrid::Vector2());
        positionList.push_back(Wordgrid::Vector2());

        return positionList;
    }

    const Wordgrid::Grid & m_grid;
};

BOOST_AUTO_TEST_CASE( scanposition_gets_grid )
{
    Wordgrid::Grid grid;
    MockPositionScanner scanner(grid);

    BOOST_CHECK_EQUAL(&grid, &scanner.CheckGrid());
}

BOOST_AUTO_TEST_CASE( get_positions_is_visual )
{
    Wordgrid::Grid grid;
    MockPositionScanner scanner(grid);

    BOOST_CHECK_EQUAL(2, scanner.GetPositions().size());
}

