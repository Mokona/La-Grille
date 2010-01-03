#ifndef WORDGRID_DICTIONARYSIMPLEIMPL
#define WORDGRID_DICTIONARYSIMPLEIMPL

#include "wordgrid/Dictionary.h"
#include <vector>
#include <string>

namespace Wordgrid
{
    /** A very direct, simple and slow dictionary implementation. */
    class DictionarySimpleImpl : public Dictionary
    {
        public:
            DictionarySimpleImpl();
            virtual ~DictionarySimpleImpl();

            virtual FoundWords Search(const PartialWord & partialWord) const;

            virtual void InsertWord(const std::string & word);
            virtual void RemoveWord(const std::string & word);
            virtual bool IsWordValid(const std::string & word) const;

            virtual i32 GetWordCount() const;

        private:
            std::vector<std::string> m_words;
    };
    
}

#endif

