#include "wordgrid/PositionScannerLog.h"

namespace Wordgrid
{
    PositionScannerLog::PositionScannerLog(PositionScanner & next, std::ostream & stream) :
        m_nextScanner(next),
        m_stream(stream)
    {
    }

    PositionScannerLog::~PositionScannerLog()
    {
    }

    PositionScanner::PositionList PositionScannerLog::GetPositions() const
    {
        const PositionList & positions = m_nextScanner.GetPositions();

        m_stream << "Positions: ";
        std::copy(positions.begin(), positions.end(),
                  std::ostream_iterator<Vector2>(m_stream, " "));
        m_stream << std::endl;

        return positions;
    }
}

