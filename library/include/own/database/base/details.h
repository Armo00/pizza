/**
 * @file own/database/base/details.h
 * @brief Details
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#include <external/fmt/all.h>
#include <own/generic/any_to_str.h>
#include <own/generic/types.h>

/**
 * Details.
 *
 * Everything under this namespace shouldn't be used outside this module
 */
namespace own::database::base::details
{

    /**
     * Type definition of database values
     */
    using Value = std::vector<std::any>;

    /**
     * Type definition of database values
     */
    using Values = std::vector<Value>;

    /** Compose a simple INSERT INTO statement
     *
     * @param table is the table name after the INSERT INTO word
     * @param value is a vector of `any` objects
     *
     * @ref https://www.sqlite.org/syntax/insert-stmt.html
     */
    inline auto generateSimpleInsertInto(const std::string_view table, const Value& value)
    {
        std::vector<std::string> value_;
        std::transform(value.begin(), value.end(), std::back_inserter(value_),
                       [&](const auto& obj) { return own::toString(obj); });

        return fmt::format("INSERT INTO {} VALUES ({});", table, fmt::join(value_, ", "));
    }

    /** Compose a simple INSERT INTO statement
     *
     * @param table is the table name after the INSERT INTO word
     * @param values is a vector of `Value` objects
     *
     * @ref https://www.sqlite.org/syntax/insert-stmt.html
     */
    inline auto generateSimpleInsertInto(const std::string_view table, const Values& values)
    {
        std::vector<std::string> statements;
        std::transform(values.begin(), values.end(), std::back_inserter(statements),
                       [&](const auto& value) { return generateSimpleInsertInto(table, value); });

        return fmt::format("{}", fmt::join(statements, " "));
    }

    /** Compose a simple SELECT statement
     *
     * @param columns is the result columns after the SELECT word
     * @param table is the table name after the FROM word
     * @param expr is the expression after the WHERE word
     *
     * @returns the outcome statement string
     * @ref https://www.sqlite.org/syntax/select-stmt.html
     */
    inline auto generateSimpleSelect(const std::string_view columns, const std::string_view table,
                                     const std::string_view expr)
    {
        return fmt::format("SELECT {} FROM {} WHERE {};", columns, table, expr);
    }

} // namespace own::database::base::details
