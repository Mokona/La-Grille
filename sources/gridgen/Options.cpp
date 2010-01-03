#include "gridgen/Options.h"
#include "boost/program_options/options_description.hpp"
#include "boost/program_options/parsers.hpp"

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
            ("logscanner", "activate position scanner log")
            ("logdict", "activate dictionary log")
            ("logwriter", "activate word writer log")
            ("logsolver", "activate solver log")
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
}

