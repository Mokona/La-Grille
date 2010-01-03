#include "wordgrid/GridOutputStream.h"
#include "wordgrid/Square.h"
#include "wordgrid/Grid.h"

namespace Wordgrid
{

    GridOutputStream::GridOutputStream(std::ostream & st) :
        m_stream(st)
    {
    }

    GridOutputStream::~GridOutputStream()
    {
    }

    // TODO : returning stream doesn't make much sense. For chain, use operator <<
    // TODO : making grid parameter const needs a little work on the begin() end() of grid
    std::ostream & GridOutputStream::operator()(Wordgrid::Grid & grid)
    {
        std::string headAndTail(grid.GetWidth() + 2, '-');
        m_stream << headAndTail << std::endl;

        LineByLineGridConstIterator it = grid.begin();
        LineByLineGridConstIterator itEnd = grid.end();
        i32 column = 0;

        while (it != itEnd)
        {
            if (column == 0)
            {
                m_stream << "|";
            }

            m_stream << (*it).GetChar();

            ++column;
            if (column == grid.GetWidth())
            {
                m_stream << "|\n";
                column = 0;
            }
            ++it;
        }
        
        m_stream << headAndTail;
        return m_stream;
    }

    std::ostream & operator << (std::ostream & stream, Wordgrid::Grid & grid)
    {
        Wordgrid::GridOutputStream output(stream);
        output(grid);
        return stream;
    }

}

