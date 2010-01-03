#ifndef WORDGRID_DIRECTION
#define WORDGRID_DIRECTION

namespace Wordgrid
{
    class Vector2;

    enum EDirection
    {
        EDirection_Vertical,
        EDirection_Horizontal,
        EDirection_MAX
    };

    // TODO : velocity would be a nicer name
    const Vector2 & SpeedFromDirectionEnum(EDirection direction);
    char GetOutputCharForDirection(EDirection direction);
    EDirection OtherDirection(EDirection direction);
}


#endif

