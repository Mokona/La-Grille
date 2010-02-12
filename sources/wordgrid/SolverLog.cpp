#include "wordgrid/SolverLog.h"
#include "wordgrid/Grid.h"
#include "wordgrid/GridOutputStream.h"
#include <algorithm>

namespace Wordgrid
{
    static const int FORCE_PRINT_PERIOD = 1000;

    SolverLog::SolverLog(Solver & nextSolver, std::ostream & stream) :
        m_nextSolver(nextSolver),
        m_depth(0),
        m_maximumDepth(0),
        m_forcePrintPeriod(FORCE_PRINT_PERIOD),
        m_stream(stream)
    {
    }

    void SolverLog::PrintLog(Grid & grid)
    {
        m_stream << "Reached depth : " << GetRecursiveDepth() << "\n";
        m_stream << "With grid : " << "\n";
        m_stream << grid << "\n";
    }

    void SolverLog::SetForcePrintPeriod(ui32 period)
    {
        m_forcePrintPeriod = period;
    }

    bool SolverLog::Solve(Grid & grid)
    {
        ++m_callCount;
        ++m_depth;
        m_maximumDepth = std::max(m_depth, m_maximumDepth);

        if (m_maximumDepth == m_depth || m_callCount == m_forcePrintPeriod)
        {
            PrintLog(grid);
            m_callCount = 0;
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
