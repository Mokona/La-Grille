#include "Framework.h"
#include "wordgrid/CharTree.h"

#include <iostream>

BOOST_AUTO_TEST_SUITE(TestCharTree)

BOOST_AUTO_TEST_CASE( creation )
{
    Wordgrid::CharTree charTree;
}

BOOST_AUTO_TEST_CASE ( insert_empty_string )
{
    Wordgrid::CharTree charTree;
    std::string emptyWord;
    charTree.Insert(emptyWord.begin(), emptyWord.end());

    BOOST_CHECK_EQUAL(0, charTree.MaximumDepth());
}

BOOST_AUTO_TEST_CASE ( insert_empty_string_2 )
{
    Wordgrid::CharTree charTree;
    std::string emptyWord("");
    charTree.Insert(emptyWord.begin(), emptyWord.end());

    BOOST_CHECK_EQUAL(0, charTree.MaximumDepth());
}

BOOST_AUTO_TEST_CASE ( insert_onechar_string )
{
    Wordgrid::CharTree charTree;
    std::string word("a");
    charTree.Insert(word.begin(), word.end());

    BOOST_CHECK_EQUAL(1, charTree.MaximumDepth());
}

BOOST_AUTO_TEST_CASE ( insert_twochar_string )
{
    Wordgrid::CharTree charTree;
    std::string word("ab");
    charTree.Insert(word.begin(), word.end());

    BOOST_CHECK_EQUAL(2, charTree.MaximumDepth());
}

BOOST_AUTO_TEST_CASE ( insert_twochar_string_several_times )
{
    Wordgrid::CharTree charTree;
    std::string word("ab");
    charTree.Insert(word.begin(), word.end());
    charTree.Insert(word.begin(), word.end());

    std::string word2("cd");
    charTree.Insert(word2.begin(), word2.end());

    std::string word3("ac");
    charTree.Insert(word3.begin(), word3.end());

    BOOST_CHECK_EQUAL(2, charTree.MaximumDepth());
}

BOOST_AUTO_TEST_CASE ( insert_different_string_size )
{
    Wordgrid::CharTree charTree;
    std::string word("abfgka");
    charTree.Insert(word.begin(), word.end());
    charTree.Insert(word.begin(), word.end());

    std::string word2("cde");
    charTree.Insert(word2.begin(), word2.end());

    std::string word3("acfg");
    charTree.Insert(word3.begin(), word3.end());

    BOOST_CHECK_EQUAL(6, charTree.MaximumDepth());
}

BOOST_AUTO_TEST_CASE ( insert_then_contains )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("cde");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    BOOST_CHECK(charTree.Contains(word1.begin(), word1.end(), '*'));
    BOOST_CHECK(charTree.Contains(word2.begin(), word2.end(), '*'));
    BOOST_CHECK(charTree.Contains(word3.begin(), word3.end(), '*'));
}

BOOST_AUTO_TEST_CASE ( insert_subwords_then_contains )
{
    Wordgrid::CharTree charTree;
    std::string word1("ab");
    std::string word2("abc");
    std::string word3("abcde");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    BOOST_CHECK(charTree.Contains(word1.begin(), word1.end(), '*'));
    BOOST_CHECK(charTree.Contains(word2.begin(), word2.end(), '*'));
    BOOST_CHECK(charTree.Contains(word3.begin(), word3.end(), '*'));

    std::string word4("");
    std::string word5("a");
    std::string word6("abcd");

    BOOST_CHECK(!charTree.Contains(word4.begin(), word4.end(), '*'));
    BOOST_CHECK(!charTree.Contains(word5.begin(), word5.end(), '*'));
    BOOST_CHECK(!charTree.Contains(word6.begin(), word6.end(), '*'));
}

BOOST_AUTO_TEST_CASE ( insert_then_doesnt_contain_subword )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("cde");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    std::string subWord1("abf");
    std::string subWord2("cd");
    std::string subWord3("a");
    BOOST_CHECK(!charTree.Contains(subWord1.begin(), subWord1.end(), '*'));
    BOOST_CHECK(!charTree.Contains(subWord2.begin(), subWord2.end(), '*'));
    BOOST_CHECK(!charTree.Contains(subWord3.begin(), subWord3.end(), '*'));
}

BOOST_AUTO_TEST_CASE ( insert_then_doesnt_contain_longerword )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("cde");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    std::string subWord1("abfgkaa");
    std::string subWord2("cdeb");
    std::string subWord3("acfgp");
    BOOST_CHECK(!charTree.Contains(subWord1.begin(), subWord1.end(), '*'));
    BOOST_CHECK(!charTree.Contains(subWord2.begin(), subWord2.end(), '*'));
    BOOST_CHECK(!charTree.Contains(subWord3.begin(), subWord3.end(), '*'));

    std::string subWord4("abfgka$");
    std::string subWord5("cde$");
    std::string subWord6("acfg$");
    BOOST_CHECK(!charTree.Contains(subWord4.begin(), subWord4.end(), '*'));
    BOOST_CHECK(!charTree.Contains(subWord5.begin(), subWord5.end(), '*'));
    BOOST_CHECK(!charTree.Contains(subWord6.begin(), subWord6.end(), '*'));
}

