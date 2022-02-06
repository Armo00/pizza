/**
 * @file own/database/base/db.h
 * @brief Base class for all relational databases
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#ifndef DATABASE_BASE_DB_INCLUDED
#define DATABASE_BASE_DB_INCLUDED

#include <own/database/base/details.h>
#include <own/generic/not_implemented.h>

/**
 * Base
 */
namespace own::database::base
{

    /**
     * Base class for all relational databases
     */
    class Database
    {
    public:
        /**
         * Type definition of database values
         */
        using Value = details::Value;

        /**
         * Type definition of database values
         */
        using Values = details::Values;

        /** Execute a statement, and return the query result if any
         *
         * @param query is the SQL statement to be executed
         *
         * @returns a vector of query results stored in `any` objects
         */
        virtual Values execute(const std::string_view query)
        {
            own::notImplemented("execute", m_logger);
            return {};
        }

        /** Execute a `INSERT INTO` statement
         *
         * @param table is the table name after the INSERT INTO word
         * @param values is a vector of `Value` objects
         */
        virtual void insertInto(const std::string_view table, const Values& values)
        {
            execute(details::generateSimpleInsertInto(table, values));
        }

        /** Execute a `INSERT INTO` statement
         *
         * @param table is the table name after the INSERT INTO word
         * @param value is a vector of `any` objects
         */
        virtual void insertInto(const std::string_view table, const Value& value)
        {
            execute(details::generateSimpleInsertInto(table, value));
        }

        /** Execute a `SELECT` statement, and return the query result if any
         *
         * @param columns is the result columns after the SELECT word
         * @param table is the table name after the FROM word
         * @param expr is the expression after the WHERE word
         *
         * @returns a vector of query results stored in `any` objects
         */
        virtual Values select(const std::string_view columns, const std::string_view table,
                              const std::string_view expr)
        {
            return execute(details::generateSimpleSelect(columns, table, expr));
        }

        /**
         * Disconnect from database
         */
        virtual void disconnect() { }

    protected:
        /** Constructor
         *
         * @param name is the name of database
         */
        explicit Database(const std::string_view name)
            : m_logger { name }
        { }

        /**
         * Destructor
         */
        virtual ~Database() = default;

        /**
         * Logger
         */
        const own::logging::Logger m_logger;
    };

} // namespace own::database::base

#endif
