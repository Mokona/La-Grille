#include "Framework.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/Assert.h"

BOOST_AUTO_TEST_SUITE(TestLineByLineGridIterator)

using namespace Wordgrid; // Note : ok if not comiling with single unit

class MockGridGet : public Wordgrid::Grid
{
    public:
        MockGridGet() :
            m_index(0)
        {
            m_squares[0].SetChar('a');
            m_squares[1].SetChar('b');
        }

        const Square & GetSquare(const Vector2 & position) const
        {
            ASSERT(m_index < 2, "Too much recording");
            // m_positions[m_index] = position;

            return m_squares[m_index++];
        }

    public:
        mutable i32 m_index;
        // TODO : no test on positions ?
        // mutable Wordgrid::Vector2 m_positions[2];
        Square m_squares[2];
};

// Const version
BOOST_AUTO_TEST_CASE( grid_accessed_by_const_iterator_calls_get_content )
{
    MockGridGet grid;
    grid.Init(Wordgrid::Vector2(3, 2));

    // Force grid to be treated as const
    Wordgrid::LineByLineGridConstIterator it = static_cast<const MockGridGet *>(&grid)->begin();

    (*it).GetChar();
    ++it;
    (*it).GetChar();

    BOOST_CHECK_EQUAL(2, grid.m_index);
}

BOOST_AUTO_TEST_CASE( grid_get_content_by_const_iterator )
{
    MockGridGet grid;
    grid.Init(Wordgrid::Vector2(3, 2));

    Wordgrid::LineByLineGridConstIterator it = static_cast<const MockGridGet *>(&grid)->begin();

    BOOST_CHECK_EQUAL('a', (*it).GetChar());
    ++it;
    BOOST_CHECK_EQUAL('b', (*it).GetChar());
}

BOOST_AUTO_TEST_CASE( get_position )
{
    MockGridGet grid;
    grid.Init(Wordgrid::Vector2(3, 2));

    Wordgrid::LineByLineGridConstIterator it = static_cast<const MockGridGet *>(&grid)->begin();

    BOOST_CHECK(Wordgrid::Vector2(0,0) == it.GetPosition());
    ++it;
    BOOST_CHECK(Wordgrid::Vector2(1,0) == it.GetPosition());
}

BOOST_AUTO_TEST_SUITE_END()

