#include "Framework.h"
#include "wordgrid/SolverImpl.h"
#include "wordgrid/PositionScanner.h"
#include "wordgrid/Grid.h"
#include "wordgrid/WordRequestGenerator.h"
#include "wordgrid/Dictionary.h"
#include "wordgrid/Request.h"
#include "wordgrid/Assert.h"
#include "wordgrid/Square.h"
#include "wordgrid/WordWriterImpl.h"
#include "wordgrid/PartialWord.h"
#include <list>

BOOST_AUTO_TEST_SUITE(TestSolver)

using namespace Wordgrid;

struct MockGridForSolver : public Grid
{
    MockGridForSolver() :
        m_full(false),
        m_count(0),
        m_size(15,15)
    {
    }

    bool IsFull() const
    {
        return m_full;
    }

    void SetFull(bool full)
    {
        m_full = full;
    }

    const Vector2 & GetSize() const
    {
        return m_size;
    }

    void SetSquare(const Vector2 & position, const Square & content)
    {
        ++m_count;
    }

    /*
    const Square & GetSquare(const Vector2 & position) const
    {
        static Square notFound;
        for (unsigned int index = 0; index < m_returnedPositions.size(); ++index)
        {
            if (m_returnedPositions[index] == position)
            {
                return m_returnedSquare[index];
            }
        }
        return notFound;
    }
    */

    bool IsInitialized() const
    {
        return true;
    }

    bool m_full;
    i32 m_count;
    Vector2 m_size;

    /*
    std::vector<Vector2> m_returnedPositions;
    std::vector<Square> m_returnedSquare;
    */
};

struct MockPositionScannerForSolver : public PositionScanner
{
    MockPositionScannerForSolver(const Grid & grid, i32 positions = 0)
    {
        switch(positions)
        {
            case 2:
                m_positions.push_back(Vector2(4,5));
            case 1:
                m_positions.push_back(Vector2(9,2));
                break;
        }
    }

    PositionScanner::PositionList GetPositions() const
    {
        return m_positions;
    }

    PositionScanner::PositionList m_positions;
};

struct MockWordRequestGenerator : public WordRequestGenerator
{
    MockWordRequestGenerator(const Grid & grid, i32 places = 0) :
        WordRequestGenerator(grid),
        m_count(0)
    {
        Request request;

        switch(places)
        {
            case 2:
                request.SetStart(Vector2(2,0));
                request.SetDirection(EDirection_Vertical);
                request.AddConstraint(Request::Constraint('A'));
                request.AddConstraint(Request::NoConstraint());
                m_requests.push_back(request);
            case 1:
                request.SetStart(Vector2(1,3));
                request.SetDirection(EDirection_Horizontal);
                request.AddConstraint(Request::NoConstraint());
                request.AddConstraint(Request::Constraint('B'));
                request.AddConstraint(Request::NoConstraint());
                m_requests.push_back(request);
        }
    }

    RequestList Generate(const Vector2 & position)
    {
        ++m_count;
        m_positions.push_back(position);

        return m_requests;
    }

    const Grid & GetInternalGrid() const
    {
        return GetGrid();
    }

    RequestList m_requests;

    i32 m_count;
    // TODO : when implementing a mock framework, this could be a list upon which we iterate
    // to check equality of requested and received. At now, vector gives us a handy [] operator
    std::vector<Vector2> m_positions;
};

struct MockDictionary : public Dictionary
{
    MockDictionary(i32 words = 0) :
        m_count(0)
    {
        while (words)
        {
            m_wordList.push_back(std::string("WORD"));
            --words;
        }
    }

    virtual std::vector<std::string> Search(const PartialWord & partialWord) const
    {
        m_partialWords[m_count] = partialWord;
        ++m_count;

        return m_wordList;
    }

    virtual void InsertWord(const std::string & word)
    {
    }

    virtual void RemoveWord(const std::string & word)
    {
    }

    virtual bool IsWordValid(const std::string & word) const
    {
        return true;
    }

    virtual i32 GetWordCount() const
    {
        return 0;
    }

    mutable i32 m_count;
    mutable PartialWord m_partialWords[15];

    std::vector<std::string> m_wordList;
};

struct MockWordWriterImpl : public WordWriter
{
    MockWordWriterImpl(Grid & m_grid) :
        WordWriter(m_grid),
        m_count(0),
        m_countUndo(0)
    {
    }

    PartialWord Write(const Vector2 & position, EDirection direction, const std::string & word)
    {
        m_positions[m_count] = position;
        m_directions[m_count] = direction;
        m_words[m_count] = word;

        ++m_count;

        return PartialWord();
    }

