#include "wordgrid/OneWordByLineReader.h"

#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/bind.hpp>
#include "wordgrid/Dictionary.h"

namespace Wordgrid
{
    void addToDictionary(Dictionary & dictionary, const Filter::Filter * filter, const std::string & word)
    {
        if (!filter || (*filter)(word))
        {
            dictionary.InsertWord(word);
        }
    }

    OneWordByLineReader::OneWordByLineReader(Dictionary & dictionary, std::istream & stream) :
        m_dictionary(dictionary),
        m_stream(stream),
        m_filter(NULL)
    {
    }
    
    OneWordByLineReader::~OneWordByLineReader()
    {
    }

    void OneWordByLineReader::Read()
    {
        std::for_each(std::istream_iterator<std::string>(m_stream),
                      std::istream_iterator<std::string>(),
                      boost::bind(addToDictionary, boost::ref(m_dictionary), m_filter, _1));
    }

    void OneWordByLineReader::SetFilter(const Filter::Filter & filter)
    {
        m_filter = &filter;
    }
}

