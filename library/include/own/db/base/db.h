/**
 * @file own/db/base/db.h
 * @brief The base @c Database class.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_BASE_DB_INCLUDED
#define OWN_DB_BASE_DB_INCLUDED

#include <external/fmt/all.h>
#include <own/db/values.h>
#include <own/generic/types.h>
#include <own/logging/logging.h>

namespace own::db::base
{

    /** The base @c Database class
     *
     * This is a redesign
     */
    class Database
    {
    public:
        /** Constructor
         *
         * @param name is the name of database
         */
        explicit Database(const std::string_view name)
            : m_logger { name }
        { }

        /// The Values
        using Values = own::db::Values;

        /** Execute statement
         *
         * @param statement is the statement to execute
         */
        virtual void executeStatement(const std::string_view statement)
        {
            m_logger.debug(statement);
        }

        /** Execute statement
         *
         * @param statement is the statement to execute
         * @param result is passed in to store the query result
         */
        virtual void executeStatement(const std::string_view statement,
                                      [[maybe_unused]] std::vector<Values>& result)
        {
            m_logger.debug(statement);
        }

        /** Execute INSERT INTO statement
         *
         * @param tableName is the table name
         * @param columns are the columns to insert
         * @param values are the values to insert
         */
        void executeInsertInto(const std::string_view tableName,
                               const std::vector<std::string>& columns,
                               const std::vector<std::string>& values)
        {
            static constexpr std::string_view k_InsertInto { "INSERT INTO {} {} VALUES {};" };
            const auto statement = fmt::format(k_InsertInto, tableName,
                                               fmt::format("({})", fmt::join(columns, ", ")),
                                               fmt::format("({})", fmt::join(values, ", ")));
            executeStatement(statement);
        }

        /** Execute INSERT INTO statement
         *
         * @param tableName is the table name
         * @param values are the values to insert
         */
        void executeInsertInto(const std::string_view tableName,
                               const std::vector<std::string>& values)
        {
            static constexpr std::string_view k_InsertInto { "INSERT INTO {} VALUES {};" };
            const auto statement = fmt::format(k_InsertInto, tableName,
                                               fmt::format("({})", fmt::join(values, ", ")));
            executeStatement(statement);
        }

        /** Execute SELECT statement
         *
         * @param columns are the columns to select from
         * @param tableName is the table name
         * @returns the query result
         */
        [[nodiscard]] std::unique_ptr<std::vector<Values>>
        executeSelectFrom(const std::vector<std::string>& columns, const std::string_view tableName)
        {
            static constexpr std::string_view k_SelectFrom { "SELECT {} FROM {};" };
            const auto statement
                = fmt::format(k_SelectFrom, fmt::format("{}", fmt::join(columns, ", ")), tableName);

            /// Use @c unique_ptr to prevent copy
            auto result = std::make_unique<std::vector<Values>>();
            executeStatement(statement, *result);
            return result;
        }

        /** Execute SELECT statement
         *
         * @param columns are the columns to select from
         * @param tableName is the table name
         * @param condition is the condition
         * @returns the query result
         */
        [[nodiscard]] std::unique_ptr<std::vector<Values>>
        executeSelectFrom(const std::vector<std::string>& columns, const std::string_view tableName,
                          const std::string_view condition)
        {
            static constexpr std::string_view k_SelectFrom { "SELECT {} FROM {} WHERE {};" };
            const auto statement = fmt::format(
                k_SelectFrom, fmt::format("{}", fmt::join(columns, ", ")), tableName, condition);

            /// Use @c unique_ptr to prevent copy
            auto result = std::make_unique<std::vector<Values>>();
            executeStatement(statement, *result);
            return result;
        }

    protected:
        /// The logger
        const logging::Logger m_logger;
    };

} // namespace own::db::base

#endif
