/**
 * @file own/logging/details.h
 * @brief Unit where all logging related implementations gathered
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#ifndef LOGGING_DETAILS_INCLUDED
#define LOGGING_DETAILS_INCLUDED

#include <external/fmt/all.h>
#include <own/generic/types.h>

/**
 * Namespace where all logging related implementations gathered
 *
 * Everything under this namespace shouldn't be used outside this module
 */
namespace own::logging::details
{

/// Logging level
enum class Level
{
    Debug,  ///< Represents Debug logging level
    Info,   ///< Represents Info logging level
    Warn,   ///< Represents Warn logging level
    Error,  ///< Represents Error logging level
    Fatal   ///< Represents Fatal logging level
};

/// Represents the format of each log
static constexpr std::string_view k_Log = "{}:{}:{}:{}\n";

/** Write log to stdout
 *
 * @tparam Args are the types of arguments
 * @param level is the log level
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
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
 */
template <typename... Args>
void writeStderr(const Level level, const std::string_view where, const std::string_view what,
                 const Args&... args) noexcept
{
    fmt::print(stderr, k_Log, std::time(nullptr), magic_enum::enum_name(level), where,
               fmt::vformat(what, fmt::make_format_args(args...)));
}

}  // namespace own::logging::details

#endif
