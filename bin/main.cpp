/*
 * This file is part of etsi-qkd-004.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <cstdint>
#include <iostream>
#include <stdexcept>

#include <boost/program_options.hpp>

#include "lkms.hpp"


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
 * @return  true, if we managed to successfully parse the command line and should proceed.
 */
static bool parseCommandLine(boost::program_options::variables_map & programOptions, int argc, char ** argv);


/**
 * Gets the host and port portion of the command line.
 *
 * @param   programOptions      options as passed on the command line.
 * @return  a tuple of host and port
 */
static std::tuple<std::string, std::uint16_t> pickHostAndPort(boost::program_options::variables_map & programOptions);


/**
 * Picks the north bound interface uri as a socket
 *
 * @param   programOptions      options as passed on the command line.
 * @return  address of the north bound socket to use.
 */
static std::string pickNorth(boost::program_options::variables_map & programOptions);


/**
 * Picks the south bound interface uri as a socket
 *
 * @param   programOptions      options as passed on the command line.
 * @return  address of the south bound socket to use.
 */
std::string pickSouth(boost::program_options::variables_map & programOptions);


int main(int argc, char ** argv) {

    boost::program_options::variables_map programOptions;
    if (!parseCommandLine(programOptions, argc, argv)) {
        return 0;
    }
    
    std::string host;
    std::uint16_t port;
    try {
        std::tie(host, port) = pickHostAndPort(programOptions);
    }
    catch (std::invalid_argument const & e) {
        std::cerr << "Failed to pick host and port: " << e.what() << std::endl;
        return 1;
    }
    
    std::string north;
    try {
        north = pickNorth(programOptions);
    }
    catch (std::invalid_argument const & e) {
        std::cerr << "Failed to pick north bound socket: " << e.what() << std::endl;
        return 1;
    }
    
    std::string south;
    try {
        south = pickSouth(programOptions);
    }
    catch (std::invalid_argument const & e) {
        std::cerr << "Failed to pick south bound socket: " << e.what() << std::endl;
        return 1;
    }
    
    int exitcode = 0;
    try {
        exitcode = runLKMS({host, port, north, south});
    }
    catch (std::exception const & e) {
        std::cerr << "Failed to run LKMS: " << e.what() << std::endl;
    }

    return exitcode;
}


bool parseCommandLine(boost::program_options::variables_map & programOptions, int argc, char ** argv) {

    auto applicationHeader = std::string{"qkd-lkms - ETSI QKD 004 LKMS implementation "} + VERSION;
    auto description = std::string{PROGRAM_DESCRIPTION};
    auto synopsis = std::string{"Usage: "} + argv[0] + " HOST:PORT NORTH-SOCKET SOUTH-SOCKET";

    auto optionsLine = applicationHeader + "\n" + description + "\n\n" + synopsis + "\n\nAllowed Options";
    boost::program_options::options_description options{optionsLine};
    options.add_options()("help,h", "this page");
    options.add_options()("version,v", "print version string");

    boost::program_options::options_description arguments{"Arguments"};
    boost::program_options::positional_options_description positionalArgumentDescriptions;
    arguments.add_options()("HOST:PORT", "public address for this LKMS.");
    positionalArgumentDescriptions.add("HOST:PORT", 1);
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
        std::cout << "HOST:PORT: " << arguments.find("HOST:PORT", false).description() << "\n"
                  << "NORTH-SOCKET: " << arguments.find("NORTH-SOCKET", false).description() << "\n"
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


std::tuple<std::string, std::uint16_t> pickHostAndPort(boost::program_options::variables_map & programOptions) {
    
    std::tuple<std::string, std::uint16_t> res{"0.0.0.0", 9014};
    
    if (programOptions.count("HOST:PORT")) {
        auto value = programOptions["HOST:PORT"].as<std::string>();
        // TODO: parse the HOST:PORT value
    }
    
    return res;
}


std::string pickNorth(boost::program_options::variables_map & programOptions) {
    
    std::string socket{"/run/qkd/lkms/north"};
    if (programOptions.count("NORTH-SOCKET")) {
        socket = programOptions["NORTH-SOCKET"].as<std::string>();
    }
    return socket;
}


std::string pickSouth(boost::program_options::variables_map & programOptions) {
    
    std::string socket{"/run/qkd/lkms/south"};
    if (programOptions.count("SOUTH-SOCKET")) {
        socket = programOptions["SOUTH-SOCKET"].as<std::string>();
    }
    return socket;

}
