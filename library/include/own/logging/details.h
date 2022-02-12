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
    enum class Level { Debug, Info, Warn, Error, Fatal };

    /// Template of every log
    static constexpr std::string_view k_LogTemplate = "{}:{}:{}:{}\n";

    /** Write log to stdout
     *
     * @param level is the log level
     * @param where is where this log occurs
     * @param what is the message to print
     */
    inline void writeStdout(const Level level, const std::string_view where,
                            const std::string_view what)
    {
        const auto message = fmt::format(k_LogTemplate, std::time(nullptr),
                                         magic_enum::enum_name(level), where, what);

        std::fprintf(stdout, "%s", message.data());
    }

    /** Write log to stderr
     *
     * @param level is the log level
     * @param where is where this log occurs
     * @param what is the message to print
     */
    inline void writeStderr(const Level level, const std::string_view where,
                            const std::string_view what)
    {
        const auto message = fmt::format(k_LogTemplate, std::time(nullptr),
                                         magic_enum::enum_name(level), where, what);

        std::fprintf(stderr, "%s", message.data());
    }

} // namespace own::logging::details

#endif
