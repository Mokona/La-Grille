#include "gridgen/SolverFactory.h"
#include "gridgen/Options.h"
#include "wordgrid/Grid.h"
#include "wordgrid/SolverImpl.h"
#include "wordgrid/SolverLog.h"
#include "wordgrid/WordWriterImpl.h"
#include "wordgrid/WordWriterLog.h"
#include "wordgrid/PositionScannerImpl.h"
#include "wordgrid/PositionScannerLog.h"
#include "wordgrid/DictionarySimpleImpl.h"
#include "wordgrid/DictionaryLog.h"
#include "wordgrid/FullGridWordRequestGenerator.h"
#include "wordgrid/OneWordByLineReader.h"
#include "wordgrid/GridOutputStream.h"
#include "wordgrid/ScopedTimer.h"
#include <fstream>

// TODO : very very wrong
// Should have a Factory for each component, constructing with options
// Hooks should have responsability for their chain (thus, delete the first hook is ok)

namespace Gridgen
{
    void LoadDictionary(Wordgrid::Dictionary & dictionary)
    {
        std::ifstream inputFile("/home/mokona/Developpement/AteliersGCN/Grille/grille/data/dictionary.txt");

        Wordgrid::OneWordByLineReader reader(dictionary, inputFile);
        reader.Read();
    }

    SolverFactory::SolverFactory(const Options & options) :
        m_options(options)
    {
    }

    SolverFactory::~SolverFactory()
    {
    }

    void SolverFactory::Solve()
    {
        Wordgrid::Grid grid;
        grid.Init(m_options.GetGridSize());

        Wordgrid::SolverImpl solver;

        Wordgrid::PositionScannerImpl scanner(grid);
        Wordgrid::PositionScannerLog scannerLog(scanner);

        if (m_options.LogPositionScanner())
        {
            solver.SetPositionScanner(scannerLog);
        }
        else
        {
            solver.SetPositionScanner(scanner);
        }

        Wordgrid::DictionarySimpleImpl dictionary;
        Wordgrid::DictionaryLog dictionaryLog(dictionary);
        if (m_options.LogDictionary())
        {
            solver.SetDictionary(dictionaryLog);
        }
        else
        {
            solver.SetDictionary(dictionary);
        }

        Wordgrid::WordWriterImpl writer(grid);
        Wordgrid::WordWriterLog writerLog(grid, writer);
        if (m_options.LogWordWriter())
        {
            solver.SetWordWriter(writerLog);
        }
        else
        {
            solver.SetWordWriter(writer);
        }

        Wordgrid::FullGridWordRequestGenerator requestGenerator(grid);
        solver.SetWordRequestGenerator(requestGenerator);

        Wordgrid::SolverLog solverLog(solver);
        if (m_options.LogSolver())
        {
            solver.SetSolverHook(solverLog);
        }
        else
        {
            solver.SetSolverHook(solver);
        }

        LoadDictionary(dictionary);

        std::cout << "Solving...\n";
        {
            Wordgrid::ScopedTimer timer("Solved time : ");
            solver.Solve(grid);
        }

        std::cout << "Grid :\n";
        std::cout << grid << std::endl;
    }
}

