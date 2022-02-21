/**
 * @file pizza/db/sqlite/concepts.h
 * @brief Concepts
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/hash.h>

namespace pizza::db::sqlite::concepts
{

/**
 * Represents a SQLite Database description struct
 *
 * @details
 *  In Desc, two fields are mandatory: k_Name, k_FileName.
 *  Desc::k_Name is the name of database to be registered to the database hub.
 *  Desc::k_FileName is the filename of the database file.
 */
template <typename Desc>
concept Description = std::is_same_v<decltype(Desc::k_Name), const std::string_view> &&
    std::is_same_v<decltype(Desc::k_FileName), const std::string_view>;

}  // namespace pizza::db::sqlite::concepts
