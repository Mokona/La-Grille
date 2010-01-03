#include "wordgrid/Array2D/WalkerCommon.h"
#include "wordgrid/Assert.h"

namespace Wordgrid
{
namespace Array2D
{
    WalkerCommon::WalkerCommon(const Vector2 & size) :
        m_size(size),
        m_position(0,0),
        m_flatSize(m_size[0] * m_size[1]),
        m_flatPosition(0)
    {
        ASSERT(m_size[0] > 0, "Width must be greater than 0.");
        ASSERT(m_size[1] > 0, "Height must be greater than 0.");
    }

    WalkerCommon::WalkerCommon(const Walker & walker) :
        m_size(walker.GetSize()),
        m_position(walker.GetPosition())
    {
        m_flatSize = m_size[0] * m_size[1];
        UpdateFlatPositionFromPosition();
    }

    WalkerCommon::~WalkerCommon()
    {
    }

    void WalkerCommon::UpdateFlatPositionFromPosition()
    {
        m_flatPosition = m_position[0] + m_position[1] * GetSize()[0];
    }

    void WalkerCommon::UpdatePositionFromFlatPosition()
    {
        while (m_flatPosition < 0)
        {
            m_flatPosition += m_flatSize - 1;
        }
        m_position[1] = m_flatPosition / GetSize()[0];
        m_position[0] = m_flatPosition - (m_position[1] * GetSize()[0]);

        ASSERT(m_position[0] >= 0, "m_position[0] must be positive as a postcondition");
        ASSERT(m_position[1] >= 0, "m_position[1] must be positive as a postcondition");
        ASSERT(m_position[0] < GetSize()[0], "m_position[0] must be less than horizontal size");
    }

    const Vector2 & WalkerCommon::GetSize() const
    {
        return m_size;
    }

    const Vector2 & WalkerCommon::GetPosition() const
    {
        return m_position;
    }

    void WalkerCommon::SetInternalPosition(const Vector2 & position)
    {
        m_position = position;
        UpdateFlatPositionFromPosition();
    }

    void WalkerCommon::GoUp(i32 count)
    {
        m_flatPosition -= count * GetSize()[0];
        AdjustCoordinatesVertical();
    }

    void WalkerCommon::GoDown(i32 count)
    {
        m_flatPosition += count * GetSize()[0];
        AdjustCoordinatesVertical();
    }

    void WalkerCommon::GoLeft(i32 count)
    {
        m_flatPosition -= count;
        AdjustCoordinatesHorizontal();
    }

    void WalkerCommon::GoRight(i32 count)
    {
        m_flatPosition += count;
        AdjustCoordinatesHorizontal();
    }

    void WalkerCommon::AdjustCoordinatesHorizontal()
    {
        UpdatePositionFromFlatPosition();
        ASSERT(m_position[0] >= 0, "m_position[0] must be positive");
        ASSERT(m_position[0] < m_size[0], "m_position[0] is too big");

        // UpdateFlatPositionFromPosition();
    }

    void WalkerCommon::AdjustCoordinatesVertical()
    {
        UpdatePositionFromFlatPosition();
        while(m_position[1] >= GetSize()[1])
        {
            m_position[1] -= GetSize()[1];
            ++m_position[0];
        }
        ASSERT(m_position[1] >= 0, "m_position[1] must be positive");
        ASSERT(m_position[1] < m_size[1], "m_position[0] is too big");

        UpdateFlatPositionFromPosition();
    }

    bool WalkerCommon::IsAtEnd() const
    {
        return m_flatPosition >= m_flatSize;
    }
}
}

