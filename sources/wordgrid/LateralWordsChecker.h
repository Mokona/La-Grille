#ifndef WORDGRID_LATERALWORDSCHECKER
#define WORDGRID_LATERALWORDSCHECKER

#include "wordgrid/CommonIncludes.h"

namespace Wordgrid
{
    class Request;

    // TODO : is an interface really needed for this ? Check after having time stats working.
    class LateralWordsChecker
    {
        public:
            LateralWordsChecker();
            virtual ~LateralWordsChecker();

            virtual bool AreSideWordsValid(const Request & request) const = 0;
    };
}

#endif

