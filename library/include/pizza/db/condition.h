/**
 * @file pizza/db/condition.h
 * @brief Immutable data bindings represents a WHERE condition
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/generic/support.h>

namespace pizza::db
{

/**
 * Immutable data bindings represents a WHERE condition
 *
 * @note We've got Columns and Values; why not for just one more Condition? :)
 * @note If your condition is based on a string test, don't forget to quote it.
 */
class Condition final
{
    DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Condition)

   public:
    /** Constructor
     *
     * @tparam Args are the types of arguments
     * @param condition is the condition expression
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] explicit Condition(const std::string_view condition, const Args&... args) noexcept
        : m_self{fmt::vformat(condition, fmt::make_format_args(args...))}
    {
    }

    /** Get a view of the actual condition string
     *
     * @returns a view of the actual condition string
     */
    [[nodiscard]] std::string_view operator*() const noexcept { return m_self; }

   private:
    /// The Condition itself
    const std::string m_self;
};

}  // namespace pizza::db
