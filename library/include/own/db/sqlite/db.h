/**
 * @file own/db/sqlite/db.h
 * @brief The @c Database class for SQLite
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_SQLITE_DB_INCLUDED
#define OWN_DB_SQLITE_DB_INCLUDED

#include <external/sqlitecpp/all.h>
#include <own/db/base/db.h>
#include <own/db/sqlite/details.h>

namespace own::db::sqlite
{
    /** The Database class for SQLite
     *
     * Don't use it on databases other than @c foo.sqlite3 ! ;)
     */
    class Database : public base::Database
    {
    public:
        /** Constructor
         *
         * @param name is the name of database
         * @param dbPath is the path to the database file
         */
        explicit Database(const std::string_view name, const std::string_view dbPath)
            : base::Database { name }
            , m_connection { dbPath.data(), SQLite::OPEN_READWRITE }
        { }

        void executeStatement(const std::string_view statement) final
        {
            m_logger.debug(statement);
            SQLite::Statement query { m_connection, statement.data() };
            query.exec();
        }

        void executeStatement(const std::string_view statement, std::vector<Values>& result) final
        {
            m_logger.debug(statement);
            SQLite::Statement query { m_connection, statement.data() };
            while (query.executeStep())
            {
                const size_t columnCount = query.getColumnCount();
                std::vector<std::any> resultStep;
                resultStep.reserve(columnCount);
                for (size_t index = 0; index < columnCount; ++index)
                {
                    resultStep.emplace_back(details::getColumn(query, index));
                }
                result.emplace_back(std::move(resultStep));
            }
        }

    private:
        /// The connection
        SQLite::Database m_connection;
    };
} // namespace own::db::sqlite

#endif