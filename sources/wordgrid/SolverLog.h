#ifndef WORDGRID_SOLVERLOG
#define WORDGRID_SOLVERLOG

#include "wordgrid/CommonIncludes.h"
#include "wordgrid/Solver.h"
#include <iostream>

namespace Wordgrid
{
    class Grid;

    class SolverLog : public Solver
    {
        public:
            SolverLog(Solver & nextSolver, std::ostream & stream = std::cout);
            // virtual ~SolverLog();
        
            virtual bool Solve(Grid & grid);

            ui32 GetRecursiveDepth() const;
            ui32 GetMaximumRecursiveDepth() const;

            void SetForcePrintPeriod(ui32 period);

        private:
            void PrintLog(Grid & grid);

            Solver & m_nextSolver;
            ui32 m_depth;
            ui32 m_maximumDepth;
            ui32 m_callCount;
            ui32 m_forcePrintPeriod;
            std::ostream & m_stream;
    };
    
}

#endif

