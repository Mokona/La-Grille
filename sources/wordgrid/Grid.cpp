#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/Assert.h"

#include <cstdlib> // TODO : put this in common header. At least with win32-mingw

namespace Wordgrid
{
    namespace Exception
    {
        EXCEPTION_IMPLEMENT(WrongSize, "The given size for grid was illegal");
        EXCEPTION_IMPLEMENT(Uninitialized, "Tried to access a non initialized object");
        EXCEPTION_IMPLEMENT(WrongPosition, "Tried to access an invalid position : outside the grid");
    }

    void CheckSize(const Vector2 & size)
    {
        if (size[0] <= 0 || size[1] <= 0)
        {
            throw Exception::WrongSize();
        }
        if (size[0] >= Grid::MaxSize || size[1] >= Grid::MaxSize)
        {
            throw Exception::WrongSize();
        }
    }

    Grid::Grid() :
        m_squares(NULL),
        m_numberEmptySquares(0)
    {
    }

    Grid::Grid(Grid & other)
    {
        Init(other.GetSize());

        for (i32 index = 0; index < m_numberEmptySquares; ++index)
        {
            m_squares[index] = other.m_squares[index];
        }

        m_numberEmptySquares = other.m_numberEmptySquares;
    }

    Grid::~Grid()
    {
        // TODO : make macro for this
        if (m_squares)
        {
            delete[] m_squares;
        }
    }

    void Grid::Init(const Vector2 & size)
    {
        CheckSize(size);

        m_size.Set(size[0], size[1]);

        i32 totalSize = m_size[0] * m_size[1];
        m_squares = new Square[totalSize];
        m_numberEmptySquares = totalSize;
    }

    bool Grid::IsInitialized() const
    {
        return m_squares != NULL;
    }

    i32 Grid::GetWidth() const
    {
        return GetSize()[0];
    }

    i32 Grid::GetHeight() const
    {
        return GetSize()[1];
    }

    const Vector2 & Grid::GetSize() const
    {
        return m_size;
    }

    void Grid::CheckPosition(const Vector2 & position) const
    {
        if (position[0] < 0 || position[0] >= GetWidth() ||
            position[1] < 0 || position[1] >= GetHeight())
        {
            throw Exception::WrongPosition();
        }
    }

    void Grid::CheckInitialized() const
    {
        if (!IsInitialized())
        {
            throw Exception::Uninitialized();
        }
    }

    void Grid::KeepCountEmptySquares(const Square & oldSquare, const Square & newSquare)
    {
        if (oldSquare.IsEmpty() != newSquare.IsEmpty())
        {
            if (newSquare.GetChar() == Square::EmptySquare())
            {
                ++m_numberEmptySquares;
            }
            else
            {
                --m_numberEmptySquares;
            }
        }
    }

    i32 Grid::Vector2ToLinearPosition(const Vector2 & position) const
    {
        return position[0] + position[1] * GetWidth();
    }

    const Square & Grid::GetSquare(const Vector2 & position) const
    {
        CheckInitialized();
        CheckPosition(position);

        return m_squares[Vector2ToLinearPosition(position)];
    }

    void Grid::SetSquare(const Vector2 & position, const Square & square)
    {
        CheckInitialized();
        CheckPosition(position);

        Square & thisSquare = m_squares[Vector2ToLinearPosition(position)];

        if (thisSquare != square)
        {
            KeepCountEmptySquares(thisSquare, square);
            m_squares[Vector2ToLinearPosition(position)] = square;
        }
    }

    bool Grid::IsFull() const
    {
        return m_numberEmptySquares == 0;
    }

    LineByLineGridConstIterator Grid::begin() const
    {
        return LineByLineGridConstIterator(*this, Vector2());
    }

    LineByLineGridConstIterator Grid::end() const
    {
        return LineByLineGridConstIterator(*this, Vector2(0, GetHeight()));
    }

    bool operator == (const Grid & left, const Grid & right)
    {
        // Can't use std::mismatch because it need operator = and default constructor
        if (left.GetSize() != right.GetSize())
        {
            return false;
        }

        // Cryptic !
        LineByLineGridConstIterator itLeft(left.begin());
        LineByLineGridConstIterator itRight(right.begin());

        LineByLineGridConstIterator itLeftEnd(left.end());
        LineByLineGridConstIterator itRightEnd(right.end());

        for ( ;
                itLeft != itLeftEnd &&
                itRight != itRightEnd &&
                *itLeft == *itRight ;
                ++itLeft, ++itRight)
        {
        }

        return (itLeft == itLeftEnd) && (itRight == itRightEnd);
    }

    bool operator != (const Grid & left, const Grid & right)
    {
        return !(left == right);
    }

}

