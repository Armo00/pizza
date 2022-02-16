/**
 * @file own/db/sqlite/details.h
 * @brief Implementation details.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_SQLITE3_DETAILS_INCLUDED
#define OWN_DB_SQLITE3_DETAILS_INCLUDED

#include <external/sqlitecpp/all.h>
#include <own/generic/types.h>

namespace own::db::sqlite::details
{
/** Get column -> @c any
 *
 * @param query is the executing query
 * @param index is the column index
 * @returns the value from column
 */
[[nodiscard]] inline nlohmann::json getColumn(SQLite::Statement& query, const int index) noexcept
{
    const auto column = query.getColumn(index);
    if (column.isNull())
    {
        return {};
    }
    if (column.isInteger())
    {
        return column.getInt64();
    }
    if (column.isFloat())
    {
        return column.getDouble();
    }
    return column.getString();
}
}  // namespace own::db::sqlite::details

#endif
