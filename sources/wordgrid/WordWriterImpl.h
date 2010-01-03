#ifndef WORDGRID_SIMPLEWORDWRITER
#define WORDGRID_SIMPLEWORDWRITER

#include "wordgrid/CommonTypes.h"
#include "wordgrid/WordWriter.h"
#include <string>

namespace Wordgrid
{
    class Vector2;

    /** A WordWriter simple implementation
     *
     * TODO : at now, WordWriter is kept by solver. If we had an instance
     * by loop, the undoing would be easier and less parameters would be
     * needed.
     *
     * But to have access to implementation, solver needs a factory to
     * obtain WordWriterImpl
     */
    class WordWriterImpl : public WordWriter
    {
        public:
            WordWriterImpl(Grid & grid);

            PartialWord Write(const Vector2 & position, EDirection direction, const std::string & word);
            void UndoWrite(const Vector2 & position, EDirection chosenDirection, const PartialWord & writtenWord);

        private:
            void CheckIfCanWrite(const std::string & word);
            void CheckWordFittingOnGrid(const Vector2 & endPosition);
            Vector2 ComputeEndPosition(const std::string & word, const Vector2 & position, EDirection chosenDirection) const;
            void FillWrittenWord(const Vector2 & position, char character);

            PartialWord writtenWord;
    };

} // namespace

#endif // guard

