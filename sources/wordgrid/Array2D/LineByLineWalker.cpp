#include "wordgrid/Array2D/LineByLineWalker.h"

namespace Wordgrid {
namespace Array2D {

    LineByLineWalker::LineByLineWalker(const Vector2 & size) :
        WalkerCommon(size)
    {
    }
    
    LineByLineWalker::LineByLineWalker(const Walker & walker) :
        WalkerCommon(walker)
    {
    }

    LineByLineWalker::~LineByLineWalker()
    {
    }

    Walker & LineByLineWalker::operator ++ ()
    {
        GoRight();
        return *this;
    }

    Walker & LineByLineWalker::operator -- ()
    {
        GoLeft();
        return *this;
    }

}
}