BOOST_AUTO_TEST_CASE ( insert_then_contains_word_with_wildcard )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("cde");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    std::string subWord1("ab*gka");
    std::string subWord2("cd*");
    std::string subWord3("*cf*");
    BOOST_CHECK(charTree.Contains(subWord1.begin(), subWord1.end(), '*'));
    BOOST_CHECK(charTree.Contains(subWord2.begin(), subWord2.end(), '*'));
    BOOST_CHECK(charTree.Contains(subWord3.begin(), subWord3.end(), '*'));
}

BOOST_AUTO_TEST_CASE ( can_remove_null_word )
{
    Wordgrid::CharTree charTree;
    std::string word1("");
    std::string word2;

    charTree.Remove(word1.begin(), word1.end());
    charTree.Remove(word2.begin(), word2.end());
}

BOOST_AUTO_TEST_CASE ( insert_then_removes_non_inserted_words )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("cde");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    std::string word4("");
    std::string word5("gfh");
    std::string word6("acfgh");
    std::string word7("cd");

    charTree.Remove(word4.begin(), word4.end());
    charTree.Remove(word5.begin(), word5.end());
    charTree.Remove(word6.begin(), word6.end());
    charTree.Remove(word7.begin(), word7.end());

    BOOST_CHECK(charTree.Contains(word1.begin(), word1.end(), '*'));
    BOOST_CHECK(charTree.Contains(word2.begin(), word2.end(), '*'));
    BOOST_CHECK(charTree.Contains(word3.begin(), word3.end(), '*'));
}

BOOST_AUTO_TEST_CASE ( insert_then_removes_words )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("abf");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    charTree.Remove(word1.begin(), word1.end());
    charTree.Remove(word2.begin(), word2.end());
    charTree.Remove(word3.begin(), word3.end());

    BOOST_CHECK(!charTree.Contains(word1.begin(), word1.end(), '*'));
    BOOST_CHECK(!charTree.Contains(word2.begin(), word2.end(), '*'));
    BOOST_CHECK(!charTree.Contains(word3.begin(), word3.end(), '*'));
}

struct TestFindCallback : public Wordgrid::CharTree::FindCallback
{
    public:
        void Found(const std::string & word)
        {
            // std::cout << word << std::endl;
            m_foundWords.push_back(word);
        }

        std::vector<std::string> m_foundWords;
};

BOOST_AUTO_TEST_CASE ( find_exact_words )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("abf");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    TestFindCallback callback;

    charTree.Search(std::string(), word1.begin(), word1.end(), '*', callback);
    BOOST_CHECK_EQUAL(1, callback.m_foundWords.size());
    BOOST_CHECK_EQUAL(word1, callback.m_foundWords[0]);

    charTree.Search(std::string(), word2.begin(), word2.end(), '*', callback);
    BOOST_CHECK_EQUAL(2, callback.m_foundWords.size());
    BOOST_CHECK_EQUAL(word2, callback.m_foundWords[1]);

    charTree.Search(std::string(), word3.begin(), word3.end(), '*', callback);
    BOOST_CHECK_EQUAL(3, callback.m_foundWords.size());
    BOOST_CHECK_EQUAL(word3, callback.m_foundWords[2]);
}

BOOST_AUTO_TEST_CASE ( find_words )
{
    Wordgrid::CharTree charTree;
    std::string word1("abfgka");
    std::string word2("abfhkk");
    std::string word3("acfg");

    charTree.Insert(word1.begin(), word1.end());
    charTree.Insert(word2.begin(), word2.end());
    charTree.Insert(word3.begin(), word3.end());

    std::string word4("abf*k*");
    std::string word5("a*fh**");
    std::string word6("******");

    TestFindCallback callback;

    charTree.Search(std::string(), word4.begin(), word4.end(), '*', callback);
    BOOST_CHECK_EQUAL(2, callback.m_foundWords.size());
    BOOST_CHECK_EQUAL(word1, callback.m_foundWords[0]);
    BOOST_CHECK_EQUAL(word2, callback.m_foundWords[1]);

    charTree.Search(std::string(), word5.begin(), word5.end(), '*', callback);
    BOOST_CHECK_EQUAL(3, callback.m_foundWords.size());
    BOOST_CHECK_EQUAL(word2, callback.m_foundWords[2]);

    charTree.Search(std::string(), word6.begin(), word6.end(), '*', callback);
    BOOST_CHECK_EQUAL(5, callback.m_foundWords.size());
    BOOST_CHECK_EQUAL(word1, callback.m_foundWords[3]);
    BOOST_CHECK_EQUAL(word2, callback.m_foundWords[4]);
}

BOOST_AUTO_TEST_CASE ( find_words_longer_by_one )
{
    Wordgrid::CharTree charTree;
    std::string word1("acfg");

    charTree.Insert(word1.begin(), word1.end());

    std::string word2("*****");

    TestFindCallback callback;

    charTree.Search(std::string(), word2.begin(), word2.end(), '*', callback);
    BOOST_CHECK_EQUAL(0, callback.m_foundWords.size());
}



BOOST_AUTO_TEST_SUITE_END()

