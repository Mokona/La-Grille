#ifndef WORDGRID_SCOPEDTIMER
#define WORDGRID_SCOPEDTIMER

#include "wordgrid/CommonIncludes.h"
#include <string>
#include <iostream>
#include <ctime>

namespace Wordgrid
{
    class ScopedTimer
    {
        public:
            ScopedTimer(const std::string & name, std::ostream & stream = std::cout);
            ~ScopedTimer();

        private:
            const std::string m_name;
            std::ostream & m_stream;
            std::clock_t m_startClock;

    };
}

#endif

