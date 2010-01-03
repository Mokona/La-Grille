#include "wordgrid/LineByLineGridIterator.h"
#include "wordgrid/Grid.h"

namespace Wordgrid
{
    // Const version
    LineByLineGridConstIterator::LineByLineGridConstIterator(const Grid & grid, const Vector2 & position) :
        m_grid(grid),
        m_position(position)
    {
    }

    LineByLineGridConstIterator::LineByLineGridConstIterator(const LineByLineGridConstIterator & it) :
        m_grid(it.m_grid),
        m_position(it.m_position)
    {
    }

    LineByLineGridConstIterator & LineByLineGridConstIterator::operator ++ ()
    {
        ++m_position[0];
        if (m_position[0] >= m_grid.GetWidth())
        {
            m_position[0] = 0;
            ++m_position[1];
        }
        return *this;
    }

    bool LineByLineGridConstIterator::operator != (const LineByLineGridConstIterator & other) const
    {
        return (&m_grid != &other.m_grid) ||
               (m_position != other.m_position);
    }

    bool LineByLineGridConstIterator::operator == (const LineByLineGridConstIterator & other) const
    {
        return !((*this) != other);
    }

    const Square & LineByLineGridConstIterator::operator * () const
    {
        return m_grid.GetSquare(m_position);
    }

    const Vector2 & LineByLineGridConstIterator::GetPosition() const
    {
        return m_position;
    }

} /* Wordgrid */
