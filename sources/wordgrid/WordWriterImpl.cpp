#include "wordgrid/Assert.h"
#include "wordgrid/WordWriterImpl.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/Vector2.h"

namespace Wordgrid
{
    WordWriterImpl::WordWriterImpl(Grid & grid) :
        WordWriter(grid)
    {
    }

    void WordWriterImpl::CheckIfCanWrite(const std::string & word)
    {
        if (word.length() == 0)
        {
            throw Exception::EmptyWord();
        }

        if (!GetGrid().IsInitialized())
        {
            throw Exception::Uninitialized();
        }
    }

    void WordWriterImpl::CheckWordFittingOnGrid(const Vector2 & endPosition)
    {
        const Vector2 & maxCoords = GetGrid().GetSize();
        if (endPosition[0] > maxCoords[0] || endPosition[1] > maxCoords[1])
        {
            throw Exception::WordTooLong();
        }
    }

    Vector2 WordWriterImpl::ComputeEndPosition(const std::string & word, const Vector2 & position, EDirection chosenDirection) const
    {
        const Vector2 & speed(SpeedFromDirectionEnum(chosenDirection));
        Vector2 endPosition(speed);

        endPosition *= word.length();
        endPosition += position;

        return endPosition;
    }

    void WordWriterImpl::FillWrittenWord(const Vector2 & position, char character)
    {
        if (GetGrid().GetSquare(position).IsEmpty())
        {
            writtenWord.Add(character);
        }
        else
        {
            writtenWord.Add(PartialWord::EmptyChar());
        }
    }

    // TODO : function + command. Wrong.
    PartialWord WordWriterImpl::Write(const Vector2 & position, EDirection chosenDirection, const std::string & word)
    {
        CheckIfCanWrite(word);
        CheckWordFittingOnGrid(ComputeEndPosition(word, position, chosenDirection));

        writtenWord.Clear();

        const Vector2 & speed(SpeedFromDirectionEnum(chosenDirection));
        Vector2 localPosition(position);
        Square content;

        std::string::const_iterator stringIt = word.begin();
        for (std::string::size_type index = 0; index < word.length(); ++index, ++stringIt)
        {
            FillWrittenWord(localPosition, *stringIt);

            content.SetChar(*stringIt);
            GetGrid().SetSquare(localPosition, content);

            localPosition += speed;
        }

        ASSERT(stringIt == word.end(), "This iterator should be at the end of the string");

        return writtenWord;
    }

    void WordWriterImpl::UndoWrite(const Vector2 & position, EDirection chosenDirection, const PartialWord & writtenWord)
    {
        // TODO : parameter with same name as member. But this should
        // go away with the future implementation
        std::string word(writtenWord.begin(), writtenWord.end());
        CheckIfCanWrite(word);
        CheckWordFittingOnGrid(ComputeEndPosition(word, position, chosenDirection));

        const Vector2 & speed(SpeedFromDirectionEnum(chosenDirection));
        Vector2 localPosition(position);

        std::string::const_iterator stringIt = writtenWord.begin();
        for (std::string::size_type index = 0; index < writtenWord.Size(); ++index, ++stringIt)
        {
            if (*stringIt != PartialWord::EmptyChar())
            {
                Square content = GetGrid().GetSquare(localPosition);
                ASSERT(content.GetChar() != Square::EmptySquare(), "Unwritting an empty square is not possible !");

                GetGrid().SetSquare(localPosition, Square::EmptySquare());
            }

            localPosition += speed;
        }

        ASSERT(stringIt == writtenWord.end(), "This iterator should be at the end of the string");
    }
} // namespace

