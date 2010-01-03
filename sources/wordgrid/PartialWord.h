#ifndef WORDGRID_PARTIALWORD
#define WORDGRID_PARTIALWORD

#include "wordgrid/CommonIncludes.h"
#include <string>

namespace Wordgrid
{
    class PartialWord
    {
        public:
            typedef std::string WordContainer;
            typedef WordContainer::iterator WordIterator;
            typedef WordContainer::const_iterator WordConstIterator;
            typedef WordContainer::const_iterator const_iterator;

        public:
            PartialWord();
            virtual ~PartialWord();

            void Add(char character);
            std::size_t Size() const;

            static char EmptyChar();

            WordIterator begin();
            WordIterator end();

            WordConstIterator begin() const;
            WordConstIterator end() const;

            bool IsWordMatching(const std::string & word) const;

            void Clear();
        
        private:
            WordContainer m_word;

            friend std::ostream & operator << (std::ostream & stream, const PartialWord & request);
            friend bool operator == (const PartialWord & first, const PartialWord & second);
    };
    
    bool operator == (const PartialWord & first, const PartialWord & second);
    std::ostream & operator << (std::ostream & stream, const PartialWord & request);

}

#endif

