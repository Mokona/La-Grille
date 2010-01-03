#include "wordgrid/Vector2.h"

// TODO : make a ostream << operator for Vector2
// This will permit BOOST_CHECK_EQUAL and logging

namespace Wordgrid
{
    Vector2::Vector2() :
        boost::numeric::ublas::vector<i32>(2)
    {
        (*this)(0) = 0;
        (*this)(1) = 0;
    }

    Vector2::Vector2(i32 x, i32 y) :
        boost::numeric::ublas::vector<i32>(2)
    {
        Set(x,y);
    }

    void Vector2::Set(i32 x, i32 y)
    {
        (*this)(0) = x;
        (*this)(1) = y;
    }

    bool operator == (const Vector2 & vector1, const Vector2 & vector2)
    {
        return (vector1[0] == vector2[0]) && (vector1[1] == vector2[1]);
    }

    bool operator != (const Vector2 & vector1, const Vector2 & vector2)
    {
        return !(vector1 == vector2);
    }

    std::ostream & operator << (std::ostream & stream, const Wordgrid::Vector2 & vector)
    {
        stream << "(" << vector[0] << "," << vector[1] << ")";
        return stream;
    }

} /* Wordgrid */

