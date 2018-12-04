/*
 * This file is part of etsi-qkd-004.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <iostream>
#include <stdexcept>

#include <uv.h>

#include "lkms.hpp"


/**
 * Global UV Loop handle.
 *
 * Get rid of this global variable once.
 */
static uv_loop_t * theLoop = nullptr;


/**
 * Operating system signal hanler.
 *
 * @param   handle      the UV signal handle.
 * @param   signal      the signal captured.
 */
static void handleSignal(uv_signal_t * handle, int signal);


/**
 * Setup an uv listener for the LKMS Listen socket.
 *
 * @param   loop        the uv loop.
 * @param   config      LKMS config.
 */
static void setupListen(uv_loop_t * loop, lkms_parameters const & config);


/**
 * Setup the north bound interface.
 *
 * @param   loop        the uv loop.
 * @param   config      LKMS config.
 */
static void setupNorth(uv_loop_t * loop, lkms_parameters const & config);


/**
 * Setup the south bound interface.
 *
 * @param   loop        the uv loop.
 * @param   config      LKMS config.
 */
static void setupSouth(uv_loop_t * loop, lkms_parameters const & config);


int runLKMS(lkms_parameters const config) {
    
    theLoop = new uv_loop_t;
    
    auto error = uv_loop_init(theLoop);
    if (error) {
        throw std::runtime_error{uv_strerror(error)};
    }
    
    uv_signal_t uvSignal;
    error = uv_signal_init(theLoop, &uvSignal);
    if (error) {
        throw std::runtime_error{uv_strerror(error)};
    }
    uv_signal_start(&uvSignal, handleSignal, SIGINT);

    setupListen(theLoop, config);
    setupNorth(theLoop, config);
    setupSouth(theLoop, config);
    
    uv_run(theLoop, UV_RUN_DEFAULT);
    uv_loop_close(theLoop);
    delete theLoop;
    
    return 0;
}


void handleSignal(uv_signal_t * handle, int signal) {
    std::cerr << "Captured signal: " << signal << std::endl;
    std::cerr << "Terminating..." << std::endl;
    uv_stop(theLoop);
    uv_loop_close(theLoop);
}

void setupListen(uv_loop_t * loop, lkms_parameters const & config) {

}


void setupNorth(uv_loop_t * loop, lkms_parameters const & config) {

}


void setupSouth(uv_loop_t * loop, lkms_parameters const & config) {

}
