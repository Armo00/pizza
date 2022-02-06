/**
 * @file own/logging/logging.h
 * @brief Unit where all logging related interfaces gathered
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#ifndef LOGGING_LOGGING_INCLUDED
#define LOGGING_LOGGING_INCLUDED

#include "details.h"

/**
 * Namespace where all logging related interfaces gathered
 *
 * To utilize logging capability, use anything listed here
 */
namespace own::logging
{

    /** Write debug message to stdout
     *
     * @param where is where this log occurs
     * @param what is the message to print
     */
    inline void debug(const std::string_view where, const std::string_view what)
    {
        details::writeStdout(details::Level::Debug, where, what);
    }

    /** Write info message to stdout
     *
     * @param where is where this log occurs
     * @param what is the message to print
     */
    inline void info(const std::string_view where, const std::string_view what)
    {
        details::writeStdout(details::Level::Info, where, what);
    }

    /** Write warn message to stderr
     *
     * @param where is where this log occurs
     * @param what is the message to print
     */
    inline void warn(const std::string_view where, const std::string_view what)
    {
        details::writeStderr(details::Level::Warn, where, what);
    }

    /** Write error message to stderr
     *
     * @param where is where this log occurs
     * @param what is the message to print
     */
    inline void error(const std::string_view where, const std::string_view what)
    {
        details::writeStderr(details::Level::Error, where, what);
    }

    /** Write fatal message to stderr
     *
     * @param where is where this log occurs
     * @param what is the message to print
     */
    inline void fatal(const std::string_view where, const std::string_view what)
    {
        details::writeStderr(details::Level::Fatal, where, what);
    }

    /**
     * The logger
     */
    class Logger
    {
    public:
        /** Constructor
         *
         * @param where is where the logs occur
         */
        explicit Logger(const std::string_view where)
            : m_where { where }
        { }

        /** Write debug message to stdout
         *
         * @param what is the message to print
         */
        void debug(const std::string_view what) const { own::logging::debug(m_where, what); }

        /** Write info message to stdout
         *
         * @param what is the message to print
         */
        void info(const std::string_view what) const { own::logging::info(m_where, what); }

        /** Write warn message to stderr
         *
         * @param what is the message to print
         */
        void warn(const std::string_view what) const { own::logging::warn(m_where, what); }

        /** Write error message to stderr
         *
         * @param what is the message to print
         */
        void error(const std::string_view what) const { own::logging::error(m_where, what); }

        /** Write fatal message to stderr
         *
         * @param what is the message to print
         */
        void fatal(const std::string_view what) const { own::logging::fatal(m_where, what); }

        /**
         * @returns registered name of this logger
         */
        auto getWhere() const { return m_where; };

    private:
        const std::string m_where;
    };

} // namespace own::logging

#endif
