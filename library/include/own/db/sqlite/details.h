/**
 * @file own/db/sqlite/details.h
 * @brief Implementation details.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/sqlitecpp/all.h>
#include <own/generic/support.h>

namespace own::db::sqlite::details
{

/** Get column value
 *
 * @param query is the executing query
 * @param index is the column index
 * @returns the value from column
 *
 * @private
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
