#include "wordgrid/Request.h"
#include "wordgrid/Assert.h"

namespace Wordgrid
{
    bool Request::Equals(const Request & request) const
    {
        return (GetStart() == request.GetStart()) &&
               (GetDirection() == request.GetDirection()) &&
               (m_partialWord == request.m_partialWord);
    }

    bool operator == (const Request & first, const Request & second)
    {
        return first.Equals(second);
    }

    const Request::Constraint Request::NoConstraint()
    {
        return PartialWord::EmptyChar();
    }

    Request::Request() :
        m_direction(EDirection_Horizontal)
    {
    }

    Request::~Request()
    {
    }

    void Request::SetStart(const Vector2 & start)
    {
        m_startPosition = start;
    }

    const Vector2 & Request::GetStart() const
    {
        return m_startPosition;
    }

    void Request::SetDirection(EDirection direction)
    {
        m_direction = direction;
    }

    EDirection Request::GetDirection() const
    {
        return m_direction;
    }

    void Request::AddConstraint(const Request::Constraint & constraint)
    {
        m_partialWord.Add(constraint);
    }

    ui32 Request::Size() const
    {
        return m_partialWord.Size();
    }

    const PartialWord & Request::GetPartialWord() const
    {
        return m_partialWord;
    }

    std::ostream & operator << (std::ostream & stream, const Request & request)
    {
        stream << request.GetPartialWord();
        return stream;
    }

}

