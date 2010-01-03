#include "testgen/WriteEmptyGrid.h"
#include "testgen/WritePredefinedGrid.h"
#include "testgen/UsingWordWriter.h"
#include "testgen/CannotSolveGrid.h"
#include "testgen/SolveSimpleGrid.h"

using namespace Wordgrid;

int main(int argc, char const* argv[])
{
    const i32 GRID_SIZE = 3;

    WriteEmptyGrid(GRID_SIZE);
    WritePredefinedGrid(GRID_SIZE);
    UsingWordWriter();
    CannotSolveGrid();
    SolveSimpleGrid();
    
    return 0;
}
