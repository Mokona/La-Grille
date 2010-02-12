#include "gridgen/Options.h"
#include "boost/program_options/options_description.hpp"
#include "boost/program_options/parsers.hpp"
#include <limits>

namespace Gridgen
{
    namespace po = boost::program_options;

    Options::Options(int argc, char * argv[])
    {
        po::options_description optionsDescription("Allowed options");
        optionsDescription.add_options()
            ("help", "produce help message")
            ("hori,x", po::value<int>(), "horizontal size of grid")
            ("vert,y", po::value<int>(), "vertical size of grid")
            ("minsize", po::value<int>(), "minimum size of a word in dictionary")
            ("maxsize", po::value<int>(), "maximum size of a word in dictionary")
            ("logscanner", "activate position scanner log")
            ("logdict", "activate dictionary log")
            ("logwriter", "activate word writer log")
            ("logsolver", "activate solver log")
            ("treedict", "uses tree dictionary implementation")
        ;

        po::store(po::parse_command_line(argc, argv, optionsDescription), vm);
        po::notify(vm);

        if (vm.count("help")) {
            std::cout << optionsDescription << "\n";
            return;
        }
    }

    bool Options::WantsHelp() const
    {
        return vm.count("help");
    }

    const Wordgrid::Vector2 Options::GetGridSize() const
    {
        int hori = 2;
        int vert = 2;

        if (vm.count("hori"))
        {
            hori = vm["hori"].as<int>();
        }
        if (vm.count("vert"))
        {
            vert = vm["vert"].as<int>();
        }

        return Wordgrid::Vector2(hori, vert);
    }

    int Options::GetMinWordSize() const
    {
        int min = 0;

        if (vm.count("minsize"))
        {
            min = vm["minsize"].as<int>();
        }

        return min;
    }

    int Options::GetMaxWordSize() const
    {
        int max = std::numeric_limits<int>::max();

        if (vm.count("maxsize"))
        {
            max = vm["maxsize"].as<int>();
        }

        return max;
    }

    bool Options::LogPositionScanner() const
    {
        return vm.count("logscanner");
    }

    bool Options::LogDictionary() const
    {
        return vm.count("logdict");
    }

    bool Options::LogWordWriter() const
    {
        return vm.count("logwriter");
    }

    bool Options::LogSolver() const
    {
        return vm.count("logsolver");
    }

    bool Options::TreeDictionary() const
    {
        return vm.count("treedict");
    }
}

