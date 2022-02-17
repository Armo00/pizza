/**
 * @file own/endpoint/request.h
 * @brief The Request wrapper
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_ENDPOINT_PISTACHE_REQUEST_INCLUDED
#define OWN_ENDPOINT_PISTACHE_REQUEST_INCLUDED

#include <external/cpr/all.h>
#include <external/pistache/all.h>
#include <own/generic/support.h>

namespace own::endpoint
{
/** Request
 *
 * This class is an interface to @c Pistache::Http::Request
 */
class Request final
{
    DESTRUCTIBLE_FINAL_CLASS(Request)

   public:
    /// Request methods
    enum class Method
    {
        Get,    ///< Represents a GET request
        Post,   ///< Represents a POST request
        Put,    ///< Represents a PUT request
        Patch,  ///< Represents a PATCH request
        Delete  ///< Represents a DELETE request
    };

    /** Constructor
     *
     * @param request is a reference to @c Pistache::Http::Request object
     * @note intentionally implicit
     */
    explicit Request(const Pistache::Http::Request& request) noexcept : m_request{request} {}

    /** Get request method
     *
     * @returns request method
     */
    [[nodiscard]] Method getMethod() const noexcept
    {
        switch (m_request.method())
        {
            case Pistache::Http::Method::Get:
                return Method::Get;

            case Pistache::Http::Method::Post:
                return Method::Post;

            case Pistache::Http::Method::Put:
                return Method::Put;

            case Pistache::Http::Method::Patch:
                return Method::Patch;

            case Pistache::Http::Method::Delete:
                return Method::Delete;

            default:
                // Other methods treated as GET. Raise exceptions?
                return Method::Get;
        }
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
     * @returns @c true if query has the given key, otherwise @c false
     */
    [[nodiscard]] bool hasQuery(const std::string_view key) const noexcept
    {
        const auto& query = m_request.query();
        return query.has(key.data());
    }

    /** Get request query
     *
     * @param key is the query key, can be @c {}
     * @returns the query value if key is not @c {} , otherwise the whole query string
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

}  // namespace own::endpoint

#endif
