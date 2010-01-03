#include "wordgrid/PartialWord.h"
#include <ostream>
#include <iostream>

namespace Wordgrid
{
    PartialWord::PartialWord()
    {
    }
    
    PartialWord::~PartialWord()
    {
    }

    void PartialWord::Add(char character)
    {
        m_word += character;
    }

    std::size_t PartialWord::Size() const
    {
        return m_word.size();
    }

    char PartialWord::EmptyChar()
    {
        return ' ';
    }

    PartialWord::WordIterator PartialWord::begin()
    {
        return m_word.begin();
    }

    PartialWord::WordIterator PartialWord::end()
    {
        return m_word.end();
    }

    PartialWord::WordConstIterator PartialWord::begin() const
    {
        return m_word.begin();
    }

    PartialWord::WordConstIterator PartialWord::end() const
    {
        return m_word.end();
    }

    static bool IsCharEqualToConstraint(const char & first, const char & second)
    {
        return (second == PartialWord::EmptyChar()) || (first == second);
    }

    bool PartialWord::IsWordMatching(const std::string & word) const
    {
        if (word.size() != Size())
        {
            return false;
        }

        std::pair<WordConstIterator, WordConstIterator> result;
        result = std::mismatch(word.begin(), word.end(), m_word.begin(), IsCharEqualToConstraint);

        return result.first == word.end() && result.second == m_word.end();
    }

    void PartialWord::Clear()
    {
        m_word.clear();
    }

    bool operator == (const PartialWord & first, const PartialWord & second)
    {
        return first.m_word == second.m_word;
    }

    std::ostream & operator << (std::ostream & stream, const PartialWord & request)
    {
        stream << "\"";
        stream << request.m_word;
        stream << "\"";

        return stream;
    }
}
