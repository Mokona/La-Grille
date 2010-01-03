#include "Framework.h"
#include "wordgrid/SolverLog.h"
#include "wordgrid/Grid.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(TestSolverLog)

using namespace Wordgrid;

struct MockSolver : public Solver
{
    MockSolver() :
        m_solveCalled(0),
        m_nextSolver(NULL),
        m_maximumRecursiveLevel(1)
    {
    }

    bool Solve(Grid & grid)
    {
        ++m_solveCalled;

        bool result = true;
        if (m_nextSolver && m_nextSolver->GetRecursiveDepth() < m_maximumRecursiveLevel)
        {
            result = m_nextSolver->Solve(grid);
        }

        return result;
    }

    ui32 m_solveCalled;
    SolverLog * m_nextSolver;
    ui32 m_maximumRecursiveLevel;
};

BOOST_AUTO_TEST_CASE(can_instantiate)
{
    MockSolver solver;
    std::stringstream strStream;
    SolverLog solverLog(solver, strStream);
}

BOOST_AUTO_TEST_CASE(solve_calls_next_hook)
{
    MockSolver solver;
    std::stringstream strStream;
    SolverLog solverLog(solver, strStream);
    Grid grid;

    BOOST_CHECK_EQUAL(0, solver.m_solveCalled);
    solverLog.Solve(grid);
    BOOST_CHECK_EQUAL(1, solver.m_solveCalled);
}

BOOST_AUTO_TEST_CASE(recursive_depth_is_the_same_before_and_after_call)
{
    MockSolver solver;
    std::stringstream strStream;
    SolverLog solverLog(solver, strStream);
    Grid grid;

    BOOST_CHECK_EQUAL(0, solverLog.GetRecursiveDepth());
    solverLog.Solve(grid);
    BOOST_CHECK_EQUAL(0, solverLog.GetRecursiveDepth());
}

BOOST_AUTO_TEST_CASE(max_recursive_depth_is_set_to_maximum_reached_depth)
{
    MockSolver solver;
    std::stringstream strStream;
    SolverLog solverLog(solver, strStream);
    Grid grid;

    BOOST_CHECK_EQUAL(0, solverLog.GetMaximumRecursiveDepth());
    solverLog.Solve(grid);
    BOOST_CHECK_EQUAL(1, solverLog.GetMaximumRecursiveDepth());
}
BOOST_AUTO_TEST_CASE(recursive_depth_is_incremented_when_recurse)
{
    MockSolver solver;
    std::stringstream strStream;
    SolverLog solverLog(solver, strStream);
    solver.m_nextSolver = &solverLog;
    Grid grid;

    solver.m_maximumRecursiveLevel = 2;

    BOOST_CHECK_EQUAL(0, solverLog.GetRecursiveDepth());
    solverLog.Solve(grid);
    BOOST_CHECK_EQUAL(0, solverLog.GetRecursiveDepth());
    BOOST_CHECK_EQUAL(2, solverLog.GetMaximumRecursiveDepth());
    BOOST_CHECK_EQUAL(2, solver.m_solveCalled);
}

BOOST_AUTO_TEST_CASE(output_something_if_maxrecurse_is_reached)
{
    MockSolver solver;
    std::stringstream strStream;
    SolverLog solverLog(solver, strStream);
    solver.m_nextSolver = &solverLog;
    Grid grid;

    BOOST_CHECK_EQUAL(0, strStream.str().size());
    solver.m_maximumRecursiveLevel = 1;
    solverLog.Solve(grid);

    std::size_t sizeOfOutput = strStream.str().size();
    BOOST_CHECK(sizeOfOutput > 0);

    solverLog.Solve(grid);

    std::size_t sizeOfOutput2 = strStream.str().size();
    BOOST_CHECK(sizeOfOutput2 > sizeOfOutput);
}

BOOST_AUTO_TEST_CASE(output_nothing_when_maximum_depth_not_reached)
{
    MockSolver solver;
    std::stringstream strStream;
    SolverLog solverLog(solver, strStream);
    solver.m_nextSolver = &solverLog;
    Grid grid;

    BOOST_CHECK_EQUAL(0, strStream.str().size());
    solver.m_maximumRecursiveLevel = 9;
    solverLog.Solve(grid);

    std::size_t sizeOfOutput = strStream.str().size();
    BOOST_CHECK(sizeOfOutput > 0);

    solver.m_maximumRecursiveLevel = 1;
    solverLog.Solve(grid);

    std::size_t sizeOfOutput2 = strStream.str().size();
    BOOST_CHECK_EQUAL(sizeOfOutput2, sizeOfOutput);
}

BOOST_AUTO_TEST_SUITE_END()

