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

        private:
            void PrintLog(Grid & grid);

            Solver & m_nextSolver;
            ui32 m_depth;
            ui32 m_maximumDepth;
            std::ostream & m_stream;
    };
    
}

#endif

