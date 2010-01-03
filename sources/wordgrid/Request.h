#ifndef WORDGRID_REQUEST
#define WORDGRID_REQUEST

#include "wordgrid/CommonIncludes.h"
#include "wordgrid/Vector2.h"
#include "wordgrid/Direction.h"
#include "wordgrid/PartialWord.h"

namespace Wordgrid
{
    class Request
    {
        public:
            typedef char Constraint;
            typedef PartialWord::WordConstIterator ConstraintConstIterator;

        public:
            Request();
            virtual ~Request();

            void SetStart(const Vector2 & start);
            const Vector2 & GetStart() const;

            void SetDirection(EDirection direction);
            EDirection GetDirection() const;

            void AddConstraint(const Constraint & constraint);

            ui32 Size() const;

            bool Equals(const Request & request) const;

            const PartialWord & GetPartialWord() const;

        public:
            static const Constraint NoConstraint();
        
        private:
            Vector2 m_startPosition;
            EDirection m_direction;

            PartialWord m_partialWord;
    };

    bool operator == (const Request & first, const Request & second);
    std::ostream & operator << (std::ostream & stream, const Request & request);

} /* Wordgrid */

#endif

