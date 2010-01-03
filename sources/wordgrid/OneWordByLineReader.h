#ifndef WORDGRID_ONEWORDBYLINEREADER

#include "wordgrid/DictionaryReader.h"
#include <istream>

namespace Wordgrid
{
    class Dictionary;

    class OneWordByLineReader : public DictionaryReader
    {
        public:
            OneWordByLineReader(Dictionary & dictionary, std::istream & stream);
            virtual ~OneWordByLineReader();

            virtual void Read();
        
        private:
            Dictionary & m_dictionary;
            std::istream & m_stream;
    };
    
}

#endif

