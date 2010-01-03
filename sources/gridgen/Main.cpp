#include "wordgrid/Grid.h"
#include "gridgen/Options.h"
#include "gridgen/SolverFactory.h"
#include "wordgrid/Solver.h"
#include <memory>

int main(int argc, char * argv[])
{
    Gridgen::Options options(argc, argv);

    if (options.WantsHelp())
    {
        return 1;
    }

    Gridgen::SolverFactory solverFactory(options);

    solverFactory.Solve();

    return 0;
}
