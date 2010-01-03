#ifndef WORDGRID_ARRAY2D_WALKER
#define WORDGRID_ARRAY2D_WALKER

#include "wordgrid/CommonIncludes.h"

namespace Wordgrid
{
    class Vector2;

namespace Array2D
{
    class Walker
    {
        public:
            virtual ~Walker();

            virtual const Vector2 & GetSize() const = 0;
            virtual const Vector2 & GetPosition() const = 0;

            virtual Walker & operator ++ () = 0;
            virtual Walker & operator -- () = 0;
        
        private:
            /* data */
    };
}
}

#endif

