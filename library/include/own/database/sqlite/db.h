/**
 * @file own/database/sqlite/db.h
 * @brief Proxy class for SQLite databases
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef DATABASE_SQLITE_DB_INCLUDED
#define DATABASE_SQLITE_DB_INCLUDED

#include <own/database/base/db.h>

#include "details.h"

/**
 * SQLite
 */
namespace own::database::sqlite
{

    /**
     * Proxy class for SQLite databases
     */
    class Database : public own::database::base::Database
    {
    public:
        /** Constructor
         *
         * @param name is the name of database
         * @param path is the path to the database
         */
        explicit Database(const std::string_view name, const std::string_view path)
            : own::database::base::Database { name }
            , m_connection { details::connectToDatabase(path, m_logger) }
        { }

        Values execute(const std::string_view query) override
        {
            SQLite::Statement statement { *m_connection, query.data() };
            return details::executeSqliteQuery(statement, m_logger);
        }

    private:
        std::unique_ptr<SQLite::Database> m_connection;
    };

} // namespace own::database::sqlite

#endif
