#include "testgen/WritePredefinedGrid.h"
#include "wordgrid/Grid.h"
#include "wordgrid/GridOutputStream.h"
#include "wordgrid/Square.h"

using namespace Wordgrid;

void WritePredefinedGrid(Wordgrid::i32 size)
{
    Grid grid;
    grid.Init(Vector2(size, size));

    char character = 'A';

    for(LineByLineGridConstIterator it = grid.begin(), itEnd = grid.end();
        it != itEnd;
        ++it)
    {
        grid.SetSquare(it.GetPosition(), Square(character));
        ++character;
    }

    std::cout << "Writing a full grid (" << size << "x" << size << ") grid :\n";
    std::cout << grid << std::endl;
}
