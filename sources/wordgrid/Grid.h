#ifndef WORDGRID_GRID
#define WORDGRID_GRID

#include "wordgrid/CommonIncludes.h"
#include "wordgrid/ExceptionMacros.h"
#include "wordgrid/LineByLineGridIterator.h"
#include "wordgrid/Vector2.h"

namespace Wordgrid
{
    namespace Exception
    {
        EXCEPTION_DECLARE(WrongSize);
        EXCEPTION_DECLARE(Uninitialized);
        EXCEPTION_DECLARE(WrongPosition);
    }

    class Square;

    /** A Grid is a representation of a word grid.
     *
     * This grid is a set of Square.
     *
     * It can keep (cache/proxy) some interesting and
     * often used informations.
     *
     */
    class Grid
    { 
        public:
            Grid();
            Grid(Grid & other);
            virtual ~Grid ();

            void Init(const Vector2 & size);

            /** This implementation uses GetSize() to obtain width */
            i32 GetWidth() const;

            /** This implementation uses GetSize() to obtain height */
            i32 GetHeight() const;

            mockable const Vector2 & GetSize() const;

            mockable const Square & GetSquare(const Vector2 & position) const;
            mockable void SetSquare(const Vector2 & position, const Square & content);
            mockable bool IsInitialized() const;

            mockable bool IsFull() const;

            LineByLineGridConstIterator begin() const;
            LineByLineGridConstIterator end() const;

            // The grid size is here only because the solver needs some max size to sort vectors
            enum {
                MaxSize = 300
            };

        private:
            void CheckPosition(const Vector2 & position) const;
            void CheckInitialized() const;
            void KeepCountEmptySquares(const Square & oldSquare, const Square & newSquare);
            i32 Vector2ToLinearPosition(const Vector2 & position) const;

            Vector2 m_size;

            Square * m_squares;
            i32 m_numberEmptySquares;
    };

    bool operator == (const Grid & left, const Grid & right);
    bool operator != (const Grid & left, const Grid & right);

}

#endif

