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
        m_words.push_back(word);
    }

    void DictionarySimpleImpl::RemoveWord(const std::string & word)
    {
        std::vector<std::string>::iterator it = std::find(m_words.begin(), m_words.end(), word);
        if (it != m_words.end())
        {
            m_words.erase(it);
        }
    }

    // TODO : change to IsWordInDictionary
    // It is different because one letter word is valid even if not in the dictionary
    // Or is it ?
    bool DictionarySimpleImpl::IsWordValid(const std::string & word) const
    {
        return std::find(m_words.begin(), m_words.end(), word) != m_words.end();
    }

    i32 DictionarySimpleImpl::GetWordCount() const
    {
        return m_words.size();
    }

}

