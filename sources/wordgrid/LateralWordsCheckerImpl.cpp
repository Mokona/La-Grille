#include "wordgrid/LateralWordsCheckerImpl.h"
#include "wordgrid/Request.h"
#include "wordgrid/Dictionary.h"
#include "wordgrid/Grid.h"
#include "wordgrid/Square.h"
#include <boost/foreach.hpp>

namespace Wordgrid
{
    LateralWordsCheckerImpl::LateralWordsCheckerImpl(const Grid & grid, const Dictionary & dictionary) :
        m_grid(grid),
        m_dictionary(dictionary)
    {
    }

    LateralWordsCheckerImpl::~LateralWordsCheckerImpl()
    {
    }

    Vector2 LateralWordsCheckerImpl::GetStartOfWord(const Vector2 & startPosition, const Vector2 & velocity) const
    {
        // TODO : redo with a Walker ?
        // TODO : not really tester and thus, bugged
        Vector2 position(startPosition);

        // TODO : Quick fix. Do a component for this responsability
        int positionToCheckIndex = 0;
        if (velocity[1] != 0)
        {
            positionToCheckIndex = 1;
        }

        while (m_grid.GetSquare(position) != Square::BlackSquare() && (position[positionToCheckIndex] > 0))
        {
            position -= velocity;
        }
        return position;
    }

    Vector2 LateralWordsCheckerImpl::GetEndOfWord(const Vector2 & startPosition, const Vector2 & velocity) const
    {
        // TODO : redo with a Walker ?
        Vector2 position(startPosition);

        // TODO : this first part of test (on position) is found at a lot of place.
        while ((position[0] < m_grid.GetWidth() && position[1] < m_grid.GetHeight()) && m_grid.GetSquare(position) != Square::BlackSquare())
        {
            position += velocity;
        }
        return position;
    }

    bool LateralWordsCheckerImpl::IsWordValid(const Vector2 & position, const Vector2 & velocity) const
    {
        Vector2 startOfWord = GetStartOfWord(position, velocity);
        Vector2 endOfWord = GetEndOfWord(position, velocity);

        ui32 countChar = 0;

        std::string word;
        for (Vector2 position(startOfWord); position != endOfWord; position += velocity)
        {
            char character = m_grid.GetSquare(position).GetChar();
            word += character;

            if (character != Square::EmptySquare())
            {
                ++countChar;
            }
        }

        if (word.size() == countChar)
        {
            return m_dictionary.IsWordValid(word);
        }

        return true;
    }

    bool LateralWordsCheckerImpl::AreSideWordsValid(const Request & writtenWord) const
    {
        const Vector2 & writtenWordPosition = writtenWord.GetStart();
        const Vector2 & velocity = SpeedFromDirectionEnum(writtenWord.GetDirection());
        const Vector2 & sideVelocity = SpeedFromDirectionEnum(OtherDirection(writtenWord.GetDirection()));

        Vector2 position(writtenWordPosition);
        BOOST_FOREACH(char character, writtenWord.GetPartialWord())
        {
            if (character != Request::NoConstraint())
            {
                if (!IsWordValid(position, sideVelocity))
                {
                    return false;
                }
            }
            position += velocity;
        }

        return true;
    }
    
}
