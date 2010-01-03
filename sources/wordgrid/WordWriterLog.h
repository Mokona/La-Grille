#ifndef WORDGRID_WORDWRITERLOG
#define WORDGRID_WORDWRITERLOG

#include "wordgrid/WordWriter.h"
#include <iostream>

namespace Wordgrid
{
    class WordWriterLog : public WordWriter
    {
        public:
            // TODO : grid here is useless. But needed by interface. Change interface
            WordWriterLog(Grid & grid, WordWriter & next, std::ostream & stream = std::cout);
            virtual ~WordWriterLog();
        
            PartialWord Write(const Vector2 & position, EDirection direction, const std::string & word);
            void UndoWrite(const Vector2 & position, EDirection chosenDirection, const PartialWord & writtenWord);

        private:
            WordWriter & m_nextWordWriter;
            std::ostream & m_stream;
    };
    
}

#endif

