#include "testgen/WriteEmptyGrid.h"
#include "wordgrid/Grid.h"
#include "wordgrid/GridOutputStream.h"

using namespace Wordgrid;

void WriteEmptyGrid(i32 size)
{
    Grid grid;
    grid.Init(Vector2(size, size));

    std::cout << "Writing an empty (" << size << "x" << size << ") grid :\n";
    std::cout << grid << std::endl;
}

