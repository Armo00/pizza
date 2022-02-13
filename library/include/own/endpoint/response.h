/**
 * @file own/endpoint/response.h
 * @brief The Response wrapper
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_ENDPOINT_PISTACHE_RESPONSE_INCLUDED
#define OWN_ENDPOINT_PISTACHE_RESPONSE_INCLUDED

#include <external/fmt/all.h>
#include <external/pistache/all.h>
#include <own/generic/types.h>

namespace own::endpoint
{
    /** Response
     *
     * This class is an interface to @c Pistache::Http::ResponseWriter
     */
    class Response final
    {
        DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Response)

    public:
        /// Response codes
        enum class Code { Ok, BadRequest, ServerError };

        /** Constructor
         *
         * @param response is a reference to @c Pistache::Http::ResponseWriter object
         */
        explicit Response(Pistache::Http::ResponseWriter& response) noexcept
            : m_response { response }
            , m_sent { false }
        { }

        /** Send response
         *
         * @tparam Args are the types of arguments
         * @param code is the response code
         * @param body is the response body
         * @param args are the arguments
         */
        template <typename... Args>
        void send(const Code code, const std::string_view body, const Args&... args)
        {
            if (m_sent)
            {
                return;
            }

            switch (code)
            {
            case Code::Ok:
                m_response.send(Pistache::Http::Code::Ok,
                                fmt::vformat(body, fmt::make_format_args(args...)));
                return;

            case Code::BadRequest:
                m_response.send(Pistache::Http::Code::Bad_Request,
                                fmt::vformat(body, fmt::make_format_args(args...)));
                m_sent = true;
                return;

            case Code::ServerError:
                m_response.send(Pistache::Http::Code::Internal_Server_Error,
                                fmt::vformat(body, fmt::make_format_args(args...)));
                m_sent = true;
                return;

            default:
                throw std::logic_error { "That's not possible!" };
            }
        }

    private:
        /// The Response object
        Pistache::Http::ResponseWriter& m_response;

        /// Indicates if the response has been sent
        bool m_sent;
    };

} // namespace own::endpoint

#endif
