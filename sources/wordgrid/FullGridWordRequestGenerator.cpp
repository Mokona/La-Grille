#include "wordgrid/FullGridWordRequestGenerator.h"
#include "wordgrid/Request.h"
#include "wordgrid/Assert.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include "wordgrid/Direction.h"

namespace Wordgrid
{
    FullGridWordRequestGenerator::FullGridWordRequestGenerator(const Grid & grid) :
        WordRequestGenerator(grid)
    {
    }

    FullGridWordRequestGenerator::~FullGridWordRequestGenerator()
    {
    }

    bool FullGridWordRequestGenerator::HasAnEmptySquare(Vector2 start, const Vector2 & stop, const Vector2 & speed) const
    {
        while (start != stop)
        {
            if (GetGrid().GetSquare(start).IsEmpty())
            {
                return true;
            }
            start += speed;
        }

        return false;
    }

    bool FullGridWordRequestGenerator::HorizontalIsFull(const Vector2 & position) const
    {
        ASSERT(position[0] == 0, "Position must be on left border");

        Vector2 endPosition(position);
        endPosition[0] = GetGrid().GetWidth();

        if (HasAnEmptySquare(position, endPosition, SpeedFromDirectionEnum(EDirection_Horizontal)))
        {
            return false;
        }
        return true;
    }

    bool FullGridWordRequestGenerator::VerticalIsFull(const Vector2 & position) const
    {
        ASSERT(position[1] == 0, "Position must be on top border");

        Vector2 endPosition(position);
        endPosition[1] = GetGrid().GetHeight();

        if (HasAnEmptySquare(position, endPosition, SpeedFromDirectionEnum(EDirection_Vertical)))
        {
            return false;
        }
        return true;
    }

    void FullGridWordRequestGenerator::FillWithConstraints(Request & constructedRequest, Vector2 start, const Vector2 & stop, const Vector2 & speed) const
    {
        // TODO : filling the constraints and searching for empty square are similar.
        // Maybe, it would be better to begin de the contraint construction and drop it if it's full with constraints (ie no free square)
        while (start != stop)
        {
            const Square & currentSquare = GetGrid().GetSquare(start);

            ASSERT(!currentSquare.IsBlack(), "FullGridWordRequestGenerator cannot be used with a grid containing black squares.");

            if (!currentSquare.IsEmpty())
            {
                constructedRequest.AddConstraint(currentSquare.GetChar());
            }
            else
            {
                constructedRequest.AddConstraint(PartialWord::EmptyChar());
            }
            start += speed;
        }

    }

    void FullGridWordRequestGenerator::ConstructHorizontalRequest(const Vector2 & position, RequestList & currentRequests)
    {
        if (HorizontalIsFull(position))
        {
            return;
        }
        Request constructedRequest;
        constructedRequest.SetStart(position);
        constructedRequest.SetDirection(EDirection_Horizontal);

        Vector2 endPosition(position); // TODO : duplicated code
        endPosition[0] = GetGrid().GetWidth();
        FillWithConstraints(constructedRequest, position, endPosition, Vector2(1, 0)); // TODO : signature too big.

        currentRequests.push_back(constructedRequest);
    }

    void FullGridWordRequestGenerator::ConstructVerticalRequest(const Vector2 & position, RequestList & currentRequests)
    {
        if (VerticalIsFull(position))
        {
            return;
        }
        Request constructedRequest;
        constructedRequest.SetStart(position);
        constructedRequest.SetDirection(EDirection_Vertical);

        Vector2 endPosition(position); // TODO : duplicated code
        endPosition[1] = GetGrid().GetHeight();
        FillWithConstraints(constructedRequest, position, endPosition, Vector2(0, 1)); // TODO : signature too big.

        currentRequests.push_back(constructedRequest);
    }

    WordRequestGenerator::RequestList FullGridWordRequestGenerator::Generate(const Vector2 & position)
    {
        RequestList requests;

        if(position[0] == 0)
        {
            ConstructHorizontalRequest(position, requests);
        }

        if(position[1] == 0)
        {
            ConstructVerticalRequest(position, requests);
        }

        return requests;
    }
    
}

