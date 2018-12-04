/*
 * This file is part of etsi-qkd-004.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#include <qkd-lkms/qkd-lkms.hpp>


void qkd::etsi::appint::qkd_open(uri const & source,
        uri const & destination,
        qos_t const & qos,
        uuid_t & key_stream_id,
        status_t & status) {
    
    status = static_cast<status_t>(status_codes::success);
}


void qkd::etsi::appint::qkd_get_key(uuid_t const & key_stream_id,
        std::uint32_t & index,
        std::vector<std::byte> & buffer,
        status_t & status) {
    
    status = static_cast<status_t>(status_codes::success);
}


void qkd::etsi::appint::qkd_close(uuid_t const & key_stream_id, status_t & status) {
    
    status = static_cast<status_t>(status_codes::success);
}


void qkd::etsi::appint::qkd_init(uri & source, uri & north, uri & south, init_code & error) {
}
