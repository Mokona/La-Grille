#ifndef WORDGRID_DICTIONARY
#define WORDGRID_DICTIONARY

#include "wordgrid/CommonIncludes.h"
#include <vector>
#include <string>

namespace Wordgrid
{
    class PartialWord;

    class Dictionary
    {
        public:
            typedef std::vector<std::string> FoundWords;

        public:
            Dictionary();
            virtual ~Dictionary();

            virtual FoundWords Search(const PartialWord & partialWord) const = 0;

            virtual void InsertWord(const std::string & word) = 0;
            virtual void RemoveWord(const std::string & word) = 0;
            virtual bool IsWordValid(const std::string & word) const = 0;
            virtual i32 GetWordCount() const = 0;
    };
    
} /* Wordgrid */

#endif

