/**
 * @file pizza/log/logger.h
 * @brief Unit where all logging related interfaces gathered
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include "details.h"

namespace pizza::log
{

/** Write debug message to stdout
 *
 * @tparam Args are the types of arguments
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
 */
template <typename... Args>
void debug(const std::string_view where, const std::string_view what, const Args&... args) noexcept
{
    details::writeStdout(details::Level::Debug, where, what, args...);
}

/** Write info message to stdout
 *
 * @tparam Args are the types of arguments
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
 */
template <typename... Args>
void info(const std::string_view where, const std::string_view what, const Args&... args) noexcept
{
    details::writeStdout(details::Level::Info, where, what, args...);
}

/** Write warn message to stderr
 *
 * @tparam Args are the types of arguments
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
 */
template <typename... Args>
void warn(const std::string_view where, const std::string_view what, const Args&... args) noexcept
{
    details::writeStderr(details::Level::Warn, where, what, args...);
}

/** Write error message to stderr
 *
 * @tparam Args are the types of arguments
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
 */
template <typename... Args>
void error(const std::string_view where, const std::string_view what, const Args&... args) noexcept
{
    details::writeStderr(details::Level::Error, where, what, args...);
}

/** Write fatal message to stderr
 *
 * @tparam Args are the types of arguments
 * @param where is where this log occurs
 * @param what is the message to print
 * @param args are the arguments
 */
template <typename... Args>
void fatal(const std::string_view where, const std::string_view what, const Args&... args) noexcept
{
    details::writeStderr(details::Level::Fatal, where, what, args...);
}

/**
 * The logger
 */
class Logger final
{
    DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Logger)

   public:
    /** Constructor
     *
     * @param where is where the logs occur
     */
    explicit Logger(const std::string_view where) noexcept : m_where{where} {}

    /** Write debug message to stdout
     *
     * @tparam Args are the types of arguments
     * @param what is the message to print
     * @param args are the arguments
     */
    template <typename... Args>
    void debug(const std::string_view what, const Args&... args) const noexcept
    {
        pizza::log::debug(m_where, what, args...);
    }

    /** Write info message to stdout
     *
     * @tparam Args are the types of arguments
     * @param what is the message to print
     * @param args are the arguments
     */
    template <typename... Args>
    void info(const std::string_view what, const Args&... args) const noexcept
    {
        pizza::log::info(m_where, what, args...);
    }

    /** Write warn message to stderr
     *
     * @tparam Args are the types of arguments
     * @param what is the message to print
     * @param args are the arguments
     */
    template <typename... Args>
    void warn(const std::string_view what, const Args&... args) const noexcept
    {
        pizza::log::warn(m_where, what, args...);
    }

    /** Write error message to stderr
     *
     * @tparam Args are the types of arguments
     * @param what is the message to print
     * @param args are the arguments
     */
    template <typename... Args>
    void error(const std::string_view what, const Args&... args) const noexcept
    {
        pizza::log::error(m_where, what, args...);
    }

    /** Write fatal message to stderr
     *
     * @tparam Args are the types of arguments
     * @param what is the message to print
     * @param args are the arguments
     */
    template <typename... Args>
    void fatal(const std::string_view what, const Args&... args) const noexcept
    {
        pizza::log::fatal(m_where, what, args...);
    }

    /**
     * @returns registered name of this logger
     */
    [[nodiscard]] std::string_view getWhere() const noexcept { return m_where; };

   private:
    const std::string_view m_where;
};

}  // namespace pizza::log
