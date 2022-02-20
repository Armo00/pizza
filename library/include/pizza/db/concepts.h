/**
 * @file pizza/db/concepts.h
 * @brief Concepts
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/generic/support.h>

namespace pizza::db
{

/**
 * Represents a database class
 *
 * @details
 *  In Database, one field is mandatory: k_Name, which represents the name of the database
 */
template <typename Database>
concept PizzaDatabase = std::is_same_v<decltype(Database::k_Name), const std::string_view>;

}  // namespace pizza::db
