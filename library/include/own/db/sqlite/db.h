/**
 * @file own/db/sqlite/db.h
 * @brief The @c Database class for SQLite
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/sqlitecpp/all.h>
#include <own/db/base/db.h>
#include <own/db/sqlite/details.h>

namespace own::db::sqlite
{
/** The Database class for SQLite
 *
 * Don't use it on databases other than @c foo.sqlite3 ! ;)
 */
class Database final : public base::Database
{
   public:
    /** Constructor
     *
     * @param name is the name of database
     * @param path is the path to the database file
     */
    explicit Database(const std::string_view name, const std::string_view path) noexcept
        : base::Database{name}, m_connection{path.data(), SQLite::OPEN_READWRITE}
    {
    }

   private:
    /** Do statement execution
     *
     * @param statement is the statement to execute
     */
    void doStatementExecution(const std::string_view statement) noexcept final
    {
        SQLite::Statement query{m_connection, statement.data()};
        query.exec();
    }

    /** Do statement execution
     *
     * @param result is passed in to store the query result
     * @param statement is the statement to execute
     */
    void doStatementExecution(std::vector<Values>& result,
                              const std::string_view statement) noexcept final
    {
        SQLite::Statement query{m_connection, statement.data()};
        while (query.executeStep())
        {
            auto resultStep = nlohmann::json::array();
            for (int index = 0; index < query.getColumnCount(); ++index)
            {
                resultStep.emplace_back(details::getColumn(query, index));
            }
            result.emplace_back(std::move(resultStep));
        }
    }

    /// The Connection
    SQLite::Database m_connection;
};
}  // namespace own::db::sqlite
