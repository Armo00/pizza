/**
 * @file pizza/logging/details.h
 * @brief Unit where all logging related implementations gathered
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/support.h>

namespace pizza::log::details
{

/// Logging level
/// @private
enum class Level
{
    Debug,  ///< Represents Debug logging level
    Info,   ///< Represents Info logging level
    Warn,   ///< Represents Warn logging level
    Error,  ///< Represents Error logging level
    Fatal   ///< Represents Fatal logging level
};

/// Represents the format of each log
/// @private
static constexpr std::string_view k_Log = "{}:{}:{}:{}\n";

/** Write log to stdout
 *
 * @tparam Args are the types of arguments
 * @param level is the log level
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
 *
 * @private
 */
template <typename... Args>
void writeStdout(const Level level, const std::string_view where, const std::string_view what,
                 const Args&... args) noexcept
{
    fmt::print(stdout, k_Log, std::time(nullptr), magic_enum::enum_name(level), where,
               fmt::vformat(what, fmt::make_format_args(args...)));
}

/** Write log to stderr
 *
 * @tparam Args are the types of arguments
 * @param level is the log level
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
 *
 * @private
 */
template <typename... Args>
void writeStderr(const Level level, const std::string_view where, const std::string_view what,
                 const Args&... args) noexcept
{
    fmt::print(stderr, k_Log, std::time(nullptr), magic_enum::enum_name(level), where,
               fmt::vformat(what, fmt::make_format_args(args...)));
}

}  // namespace pizza::log::details
