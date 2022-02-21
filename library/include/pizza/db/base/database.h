/**
 * @file pizza/db/base/database.h
 * @brief The base Database class.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/db/arguments.h>
#include <pizza/db/base/details.h>
#include <pizza/log/logger.h>
#include <pizza/support.h>

namespace pizza::db::base
{

/**
 * The base Database class
 *
 * @note This is a redesign
 * @todo Make each query async and returns promise (?)
 */
class Database
{
    DEFAULT_DESTRUCTIBLE_BASE_CLASS(Database)

   private:
    /** Do statement execution that doesn't have result
     *
     * @param statement is the statement to execute
     */
    virtual void doStatementExecution(
        [[maybe_unused]] const std::string_view statement) const noexcept
    {
        m_log.warn("`doStatementExecution` is not implemented!");
    }

    /** Do statement execution that has result
     *
     * @param result is passed in to store the query result
     * @param statement is the statement to execute
     */
    virtual void doStatementExecution(
        [[maybe_unused]] std::vector<Values>& result,
        [[maybe_unused]] const std::string_view statement) const noexcept
    {
        m_log.warn("`doStatementExecution` is not implemented!");
    }

    /// Represents a separator
    static constexpr std::string_view k_Separator{", "};

   public:
    /** Constructor
     *
     * @param name is the name of database
     */
    explicit Database(const std::string_view name) noexcept : m_log{name} {}

    /** Execute statement that doesn't have result
     *
     * @tparam Args are the types of arguments
     * @param statement is the statement to execute
     * @param args are the data to bind
     */
    template <typename... Args>
    void execute(const std::string_view statement, const Args&... args) const noexcept
    {
        m_log.debug(statement, args...);

        // Must be overridden or it won't do anything.
        doStatementExecution(fmt::vformat(statement, fmt::make_format_args(args...)));
    }

    /** Execute statement that has result
     *
     * @tparam Args are the types of arguments
     * @param result is passed in to store the query result
     * @param statement is the statement to execute
     * @param args are the data to bind
     */
    template <typename... Args>
    void execute(std::vector<Values>& result, const std::string_view statement,
                 const Args&... args) const noexcept
    {
        m_log.debug(statement, args...);

        // Must be overridden or it won't do anything.
        doStatementExecution(result, fmt::vformat(statement, fmt::make_format_args(args...)));
    }

    /** Execute INSERT INTO statement
     *
     * @param args contains the information needed to perform an execution
     */
    void execute(const InsertIntoArguments& args) const noexcept
    {
        std::vector<std::string> encodedValues;
        std::transform(args.values.begin(), args.values.end(), std::back_inserter(encodedValues),
                       details::makeSqlEncodedString);

        const auto joinedValues = fmt::join(encodedValues, k_Separator);
        if (args.columns)
        {
            static constexpr std::string_view k_Sql{"INSERT INTO {} ({}) VALUES ({});"};
            const auto joinedColumns = fmt::join(*args.columns, k_Separator);
            execute(k_Sql, args.insertInto.tableName, joinedColumns, joinedValues);
        }
        else
        {
            static constexpr std::string_view k_Sql{"INSERT INTO {} VALUES ({});"};
            execute(k_Sql, args.insertInto.tableName, joinedValues);
        }
    }

    /** Execute SELECT statement
     *
     * @param args contains the information needed to perform an execution
     */
    [[nodiscard]] std::vector<Values> execute(const SelectFromArguments& args) const noexcept
    {
        std::vector<Values> result{};
        const auto joinedColumns = fmt::join(args.select, k_Separator);
        if (args.where)
        {
            static constexpr std::string_view k_Sql{"SELECT {} FROM {} WHERE {};"};
            execute(result, k_Sql, joinedColumns, args.from.tableName, **args.where);
        }
        else
        {
            static constexpr std::string_view k_Sql{"SELECT {} FROM {};"};
            execute(result, k_Sql, joinedColumns, args.from.tableName);
        }
        return result;
    }

   protected:
    const pizza::log::Logger m_log;
};

}  // namespace pizza::db::base
