/**
 * @file own/db/base/db.h
 * @brief The base @c Database class.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_BASE_DB_INCLUDED
#define OWN_DB_BASE_DB_INCLUDED

#include <external/fmt/all.h>
#include <own/db/base/details.h>
#include <own/db/columns.h>
#include <own/db/values.h>
#include <own/generic/types.h>
#include <own/logging/logging.h>

namespace own::db::base
{

/** The base @c Database class
 *
 * @note This is a redesign
 * @todo Make each query async and returns @c promise (?)
 */
class Database
{
    DEFAULT_DESTRUCTIBLE_BASE_CLASS(Database)

   private:
    /** Do statement execution
     *
     * @param statement is the statement to execute
     */
    virtual void doStatementExecution([[maybe_unused]] const std::string_view statement) noexcept
    {
        m_logger.warn("`doStatementExecution' is not implemented!");
    }

    /** Do statement execution
     *
     * @param result is passed in to store the query result
     * @param statement is the statement to execute
     */
    virtual void doStatementExecution([[maybe_unused]] std::vector<Values>& result,
                                      [[maybe_unused]] const std::string_view statement) noexcept
    {
        m_logger.warn("`doStatementExecution' is not implemented!");
    }

   public:
    /** Constructor
     *
     * @param name is the name of database
     */
    explicit Database(const std::string_view name) noexcept : m_logger{name} {}

    /** Execute statement
     *
     * @tparam Args are the types of arguments
     * @param statement is the statement to execute
     * @param args are the data to bind
     */
    template <typename... Args>
    void executeStatement(const std::string_view statement, const Args&... args) noexcept
    {
        m_logger.debug(statement, args...);

        // Must be overridden or it won't do anything.
        doStatementExecution(fmt::vformat(statement, fmt::make_format_args(args...)));
    }

    /** Execute statement
     *
     * @tparam Args are the types of arguments
     * @param result is passed in to store the query result
     * @param statement is the statement to execute
     * @param args are the data to bind
     */
    template <typename... Args>
    void executeStatement(std::vector<Values>& result, const std::string_view statement,
                          const Args&... args) noexcept
    {
        m_logger.debug(statement, args...);

        // Must be overridden or it won't do anything.
        doStatementExecution(result, fmt::vformat(statement, fmt::make_format_args(args...)));
    }

    /** Execute INSERT INTO statement
     *
     * @param tableName is the table name
     * @param columns are the columns to insert
     * @param values are the values to insert
     */
    void executeInsertInto(const std::string_view tableName, const Columns& columns,
                           const Values& values) noexcept
    {
        /// Represents the INSERT INTO statement
        static constexpr std::string_view k_InsertInto{"INSERT INTO {} ({}) VALUES ({});"};

        std::vector<std::string> encodedValues;
        std::transform(values.begin(), values.end(), std::back_inserter(encodedValues),
                       details::toSqlEncodedString);

        executeStatement(k_InsertInto, tableName, fmt::join(columns, ", "),
                         fmt::join(encodedValues, ", "));
    }

    /** Execute INSERT INTO statement
     *
     * @param tableName is the table name
     * @param values are the values to insert
     */
    void executeInsertInto(const std::string_view tableName, const Values& values) noexcept
    {
        /// Represents the INSERT INTO statement
        static constexpr std::string_view k_InsertInto{"INSERT INTO {} VALUES ({});"};

        std::vector<std::string> encodedValues;
        std::transform(values.begin(), values.end(), std::back_inserter(encodedValues),
                       details::toSqlEncodedString);

        executeStatement(k_InsertInto, tableName, fmt::join(encodedValues, ", "));
    }

    /** Execute SELECT statement
     *
     * @param tableName is the table name
     * @param columns are the columns to select from
     * @returns the query result
     */
    [[nodiscard]] std::vector<Values> executeSelectFrom(const std::string_view tableName,
                                                        const Columns& columns) noexcept
    {
        /// Represents the SELECT statement
        static constexpr std::string_view k_SelectFrom{"SELECT {} FROM {};"};

        std::vector<Values> result{};
        executeStatement(result, k_SelectFrom, fmt::join(columns, ", "), tableName);
        return result;
    }

    /** Execute SELECT statement
     *
     * @tparam Args are the types of arguments
     * @param tableName is the table name
     * @param columns are the columns to select from
     * @param condition is the condition expression
     * @param args are the values for plugging-in to the condition
     *
     * @returns the query result
     */
    template <typename... Args>
    [[nodiscard]] std::vector<Values> executeSelectFrom(const std::string_view tableName,
                                                        const Columns& columns,
                                                        const std::string_view condition,
                                                        const Args&... args) noexcept
    {
        /// Represents the SELECT statement
        static constexpr std::string_view k_SelectFrom{"SELECT {} FROM {} WHERE {};"};

        std::vector<Values> result{};
        executeStatement(result, k_SelectFrom, fmt::join(columns, ", "), tableName,
                         fmt::vformat(condition, fmt::make_format_args(args...)));
        return result;
    }

   protected:
    /// The Logger
    const logging::Logger m_logger;
};

}  // namespace own::db::base

#endif
