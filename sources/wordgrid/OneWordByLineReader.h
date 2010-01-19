#ifndef WORDGRID_ONEWORDBYLINEREADER
#define WORDGRID_ONEWORDBYLINEREADER

#include "wordgrid/DictionaryReader.h"
#include "wordgrid/ReaderFilter.h"
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

            void SetFilter(const Filter::Filter & filter);
        
        private:
            Dictionary & m_dictionary;
            std::istream & m_stream;
            const Filter::Filter * m_filter;
    };
    
}

#endif

