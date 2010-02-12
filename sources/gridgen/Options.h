#include "wordgrid/Vector2.h"
#include "boost/program_options/variables_map.hpp"

namespace Gridgen
{
    class Options
    {
        public:
            Options(int argc, char * argv[]);

            bool WantsHelp() const;

            const Wordgrid::Vector2 GetGridSize() const;
            int GetMinWordSize() const;
            int GetMaxWordSize() const;
            bool LogPositionScanner() const;
            bool LogDictionary() const;
            bool LogWordWriter() const;
            bool LogSolver() const;
            bool TreeDictionary() const;

        private:
            boost::program_options::variables_map vm;
    };
}

