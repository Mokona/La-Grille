#include "Framework.h"
#include "wordgrid/LateralWordsCheckerImpl.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/Request.h"
#include "wordgrid/Dictionary.h"

BOOST_AUTO_TEST_SUITE(TestLateralWordsCheckerImpl)

using namespace Wordgrid;

struct MockGrid : public Grid
{
    MockGrid() :
        m_full(false),
        m_count(0),
        m_size(3,3)
    {
    }

    bool IsFull() const
    {
        return m_full;
    }

    void SetFull(bool full)
    {
        m_full = full;
    }

    const Vector2 & GetSize() const
    {
        return m_size;
    }

    const Square & GetSquare(const Vector2 & position) const
    {
        // std::cout << "Mock " << m_returnedPositions.size() << position << std::endl;
        static Square notFound;
        for (unsigned int index = 0; index < m_returnedPositions.size(); ++index)
        {
            // std::cout << "Mock : " << index << std::endl;
            // std::cout << m_returnedPositions[index] << std::endl;
            if (m_returnedPositions[index] == position)
            {
                return m_returnedSquare[index];
            }
        }
        return notFound;
    }

    bool IsInitialized() const
    {
        return true;
    }

    bool m_full;
    i32 m_count;
    Vector2 m_size;

    std::vector<Vector2> m_returnedPositions;
    std::vector<Square> m_returnedSquare;
};

struct MockDictionary : public Dictionary
{
    MockDictionary(i32 words = 0) :
        m_count(0),
        m_result(true)
    {
        while (words)
        {
            m_wordList.push_back(std::string("WORD"));
            --words;
        }
    }

    virtual std::vector<std::string> Search(const PartialWord & partialWord) const
    {
        return m_wordList;
    }

    virtual void InsertWord(const std::string & word)
    {
    }

    virtual void RemoveWord(const std::string & word)
    {
    }

    virtual bool IsWordValid(const std::string & word) const
    {
        m_words[m_count] = word;
        ++m_count;

        return m_result;
    }

    virtual i32 GetWordCount() const
    {
        return 0;
    }

    mutable i32 m_count;
    mutable std::string m_words[15];
    bool m_result;

    std::vector<std::string> m_wordList;
};

BOOST_AUTO_TEST_CASE(valid_if_request_contains_empty_word)
{
    Request request;
    MockGrid grid;
    MockDictionary dictionary;

    LateralWordsCheckerImpl checker(grid, dictionary);
    BOOST_CHECK_EQUAL(0, dictionary.m_count);
    BOOST_CHECK(checker.AreSideWordsValid(request));
}

BOOST_AUTO_TEST_CASE(valid_if_request_contains_word_with_no_char)
{
    Request request;
    request.AddConstraint(Request::NoConstraint());
    request.AddConstraint(Request::NoConstraint());
    request.AddConstraint(Request::NoConstraint());

    MockGrid grid;
    MockDictionary dictionary;

    LateralWordsCheckerImpl checker(grid, dictionary);
    BOOST_CHECK_EQUAL(0, dictionary.m_count);
    BOOST_CHECK(checker.AreSideWordsValid(request));
}

BOOST_AUTO_TEST_CASE(valid_if_request_contains_word_chars_not_creating_lateral_words)
{
    Request request;
    request.AddConstraint(Request::NoConstraint());
    request.AddConstraint('O');
    request.AddConstraint(Request::NoConstraint());
    request.SetStart(Vector2(1,1));
    request.SetDirection(EDirection_Horizontal);

    MockGrid grid;
    MockDictionary dictionary;

    LateralWordsCheckerImpl checker(grid, dictionary);
    BOOST_CHECK_EQUAL(0, dictionary.m_count);
    BOOST_CHECK(checker.AreSideWordsValid(request));
}

BOOST_AUTO_TEST_CASE(calls_dictionary_if_lateral_word_created)
{
    Request writtenWord;
    writtenWord.AddConstraint(Request::NoConstraint());
    writtenWord.AddConstraint('O');
    writtenWord.AddConstraint(Request::NoConstraint());
    writtenWord.SetStart(Vector2(0,1));
    writtenWord.SetDirection(EDirection_Horizontal);

    MockGrid grid;
    grid.m_returnedPositions.push_back(Vector2(1,0));
    grid.m_returnedSquare.push_back(Square('M'));
    grid.m_returnedPositions.push_back(Vector2(1,1));
    grid.m_returnedSquare.push_back(Square('O'));
    grid.m_returnedPositions.push_back(Vector2(1,2));
    grid.m_returnedSquare.push_back(Square('T'));

    MockDictionary dictionary;

    LateralWordsCheckerImpl checker(grid, dictionary);
    BOOST_CHECK(checker.AreSideWordsValid(writtenWord));
    BOOST_CHECK_EQUAL(1, dictionary.m_count);
    if (dictionary.m_count > 0)
    {
        BOOST_CHECK_EQUAL("MOT", dictionary.m_words[0]);
    }
}

BOOST_AUTO_TEST_CASE(calls_dictionary_if_lateral_word_created_and_checks_invalid)
{
    Request writtenWord;
    writtenWord.AddConstraint(Request::NoConstraint());
    writtenWord.AddConstraint('O');
    writtenWord.AddConstraint(Request::NoConstraint());
    writtenWord.SetStart(Vector2(0,1));
    writtenWord.SetDirection(EDirection_Horizontal);

    MockGrid grid;
    grid.m_returnedPositions.push_back(Vector2(1,0));
    grid.m_returnedSquare.push_back(Square('M'));
    grid.m_returnedPositions.push_back(Vector2(1,1));
    grid.m_returnedSquare.push_back(Square('O'));
    grid.m_returnedPositions.push_back(Vector2(1,2));
    grid.m_returnedSquare.push_back(Square('T'));

    MockDictionary dictionary;
    dictionary.m_result = false;

    LateralWordsCheckerImpl checker(grid, dictionary);
    BOOST_CHECK(!checker.AreSideWordsValid(writtenWord));
    BOOST_CHECK_EQUAL(1, dictionary.m_count);
    if (dictionary.m_count > 0)
    {
        BOOST_CHECK_EQUAL("MOT", dictionary.m_words[0]);
    }
}
BOOST_AUTO_TEST_SUITE_END()

