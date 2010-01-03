#ifndef WORDGRID_POSITIONSCANNER
#define WORDGRID_POSITIONSCANNER

#include "wordgrid/CommonIncludes.h"
#include "wordgrid/Vector2.h"
#include <vector>

namespace Wordgrid
{
    class Grid;

    /** Component interface for components in charge of finding starting points to try to place words on the grid.
     */
    class PositionScanner
    {
        public:
            typedef std::vector<Vector2> PositionList;

        public:
            PositionScanner();
            virtual ~PositionScanner();

            // TODO : Returning a smart pointer would be faster than copying the list
            virtual PositionList GetPositions() const = 0;
    };
    
} /* Word */

#endif

