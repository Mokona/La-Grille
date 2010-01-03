#ifndef WORDGRID_ARRAY2D_WALKERIMPL
#define WORDGRID_ARRAY2D_WALKERIMPL

#include "wordgrid/Array2D/Walker.h"
#include "wordgrid/Vector2.h"

namespace Wordgrid
{
namespace Array2D
{
    class WalkerCommon : public Walker
    {
        public:
            WalkerCommon(const Vector2 & size);
            WalkerCommon(const Walker & walker);
            virtual ~WalkerCommon();

            virtual const Vector2 & GetSize() const;
            virtual const Vector2 & GetPosition() const;

            void GoUp(i32 count = 1);
            void GoDown(i32 count = 1);
            void GoLeft(i32 count = 1);
            void GoRight(i32 count = 1);

            bool IsAtEnd() const;

        protected:
            void SetInternalPosition(const Vector2 & position);
        
        private:
            void AdjustCoordinatesHorizontal();
            void AdjustCoordinatesVertical();
            void UpdateFlatPositionFromPosition();
            void UpdatePositionFromFlatPosition();

        private:
            const Vector2 m_size;
            Vector2 m_position;
            i32 m_flatSize;
            i32 m_flatPosition;
    };
    
} 
}

#endif