    void UndoWrite(const Vector2 & position, EDirection chosenDirection, const PartialWord & writtenWord)
    {
        m_positionsUndo[m_countUndo] = position;
        m_directionsUndo[m_countUndo] = chosenDirection;
        m_wordsUndo[m_countUndo] = std::string(writtenWord.begin(), writtenWord.end());

        ++m_countUndo;
    }

    i32 m_count;
    Vector2 m_positions[15];
    EDirection m_directions[15];
    std::string m_words[15];

    i32 m_countUndo;
    Vector2 m_positionsUndo[15];
    EDirection m_directionsUndo[15];
    std::string m_wordsUndo[15];
};

struct MockCalledSolver : public SolverImpl
{
    MockCalledSolver() :
        m_count(0)
    {
    }

    bool Solve(Grid & grid)
    {
        ++m_count;
        return false;
    }

    i32 m_count;
};

struct SolverWithMockedComponents
{
    SolverWithMockedComponents(i32 positions = 0,
                               i32 places = 0,
                               i32 words = 0) :
        m_mockPositionScanner(m_grid, positions),
        m_mockWordRequestGenerator(m_grid, places),
        m_mockDictionary(words),
        m_mockSimpleWriter(m_grid)
    {
        m_solver.SetPositionScanner(m_mockPositionScanner);
        m_solver.SetWordRequestGenerator(m_mockWordRequestGenerator);
        m_solver.SetDictionary(m_mockDictionary);
        m_solver.SetWordWriter(m_mockSimpleWriter);
        m_solver.SetSolverHook(m_mockCalledSolver);
    }

    SolverImpl m_solver;
    MockGridForSolver m_grid;
    MockPositionScannerForSolver m_mockPositionScanner;
    MockWordRequestGenerator m_mockWordRequestGenerator;
    MockDictionary m_mockDictionary;
    MockWordWriterImpl m_mockSimpleWriter;
    MockCalledSolver m_mockCalledSolver;
};

struct SolverWithReturnedPositions : SolverWithMockedComponents
{
    /*
     * 2 start positions
     * 0 requests
     * 0 returned word
     */
    SolverWithReturnedPositions() :
        SolverWithMockedComponents(2, 0, 0)
    {
    }
};

struct SolverWithReturnedPositionsAndRequestsButNoWord : SolverWithMockedComponents
{
    /*
     * 2 start positions
     * 1 requests (so 2 calls to Search)
     * 0 returned word
     */
    SolverWithReturnedPositionsAndRequestsButNoWord() :
        SolverWithMockedComponents(2, 1, 0)
    {
    }
};

struct SolverWithReturnedPositionsAndRequests : SolverWithMockedComponents
{
    /*
     * 2 start positions
     * 1 requests (so 2 calls to Search)
     * 1 returned word (so twice the same resolved request, so one write to Grid)
     */
    SolverWithReturnedPositionsAndRequests() :
        SolverWithMockedComponents(2, 1, 1)
    {
    }
};

struct SolverWithReturnedPositionAndRequestsDuplicateWord : SolverWithMockedComponents
{
    /*
     * 1 start position
     * 2 different requests (so 2 calls to Search)
     * 2 returned word (so 2 words written on the grid, as there is two duplicates on the 4 resolved requests)
     */
    SolverWithReturnedPositionAndRequestsDuplicateWord() :
        SolverWithMockedComponents(1, 2, 2)
    {
    }
};

BOOST_FIXTURE_TEST_CASE(return_true_if_grid_full, SolverWithMockedComponents)
{
    m_grid.SetFull(true);
    BOOST_CHECK_EQUAL( true, m_solver.Solve(m_grid) );
}

BOOST_FIXTURE_TEST_CASE(if_no_scan_position_return_false, SolverWithMockedComponents)
{
    BOOST_CHECK_EQUAL( false, m_solver.Solve(m_grid) );
}

BOOST_FIXTURE_TEST_CASE(if_no_position_no_call_to_wordplacegenerator, SolverWithMockedComponents)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 0, m_mockWordRequestGenerator.m_count );
}

BOOST_FIXTURE_TEST_CASE(if_positions_call_to_wordplacegenerator, SolverWithReturnedPositions)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 2, m_mockWordRequestGenerator.m_count );
}

BOOST_FIXTURE_TEST_CASE(if_positions_call_to_wordplacegenerator_with_these_positions, SolverWithReturnedPositions)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK(m_mockPositionScanner.m_positions[0] == m_mockWordRequestGenerator.m_positions[0] );
    BOOST_CHECK(m_mockPositionScanner.m_positions[1] == m_mockWordRequestGenerator.m_positions[1] );
}

