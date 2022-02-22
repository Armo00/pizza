/**
 * @file pizza/endpoint/concepts.h
 * @brief Concepts
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/endpoint/handler.h>
#include <pizza/support.h>

namespace pizza::endpoint::concepts
{

/**
 * Represents a handler class
 *
 * @details
 *  In Handler, two fields are mandatory: k_Name and k_ApiDesc
 *  Handler::k_Name represents the name of the handler to be registered
 *  Handler::k_ApiDesc represents the RESTful API description of the corresponding handler
 */
template <typename Handler>
concept PizzaHandler = std::is_same_v<decltype(Handler::k_Name), const std::string_view> &&
    std::is_same_v<typename decltype(Handler::k_ApiDesc)::value_type, typename Handler::ApiDesc>;

}  // namespace pizza::endpoint::concepts
