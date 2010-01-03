#ifndef WORDGRID_DICTIONARYREADER
#define WORDGRID_DICTIONARYREADER

#include "wordgrid/CommonIncludes.h"

namespace Wordgrid
{
    class DictionaryReader
    {
        public:
            DictionaryReader();
            ~DictionaryReader();

            virtual void Read() = 0;
    };
}

#endif

