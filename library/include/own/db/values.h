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

/**
 * Immutable data bindings for database query
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
     * @warning Behaviour of constructing Values into an `object` is NOT defined.
     */
    template <typename... Args>
    explicit Values(const Args&... args) noexcept : m_self{args...}
    {
    }

    /** The read-only @c at method
     *
     * @tparam Value is the value type to cast
     * @param index is the index of values
     * @returns the value at @c index of values
     */
    template <typename Value>
    [[nodiscard]] const Value& at(const size_t index) const noexcept
    {
        return m_self.at(index).get_ref<const Value&>();
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
    /// The Values itself
    const nlohmann::json m_self;
};

}  // namespace own::db

#endif
