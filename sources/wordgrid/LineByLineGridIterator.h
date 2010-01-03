#ifndef WORDGRID_LINEBYLINEGRIDITERATOR
#define WORDGRID_LINEBYLINEGRIDITERATOR

#include "wordgrid/CommonIncludes.h"
#include "wordgrid/Vector2.h"

#include <iterator>

namespace Wordgrid
{
    class Grid;
    class Square;

    /** ConstIterator that returns squares from a grid from top left to bottom right, line by line.
     */
    class LineByLineGridConstIterator : public std::iterator<std::input_iterator_tag, Square>
    {
        public:
            LineByLineGridConstIterator(const Grid & grid, const Vector2 & position);
            LineByLineGridConstIterator(const LineByLineGridConstIterator & it);

            LineByLineGridConstIterator & operator ++ ();

            bool operator != (const LineByLineGridConstIterator & other) const;
            bool operator == (const LineByLineGridConstIterator & other) const;

            LineByLineGridConstIterator & operator = (const LineByLineGridConstIterator & other);
            const Square & operator * () const;
            const Vector2 & GetPosition() const;

        private:
            const Grid & m_grid;
            Vector2 m_position;
    };

}

#endif

