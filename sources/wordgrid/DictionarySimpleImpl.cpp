#include "wordgrid/DictionarySimpleImpl.h"
#include "wordgrid/PartialWord.h"
#include "boost/foreach.hpp"

#include <algorithm>

namespace Wordgrid
{
    DictionarySimpleImpl::DictionarySimpleImpl()
    {
    }
    
    DictionarySimpleImpl::~DictionarySimpleImpl()
    {
    }

    Dictionary::FoundWords DictionarySimpleImpl::Search(const PartialWord & partialWord) const
    {
        FoundWords foundWords;

        BOOST_FOREACH( const std::string & word, m_words )
        {
            if (partialWord.IsWordMatching(word))
            {
                foundWords.push_back(word);
            }
        }

        return foundWords;
    }

    void DictionarySimpleImpl::InsertWord(const std::string & word)
    {
        m_words.insert(word);
    }

    void DictionarySimpleImpl::RemoveWord(const std::string & word)
    {
        m_words.erase(word);
    }

    bool DictionarySimpleImpl::IsWordValid(const std::string & word) const
    {
        return m_words.find(word) != m_words.end();
    }

    i32 DictionarySimpleImpl::GetWordCount() const
    {
        return m_words.size();
    }

}

