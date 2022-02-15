/**
 * @file own/db/base/values.h
 * @brief Immutable data bindings for database query
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_VALUES_INCLUDED
#define OWN_DB_VALUES_INCLUDED

#include <own/generic/types.h>

namespace own::db
{

/** Immutable data bindings for database query
 *
 * We call it @c Values because of the `INSERT INTO table VALUES (val1, val2,...)`
 */
class Values final
{
   public:
    /** Constructor
     *
     * @tparam Args are the types of arguments
     * @param args are the data to bind
     */
    template <typename... Args>
    explicit Values(const Args&... args) noexcept : m_self{args...}
    {
    }

    /** The read-only @c at method
     *
     * @tparam Value is the value type to cast
     * @param index is the index of values
     *
     * @returns the value at @c index of values
     */
    template <typename Value>
    [[nodiscard]] Value at(const size_t index) const
    {
        const auto value = m_self.at(index);
        return std::any_cast<Value>(value);
    }

    /** Get begin const-iterator
     *
     * @returns the begin const-iterator
     */
    [[nodiscard]] auto begin() const noexcept { return m_self.begin(); }

    /** Get end const-iterator
     *
     * @returns the end const-iterator
     */
    [[nodiscard]] auto end() const noexcept { return m_self.end(); }

   private:
    const std::vector<std::any> m_self;
};

}  // namespace own::db

#endif
