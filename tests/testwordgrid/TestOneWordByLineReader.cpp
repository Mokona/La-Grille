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

BOOST_AUTO_TEST_CASE(when_read_calls_dictionary)
{
    std::stringstream strStream;
    strStream << "test\n";
    strStream << "mot\n";
    strStream << "truc\n";

    MockDictionary dictionary;
    OneWordByLineReader reader(dictionary, strStream);
    reader.Read();

    BOOST_CHECK_EQUAL(3, dictionary.m_count);
}

BOOST_AUTO_TEST_SUITE_END()

