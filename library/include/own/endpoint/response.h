/**
 * @file own/endpoint/response.h
 * @brief The Response wrapper
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_ENDPOINT_PISTACHE_RESPONSE_INCLUDED
#define OWN_ENDPOINT_PISTACHE_RESPONSE_INCLUDED

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
    public:
        /// Response codes
        enum class Code { Ok, BadRequest, ServerError };

        /** Constructor
         *
         * @param request is a reference to @c Pistache::Http::Request object
         * @note intentionally implicit
         */
        explicit Response(Pistache::Http::ResponseWriter& response)
            : m_response { response }
            , m_sent { false }
        { }

        /** Send response
         *
         * @param code is the response code
         * @param body is the response body
         */
        void send(const Code code, const std::string_view body)
        {
            if (m_sent)
            {
                return;
            }

            switch (code)
            {
            case Code::Ok:
                m_response.send(Pistache::Http::Code::Ok, body.data());
                return;

            case Code::BadRequest:
                m_response.send(Pistache::Http::Code::Bad_Request, body.data());
                m_sent = true;
                return;

            case Code::ServerError:
                m_response.send(Pistache::Http::Code::Internal_Server_Error, body.data());
                m_sent = true;
                return;

            default:
                throw std::logic_error { "That's not possible!" };
            }
        }

    private:
        /// The request object
        Pistache::Http::ResponseWriter& m_response;

        /// Response sent?
        bool m_sent;
    };

} // namespace own::endpoint

#endif
