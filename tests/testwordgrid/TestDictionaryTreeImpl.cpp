#include "Framework.h"
#include "wordgrid/DictionaryTreeImpl.h"
#include "wordgrid/PartialWord.h"

using namespace Wordgrid;

BOOST_AUTO_TEST_SUITE(TestDictionaryTreeImpl)

BOOST_AUTO_TEST_CASE( get_word_count_after_creation )
{
    DictionaryTreeImpl dictionary;

    BOOST_CHECK_EQUAL(0, dictionary.GetWordCount());
}

BOOST_AUTO_TEST_CASE( get_word_count_after_insertion )
{
    DictionaryTreeImpl dictionary;

    dictionary.InsertWord("WORD");
    dictionary.InsertWord("DICTIONARY");

    BOOST_CHECK_EQUAL(2, dictionary.GetWordCount());
}

BOOST_AUTO_TEST_CASE( remove_unvalid_word_does_nothing )
{
    DictionaryTreeImpl dictionary;

    dictionary.InsertWord("WORD");
    dictionary.InsertWord("DICTIONARY");
    dictionary.RemoveWord("BLAH");

    BOOST_CHECK_EQUAL(2, dictionary.GetWordCount());
}

BOOST_AUTO_TEST_CASE( remove_valid_word )
{
    DictionaryTreeImpl dictionary;

    dictionary.InsertWord("WORD");
    dictionary.InsertWord("DICTIONARY");
    dictionary.RemoveWord("WORD");

    BOOST_CHECK_EQUAL(1, dictionary.GetWordCount());
    BOOST_CHECK( !dictionary.IsWordValid("WORD"));
}

BOOST_AUTO_TEST_CASE( word_in_the_dictionary_after_insertion )
{
    DictionaryTreeImpl dictionary;

    dictionary.InsertWord("WORD");

    BOOST_CHECK( dictionary.IsWordValid("WORD"));
    BOOST_CHECK( !dictionary.IsWordValid("DICTIONARY"));
}

BOOST_AUTO_TEST_CASE( word_in_dictionary_found_by_search )
{
    DictionaryTreeImpl dictionary;

    dictionary.InsertWord("WORD");
    dictionary.InsertWord("DICTIONARY");

    PartialWord partialWord;
    partialWord.Add(PartialWord::EmptyChar());
    partialWord.Add('I');
    while (partialWord.Size() < 10)
    {
        partialWord.Add(PartialWord::EmptyChar());
    }

    Dictionary::FoundWords words = dictionary.Search(partialWord);

    BOOST_CHECK_EQUAL( 1, words.size() );
    if (words.size() > 0)
    {
        BOOST_CHECK_EQUAL( "DICTIONARY", words[0] );
    }

}

BOOST_AUTO_TEST_SUITE_END()

