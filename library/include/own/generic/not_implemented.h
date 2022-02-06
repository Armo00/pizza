/**
 * @file own/generic/not_implemented.h
 * @brief Placeholder for not implemented functions.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_GENERIC_NOT_IMPLEMENTED_INCLUDED
#define OWN_GENERIC_NOT_IMPLEMENTED_INCLUDED

#include <own/logging/logging.h>

/**
 * @namespace own
 *
 * Placeholder for not implemented functions.
 */
namespace own
{

    /** Throw not implemented error with a message
     *
     * @param method is the method name
     * @param logger is the logger object
     */
    inline void notImplemented(const std::string_view method, const own::logging::Logger& logger)
    {
        const auto what = fmt::format("`{}` for {} is not implemented.", method, logger.getWhere());

        logger.fatal(what);
        throw std::logic_error { what };
    }

} // namespace own

#endif
