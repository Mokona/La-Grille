#include "wordgrid/Assert.h"
#include "wordgrid/WordWriter.h"

namespace Wordgrid
{
    namespace Exception
    {
        EXCEPTION_IMPLEMENT(EmptyWord, "Empty word");
        EXCEPTION_IMPLEMENT(WordTooLong, "The word is too long for the grid");
    }

    WordWriter::WordWriter(Grid & grid) :
        m_grid(grid)
    {
    }

    Grid & WordWriter::GetGrid()
    {
        return m_grid;
    }

} // namespace

