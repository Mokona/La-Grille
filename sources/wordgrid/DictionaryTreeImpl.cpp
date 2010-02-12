#include "wordgrid/DictionaryTreeImpl.h"
#include "wordgrid/PartialWord.h"
#include "boost/foreach.hpp"

#include <algorithm>
#include <iostream>

namespace Wordgrid
{
    struct DictionaryFindCallback : public Wordgrid::CharTree::FindCallback
    {
        public:
            DictionaryFindCallback(Dictionary::FoundWords & foundWords) :
                m_foundWords(foundWords)
            {
            }

            void Found(const std::string & word)
            {
                m_foundWords.push_back(word);
            }

            std::vector<std::string> & m_foundWords;
    };

    DictionaryTreeImpl::DictionaryTreeImpl() :
        m_wordCount(0)
    {
    }
    
    DictionaryTreeImpl::~DictionaryTreeImpl()
    {
    }

    Dictionary::FoundWords DictionaryTreeImpl::Search(const PartialWord & partialWord) const
    {
        FoundWords foundWords;
        DictionaryFindCallback callback(foundWords);

        m_charTree.Search(std::string(), partialWord.begin(), partialWord.end(), PartialWord::EmptyChar(), callback);

        return callback.m_foundWords;
    }

    void DictionaryTreeImpl::InsertWord(const std::string & word)
    {
        if (!m_charTree.Contains(word.begin(), word.end(), '*'))
        {
            m_charTree.Insert(word.begin(), word.end());
            ++m_wordCount;
        }
    }

    void DictionaryTreeImpl::RemoveWord(const std::string & word)
    {
        if (m_charTree.Contains(word.begin(), word.end(), '*'))
        {
            m_charTree.Remove(word.begin(), word.end());
            --m_wordCount;
        }
    }

    bool DictionaryTreeImpl::IsWordValid(const std::string & word) const
    {
        return m_charTree.Contains(word.begin(), word.end(), '*');
    }

    i32 DictionaryTreeImpl::GetWordCount() const
    {
        return m_wordCount;
    }

}

