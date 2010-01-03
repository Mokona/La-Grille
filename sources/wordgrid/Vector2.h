#ifndef WORDGRID_VECTOR2
#define WORDGRID_VECTOR2

#include <ostream>
#include "wordgrid/CommonIncludes.h"
#include <boost/numeric/ublas/vector.hpp> // TODO : too heavy (specialized in big vectors). Reimplement something simple

namespace Wordgrid
{
    /** Really simple vector of size 2.
     */
    class Vector2 : public boost::numeric::ublas::vector<i32>
    {
        public:
            Vector2();
            Vector2(i32 x, i32 y);

            void Set(i32 x, i32 y);
        
        private:
    };

    bool operator == (const Vector2 & vector1, const Vector2 & vector2);
    bool operator != (const Vector2 & vector1, const Vector2 & vector2);

    std::ostream & operator << (std::ostream & stream, const Wordgrid::Vector2 & vector);
} /* WordGrid */

#endif // guard

