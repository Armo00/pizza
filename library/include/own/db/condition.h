/**
 * @file own/db/condition.h
 * @brief Represents a WHERE condition in a more natural manner
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <own/generic/support.h>

namespace own::db
{

/**
 * Represents a WHERE condition in a more natural manner
 *
 * @note We've got Columns and Values; why not for just one more Condition? :)
 * @note If your condition is based on a string test, don't forget to quote it.
 */
class Condition final
{
    DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Condition)

   public:
    /** Begins the first condition
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

    /** Get the actual condition string
     *
     * @returns the condition string
     */
    [[nodiscard]] std::string_view operator*() const noexcept { return m_self; }

   private:
    /// The Condition itself
    const std::string m_self;
};

}  // namespace own::db
