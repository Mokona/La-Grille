#ifndef WORDGRID_CHARTREE
#define WORDGRID_CHARTREE

#include "wordgrid/CommonIncludes.h"
#include <string>
#include <vector>

namespace Wordgrid
{
    class CharTree
    {
        public:
            typedef const std::string::const_iterator WordIterator;

            struct FindCallback
            {
                virtual void Found(const std::string & word) = 0;
            };

        public:
            CharTree();
            ~CharTree();

            void Insert(const WordIterator & itWord, const WordIterator & itEnd);
            void Remove(const WordIterator & itWord, const WordIterator & itEnd);
            ui32 MaximumDepth() const;

            bool Contains(const WordIterator & itWord, const WordIterator & itEnd, char neutralChar) const;
            bool Search(const std::string & word, const WordIterator & itWord, const WordIterator & itEnd, char neutralChar, FindCallback & callback) const;
            bool IsLeaf() const;


        private:
            int FindIndex(char nextChar) const;
            int CreateChainedAndReturnIndex(char nextChar);
            int AddNextChar(char nextChar);
            bool ContainsInAnyNext(const WordIterator & itWord, const WordIterator & itEnd, char neutralChar) const;
            bool SearchInAnyNext(const std::string & word, const WordIterator & itWord, const WordIterator & itEnd, char neutralChar, FindCallback & callback) const;
            void DeleteAll();

        private:
            std::vector<CharTree *> m_nextChars;
            char m_char;
    };
}

#endif

