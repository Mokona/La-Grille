#include "wordgrid/WordWriterLog.h"
#include "wordgrid/Vector2.h"

namespace Wordgrid
{
    WordWriterLog::WordWriterLog(Grid & grid, WordWriter & next, std::ostream & stream) :
        WordWriter(grid),
        m_nextWordWriter(next),
        m_stream(stream)
    {
    }

    WordWriterLog::~WordWriterLog()
    {
    }
    
    PartialWord WordWriterLog::Write(const Vector2 & position, EDirection direction, const std::string & word)
    {
        m_stream << "Writing to grid at " << position << GetOutputCharForDirection(direction) << " : " << word << std::endl;
        return m_nextWordWriter.Write(position, direction, word);
    }

    void WordWriterLog::UndoWrite(const Vector2 & position, EDirection chosenDirection, const PartialWord & writtenWord)
    {
        m_stream << "Undo Writing to grid at " << position << GetOutputCharForDirection(chosenDirection) << " : " << std::string(writtenWord.begin(), writtenWord.end()) << std::endl;
        m_nextWordWriter.UndoWrite(position, chosenDirection, writtenWord);
    }
}

