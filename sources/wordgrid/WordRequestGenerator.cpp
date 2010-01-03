#include "wordgrid/WordRequestGenerator.h"
#include "wordgrid/Grid.h"

namespace Wordgrid
{

    WordRequestGenerator::WordRequestGenerator(const Grid & grid) :
        m_grid(grid)
    {
    }

    WordRequestGenerator::~WordRequestGenerator()
    {
    }

    const Grid & WordRequestGenerator::GetGrid() const
    {
        return m_grid;
    }

} /* Word */
