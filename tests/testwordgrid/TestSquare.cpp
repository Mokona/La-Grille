#include "Framework.h"
#include "wordgrid/Square.h"

BOOST_AUTO_TEST_SUITE(TestSquare)

BOOST_AUTO_TEST_CASE(squarecontent_instantiation)
{
    Wordgrid::Square content;
    // No check. Should just not crash
}

BOOST_AUTO_TEST_CASE(set_char)
{
    Wordgrid::Square content;

    content.SetChar('m');
    BOOST_CHECK_EQUAL( 'm', content.GetChar() );
}

BOOST_AUTO_TEST_CASE(construct_with_char)
{
    Wordgrid::Square content('R');
    BOOST_CHECK_EQUAL( 'R', content.GetChar() );
}

BOOST_AUTO_TEST_CASE ( test_equality )
{
    Wordgrid::Square content1;
    Wordgrid::Square content2;
    Wordgrid::Square content3;

    content1.SetChar('a');
    content2.SetChar('a');
    content3.SetChar('b');

    BOOST_CHECK( content1 == content2 );
    BOOST_CHECK( !(content1 != content2) );

    BOOST_CHECK( content1 != content3 );

}

BOOST_AUTO_TEST_CASE(test_set)
{
    Wordgrid::Square content;
    
    BOOST_CHECK( content.IsEmpty() );

    content.SetChar('A');
    BOOST_CHECK( !content.IsEmpty() );

    content.SetChar(content.EmptySquare());
    BOOST_CHECK( content.IsEmpty() );

    content.SetChar(content.BlackSquare());
    BOOST_CHECK( !content.IsEmpty() );
}

BOOST_AUTO_TEST_CASE(test_set_empty_square)
{
    Wordgrid::Square content;
}

BOOST_AUTO_TEST_CASE(test_is_black_square)
{
    Wordgrid::Square content;
}

BOOST_AUTO_TEST_SUITE_END()

