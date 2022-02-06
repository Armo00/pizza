/**
 * @file own/database/sqlite/details.h
 * @brief SQLite details
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef DATABASE_SQLITE_DETAILS_INCLUDED
#define DATABASE_SQLITE_DETAILS_INCLUDED

#include <external/sqlitecpp/all.h>
#include <own/database/base/db.h>
#include <own/generic/types.h>
#include <own/logging/logging.h>

/**
 * SQLite details
 */
namespace own::database::sqlite::details
{

    /**
     * Using base Database
     */
    using own::database::base::Database;

    /** Connect to SQLite database
     *
     * @param path is the path to SQLite database
     * @param logger is the logger
     */
    inline auto connectToDatabase(const std::string_view path, const own::logging::Logger& logger)
    {
        try
        {
            logger.info(fmt::format("{} is connecting to {}", logger.getWhere(), path));

            const auto perm = (SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
            return std::make_unique<SQLite::Database>(path.data(), perm);
        }

        catch (const std::exception& e)
        {
            logger.error(e.what());
            throw;
        }
    }

    /** Enumerate value type contained in `SQLite::Column` object
     *
     * @param column is the `SQLite::Column` object
     *
     * @returns an `any` object with value of that type stored
     */
    inline std::any castColumnToAny(const SQLite::Column& column)
    {
        if (column.isInteger())
        {
            // treat as generic interger
            return static_cast<size_t>(column.getInt());
        }

        if (column.isFloat())
        {
            // treat as generic float
            return static_cast<double>(column.getDouble());
        }

        // type guess failed, treat everything as string
        return column.getString();
    }

    /** Execute a SQLite statement
     *
     * @param statement is a compiled SQL query statement
     * @param logger is the logger
     */
    inline auto executeSqliteQuery(SQLite::Statement& statement, const own::logging::Logger& logger)
    {
        logger.debug(statement.getQuery());

        try
        {
            Database::Values values;
            while (statement.executeStep())
            {
                Database::Value value;
                for (size_t ii = 0; ii < statement.getColumnCount(); ++ii)
                {
                    auto const column = statement.getColumn(ii);
                    value.emplace_back(castColumnToAny(column));
                }
                values.emplace_back(value);
            }
            return values;
        }

        catch (const std::exception& e)
        {
            logger.error(e.what());
            throw;
        }
    }

} // namespace own::database::sqlite::details

#endif
