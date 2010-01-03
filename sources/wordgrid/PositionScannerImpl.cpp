#include "wordgrid/PositionScannerImpl.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Array2D/LineByLineWalker.h"
#include "wordgrid/Square.h"

namespace Wordgrid
{
    PositionScannerImpl::PositionScannerImpl(const Grid & grid) :
        m_grid(grid)
    {
    }
    
    PositionScannerImpl::~PositionScannerImpl()
    {
    }

    const Grid & PositionScannerImpl::GetGrid() const
    {
        return m_grid;
    }

    PositionScanner::PositionList PositionScannerImpl::GetPositions() const
    {
        PositionList posList;

        for(Array2D::LineByLineWalker walker(GetGrid().GetSize()) ;
            !walker.IsAtEnd() ;
            ++walker)
        {
            if (!GetGrid().GetSquare(walker.GetPosition()).IsBlack())
            {
                posList.push_back(walker.GetPosition());
            }
        }

        return posList;
    }

}

