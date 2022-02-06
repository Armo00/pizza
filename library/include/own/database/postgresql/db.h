/**
 * @file own/database/postgresql/db.h
 * @brief Proxy class for PostgreSQL databases
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef DATABASE_POSTGRESQL_DB_INCLUDED
#define DATABASE_POSTGRESQL_DB_INCLUDED

#include <own/database/base/db.h>

#include "details.h"

/**
 * @namespace PostgreSQL
 */
namespace own::database::postgresql
{

    /**
     * @class Proxy class for PostgreSQL databases
     */
    class Database : public own::database::base::Database
    {
    public:
        /** Connect to PostgreSQL database and construct a `Database` object
         *
         * @param name is the name of database
         * @param connString is the postgres connection string (postgresql://)
         */
        explicit Database(const std::string_view name, const std::string_view connString)
            : own::database::base::Database { name }
            , m_connection { details::connectToDatabase(connString, m_logger) }
        { }

        Values execute(const std::string_view query) override
        {
            pqxx::work work { *m_connection };
            return details::executePostgresQuery(work, query);
        }

    private:
        std::unique_ptr<pqxx::connection> m_connection;
    };

} // namespace own::database::postgresql

#endif
