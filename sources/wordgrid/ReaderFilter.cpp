#include "wordgrid/ReaderFilter.h"

namespace Wordgrid
{
    namespace Filter
    {
        MinMax::MinMax(unsigned int min, unsigned int max) :
            m_min(min),
            m_max(max)
        {
        }

        bool MinMax::operator()(const std::string & word) const
        {
            const size_t wordLen = word.size();
            return wordLen >= m_min && wordLen <= m_max;
        }
    }
}

