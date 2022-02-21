/**
 * @file pizza/endpoint/concepts.h
 * @brief Concepts
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/endpoint/handler.h>
#include <pizza/support.h>

namespace pizza::endpoint
{

/**
 * Represents a handler class
 *
 * @details
 *  In Handler, two fields are mandatory: k_Name and k_Api
 *  Handler::k_Name represents the name of the handler to be registered
 *  Handler::k_Api represents the RESTful API description of the corresponding handler
 */
template <typename Handler>
concept PizzaHandler = std::is_same_v<decltype(Handler::k_Name), const std::string_view> &&
    std::is_same_v<typename decltype(Handler::k_Api)::value_type,
                   std::pair<Request::Method, const std::string_view>>;

}  // namespace pizza::endpoint
