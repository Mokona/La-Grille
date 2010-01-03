#ifndef WORDGRID_POSITIONSCANNERLOG
#define WORDGRID_POSITIONSCANNERLOG

#include "wordgrid/PositionScanner.h"
#include <iostream>

namespace Wordgrid
{
    class PositionScannerLog : public PositionScanner
    {
        public:
            PositionScannerLog(PositionScanner & next, std::ostream & stream = std::cout);
            virtual ~PositionScannerLog();
        
            virtual PositionList GetPositions() const;

        private:
            PositionScanner & m_nextScanner;
            std::ostream & m_stream;
    };
    
}

#endif

