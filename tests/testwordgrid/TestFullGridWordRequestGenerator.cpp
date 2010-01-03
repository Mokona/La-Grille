#include "Framework.h"
#include "wordgrid/FullGridWordRequestGenerator.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/Request.h"

using namespace Wordgrid;

BOOST_AUTO_TEST_SUITE(CompleteWordRequestGenerator)

struct MockGridForRequest : public Grid
{
    MockGridForRequest() :
        m_count(0),
        m_size(15,12)
    {
    }

    const Vector2 & GetSize() const
    {
        return m_size;
    }

    const Square & GetSquare(const Vector2 & position) const
    {
        static Square square;
        return square;
    }

    bool IsInitialized() const
    {
        return true;
    }

    i32 m_count;
    Vector2 m_size;
};

struct EmptyGridFixture
{
    EmptyGridFixture() :
        m_generator(m_grid)
    {
    }

    MockGridForRequest m_grid;
    FullGridWordRequestGenerator m_generator;
};

BOOST_FIXTURE_TEST_CASE(position_on_top_left_returns_two_requests, EmptyGridFixture)
{
    WordRequestGenerator::RequestList requests = m_generator.Generate(Vector2(0,0));

    BOOST_CHECK_EQUAL(2, requests.size());

    if (requests.size() > 0)
    {
        BOOST_CHECK(Vector2(0,0) == requests[0].GetStart());
        BOOST_CHECK(Vector2(0,0) == requests[1].GetStart());

        BOOST_CHECK(requests[0].GetDirection() != requests[1].GetDirection());
    }
}

BOOST_FIXTURE_TEST_CASE( position_not_on_border_returns_no_request, EmptyGridFixture )
{
    WordRequestGenerator::RequestList requests = m_generator.Generate(Vector2(1,1));

    BOOST_CHECK_EQUAL(0, requests.size());
}

BOOST_FIXTURE_TEST_CASE( position_on_top_border_returns_one_vertical_request, EmptyGridFixture )
{
    WordRequestGenerator::RequestList requests = m_generator.Generate(Vector2(1,0));

    BOOST_CHECK_EQUAL(1, requests.size());

    if (requests.size() > 0)
    {
        BOOST_CHECK(Vector2(1,0) == requests[0].GetStart());
        BOOST_CHECK_EQUAL(EDirection_Vertical, requests[0].GetDirection());
        BOOST_CHECK_EQUAL(m_grid.GetHeight(), requests[0].Size());
    }
}

BOOST_FIXTURE_TEST_CASE( position_on_left_border_returns_one_horizontal_request, EmptyGridFixture )
{
    WordRequestGenerator::RequestList requests = m_generator.Generate(Vector2(0,1));

    BOOST_CHECK_EQUAL(1, requests.size());

    if (requests.size() > 0)
    {
        BOOST_CHECK(Vector2(0,1) == requests[0].GetStart());
        BOOST_CHECK_EQUAL(EDirection_Horizontal, requests[0].GetDirection());
        BOOST_CHECK_EQUAL(m_grid.GetWidth(), requests[0].Size());
    }
}

struct MockGridFull : public MockGridForRequest
{
    MockGridFull()
    {
        m_square.SetChar('A');
    }

    const Square & GetSquare(const Vector2 & position) const
    {
        return m_square;
    }

    Square m_square;
};

struct FullGridFixture
{
    FullGridFixture() :
        m_generator(m_grid)
    {
    }

    MockGridFull m_grid;
    FullGridWordRequestGenerator m_generator;
};

BOOST_FIXTURE_TEST_CASE( position_on_left_border_has_no_request_when_grid_full, FullGridFixture )
{
    WordRequestGenerator::RequestList requests = m_generator.Generate(Vector2(0,1));

    BOOST_CHECK_EQUAL(0, requests.size());
}

BOOST_FIXTURE_TEST_CASE( position_on_right_border_has_no_request_when_grid_full, FullGridFixture )
{
    WordRequestGenerator::RequestList requests = m_generator.Generate(Vector2(1,0));

    BOOST_CHECK_EQUAL(0, requests.size());
}

struct MockGridWithLetters : public MockGridForRequest
{
    MockGridWithLetters()
    {
        m_squares[0].SetChar('A');
        m_squares[1].SetChar('B');

        m_positions[0] = Vector2(1,0);
        m_positions[1] = Vector2(1,1);
    }

    const Square & GetSquare(const Vector2 & position) const
    {
        if (position == m_positions[0])
        {
            return m_squares[0];
        }
        if (position == m_positions[1])
        {
            return m_squares[1];
        }

        return m_defaultSquare;
    }

    Square m_defaultSquare;
    Square m_squares[2];
    Vector2 m_positions[2];
};

struct NotEmptyGridFixture
{
    NotEmptyGridFixture() :
        m_generator(m_grid)
    {
    }

    MockGridWithLetters m_grid;
    FullGridWordRequestGenerator m_generator;
};

BOOST_FIXTURE_TEST_CASE( check_vertical_constraints, NotEmptyGridFixture )
{
    WordRequestGenerator::RequestList requests = m_generator.Generate(Vector2(1,0));

    BOOST_CHECK_EQUAL(1, requests.size());

    Request & request = requests[0];

    BOOST_CHECK_EQUAL(m_grid.GetHeight(), request.Size());
    
    Request::ConstraintConstIterator it = request.GetPartialWord().begin();
    BOOST_CHECK_EQUAL('A', (*it));
    ++it;
    BOOST_CHECK_EQUAL('B', (*it));
    ++it;

    Request::ConstraintConstIterator itEnd = request.GetPartialWord().end();
    while (it != itEnd)
    {
        BOOST_CHECK_EQUAL(PartialWord::EmptyChar(), (*it));
        ++it;
    }
}

BOOST_AUTO_TEST_SUITE_END()

