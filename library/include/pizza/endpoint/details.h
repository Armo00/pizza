/**
 * @file pizza/endpoint/details.h
 * @brief Implementation details of endpoint
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/pistache/all.h>
#include <pizza/endpoint/handler.h>
#include <pizza/generic/support.h>
#include <pizza/logging/logging.h>

namespace pizza::endpoint::details
{

/** Append a new router record
 *
 * @param router is the Pistache router
 * @param handler is the handler object
 * @param method is the request method
 * @param path is the request path
 *
 * @private
 */
inline void addHandler(Pistache::Rest::Router& router, Handler& handler,
                       const Request::Method method, const std::string_view path) noexcept
{
    switch (method)
    {
        case Request::Method::Get:
            return Pistache::Rest::Routes::Get(
                router, path.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &handler));

        case Request::Method::Post:
            return Pistache::Rest::Routes::Post(
                router, path.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &handler));

        case Request::Method::Put:
            return Pistache::Rest::Routes::Put(
                router, path.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &handler));

        case Request::Method::Patch:
            return Pistache::Rest::Routes::Patch(
                router, path.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &handler));

        case Request::Method::Delete:
            return Pistache::Rest::Routes::Delete(
                router, path.data(),
                Pistache::Rest::Routes::bind(&Handler::handleRequest, &handler));

        default:
            RUNTIME_ASSERT(false && "Use of unsupported request method")
    }
}

}  // namespace pizza::endpoint::details
