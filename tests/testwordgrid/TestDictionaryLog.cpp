#include "Framework.h"
#include "wordgrid/DictionaryLog.h"
#include "wordgrid/PartialWord.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(TestDictionaryLog)

using namespace Wordgrid;

struct MockDictionary : public Dictionary
{
    MockDictionary() :
        m_getWordCountCalled(false)
    {
        m_wordList.push_back("test");
    }

    virtual std::vector<std::string> Search(const PartialWord & partialWord) const
    {
        m_partialWord = partialWord;
        return m_wordList;
    }

    virtual void InsertWord(const std::string & word)
    {
        m_insertWord = word;
    }

    virtual void RemoveWord(const std::string & word)
    {
        m_removedWord = word;
    }

    virtual bool IsWordValid(const std::string & word) const
    {
        m_isWordValid = word;
        return true;
    }

    virtual i32 GetWordCount() const
    {
        m_getWordCountCalled = true;
        return 42;
    }

    mutable PartialWord m_partialWord;

    std::vector<std::string> m_wordList;
    std::string m_insertWord;
    std::string m_removedWord;
    mutable std::string m_isWordValid;

    mutable bool m_getWordCountCalled;

};

struct DictionaryLogFixture
{
    DictionaryLogFixture() :
        m_dictionaryLog(m_mockDictionary, m_strStream)
    {
    }

    DictionaryLog m_dictionaryLog;
    MockDictionary m_mockDictionary;
    std::stringstream m_strStream;
};

BOOST_FIXTURE_TEST_CASE(search_calls_next_dictionary, DictionaryLogFixture)
{
    PartialWord partialWord;
    partialWord.Add('A');
    partialWord.Add('B');
    Dictionary::FoundWords words = m_dictionaryLog.Search(partialWord);

    BOOST_CHECK(partialWord == m_mockDictionary.m_partialWord);
    BOOST_CHECK_EQUAL(1, words.size());
    BOOST_CHECK_EQUAL("Searching with partialWord: \"AB\"\n  answer : test\n", m_strStream.str());
}

BOOST_FIXTURE_TEST_CASE(insert_word_calls_next_dictionary, DictionaryLogFixture)
{
    m_dictionaryLog.InsertWord("word");
    BOOST_CHECK_EQUAL("word", m_mockDictionary.m_insertWord);
}

BOOST_FIXTURE_TEST_CASE(remove_word_calls_next_dictionary, DictionaryLogFixture)
{
    m_dictionaryLog.RemoveWord("word");
    BOOST_CHECK_EQUAL("word", m_mockDictionary.m_removedWord);
}

BOOST_FIXTURE_TEST_CASE(is_word_valid_calls_next_dictionary, DictionaryLogFixture)
{
    m_dictionaryLog.IsWordValid("mot");
    BOOST_CHECK_EQUAL("mot", m_mockDictionary.m_isWordValid);
}

BOOST_FIXTURE_TEST_CASE(get_word_valid_calls_next_dictionary, DictionaryLogFixture)
{
    i32 count = m_dictionaryLog.GetWordCount();
    BOOST_CHECK_EQUAL(42, count);
    BOOST_CHECK(m_mockDictionary.m_getWordCountCalled);
}

BOOST_AUTO_TEST_SUITE_END()

