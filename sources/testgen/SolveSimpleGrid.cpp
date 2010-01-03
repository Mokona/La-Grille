#include "testgen/SolveSimpleGrid.h"
#include "wordgrid/Grid.h"
#include "wordgrid/GridOutputStream.h"
#include "wordgrid/SolverImpl.h"
#include "wordgrid/WordWriterImpl.h"
#include "wordgrid/WordWriterLog.h"
#include "wordgrid/PositionScannerImpl.h"
#include "wordgrid/PositionScannerLog.h"
#include "wordgrid/DictionarySimpleImpl.h"
#include "wordgrid/DictionaryLog.h"
#include "wordgrid/FullGridWordRequestGenerator.h"
#include "wordgrid/OneWordByLineReader.h"
#include "wordgrid/ScopedTimer.h"

using namespace Wordgrid;

void SolveSimpleGrid()
{
    Grid grid;
    grid.Init(Vector2(3,2));

    PositionScannerImpl scanner(grid);
    PositionScannerLog scannerLog(scanner);

    DictionarySimpleImpl dictionary;
    DictionaryLog dictionaryLog(dictionary);

    std::stringstream strStream;
    strStream << "SOU\nEST\nSE\nOS\nUT\n";

    OneWordByLineReader reader(dictionary, strStream);
    reader.Read();

    WordWriterImpl writer(grid);
    WordWriterLog writerLog(grid, writer);

    FullGridWordRequestGenerator requestGenerator(grid);

    SolverImpl solver;

    solver.SetPositionScanner(scannerLog);
    solver.SetWordRequestGenerator(requestGenerator);
    solver.SetDictionary(dictionaryLog);
    solver.SetWordWriter(writerLog);
    solver.SetSolverHook(solver);

    ScopedTimer timer("Solving time");
    solver.Solve(grid);

    std::cout << "Resolved grid :\n";
    std::cout << grid << std::endl;
}

