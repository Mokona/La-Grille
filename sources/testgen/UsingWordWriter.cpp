#include "testgen/UsingWordWriter.h"
#include "wordgrid/Grid.h"
#include "wordgrid/GridOutputStream.h"
#include "wordgrid/WordWriterImpl.h"

using namespace Wordgrid;

void UsingWordWriter()
{
    Grid grid;
    grid.Init(Vector2(4,3));

    WordWriterImpl writer(grid);

    writer.Write(Vector2(0,0), EDirection_Horizontal, "WORD");
    writer.Write(Vector2(0,1), EDirection_Horizontal, "MOTS");
    writer.Write(Vector2(0,2), EDirection_Horizontal, "NIDS");

    std::cout << "Writing a grid with WordWriter\n";
    std::cout << grid << std::endl;
}

