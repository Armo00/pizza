/**
 * @file pizza/endpoint/details.h
 * @brief Implementation details of endpoint
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/pistache/all.h>
#include <pizza/endpoint/handler.h>
#include <pizza/log/logger.h>
#include <pizza/support.h>

namespace pizza::endpoint::details
{

/** Append a new router record
 *
 * @param pistacheRouter is the Pistache router
 * @param pizzaHandler is the handler object
 * @param requestMethod is the request method
 * @param requestPath is the request path
 *
 * @private
 */
inline void addHandler(Pistache::Rest::Router& pistacheRouter, Handler& pizzaHandler,
                       const Request::Method requestMethod,
                       const std::string_view requestPath) noexcept
{
    switch (requestMethod)
    {
        case Request::Method::Get:
            return Pistache::Rest::Routes::Get(
                pistacheRouter, requestPath.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &pizzaHandler));

        case Request::Method::Post:
            return Pistache::Rest::Routes::Post(
                pistacheRouter, requestPath.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &pizzaHandler));

        case Request::Method::Put:
            return Pistache::Rest::Routes::Put(
                pistacheRouter, requestPath.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &pizzaHandler));

        case Request::Method::Patch:
            return Pistache::Rest::Routes::Patch(
                pistacheRouter, requestPath.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &pizzaHandler));

        case Request::Method::Delete:
            return Pistache::Rest::Routes::Delete(
                pistacheRouter, requestPath.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &pizzaHandler));

        default:
            RUNTIME_ASSERT(false && "Use of unsupported request method")
    }
}

}  // namespace pizza::endpoint::details
