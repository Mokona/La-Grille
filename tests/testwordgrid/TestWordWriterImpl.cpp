#include "Framework.h"
#include "wordgrid/WordWriterImpl.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/Assert.h"

BOOST_AUTO_TEST_SUITE(TestSimpleWordWriter)

using namespace Wordgrid;

BOOST_AUTO_TEST_CASE( wordwriter_instantiation )
{
    Grid grid;
    WordWriterImpl writer(grid);
    // No check. Should just not crash
}

BOOST_AUTO_TEST_CASE( wont_write_an_empty_word )
{
    Grid grid;
    WordWriterImpl writer(grid);

    BOOST_CHECK_THROW( writer.Write(Vector2(0,0), EDirection_Vertical, ""), Exception::EmptyWord);
    BOOST_CHECK_THROW( writer.Write(Vector2(0,0), EDirection_Horizontal, ""), Exception::EmptyWord);
}

BOOST_AUTO_TEST_CASE( cannot_write_if_grid_uninitialized )
{
    Grid grid;
    WordWriterImpl writer(grid);

    BOOST_CHECK_THROW( writer.Write(Vector2(0,0), EDirection_Vertical, "WORD"), Exception::Uninitialized );
    BOOST_CHECK_THROW( writer.Write(Vector2(0,0), EDirection_Horizontal, "WORD"), Exception::Uninitialized );
}

BOOST_AUTO_TEST_CASE( cannot_write_too_long_words )
{
    Grid grid;
    WordWriterImpl writer(grid);

    grid.Init(Vector2(3,3));

    BOOST_CHECK_THROW( writer.Write(Vector2(Vector2(0,0)), EDirection_Vertical, "WORD"), Exception::WordTooLong );
    BOOST_CHECK_THROW( writer.Write(Vector2(Vector2(0,0)), EDirection_Horizontal, "WORD"), Exception::WordTooLong );
} 

BOOST_AUTO_TEST_CASE( cannot_write_too_long_words_not_at_origin )
{
    Grid grid;
    WordWriterImpl writer(grid);

    grid.Init(Vector2(3,3));

    BOOST_CHECK_THROW( writer.Write(Vector2(Vector2(1,1)), EDirection_Vertical, "WOR"), Exception::WordTooLong );
    BOOST_CHECK_THROW( writer.Write(Vector2(Vector2(1,1)), EDirection_Horizontal, "WOR"), Exception::WordTooLong );
} 

class MockGrid : public Grid
{
    public:
        MockGrid() :
            m_index(0)
        {
        }

        void SetSquare(const Vector2 & position, const Square & content)
        {
            ASSERT(m_index < 5, "Too much recording");
            m_xpos[m_index] = position[0];
            m_ypos[m_index] = position[1];
            m_mockedContent[m_index] = content;

            m_index++;
        }

    public:
        i32 m_index;
        i32 m_xpos[5];
        i32 m_ypos[5];
        Square m_mockedContent[5];
};


// Testing horizontally

struct MockGrid42Fixture
{
    MockGrid42Fixture() :
        m_writer(m_grid)
    {
        m_grid.Init(Vector2(4,2));
    }

    MockGrid m_grid;
    WordWriterImpl m_writer;
};

BOOST_FIXTURE_TEST_CASE(valid_writer_calls_writes_correct_number_of_squares, MockGrid42Fixture )
{
    m_writer.Write(Vector2(0,0), EDirection_Horizontal, "WORD");

    BOOST_CHECK_EQUAL(4, m_grid.m_index);
}

BOOST_FIXTURE_TEST_CASE(valid_writer_calls_writes_at_correct_positions, MockGrid42Fixture )
{
    m_writer.Write(Vector2(0,0), EDirection_Horizontal, "WORD");

    BOOST_CHECK_EQUAL(0, m_grid.m_xpos[0]);
    BOOST_CHECK_EQUAL(1, m_grid.m_xpos[1]);
    BOOST_CHECK_EQUAL(2, m_grid.m_xpos[2]);
    BOOST_CHECK_EQUAL(3, m_grid.m_xpos[3]);

    BOOST_CHECK_EQUAL(0, m_grid.m_ypos[0]);
    BOOST_CHECK_EQUAL(0, m_grid.m_ypos[1]);
    BOOST_CHECK_EQUAL(0, m_grid.m_ypos[2]);
    BOOST_CHECK_EQUAL(0, m_grid.m_ypos[3]);
}


