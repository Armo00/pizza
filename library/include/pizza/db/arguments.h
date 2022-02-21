/**
 * @file pizza/db/arguments.h
 * @brief Structs that represent Arguments for executing SQL statements
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/db/columns.h>
#include <pizza/db/condition.h>
#include <pizza/db/values.h>
#include <pizza/support.h>

namespace pizza::db
{

/// Represents the table name
struct Table final
{
    const std::string_view tableName;  ///< Represents the table name
};

/// Represents Arguments for executing INSERT INTO statements
struct InsertIntoArguments final
{
    const Table insertInto;                        ///< Represents the INSERT INTO word
    const std::optional<const Columns> columns{};  ///< Represents (col1, col2, ...)
    const Values values;                           ///< Represents the VALUES word
};

/// Represents Arguments for executing SELECT statements
struct SelectFromArguments final
{
    const Columns select;                          ///< Represents the SELECT word
    const Table from;                              ///< Represents the FROM word
    const std::optional<const Condition> where{};  ///< Represents the WHERE word
};

}  // namespace pizza::db
