/*
 * This file is part of etsi-qkd-004.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef LKMS_HPP
#define LKMS_HPP

#include <cstdint>
#include <string>


/**
 * LKMS startup parameters.
 */
struct lkms_parameters {
    std::string host;       /**< local hostname or IP to serve. */
    std::uint16_t port;     /**< port to serve. */
    std::string north;      /**< North bound interface. */
    std::string south;      /**< South bound interface. */
};


/**
 * Run the LKMS
 * @param   config      configuration of the LKMS.
 * @return  exit code for the process.
 */
int runLKMS(lkms_parameters const config);


#endif
