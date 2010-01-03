#include "wordgrid/ScopedTimer.h"

namespace Wordgrid
{
    float clockToMiliseconds(std::clock_t clock)
    {
        return (float)(clock * 1000.f) / CLOCKS_PER_SEC;
    }

    ScopedTimer::ScopedTimer(const std::string & name, std::ostream & stream) :
        m_name(name),
        m_stream(stream)
    {
        m_startClock = std::clock();
    }
    
    ScopedTimer::~ScopedTimer()
    {
        std::clock_t endClock = std::clock();
        float timeMiliseconds = clockToMiliseconds(endClock - m_startClock);
        m_stream << m_name << " : " << timeMiliseconds << "ms\n";
    }
}
