/**
 * @file own/endpoint/error_response.h
 * @brief Represents an Error Response
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <own/endpoint/cake.h>
#include <own/endpoint/response.h>
#include <own/generic/support.h>

namespace own::endpoint
{

/**
 * Represents an error response
 *
 * This class is an exception that meant to be thrown
 */
class ErrorResponse final : public std::runtime_error
{
   public:
    /** Constructor
     *
     * @param code is the response code
     * @param what is the general cause of the current error
     * @param args are the arguments
     */
    template <typename... Args>
    explicit ErrorResponse(const Response::Code code, const std::string_view what,
                           const Args&... args) noexcept
        : std::runtime_error{fmt::vformat(what, fmt::make_format_args(args...))}, m_code{code}
    {
        m_cake.emplace("code", static_cast<uintmax_t>(code));
        m_cake.emplace("what", std::runtime_error::what());
    }

    /** Constructor
     *
     * @param code is the response code
     * @param cake is the Cake object
     */
    explicit ErrorResponse(const Response::Code code, const Cake& cake) noexcept
        : std::runtime_error{cake.dump()}, m_code{code}
    {
        m_cake.emplace("code", static_cast<uintmax_t>(code));
        m_cake.emplace("what", *cake);
    }

    /** Get the response code
     *
     * @returns the response code
     */
    [[nodiscard]] Response::Code getCode() const noexcept { return m_code; }

    /** Get the response cake
     *
     * @returns a const-reference of the response cake
     */
    [[nodiscard]] const Cake& getCake() const noexcept { return m_cake; }

   private:
    /// The error code
    const Response::Code m_code;

    /// The response cake
    Cake m_cake;
};

}  // namespace own::endpoint
