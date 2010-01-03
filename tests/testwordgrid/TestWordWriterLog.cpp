#include "Framework.h"
#include "wordgrid/WordWriterLog.h"
#include "wordgrid/Grid.h"

#include <sstream>

BOOST_AUTO_TEST_SUITE(TestWordWriterLog)

using namespace Wordgrid;

struct MockGrid : public Grid
{
};

struct MockWordWriter : public WordWriter
{
    MockWordWriter(Grid & grid) :
        WordWriter(grid),
        m_writeCount(0),
        m_undoWriteCount(0)
    {
    }

    PartialWord Write(const Vector2 & position, EDirection direction, const std::string & word)
    {
        ++m_writeCount;

        PartialWord partialWord;
        partialWord.Add('A');
        partialWord.Add('B');
        return partialWord;
    }

    void UndoWrite(const Vector2 & position, EDirection chosenDirection, const PartialWord & writtenWord)
    {
        ++m_undoWriteCount;
    }

    i32 m_writeCount;
    i32 m_undoWriteCount;
};

struct WordWriterLogFixture
{
    WordWriterLogFixture() :
        m_wordWriterLog(m_grid, m_mockWordWriter, m_strStream),
        m_mockWordWriter(m_grid)
    {
    }

    WordWriterLog m_wordWriterLog;
    MockWordWriter m_mockWordWriter;
    std::stringstream m_strStream;
    MockGrid m_grid;
};

BOOST_FIXTURE_TEST_CASE(write_calls_next_wordwriter, WordWriterLogFixture)
{
    Vector2 position(2,3);
    EDirection direction = EDirection_Horizontal;
    std::string word("test");

    m_wordWriterLog.Write(position, direction, word);

    BOOST_CHECK_EQUAL(1, m_mockWordWriter.m_writeCount);
    BOOST_CHECK_EQUAL(0, m_mockWordWriter.m_undoWriteCount);
    BOOST_CHECK_EQUAL("Writing to grid at (2,3)H : test\n", m_strStream.str());
}

BOOST_FIXTURE_TEST_CASE(undowrite_calls_next_wordwriter, WordWriterLogFixture)
{
    Vector2 position(2,3);
    EDirection direction = EDirection_Horizontal;

    PartialWord partialWord;
    partialWord.Add('A');
    partialWord.Add('B');

    m_wordWriterLog.UndoWrite(position, direction, partialWord);

    BOOST_CHECK_EQUAL(1, m_mockWordWriter.m_undoWriteCount);
    BOOST_CHECK_EQUAL(0, m_mockWordWriter.m_writeCount);
    BOOST_CHECK_EQUAL("Undo Writing to grid at (2,3)H : AB\n", m_strStream.str());
}

BOOST_AUTO_TEST_SUITE_END()