BOOST_FIXTURE_TEST_CASE(if_positions_call_to_wordplacegenerator_with_grid, SolverWithReturnedPositions)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( &m_grid, &m_mockWordRequestGenerator.GetInternalGrid() );
}

BOOST_FIXTURE_TEST_CASE(if_no_request_then_no_call_to_dictionary, SolverWithMockedComponents)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 0, m_mockDictionary.m_count );
}

BOOST_FIXTURE_TEST_CASE(if_positions_but_no_request_then_no_call_to_dictionary, SolverWithReturnedPositions)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 0, m_mockDictionary.m_count );
}

BOOST_FIXTURE_TEST_CASE(if_positions_and_requests_then_call_to_dictionary, SolverWithReturnedPositionsAndRequests)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 2, m_mockDictionary.m_count );
}

BOOST_FIXTURE_TEST_CASE(if_no_word_no_grid_fill, SolverWithReturnedPositionsAndRequestsButNoWord)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 0, m_mockSimpleWriter.m_count );
}

BOOST_FIXTURE_TEST_CASE(after_call_to_dictionary_fill_grid, SolverWithReturnedPositionsAndRequests)
{
    m_solver.Solve(m_grid);
    // WORD is written only once because there's twice the same position
    BOOST_CHECK_EQUAL( 1, m_mockSimpleWriter.m_count );
}

BOOST_FIXTURE_TEST_CASE(after_dictionary_fill_grid_at_correct_positions, SolverWithReturnedPositionAndRequestsDuplicateWord)
{
    m_solver.Solve(m_grid);

    BOOST_CHECK(Vector2(2,0) == m_mockSimpleWriter.m_positions[0]);
    BOOST_CHECK(EDirection_Vertical == m_mockSimpleWriter.m_directions[0]);

    BOOST_CHECK(Vector2(1,3) == m_mockSimpleWriter.m_positions[1]);
    BOOST_CHECK(EDirection_Horizontal == m_mockSimpleWriter.m_directions[1]);
}

BOOST_FIXTURE_TEST_CASE(if_twice_same_word_drop_a_write, SolverWithReturnedPositionAndRequestsDuplicateWord)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 2, m_mockSimpleWriter.m_count );
}

BOOST_FIXTURE_TEST_CASE(call_to_dictionary_with_correct_constraints, SolverWithReturnedPositionAndRequestsDuplicateWord)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 2, m_mockDictionary.m_partialWords[0].Size());
    BOOST_CHECK_EQUAL( 5, m_mockDictionary.m_partialWords[1].Size());

    PartialWord::WordIterator it1 = m_mockDictionary.m_partialWords[0].begin();
    BOOST_CHECK_EQUAL( 'A', *it1);
    ++it1;
    BOOST_CHECK_EQUAL( PartialWord::EmptyChar(), *it1);

    PartialWord::WordIterator it2 = m_mockDictionary.m_partialWords[1].begin();
    BOOST_CHECK_EQUAL( 'A', *it2);
    ++it2;
    BOOST_CHECK_EQUAL( PartialWord::EmptyChar(), *it2);
    ++it2;
    BOOST_CHECK_EQUAL( PartialWord::EmptyChar(), *it2);
    ++it2;
    BOOST_CHECK_EQUAL( 'B', *it2);
    ++it2;
    BOOST_CHECK_EQUAL( PartialWord::EmptyChar(), *it2);
}

BOOST_FIXTURE_TEST_CASE(if_call_to_write_then_call_to_solver_hook, SolverWithReturnedPositionsAndRequests)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 1, m_mockCalledSolver.m_count );
}

BOOST_FIXTURE_TEST_CASE(if_solver_hook_returns_false_then_call_to_undowrite, SolverWithReturnedPositionsAndRequests)
{
    m_solver.Solve(m_grid);
    BOOST_CHECK_EQUAL( 1, m_mockSimpleWriter.m_countUndo );
    BOOST_CHECK(m_mockSimpleWriter.m_directions[0] == m_mockSimpleWriter.m_directionsUndo[0]);
    BOOST_CHECK(m_mockSimpleWriter.m_positions[0] == m_mockSimpleWriter.m_positionsUndo[0]);
}

BOOST_FIXTURE_TEST_CASE(after_a_write_to_grid_check_full_formed_words, SolverWithReturnedPositionsAndRequests)
{
    m_solver.Solve(m_grid);
}

BOOST_AUTO_TEST_SUITE_END()

