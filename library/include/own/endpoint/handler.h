/**
 * @file own/endpoint/handler.h
 * @brief The Handler
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_ENDPOINT_PISTACHE_HANDLER_INCLUDED
#define OWN_ENDPOINT_PISTACHE_HANDLER_INCLUDED

#include <own/endpoint/cake.h>
#include <own/endpoint/request.h>
#include <own/endpoint/response.h>
#include <own/generic/types.h>
#include <own/logging/logging.h>

/**
 * @namespace own::endpoint
 */
namespace own::endpoint
{

    /** The base class of all handlers
     *
     * @note Remember, this is a singleton-multithreaded class - Mark every phase with @c const !
     */
    class Handler
    {
    public:
        /// Allow direct access of @c own::endpoint::Request class
        using Request = own::endpoint::Request;

        /// Allow direct access of @c own::endpoint::Response class
        using Response = own::endpoint::Response;

        /// The cake
        using Cake = own::endpoint::Cake;

        /// The RESTful description
        using ApiDesc = std::pair<Request::Method, const std::string_view>;

        /** Handle the request
         *
         * @param request is the @c Pistache::Http::Request object
         * @param response is the @c Pistache::Http::ResponseWriter object
         */
        void handleRequest(const Pistache::Rest::Request& request,
                           Pistache::Http::ResponseWriter response)
        {
            const Request requestWrapper { request };
            Response responseWrapper { response };
            Cake cake;

            try
            {
                validateRequest(requestWrapper);
            }
            catch (const std::invalid_argument& e)
            {
                responseWrapper.send(Response::Code::BadRequest, "Bad Request");
                m_logger.error(fmt::format("std::invalid_argument caught: {}", e.what()));
                return;
            }
            catch (const std::runtime_error& e)
            {
                responseWrapper.send(Response::Code::BadRequest, "Bad Request");
                m_logger.error(fmt::format("std::runtime_error caught: {}", e.what()));
                return;
            }
            catch (const std::logic_error& e)
            {
                responseWrapper.send(Response::Code::BadRequest, "Bad Request");
                m_logger.error(fmt::format("std::logic_error caught: {}", e.what()));
                return;
            }
            catch (const std::exception& e)
            {
                responseWrapper.send(Response::Code::BadRequest, "Bad Request");
                m_logger.error(fmt::format("std::exception caught: {}", e.what()));
                return;
            }

            try
            {
                processRequest(requestWrapper, cake);
                sendResponse(cake, responseWrapper);
            }
            catch (const std::invalid_argument& e)
            {
                responseWrapper.send(Response::Code::ServerError, "Server Error");
                m_logger.error(fmt::format("std::invalid_argument caught: {}", e.what()));
            }
            catch (const std::runtime_error& e)
            {
                responseWrapper.send(Response::Code::ServerError, "Server Error");
                m_logger.error(fmt::format("std::runtime_error caught: {}", e.what()));
            }
            catch (const std::logic_error& e)
            {
                responseWrapper.send(Response::Code::ServerError, "Server Error");
                m_logger.error(fmt::format("std::logic_error caught: {}", e.what()));
            }
            catch (const std::exception& e)
            {
                responseWrapper.send(Response::Code::ServerError, "Server Error");
                m_logger.error(fmt::format("std::exception caught: {}", e.what()));
            }
        }

        /** Prepare the handler
         *
         * @param request is the @c Request object
         */
        virtual void validateRequest([[maybe_unused]] const Request request) const { }

        /** Process the request, prepare for the response
         *
         * @param request is the @c Request object
         * @param cake is the data generated in @c processRequest
         */
        virtual void processRequest([[maybe_unused]] const Request request,
                                    [[maybe_unused]] Cake& cake) const
        { }

        /** Send the response
         *
         * @param cake is the data generated in @c processRequest
         * @param response is the @c Response object
         */
        virtual void sendResponse([[maybe_unused]] const Cake& cake,
                                  [[maybe_unused]] Response response) const
        { }

    protected:
        /** Constructor
         *
         * @param name is the name of this handler
         */
        explicit Handler(const std::string_view endpointName)
            : m_logger { endpointName }
        { }

        /// Logger
        const own::logging::Logger m_logger;
    };

} // namespace own::endpoint

#endif
