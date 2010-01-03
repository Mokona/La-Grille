#include "Framework.h"
#include "wordgrid/DictionaryLog.h"
#include "wordgrid/PositionScannerLog.h"

#include <sstream>

using namespace Wordgrid;

BOOST_AUTO_TEST_SUITE(TestPositionScannerLog)

struct MockPositionScanner : public PositionScanner
{
    MockPositionScanner()
    {
        m_positions.push_back(Vector2(3,4));
        m_positions.push_back(Vector2(6,1));
    }

    PositionScanner::PositionList GetPositions() const
    {
        return m_positions;
    }

    PositionScanner::PositionList m_positions;
};

struct PositionScannerLogFixture
{
    PositionScannerLogFixture() :
        m_scannerLog(m_mockPositionScanner, m_strStream)
    {
    }

    PositionScannerLog m_scannerLog;
    MockPositionScanner m_mockPositionScanner;
    std::stringstream m_strStream;
};

BOOST_FIXTURE_TEST_CASE(get_positions_calls_next_scanner, PositionScannerLogFixture)
{
    PositionScanner::PositionList positions = m_scannerLog.GetPositions();

    BOOST_CHECK_EQUAL(2, positions.size());
    if (positions.size() > 1)
    {
        BOOST_CHECK(Vector2(3,4) == positions[0]);
        BOOST_CHECK(Vector2(6,1) == positions[1]);
    }
    BOOST_CHECK_EQUAL("Positions: (3,4) (6,1) \n", m_strStream.str());
}


BOOST_AUTO_TEST_SUITE_END()

