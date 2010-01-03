#include "Framework.h"
#include "wordgrid/Request.h"
#include "wordgrid/PartialWord.h"

BOOST_AUTO_TEST_SUITE(TestRequest)

using namespace Wordgrid;

std::ostream & operator << (std::ostream & ostr, const Request & request)
{
    return ostr;
}

BOOST_AUTO_TEST_CASE( request_set_start_position )
{
    Request request;

    Vector2 setVector(6,10);
    request.SetStart(setVector);

    BOOST_CHECK(setVector == request.GetStart());
}

BOOST_AUTO_TEST_CASE( request_set_direction )
{
    Request request;

    request.SetDirection(EDirection_Vertical);

    BOOST_CHECK_EQUAL(EDirection_Vertical, request.GetDirection());
}

BOOST_AUTO_TEST_CASE ( request_copy_constructible )
{
    Request request;
    Vector2 setVector(6,10);
    request.SetStart(setVector);
    request.SetDirection(EDirection_Vertical);

    Request request2(request);

    BOOST_CHECK(request == request2);
}

BOOST_AUTO_TEST_CASE ( after_construction_size_is_zero )
{
    Request request;
    BOOST_CHECK_EQUAL(0, request.Size());
}

BOOST_AUTO_TEST_CASE ( after_construction_no_constraint )
{
    Request request;

    BOOST_CHECK(request.GetPartialWord().begin() == request.GetPartialWord().end());
}

BOOST_AUTO_TEST_CASE ( add_one_contraint_and_test_size )
{
    Request request;
    request.AddConstraint(Request::Constraint());

    BOOST_CHECK_EQUAL(1, request.Size());
}

BOOST_AUTO_TEST_CASE ( add_one_constraint_and_get_it )
{
    Request request;
    Request::Constraint constraint;
    request.AddConstraint(constraint);

    BOOST_CHECK_EQUAL(constraint, *request.GetPartialWord().begin());
}

BOOST_AUTO_TEST_CASE ( request_copy_constructible_with_constraints )
{
    Request request;
    Vector2 setVector(6,10);
    request.SetStart(setVector);
    request.SetDirection(EDirection_Vertical);

    Request::Constraint constraint;
    request.AddConstraint(constraint);

    Request request2(request);

    BOOST_CHECK_EQUAL(1, request2.Size());
    BOOST_CHECK(request == request2);
}

BOOST_AUTO_TEST_CASE(request_can_give_a_partial_word)
{
    Request request;
    request.AddConstraint(Request::Constraint('M'));
    request.AddConstraint(Request::Constraint('O'));
    request.AddConstraint(Request::Constraint('T'));
    request.AddConstraint(Request::Constraint('S'));

    PartialWord partialWord = request.GetPartialWord();
    std::string partialString(partialWord.begin(), partialWord.end());

    BOOST_CHECK_EQUAL("MOTS", partialString);
}

BOOST_AUTO_TEST_SUITE_END()

