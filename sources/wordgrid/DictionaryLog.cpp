#include "wordgrid/DictionaryLog.h"
#include "wordgrid/PartialWord.h"

#include <boost/foreach.hpp>

namespace Wordgrid
{
    DictionaryLog::DictionaryLog(Dictionary & next, std::ostream & stream) :
        m_nextDictionary(next),
        m_stream(stream)
    {
    }

    DictionaryLog::~DictionaryLog()
    {
    }

    Dictionary::FoundWords DictionaryLog::Search(const PartialWord & partialWord) const
    {
        m_stream << "Searching with partialWord: " << partialWord << std::endl;
        FoundWords words = m_nextDictionary.Search(partialWord);

        BOOST_FOREACH(const std::string & word, words)
        {
            m_stream << "  answer : " << word << std::endl;
        }

        return words;
    }

    void DictionaryLog::InsertWord(const std::string & word)
    {
        m_nextDictionary.InsertWord(word);
    }

    void DictionaryLog::RemoveWord(const std::string & word)
    {
        m_nextDictionary.RemoveWord(word);
    }

    bool DictionaryLog::IsWordValid(const std::string & word) const
    {
        return m_nextDictionary.IsWordValid(word);
    }

    i32 DictionaryLog::GetWordCount() const
    {
        return m_nextDictionary.GetWordCount();
    }
}

