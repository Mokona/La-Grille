#include "wordgrid/CharTree.h"
#include <iostream>

namespace Wordgrid
{
    static const char LEAF_CHAR = '$';

    CharTree::CharTree()
    {
    }
    
    CharTree::~CharTree()
    {
        DeleteAll();
    }

    void CharTree::DeleteAll()
    {
        const std::size_t charCount = m_nextChars.size();

        for (std::size_t index = 0; index < charCount; ++index)
        {
            delete m_nextChars[index];
        }
        m_nextChars.clear();
    }

    int CharTree::FindIndex(char nextChar) const
    {
        const std::size_t charCount = m_nextChars.size();

        for (std::size_t index = 0; index < charCount; ++index)
        {
            if (m_nextChars[index]->m_char == nextChar)
            {
                return index;
            }
        }

        return -1;
    }

    int CharTree::AddNextChar(char nextChar)
    {
        m_nextChars.push_back(new CharTree);
        m_nextChars.back()->m_char = nextChar;

        return m_nextChars.size() - 1;
    }

    int CharTree::CreateChainedAndReturnIndex(char nextChar)
    {
        int index = FindIndex(nextChar);

        if (index == -1)
        {
            index = AddNextChar(nextChar);
        }

        return index;
    }

    bool CharTree::IsLeaf() const
    {
        // return (m_nextChars.size() == 0) || (FindIndex(LEAF_CHAR) != -1);
        return (FindIndex(LEAF_CHAR) != -1);
    }

    void CharTree::Insert(const WordIterator & itWord, const WordIterator & itEnd)
    {
        if (itWord == itEnd)
        {
            CreateChainedAndReturnIndex(LEAF_CHAR);
            return;
        }

        const char currentChar = *itWord;
        const int index = CreateChainedAndReturnIndex(currentChar);

        m_nextChars[index]->Insert(itWord + 1, itEnd);
    }

    void CharTree::Remove(const WordIterator & itWord, const WordIterator & itEnd)
    {
        if (itWord == itEnd)
        {
            if (m_nextChars.size() == 1 && m_nextChars[0]->m_char == LEAF_CHAR)
            {
                delete m_nextChars[0];
                m_nextChars.clear();
            }

            return;
        }

        const char currentChar = *itWord;
        const int index = FindIndex(currentChar);

        if (index == -1)
        {
            return;
        }

        m_nextChars[index]->Remove(itWord + 1, itEnd);

        if (m_nextChars[index]->m_nextChars.size() == 0)
        {
            delete m_nextChars[index];
            m_nextChars.erase(m_nextChars.begin() + index);
        }

    }

    ui32 CharTree::MaximumDepth() const
    {
        if (m_nextChars.size() == 1 && m_nextChars[0]->m_char == LEAF_CHAR)
        {
            return 0;
        }

        const std::size_t charCount = m_nextChars.size();
        ui32 maxCount = 0;

        for (std::size_t index = 0; index < charCount; ++index)
        {
            maxCount = std::max(maxCount, m_nextChars[index]->MaximumDepth());
        }

        return maxCount + 1;
    }

    bool CharTree::ContainsInAnyNext(const WordIterator & itWord, const WordIterator & itEnd, char neutralChar) const
    {
        bool found = false;

        const std::size_t charCount = m_nextChars.size();
        for (std::size_t index = 0; index < charCount; ++index)
        {
            found |= m_nextChars[index]->Contains(itWord, itEnd, neutralChar);
        }
        return found;
    }

    bool CharTree::Contains(const WordIterator & itWord, const WordIterator & itEnd, char neutralChar) const
    {
        if (itWord == itEnd)
        {
            return IsLeaf();
        }

        const char currentChar = *itWord;

        if (currentChar == neutralChar)
        {
            return ContainsInAnyNext(itWord + 1, itEnd, neutralChar);
        }
        else
        {
            const int index = FindIndex(currentChar);

            if (index == -1)
            {
                return false;
            }

            return m_nextChars[index]->Contains(itWord + 1, itEnd, neutralChar);
        }
    }

    bool CharTree::SearchInAnyNext(const std::string & word, const WordIterator & itWord, const WordIterator & itEnd, char neutralChar, FindCallback & callback) const
    {
        bool found = false;

        const std::size_t charCount = m_nextChars.size();
        for (std::size_t index = 0; index < charCount; ++index)
        {
            const char nextChar = m_nextChars[index]->m_char;
            found |= m_nextChars[index]->Search(word + std::string(1, nextChar), itWord, itEnd, neutralChar, callback);
        }
        return found;
    }

    bool CharTree::Search(const std::string & word, const WordIterator & itWord, const WordIterator & itEnd, char neutralChar, FindCallback & callback) const
    {
        if (itWord == itEnd)
        {
            if (IsLeaf())
            {
                callback.Found(word);
            }
            return IsLeaf();
        }

        const char currentChar = *itWord;

        if (currentChar == neutralChar)
        {
            return SearchInAnyNext(word, itWord + 1, itEnd, neutralChar, callback);
        }
        else
        {
            const int index = FindIndex(currentChar);

            if (index == -1)
            {
                return false;
            }

            return m_nextChars[index]->Search(word + std::string(1, currentChar), itWord + 1, itEnd, neutralChar, callback);
        }
    }
}

