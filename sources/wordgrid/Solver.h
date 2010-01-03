#ifndef WORDGRID_SOLVER
#define WORDGRID_SOLVER

#include "wordgrid/CommonIncludes.h"

namespace Wordgrid
{
    class Grid;

    class Solver
    {
        public:
            Solver();
            virtual ~Solver();

            virtual bool Solve(Grid & grid) = 0;
    };
    
}

#endif

