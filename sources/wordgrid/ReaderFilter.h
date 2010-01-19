#ifndef WORDGRID_READERFILTER
#define WORDGRID_READERFILTER

#include "wordgrid/CommonIncludes.h"
#include <string>

namespace Wordgrid
{
    namespace Filter
    {
        struct Filter
        {
            virtual bool operator()(const std::string & word) const = 0;
        };

        class MinMax : public Filter
        {
            public:
                MinMax(unsigned int min, unsigned int max);

                bool operator()(const std::string & word) const;

            private:
                ui32 m_min;
                ui32 m_max;
        };
    }
    
}

#endif

