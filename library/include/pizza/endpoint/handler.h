/**
 * @file pizza/endpoint/handler.h
 * @brief The Handler
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/endpoint/cake.h>
#include <pizza/endpoint/error_response.h>
#include <pizza/endpoint/request.h>
#include <pizza/endpoint/response.h>
#include <pizza/log/logger.h>
#include <pizza/support.h>

namespace pizza::endpoint
{

/**
 * The base class of all handlers
 *
 * @note Remember, this is a multithreaded class - Mark everything as const!
 */
class Handler
{
    DEFAULT_DESTRUCTIBLE_BASE_CLASS(Handler)

   private:
    /** Prepare the handler
     *
     * @param request is the Request object
     * @param cake is the data generated in processRequest
     */
    virtual void validateRequest([[maybe_unused]] const Request& request,
                                 [[maybe_unused]] Cake& cake) const
    {
        m_log.warn("`validateRequest` is not implemented!");
    }

    /** Process the request, prepare for the response
     *
     * @param request is the Request object
     * @param cake is the data generated in processRequest
     */
    virtual void processRequest([[maybe_unused]] const Request& request,
                                [[maybe_unused]] Cake& cake) const
    {
        m_log.warn("`processRequest` is not implemented!");
    }

    /** Send the response
     *
     * @param cake is the data generated in processRequest
     * @param response is the Response object
     */
    virtual void sendResponse([[maybe_unused]] const Cake& cake,
                              [[maybe_unused]] Response& response) const
    {
        m_log.warn("`sendResponse` is not implemented!");
    }

   public:
    /// Allow Handler::Request alias to pizza::endpoint::Request
    using Request = pizza::endpoint::Request;

    /// Allow Handler::Request alias to pizza::endpoint::Response
    using Response = pizza::endpoint::Response;

    /// Allow Handler::ErrorResponse alias to pizza::endpoint::ErrorResponse
    using ErrorResponse = pizza::endpoint::ErrorResponse;

    /// Allow Handler::Cake alias to pizza::endpoint::Cake
    using Cake = pizza::endpoint::Cake;

    /// The API description
    using ApiDesc = std::pair<Request::Method, const std::string_view>;

    /** Handle the request
     *
     * @param request is the Pistache::Http::Request object
     * @param response is the Pistache::Http::ResponseWriter object
     */
    void handleRequest(const Pistache::Rest::Request& request,
                       Pistache::Http::ResponseWriter response) noexcept
    {
        const Request request_{request};
        Response response_{response};
        Cake cake;

        try
        {
            validateRequest(request_, cake);
        }
        catch (const ErrorResponse& e)
        {
            response_.send(e.getCode(), e.getCake());
            m_log.error("ErrorResponse caught: {}", e.what());
            return;
        }
        catch (const std::runtime_error& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_log.error("std::runtime_error caught: {}", e.what());
            return;
        }
        catch (const std::invalid_argument& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_log.error("std::invalid_argument caught: {}", e.what());
            return;
        }
        catch (const std::logic_error& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_log.error("std::logic_error caught: {}", e.what());
            return;
        }
        catch (const std::exception& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_log.error("std::exception caught: {}", e.what());
            return;
        }

        try
        {
            processRequest(request_, cake);
            sendResponse(cake, response_);
        }
        catch (const ErrorResponse& e)
        {
            response_.send(e.getCode(), e.getCake());
            m_log.error("ErrorResponse caught: {}", e.what());
        }
        catch (const std::runtime_error& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_log.error("std::runtime_error caught: {}", e.what());
        }
        catch (const std::invalid_argument& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_log.error("std::invalid_argument caught: {}", e.what());
        }
        catch (const std::logic_error& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_log.error("std::logic_error caught: {}", e.what());
        }
        catch (const std::exception& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_log.error("std::exception caught: {}", e.what());
        }
    }

   protected:
    /** Constructor
     *
     * @param name is the name of this handler
     */
    explicit Handler(const std::string_view name) noexcept : m_log{name} {}

    /// The Logger
    const pizza::log::Logger m_log;
};

}  // namespace pizza::endpoint
