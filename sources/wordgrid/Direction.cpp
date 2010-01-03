#include "wordgrid/Direction.h"
#include "wordgrid/Assert.h"
#include "wordgrid/Vector2.h"

namespace Wordgrid
{
    static Vector2 HORIZONTAL = Vector2(1,0);
    static Vector2 VERTICAL = Vector2(0,1);

    const Vector2 & SpeedFromDirectionEnum(EDirection direction)
    {
        Vector2 * result = NULL;
        switch(direction)
        {
            case EDirection_Horizontal:
                result = &HORIZONTAL;
                break;
            case EDirection_Vertical:
                result = &VERTICAL;
                break;
            case EDirection_MAX:
                ASSERT(direction < EDirection_MAX, "Fatal error. Direction exceeding maximum value.");
        }

        ASSERT(result, "No result found");
        return *result;
    }

    EDirection OtherDirection(EDirection direction)
    {
        if (direction == EDirection_Horizontal)
        {
            return EDirection_Vertical;
        }

        return EDirection_Horizontal;
    }

    char GetOutputCharForDirection(EDirection direction)
    {
        char value = '?';
        switch(direction)
        {
            case EDirection_Horizontal:
                value = 'H';
                break;
            case EDirection_Vertical:
                value = 'V';
                break;
            case EDirection_MAX:
                break;
        }

        return value;
    }
}

