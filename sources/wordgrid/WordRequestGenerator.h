#ifndef WORDGRID_WORDPLACEGENERATOR
#define WORDGRID_WORDPLACEGENERATOR

#include "wordgrid/CommonIncludes.h"
#include <vector>

namespace Wordgrid
{
    class Grid;
    class Vector2;
    class Request;

    /** Interface for components that take a starting position and return a list of possibilities to place words on a grid.
     */
    class WordRequestGenerator
    {
        public:
            typedef std::vector<Request> RequestList;

        public:
            WordRequestGenerator(const Grid & grid);
            virtual ~WordRequestGenerator();
        
            // TODO : return by value... maybe better to pass a ref as a return value parameter. Or a smart pointer.
            virtual RequestList Generate(const Vector2 & position) = 0;

        protected:
            const Grid & GetGrid() const;

        private:
            const Grid & m_grid;
    };
    
} /* Wordgrid */

#endif

