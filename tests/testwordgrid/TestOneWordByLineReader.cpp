#include "Framework.h"
#include "wordgrid/OneWordByLineReader.h"
#include "wordgrid/Dictionary.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(TestOneWordByLineReader)

using namespace Wordgrid;

struct MockDictionary : public Dictionary
{
    MockDictionary() :
        m_count(0)
    {
    }

    ~MockDictionary() {}
    FoundWords Search(const PartialWord & partialWord) const { return FoundWords(); }
    bool IsWordValid(const std::string & word) const { return true;}
    i32 GetWordCount() const {return 0;}

    void InsertWord(const std::string & word)
    {
        ++m_count;
    }

    void RemoveWord(const std::string & word)
    {
    }

    i32 m_count;
};

struct StreamOfWords
{
    StreamOfWords()
    {
        m_strStream << "test\n";
        m_strStream << "mot\n";
        m_strStream << "trucs\n";
        m_strStream << "choses\n";
    }

    std::stringstream m_strStream;
};

BOOST_FIXTURE_TEST_CASE(when_read_calls_dictionary, StreamOfWords)
{
    MockDictionary dictionary;
    OneWordByLineReader reader(dictionary, m_strStream);
    reader.Read();

    BOOST_CHECK_EQUAL(4, dictionary.m_count);
}


BOOST_FIXTURE_TEST_CASE(can_add_filter, StreamOfWords)
{
    MockDictionary dictionary;
    OneWordByLineReader reader(dictionary, m_strStream);

    Filter::MinMax filter(3,4);
    reader.SetFilter(filter);

    reader.Read();

    BOOST_CHECK_EQUAL(2, dictionary.m_count);
}

BOOST_AUTO_TEST_SUITE_END()

