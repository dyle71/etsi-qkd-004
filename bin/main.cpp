/*
 * This file is part of etsi-qkd-004.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */


#include <iostream>

#include <boost/program_options.hpp>


#define PROGRAM_DESCRIPTION "\
This is an ETSI QKD 004 LKMS.\n\
\n\
Copyright (C) 2018 Oliver Maurhart, <dyle71@gmail.com>\n\
Licenseed under the GNU General Public License 3\n\
See: http://www.gnu.org/licenses/ for details."


/**
 * Parses the command line and places found options and arguments in the boost variables map.
 *
 * @param   programOptions      This will hold the found values of the parsed command line.
 * @param   argc                Number of command line arguments (as usual from main()).
 * @param   argv                Command line arguments (as usual from main()).
 * @return  true, if we managed to sucessfuly parse the command line and should proceed.
 */
bool parseCommandLine(boost::program_options::variables_map & programOptions, int argc, char ** argv);


int main(int argc, char ** argv) {

    boost::program_options::variables_map programOptions;
    if (!parseCommandLine(programOptions, argc, argv)) {
        return 0;
    }

    return 0;
}


bool parseCommandLine(boost::program_options::variables_map & programOptions, int argc, char ** argv) {

    auto applicationHeader = std::string{"qkd-lkms - ETSI QKD 004 LKMS implementation "} + VERSION;
    auto description = std::string{PROGRAM_DESCRIPTION};
    auto synopsis = std::string{"Usage: "} + argv[0] + " NORTH-SOCKET SOUTH-SOCKET";

    auto optionsLine = applicationHeader + "\n" + description + "\n\n" + synopsis + "\n\nAllowed Options";
    boost::program_options::options_description options{optionsLine};
    options.add_options()("help,h", "this page");
    options.add_options()("version,v", "print version string");

    boost::program_options::options_description arguments{"Arguments"};
    boost::program_options::positional_options_description positionalArgumentDescriptions;
    arguments.add_options()("NORTH-SOCKET", "Socket for northbound communication.");
    positionalArgumentDescriptions.add("NORTH-SOCKET", 1);
    arguments.add_options()("SOUTH-SOCKET", "Socket for southbound communication.");
    positionalArgumentDescriptions.add("SOUTH-SOCKET", 1);

    boost::program_options::options_description commandLineOptions{"Command Line"};
    commandLineOptions.add(options);
    commandLineOptions.add(arguments);

    try {
        auto constArgv = reinterpret_cast<char const * const *>(argv);
        boost::program_options::command_line_parser parser{argc, constArgv};
        boost::program_options::store(
                parser.options(commandLineOptions).positional(positionalArgumentDescriptions).run(),
                programOptions);
        boost::program_options::notify(programOptions);
    }
    catch (std::exception & exception) {
        std::cerr << "error parsing command line: " <<  exception.what()
                  << "\ntype '--help' for help"
                  << std::endl;
        std::exit(1);
    }

    if (programOptions.count("help")) {
        std::cout << options << std::endl;
        std::cout << "NORTH-SOCKET: " << arguments.find("NORTH-SOCKET", false).description() << "\n"
                  << "SOUTH-SOCKET: " << arguments.find("SOUTH-SOCKET", false).description() << "\n"
                  << std::endl;
        return false;
    }

    if (programOptions.count("version")) {
        std::cout << applicationHeader << std::endl;
        return false;
    }

    return true;
}

