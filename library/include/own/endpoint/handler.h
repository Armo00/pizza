/**
 * @file own/endpoint/handler.h
 * @brief The Handler
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <own/endpoint/cake.h>
#include <own/endpoint/error_response.h>
#include <own/endpoint/request.h>
#include <own/endpoint/response.h>
#include <own/generic/support.h>
#include <own/logging/logging.h>

namespace own::endpoint
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
    }

    /** Process the request, prepare for the response
     *
     * @param request is the Request object
     * @param cake is the data generated in processRequest
     */
    virtual void processRequest([[maybe_unused]] const Request& request,
                                [[maybe_unused]] Cake& cake) const
    {
    }

    /** Send the response
     *
     * @param cake is the data generated in processRequest
     * @param response is the Response object
     */
    virtual void sendResponse([[maybe_unused]] const Cake& cake,
                              [[maybe_unused]] Response& response) const
    {
    }

   public:
    /// Allow Handler::Request alias to own::endpoint::Request
    using Request = own::endpoint::Request;

    /// Allow Handler::Request alias to own::endpoint::Response
    using Response = own::endpoint::Response;

    /// Allow Handler::ErrorResponse alias to own::endpoint::ErrorResponse
    using ErrorResponse = own::endpoint::ErrorResponse;

    /// Allow Handler::Cake alias to own::endpoint::Cake
    using Cake = own::endpoint::Cake;

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
            m_logger.error("ErrorResponse caught: {}", e.what());
            return;
        }
        catch (const std::runtime_error& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_logger.error("std::runtime_error caught: {}", e.what());
            return;
        }
        catch (const std::invalid_argument& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_logger.error("std::invalid_argument caught: {}", e.what());
            return;
        }
        catch (const std::logic_error& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_logger.error("std::logic_error caught: {}", e.what());
            return;
        }
        catch (const std::exception& e)
        {
            response_.send(Response::Code::Bad_Request, "Bad Request");
            m_logger.error("std::exception caught: {}", e.what());
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
            m_logger.error("ErrorResponse caught: {}", e.what());
        }
        catch (const std::runtime_error& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_logger.error("std::runtime_error caught: {}", e.what());
        }
        catch (const std::invalid_argument& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_logger.error("std::invalid_argument caught: {}", e.what());
        }
        catch (const std::logic_error& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_logger.error("std::logic_error caught: {}", e.what());
        }
        catch (const std::exception& e)
        {
            response_.send(Response::Code::Internal_Server_Error, "Server Error");
            m_logger.error("std::exception caught: {}", e.what());
        }
    }

   protected:
    /** Constructor
     *
     * @param name is the name of this handler
     */
    explicit Handler(const std::string_view name) noexcept : m_logger{name} {}

    /// The Logger
    // NOLINTNEXTLINE(cppcoreguidelines-non-private-member-variables-in-classes)
    const own::logging::Logger m_logger;
};

}  // namespace own::endpoint
