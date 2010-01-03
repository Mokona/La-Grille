#ifndef WORDGRID_POSITIONSCANNERIMPL
#define WORDGRID_POSITIONSCANNERIMPL

#include "wordgrid/PositionScanner.h"

namespace Wordgrid
{
    class Grid;

    /** This implementation of a PositionScanner considers any non black square to be a valid scanning position. */
    class PositionScannerImpl : public PositionScanner
    {
        public:
            PositionScannerImpl(const Grid & grid);
            virtual ~PositionScannerImpl();
        
            virtual PositionList GetPositions() const;

        private:
            const Grid & GetGrid() const;

        private:
            const Grid & m_grid;
    };
    
} /* Wordgrid */
#endif

