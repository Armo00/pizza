/**
 * @file pizza/endpoint/request.h
 * @brief The Request wrapper
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/cpr/all.h>
#include <external/pistache/all.h>
#include <pizza/generic/support.h>

namespace pizza::endpoint
{

/**
 * Represents a request
 *
 * This class is an interface to Pistache::Http::Request
 */
class Request final
{
    DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Request)

   public:
    /// Request methods
    using Method = Pistache::Http::Method;

    /** Constructor
     *
     * @param request is a reference to Pistache::Http::Request object
     */
    explicit Request(const Pistache::Http::Request& request) noexcept : m_request{request} {}

    /** Get request method
     *
     * @returns request method
     */
    [[nodiscard]] Method getMethod() const noexcept
    {
        const auto method = m_request.method();
        return method;
    }

    /** Get request path
     *
     * @returns request path
     */
    [[nodiscard]] std::string getPath() const noexcept
    {
        const auto& resource = m_request.resource();
        return resource;
    }

    /** Has request query?
     *
     * @param key is the query key
     * @returns true if query has the given key, otherwise false
     */
    [[nodiscard]] bool hasQuery(const std::string_view key) const noexcept
    {
        const auto& query = m_request.query();
        return query.has(key.data());
    }

    /** Get request query
     *
     * @param key is the query key, can be an empty string (default: {})
     * @returns the query value if the query has the key, otherwise the whole query string if key is
     * empty, otherwise an empty string
     */
    [[nodiscard]] std::string getQuery(const std::string_view key = {}) const noexcept
    {
        const auto& query = m_request.query();
        if (key.empty())
        {
            return query.as_str();
        }

        const auto value = query.get(key.data());
        if (value.isEmpty())
        {
            return {};
        }

        return cpr::util::urlDecode(value.get());
    }

    /** Get request body
     *
     * @returns the request body
     */
    [[nodiscard]] std::string getBody() const noexcept
    {
        const auto& body = m_request.body();
        return body;
    }

   private:
    /// The Request object
    const Pistache::Http::Request& m_request;
};

}  // namespace pizza::endpoint