BOOST_FIXTURE_TEST_CASE(valid_writer_calls_writes_correct_letters, MockGrid42Fixture )
{
    Square content[4];
    content[0].SetChar('W');
    content[1].SetChar('O');
    content[2].SetChar('R');
    content[3].SetChar('D');

    m_writer.Write(Vector2(0,0), EDirection_Horizontal, "WORD");

    BOOST_CHECK(content[0] == m_grid.m_mockedContent[0]);
    BOOST_CHECK(content[1] == m_grid.m_mockedContent[1]);
    BOOST_CHECK(content[2] == m_grid.m_mockedContent[2]);
    BOOST_CHECK(content[3] == m_grid.m_mockedContent[3]);
}

BOOST_FIXTURE_TEST_CASE(when_writing_to_empty_grid_returns_complete_word, MockGrid42Fixture )
{
    PartialWord writtenWord = m_writer.Write(Vector2(0,0), EDirection_Horizontal, "MOT");

    BOOST_CHECK_EQUAL(3, writtenWord.Size());
    BOOST_CHECK_EQUAL("MOT", std::string(writtenWord.begin(), writtenWord.end()));
}

struct MockGridForTestingWritten : MockGrid
{
    MockGridForTestingWritten()
    {
        m_position = Vector2(1,0);
        m_square.SetChar('O');
        m_emptySquare.EmptySquare();
    }

    const Square & GetSquare(const Vector2 & position) const
    {
        if (m_position == position)
        {
            return m_square;
        }

        return m_emptySquare;
    }
    
    Vector2 m_position;
    Square m_square;
    Square m_emptySquare;
};

BOOST_AUTO_TEST_CASE(when_writing_to_non_empty_grid_returns_partial_word)
{
    MockGridForTestingWritten grid;
    grid.Init(Vector2(4,2));

    WordWriterImpl writer(grid);

    PartialWord writtenWord = writer.Write(Vector2(0,0), EDirection_Horizontal, "MOT");

    BOOST_CHECK_EQUAL(3, writtenWord.Size());
    BOOST_CHECK_EQUAL("M T", std::string(writtenWord.begin(), writtenWord.end()));
}

BOOST_AUTO_TEST_CASE(undo_write_restores_grid)
{
    // Grid is a simple container. No need to mock it for this test.
    // Perhaps with a complet Mock framework...
    Grid grid;
    grid.Init(Vector2(4,2));

    Grid savedGrid(grid);

    WordWriterImpl writer(grid);

    PartialWord writtenWord = writer.Write(Vector2(0,0), EDirection_Horizontal, "MOT");
    BOOST_CHECK(savedGrid != grid);

    writer.UndoWrite(Vector2(0,0), EDirection_Horizontal, writtenWord);

    BOOST_CHECK(savedGrid == grid);
}

// Testing Vertically
struct MockGrid24Fixture
{
    MockGrid24Fixture() :
        m_writer(m_grid)
    {
        m_grid.Init(Vector2(2,4));
    }

    MockGrid m_grid;
    WordWriterImpl m_writer;
};

BOOST_FIXTURE_TEST_CASE(vert_valid_writer_calls_writes_correct_number_of_squares, MockGrid24Fixture )
{
    m_writer.Write(Vector2(0,0), EDirection_Vertical, "WORD");

    BOOST_CHECK_EQUAL(4, m_grid.m_index);
}

BOOST_FIXTURE_TEST_CASE(vert_valid_writer_calls_writes_at_correct_positions, MockGrid24Fixture )
{
    m_writer.Write(Vector2(0,0), EDirection_Vertical, "WORD");

    BOOST_CHECK_EQUAL(0, m_grid.m_xpos[0]);
    BOOST_CHECK_EQUAL(0, m_grid.m_xpos[1]);
    BOOST_CHECK_EQUAL(0, m_grid.m_xpos[2]);
    BOOST_CHECK_EQUAL(0, m_grid.m_xpos[3]);

    BOOST_CHECK_EQUAL(0, m_grid.m_ypos[0]);
    BOOST_CHECK_EQUAL(1, m_grid.m_ypos[1]);
    BOOST_CHECK_EQUAL(2, m_grid.m_ypos[2]);
    BOOST_CHECK_EQUAL(3, m_grid.m_ypos[3]);
}


BOOST_FIXTURE_TEST_CASE(vert_valid_writer_calls_writes_correct_letters, MockGrid24Fixture )
{
    Square content[4];
    content[0].SetChar('W');
    content[1].SetChar('O');
    content[2].SetChar('R');
    content[3].SetChar('D');

    m_writer.Write(Vector2(0,0), EDirection_Vertical, "WORD");

    BOOST_CHECK(content[0] == m_grid.m_mockedContent[0]);
    BOOST_CHECK(content[1] == m_grid.m_mockedContent[1]);
    BOOST_CHECK(content[2] == m_grid.m_mockedContent[2]);
    BOOST_CHECK(content[3] == m_grid.m_mockedContent[3]);
}


BOOST_AUTO_TEST_SUITE_END()

