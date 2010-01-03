#include "wordgrid/SolverImpl.h"
#include "wordgrid/Assert.h"
#include "wordgrid/PositionScanner.h"
#include "wordgrid/WordRequestGenerator.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Dictionary.h"
#include "wordgrid/DictionarySimpleImpl.h"
#include "wordgrid/WordWriter.h"
#include "wordgrid/Request.h"
#include "wordgrid/LateralWordsCheckerImpl.h"
#include "boost/foreach.hpp"
#include <set>

namespace Wordgrid
{
    static int Vector2Sorting(const Vector2 & vector)
    {
        return Grid::MaxSize * vector[1] + vector[0];
    }

    // TODO : heavy because of m_request copies are heavy.
    struct ResolvedRequest
    {
        ResolvedRequest(Request & request, const std::string & answer) :
            m_request(request),
            m_answer(answer)
        {
        }

        Request m_request;
        std::string m_answer;

        // TODO : is it used ?
        /*
        bool operator == (const ResolvedRequest & other)
        {
            return (m_request.GetStart() == other.m_request.GetStart()) &&
                   (m_answer == other.m_answer);
        }
        */

        bool operator < (const ResolvedRequest & other) const
        {
            int sortedValueThis = Vector2Sorting(m_request.GetStart());
            int sortedValueOther = Vector2Sorting(other.m_request.GetStart());

            bool result = (sortedValueThis < sortedValueOther) ||
                          ((sortedValueThis == sortedValueOther) && (m_answer < other.m_answer));

            return result;
        }
    };


    SolverImpl::SolverImpl() :
        m_positionScanner(NULL),
        m_requestGenerator(NULL),
        m_dictionary(NULL),
        m_wordWriter(NULL),
        m_solverHook(NULL)
    {
        m_wordsOnGrid = new DictionarySimpleImpl;
    }

    SolverImpl::~SolverImpl()
    {
        delete m_wordsOnGrid;
    }

    void SolverImpl::SetPositionScanner(PositionScanner & scanPosition)
    {
        m_positionScanner = &scanPosition;
    }

    void SolverImpl::SetWordRequestGenerator(WordRequestGenerator & wordRequestGenerator)
    {
        m_requestGenerator = &wordRequestGenerator;
    }

    void SolverImpl::SetDictionary(Dictionary & dictionary)
    {
        m_dictionary = &dictionary;
    }

    void SolverImpl::SetWordWriter(WordWriter & wordWriter)
    {
        m_wordWriter = &wordWriter;
    }

    void SolverImpl::SetSolverHook(Solver & solver)
    {
        m_solverHook = &solver;
    }

    bool SolverImpl::DidWrittenWordGeneratedValidWords(const Grid & grid, const Vector2 & startPosition, EDirection direction, const PartialWord & writtenWord)
    {
        LateralWordsCheckerImpl checker(grid, *m_dictionary);
        Request request;

        request.SetStart(startPosition);
        request.SetDirection(direction);

        // TODO : we have the partial word, but must reconstruct it. Stupid.
        BOOST_FOREACH(char character, writtenWord)
        {
            request.AddConstraint(character);
        }

        return checker.AreSideWordsValid(request);
    }

    bool SolverImpl::TryToWriteWordOnGrid(Grid & grid, const Request & request, const std::string & word)
    {
        PartialWord writtenWord = m_wordWriter->Write(request.GetStart(),
                                                      request.GetDirection(),
                                                      word);

        if (DidWrittenWordGeneratedValidWords(grid, request.GetStart(), request.GetDirection(), writtenWord))
        {
            // TODO : don't add if the word is size one
            m_wordsOnGrid->InsertWord(word);
            if (m_solverHook->Solve(grid))
            {
                return true;
            }
            m_wordsOnGrid->RemoveWord(word);
        }


        m_wordWriter->UndoWrite(request.GetStart(),
                                request.GetDirection(),
                                writtenWord);

        return false;
    }

    // TODO : next step : extract a "StageSolver" with all what's needed for a stage in the solving
    bool SolverImpl::Solve(Grid & grid)
    {
        ASSERT(m_positionScanner, "Don't call Solve without a PositionScanner component");
        ASSERT(m_requestGenerator, "Don't call Solve without a WordRequestGenerator component");
        ASSERT(m_dictionary, "Don't call Solve without a Dictionary component");
        ASSERT(m_wordWriter, "Don't call Solve without a WordWriter component");
        ASSERT(m_solverHook, "Don't call Solve without a Solver component");

        // If the grid is full, we consider it solved
        if (grid.IsFull())
        {
            return true;
        }

        // First, we need positions to scan from
        PositionScanner::PositionList posList = m_positionScanner->GetPositions();

        std::set<ResolvedRequest> resolvedRequests;

        BOOST_FOREACH( Vector2 & position, posList )
        {
            // Be careful : requestList should not have twice the same request, or the solver
            // will do twice the job (or almost, because resolvedRequests will limit damage
            WordRequestGenerator::RequestList requestList = m_requestGenerator->Generate(position);

            BOOST_FOREACH( Request & request, requestList )
            {
                // TODO : maybe it would be better to return a vector on const std::string & to avoid a copy. But it means the Dictionary knows the words (rather than construct them)
                PartialWord partialWord = request.GetPartialWord();
                std::vector<std::string> wordList = m_dictionary->Search(partialWord);

                BOOST_FOREACH( const std::string & word, wordList )
                {
                    ResolvedRequest resolved(request, word);
                    if (resolvedRequests.find(resolved) == resolvedRequests.end())
                    {
                        if (!m_wordsOnGrid->IsWordValid(word))
                        {
                            if (TryToWriteWordOnGrid(grid, request, word))
                            {
                                return true;
                            }
                        }

                        resolvedRequests.insert(resolved);
                        ASSERT(resolvedRequests.find(resolved) != resolvedRequests.end(), "Not in the set after insertion. Something is wrong.");

                    }
                }
            }
        }

        return false;
    }
    
} /* Wordgrid */

