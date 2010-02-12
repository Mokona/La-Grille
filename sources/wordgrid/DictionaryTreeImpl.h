#ifndef WORDGRID_DICTIONARYTREEIMPL
#define WORDGRID_DICTIONARYTREEIMPL

#include "wordgrid/Dictionary.h"
#include "wordgrid/CharTree.h"
#include <vector>
#include <string>

namespace Wordgrid
{
    class DictionaryTreeImpl : public Dictionary
    {
        public:
            DictionaryTreeImpl();
            virtual ~DictionaryTreeImpl();

            virtual FoundWords Search(const PartialWord & partialWord) const;

            virtual void InsertWord(const std::string & word);
            virtual void RemoveWord(const std::string & word);
            virtual bool IsWordValid(const std::string & word) const;

            virtual i32 GetWordCount() const;

        private:
            CharTree m_charTree;
            ui32 m_wordCount;
    };
    
}

#endif

