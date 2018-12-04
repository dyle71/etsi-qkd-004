/*
 * This file is part of etsi-qkd-004.
 * See the LICENSE file for the software license.
 * (C) Copyright 2018, Oliver Maurhart, dyle71@gmail.com
 */

#ifndef QKD_LKMS_HPP
#define QKD_LKMS_HPP

#include <any>
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include <uuid/uuid.h>


namespace qkd {
namespace etsi {
namespace appint {


/**
 * ETSI QKD 004 status values.
 */
enum class status_codes {
    success = 0,                        /**< All ok. */
    insufficient_keys = 1,              /**< Error because of not enough key material available. */
    no_connection = 2,                  /**< No QKD connection present. */
    key_stream_in_use = 3,              /**< KeyStream ID is already in use. */
    timeout = 4                         /**< Timeout error. */
};


using status_t = std::uint32_t;         /**< All status codes are 32 bits. */


using uri = std::string;                /**< An uri is just a string. */


/**
 * Known QoS parameters known.
 */
enum class qos_parameter {
    key_chunk_size = 1,     /**< Length of the key buffer requested by the application. */
    max_bps = 2,            /**< Maximum key rate requested in bits per seconds. */
    min_bps = 3,            /**< Minimum key rate requested in bits per seconds. */
    jitter = 4,             /**< Maximum expected deviation in key delivery. */
    priority = 5,           /**< Priority of the request. */
    timeout = 6,            /**< Time, in msec, after which the call will be aborted, returning an error. */
    ttl = 7                 /**< Time, in seconds, after which the keys for this key stream id must be erased. */
};


/**
 * The QoS binds a QoS Parameter to a value (which can be any type).
 */
using qos_t = std::map<qos_parameter, std::any>;


/**
 * Open a key stream.
 *
 * @param   source              (in) the source identifier for the stream.
 * @param   destination         (in) the destination identifier for the stream.
 * @param   qos                 (in) Quality of Service parameters (see qos_parameter enum).
 * @param   key_stream_id       (in/out) key stream id.
 * @param   status              (out) status/error code of this call (see status_codes enum).
 */
void qkd_open(uri const & source,
        uri const & destination,
        qos_t const & qos,
        uuid_t & key_stream_id,
        status_t & status);


/**
 * Gets next key material with the key stream id.
 *
 * @param   key_stream_id       (in) the key stream id, must be retrieved by a previous qkd_open.
 * @param   index               (out) the index within the key stream id buffer.
 * @param   buffer              (out) the key material.
 * @param   status              (out) status/error code of this call (see status_codes enum).
 */
void qkd_get_key(uuid_t const & key_stream_id,
        std::uint32_t & index,
        std::vector<std::byte> & buffer,
        status_t & status);


/**
 * Closes the key stream.
 *
 * @param   key_stream_id       (in) the key stream to close.
 * @param   status              (out) status/error code of this call (see status_codes enum).
 */
void qkd_close(uuid_t const & key_stream_id, status_t & status);


}
}
}


#endif
