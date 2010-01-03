#include "wordgrid/SolverLog.h"
#include "wordgrid/Grid.h"
#include "wordgrid/GridOutputStream.h"
#include <algorithm>

namespace Wordgrid
{
    SolverLog::SolverLog(Solver & nextSolver, std::ostream & stream) :
        m_nextSolver(nextSolver),
        m_depth(0),
        m_maximumDepth(0),
        m_stream(stream)
    {
    }

    void SolverLog::PrintLog(Grid & grid)
    {
        m_stream << "Reached depth : " << GetRecursiveDepth() << "\n";
        m_stream << "With grid : " << "\n";
        m_stream << grid << "\n";
    }

    bool SolverLog::Solve(Grid & grid)
    {
        ++m_depth;
        m_maximumDepth = std::max(m_depth, m_maximumDepth);

        if (m_maximumDepth == m_depth)
        {
            PrintLog(grid);
        }

        bool result = m_nextSolver.Solve(grid);
        --m_depth;

        return result;
    }

    ui32 SolverLog::GetRecursiveDepth() const
    {
        return m_depth;
    }

    ui32 SolverLog::GetMaximumRecursiveDepth() const
    {
        return m_maximumDepth;
    }
}
