#include "wordgrid/Square.h"

namespace Wordgrid
{
    bool operator == (const Square & first, const Square & second)
    {
        return first.GetChar() == second.GetChar();
    }

    bool operator != (const Square & first, const Square & second)
    {
        return !(first == second);
    }

    Square::Square() :
        m_char(' ')
    {
    }

    Square::Square(char letter) :
        m_char(letter)
    {
    }

    void Square::SetChar(char letter)
    {
        m_char = letter;
    }

    char Square::GetChar() const
    {
        return m_char;
    }

    bool Square::IsCharSet() const
    {
        return m_char != EmptySquare() &&
               m_char != BlackSquare();
    }

    bool Square::IsEmpty() const
    {
        return m_char == EmptySquare();
    }

    bool Square::IsBlack() const
    {
        return m_char == BlackSquare();
    }

    char Square::BlackSquare()
    {
        return '#';
    }

    char Square::EmptySquare()
    {
        return ' ';
    }


} // namespace

