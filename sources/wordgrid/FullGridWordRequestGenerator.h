#ifndef WORDGRID_FULLGRIDWORDREQUESTGENERATOR
#define WORDGRID_FULLGRIDWORDREQUESTGENERATOR

#include "wordgrid/WordRequestGenerator.h"

namespace Wordgrid
{
    class FullGridWordRequestGenerator : public WordRequestGenerator
    {
        public:
            FullGridWordRequestGenerator(const Grid & grid);
            virtual ~FullGridWordRequestGenerator();
        
            virtual RequestList Generate(const Vector2 & position);

        private:
            void ConstructHorizontalRequest(const Vector2 & position, RequestList & currentRequests);
            void ConstructVerticalRequest(const Vector2 & position, RequestList & currentRequests);

            bool HasAnEmptySquare(Vector2 start, const Vector2 & stop, const Vector2 & speed) const;

            bool HorizontalIsFull(const Vector2 & position) const;
            bool VerticalIsFull(const Vector2 & position) const;

            void FillWithConstraints(Request & constructedRequest, Vector2 start, const Vector2 & stop, const Vector2 & speed) const;
    };
    
}

#endif

