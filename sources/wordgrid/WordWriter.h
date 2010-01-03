#ifndef WORDGRID_WORDWRITER
#define WORDGRID_WORDWRITER

#include "wordgrid/CommonTypes.h"
#include "wordgrid/ExceptionMacros.h"
#include "wordgrid/PartialWord.h"
#include "wordgrid/Direction.h"
#include <string>

namespace Wordgrid
{
    class Grid;
    class Vector2;

    namespace Exception
    {
        EXCEPTION_DECLARE(EmptyWord);
        EXCEPTION_DECLARE(WordTooLong);
    }

    /** A WordWriter writes word on a grid.
     *
     * It can write a word and returns what was
     * really done on the grid.
     *
     * This action can be reverted.
     *
     * A WordWriter is associated to a grid.
     */
    class WordWriter
    {
        public:
            // TODO : Grid as parameter of interface ? Weird. This interface is also an abstract implementation. Clean.
            WordWriter(Grid & grid);

            virtual PartialWord Write(const Vector2 & position, EDirection direction, const std::string & word) = 0;

            virtual void UndoWrite(const Vector2 & position, EDirection chosenDirection, const PartialWord & writtenWord) = 0;

        protected:
            Grid & GetGrid();

        private:
            Grid & m_grid;
    };

} // namespace

#endif // guard

