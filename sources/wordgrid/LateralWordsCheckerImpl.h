#ifndef WORDGRID_LATERALWORDSCHECKERIMPL
#define WORDGRID_LATERALWORDSCHECKERIMPL

#include "wordgrid/LateralWordsChecker.h"
#include "wordgrid/Vector2.h"

namespace Wordgrid
{
    class Request;
    class Dictionary;
    class Grid;

    class LateralWordsCheckerImpl
    {
        public:
            LateralWordsCheckerImpl(const Grid & grid, const Dictionary & dictionary);
            virtual ~LateralWordsCheckerImpl();

            bool AreSideWordsValid(const Request & request) const;

        private:
            const Grid & m_grid;
            const Dictionary & m_dictionary;

            // TODO : maybe this could come from another class. Return by value ? Mhh
            Vector2 GetStartOfWord(const Vector2 & startPosition, const Vector2 & velocity) const;
            Vector2 GetEndOfWord(const Vector2 & startPosition, const Vector2 & velocity) const;

            bool IsWordValid(const Vector2 & position, const Vector2 & velocity) const;
    };
}

#endif


