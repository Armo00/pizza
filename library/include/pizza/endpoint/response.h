/**
 * @file pizza/endpoint/response.h
 * @brief The Response wrapper
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/pistache/all.h>
#include <pizza/endpoint/cake.h>
#include <pizza/generic/support.h>

namespace pizza::endpoint
{

/**
 * Represents a response
 *
 * This class is an interface to Pistache::Http::ResponseWriter
 */
class Response final
{
    DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Response)

   public:
    /** Constructor
     *
     * @param response is a reference to Pistache::Http::ResponseWriter object
     */
    explicit Response(Pistache::Http::ResponseWriter& response) noexcept
        : m_response{response}, m_sent{false}
    {
    }

    /// Response codes
    using Code = Pistache::Http::Code;

    /** Send response
     *
     * @tparam Args are the types of arguments
     * @param code is the response code
     * @param body is the response body
     * @param args are the arguments
     */
    template <typename... Args>
    void send(const Code code, const std::string_view body, const Args&... args) noexcept
    {
        if (!m_sent)
        {
            m_response.send(code, fmt::vformat(body, fmt::make_format_args(args...)));
            m_sent = true;
        }
    }

    /** Send JSON response
     *
     * @param code is the response code
     * @param cake is the Cake object
     */
    void send(const Code code, const Cake& cake) noexcept
    {
        if (!m_sent)
        {
            return send(code, "{}", cake.dump());
        }
    }

   private:
    /// The Response object
    Pistache::Http::ResponseWriter& m_response;

    /// Indicates if the response has been sent
    bool m_sent;
};

}  // namespace pizza::endpoint
