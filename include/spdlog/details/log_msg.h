//
// Copyright(c) 2015 Gabi Melman.
// Distributed under the MIT License (http://opensource.org/licenses/MIT)
//

#pragma once

#include "../common.h"
#include "../details/os.h"

#include <string>
#include <utility>

namespace spdlog {
namespace details {
struct log_msg
{
    static const size_t    RECOMMENDED_BUFFER_SIZE = 20;
	
    log_msg() = default;
    log_msg(const std::string *loggers_name, level::level_enum lvl)
        : logger_name(loggers_name)
        , level(lvl)
    {
#ifndef SPDLOG_NO_DATETIME
        time = os::now();
#endif

#ifndef SPDLOG_NO_THREAD_ID
        thread_id = os::thread_id();
	
        char theThreadName[RECOMMENDED_BUFFER_SIZE];
        os::thread_name(theThreadName, sizeof(theThreadName));
        thread_name = std::string(theThreadName);
#endif
    }

    log_msg(const log_msg &other) = delete;
    log_msg &operator=(log_msg &&other) = delete;
    log_msg(log_msg &&other) = delete;

    const std::string *logger_name{nullptr};
    level::level_enum level;
    log_clock::time_point time;
    size_t thread_id;
    std::string thread_name;
    fmt::MemoryWriter raw;
    fmt::MemoryWriter formatted;
    size_t msg_id{0};
    // wrap this range with color codes
    size_t color_range_start{0};
    size_t color_range_end{0};
};
} // namespace details
} // namespace spdlog
