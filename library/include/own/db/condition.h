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
 * @note If your condition is based on a string test, don't forget to makeQuoted it.
 * @details It just stacks up the subconditions; watch out the order of logical operations.
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

    /** Begins the first condition with (<another condition>)
     *
     * @param condition is another Condition object
     */
    [[nodiscard]] static Condition parens(const Condition& condition) noexcept
    {
        return Condition{k_Parens, *condition};
    }

    /** Begins the first condition with NOT
     *
     * @tparam Args are the types of arguments
     * @param condition is the condition expression
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] static Condition not_(const std::string_view condition,
                                        const Args&... args) noexcept
    {
        return Condition{k_Not, *Condition(condition, args...)};
    }

    /** Begins the first condition with NOT (<another condition>)
     *
     * @param condition is another Condition object
     */
    [[nodiscard]] static Condition not_(const Condition& condition) noexcept
    {
        return Condition{k_Not, *parens(condition)};
    }

    /** Stacks another condition with AND
     *
     * @tparam Args are the types of arguments
     * @param condition is the condition expression
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] Condition& and_(const std::string_view condition, const Args&... args) noexcept
    {
        m_self = *Condition{k_And, m_self, *Condition(condition, args...)};
        return *this;
    }

    /** Begins the first condition with AND (<another condition>)
     *
     * @param condition is another Condition object
     */
    [[nodiscard]] Condition& and_(const Condition& condition) noexcept
    {
        m_self = *Condition{k_And, m_self, *parens(condition)};
        return *this;
    }

    /** Stacks another condition with OR
     *
     * @tparam Args are the types of arguments
     * @param condition is the condition expression
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] Condition& or_(const std::string_view condition, const Args&... args) noexcept
    {
        m_self = *Condition{k_Or, m_self, *Condition(condition, args...)};
        return *this;
    }

    /** Begins the first condition with OR (<another condition>)
     *
     * @param condition is another Condition object
     */
    [[nodiscard]] Condition& or_(const Condition& condition) noexcept
    {
        m_self = *Condition{k_Or, m_self, *parens(condition)};
        return *this;
    }

    /** Stacks another condition with AND NOT
     *
     * @tparam Args are the types of arguments
     * @param condition is the condition expression
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] Condition& andNot(const std::string_view condition, const Args&... args) noexcept
    {
        m_self = *Condition{k_And, m_self, *Condition::not_(condition, args...)};
        return *this;
    }

    /** Begins the first condition with AND NOT (<another condition>)
     *
     * @param condition is another Condition object
     */
    [[nodiscard]] Condition& andNot(const Condition& condition) noexcept
    {
        m_self = *Condition{k_And, m_self, *Condition::not_(condition)};
        return *this;
    }

    /** Stacks another condition with OR NOT
     *
     * @tparam Args are the types of arguments
     * @param condition is the condition expression
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] Condition& orNot(const std::string_view condition, const Args&... args) noexcept
    {
        m_self = *Condition{k_Or, m_self, *Condition::not_(condition, args...)};
        return *this;
    }

    /** Begins the first condition with OR NOT (<another condition>)
     *
     * @param condition is another Condition object
     */
    [[nodiscard]] Condition& orNot(const Condition& condition) noexcept
    {
        m_self = *Condition{k_Or, m_self, *Condition::not_(condition)};
        return *this;
    }

    /** Get the actual condition string
     *
     * @returns the condition string
     */
    [[nodiscard]] std::string_view operator*() const noexcept { return m_self; }

   private:
    /// The Condition itself
    std::string m_self;

    /// Represents a NOT condition
    static constexpr std::string_view k_Not{"NOT {}"};

    /// Represents an AND condition
    static constexpr std::string_view k_And{"{} AND {}"};

    /// Represents an OR condition
    static constexpr std::string_view k_Or{"{} OR {}"};

    /// Represents a parened condition
    static constexpr std::string_view k_Parens{"({})"};
};

/** Put a pair of single-quotes (') around a string
 *
 * @param str is the string to be decorated
 * @returns a quoted string
 */
[[nodiscard]] inline std::string makeQuoted(const std::string_view str) noexcept
{
    /// Represents a quoted string
    static constexpr std::string_view k_Quoted{"\'{}\'"};

    return fmt::vformat(k_Quoted, fmt::make_format_args(str));
}

}  // namespace own::db
