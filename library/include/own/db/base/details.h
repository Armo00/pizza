/**
 * @file own/db/base/details.h
 * @brief Implementation details.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_BASE_DETAILS_INCLUDED
#define OWN_DB_BASE_DETAILS_INCLUDED

#include <external/fmt/all.h>
#include <own/generic/types.h>

namespace own::db::base::details
{
/** Deduce the type of an @c any object and return its SQL expression
 *
 * @param obj is the @c any object
 * @returns the "SQL-encoded" string
 */
[[nodiscard]] inline std::string toSqlEncodedString(const nlohmann::json& obj) noexcept
{
    /// Represents the @c NULL value
    static constexpr std::string_view k_Null{"NULL"};

    /// Represents a quoted string
    static constexpr std::string_view k_Quoted{"\'{}\'"};

    /// Represents a boolean false
    /// @note Since there's no such type as boolean in SQL, 0 means false
    static constexpr std::string_view k_False{"0"};

    /// Represents a boolean true
    /// @note Since there's no such type as boolean in SQL, 1 means true
    static constexpr std::string_view k_True{"1"};

    if (obj.is_null())
    {
        return k_Null.data();
    }

    if (obj.is_string())
    {
        // SQL statement requires strings to be quoted, so there we go..
        return fmt::vformat(k_Quoted, fmt::make_format_args(obj.get_ref<const std::string&>()));
    }

    if (obj.is_boolean())
    {
        return (obj.get<bool>() ? k_True.data() : k_False.data());
    }

    if (obj.is_number_float())
    {
        // By default, nlohmann::json uses double to represent float numbers
        return std::to_string(obj.get<double_t>());
    }

    if (obj.is_number_integer())
    {
        // By default, nlohmann::json uses int64 to represent signed integers
        return std::to_string(obj.get<intmax_t>());
    }

    if (obj.is_number_unsigned())
    {
        // By default, nlohmann::json uses uint64 to represent unsigned integers
        return std::to_string(obj.get<uintmax_t>());
    }

    // `obj` is not primitive and therefore cannot be SQL-encoded, but we struggle to try dumping it
    // anyway, and if even dumping fails, it suggests that the application is ill-formed enough to
    // get terminated immediately
    return obj.dump();
}

}  // namespace own::db::base::details

#endif
