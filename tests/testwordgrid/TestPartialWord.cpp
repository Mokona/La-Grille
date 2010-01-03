#include "Framework.h"
#include "wordgrid/PartialWord.h"

using namespace Wordgrid;

BOOST_AUTO_TEST_SUITE(TestPartialWord)

BOOST_AUTO_TEST_CASE(after_construction_size_is_zero)
{
    PartialWord word;
    BOOST_CHECK_EQUAL(0, word.Size());
}

BOOST_AUTO_TEST_CASE(add_a_letter_increases_size)
{
    PartialWord word;
    word.Add('A');
    BOOST_CHECK_EQUAL(1, word.Size());
}

BOOST_AUTO_TEST_CASE(is_copy_constructible)
{
    PartialWord word;
    word.Add('A');

    PartialWord copiedWord(word);
    BOOST_CHECK(word == copiedWord);
}

BOOST_AUTO_TEST_CASE(partialword_can_valid_word )
{
    PartialWord partialWord;
    partialWord.Add(PartialWord::EmptyChar());
    partialWord.Add('O');
    partialWord.Add(PartialWord::EmptyChar());
    partialWord.Add('S');

    BOOST_CHECK(!partialWord.IsWordMatching("WORD"));
    BOOST_CHECK(!partialWord.IsWordMatching("WORDS"));
    BOOST_CHECK(partialWord.IsWordMatching("MOTS"));
}

BOOST_AUTO_TEST_CASE(clearing_the_word)
{
    PartialWord word;
    word.Add('A');
    word.Clear();

    BOOST_CHECK_EQUAL(0, word.Size());
}

BOOST_AUTO_TEST_SUITE_END()

