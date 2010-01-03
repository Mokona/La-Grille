#ifndef WORDGRID_ARRAY2D_LINEBYLINEWALKER
#define WORDGRID_ARRAY2D_LINEBYLINEWALKER

#include "wordgrid/CommonIncludes.h"
#include "wordgrid/Array2D/WalkerCommon.h"

namespace Wordgrid {
namespace Array2D
{
    class LineByLineWalker : public WalkerCommon
    {
        public:
            LineByLineWalker(const Vector2 & size);
            LineByLineWalker(const Walker & walker);
            virtual ~LineByLineWalker();

            virtual Walker & operator ++ ();
            virtual Walker & operator -- ();
        
        private:
            /* data */
    };
    
}
}

#endif

