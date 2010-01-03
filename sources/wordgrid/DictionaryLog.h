#ifndef WORDGRID_DICTIONARYLOG
#define WORDGRID_DICTIONARYLOG

#include "wordgrid/Dictionary.h"
#include <iostream>

namespace Wordgrid
{
    class DictionaryLog : public Dictionary
    {
        public:
            DictionaryLog(Dictionary & next, std::ostream & stream = std::cout);
            virtual ~DictionaryLog();
        
            virtual FoundWords Search(const PartialWord & partialWord) const;

            virtual void InsertWord(const std::string & word);
            virtual void RemoveWord(const std::string & word);
            virtual bool IsWordValid(const std::string & word) const;
            virtual i32 GetWordCount() const;

        private:
            Dictionary & m_nextDictionary;
            std::ostream & m_stream;
    };
    
}

#endif

