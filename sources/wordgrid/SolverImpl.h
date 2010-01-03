#ifndef WORDGRID_SOLVERIMPL
#define WORDGRID_SOLVERIMPL

#include "wordgrid/Solver.h"
#include "wordgrid/Direction.h"

#include <string>

namespace Wordgrid
{
    class PositionScanner;
    class WordRequestGenerator;
    class Dictionary;
    class WordWriter;
    class Vector2;
    class PartialWord;
    class Request;

    /** SolverImpl takes a grid a finds a solution to it.
     *
     * SolverImpl is based on a generic algorithm that is configured by components that
     * are to be set before calling Solve().
     */
    class SolverImpl : public Solver
    {
        public:
            SolverImpl();
            virtual ~SolverImpl();

            virtual bool Solve(Grid & grid);

            virtual void SetPositionScanner(PositionScanner & scanPosition);
            virtual void SetWordRequestGenerator(WordRequestGenerator & wordRequestGenerator);
            virtual void SetDictionary(Dictionary & dictionary);
            virtual void SetWordWriter(WordWriter & wordWriter);
            virtual void SetSolverHook(Solver & solver);
        
        private:
            bool TryToWriteWordOnGrid(Grid & grid, const Request & request, const std::string & word);
            bool DidWrittenWordGeneratedValidWords(const Grid & grid, const Vector2 & startPosition, EDirection direction, const PartialWord & writtenWord);

            PositionScanner * m_positionScanner;
            WordRequestGenerator * m_requestGenerator;
            Dictionary * m_dictionary;
            WordWriter * m_wordWriter;
            Solver * m_solverHook;

            Dictionary * m_wordsOnGrid;
    };
    
}

#endif

