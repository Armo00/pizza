/**
 * @file own/db/base/columns.h
 * @brief Immutable data container for storing database columns
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_COLUMNS_INCLUDED
#define OWN_DB_COLUMNS_INCLUDED

#include <own/generic/types.h>

namespace own::db
{

/**
 * Immutable data bindings for iterating table columns
 *
 * We call it column because sqlitecpp call it columns as well.
 */
class Columns final
{
   public:
    /** Constructor
     *
     * @tparam Args are the types of arguments
     * @param args are the data to bind
     */
    template <typename... Args>
    explicit Columns(const Args&... args) noexcept : m_self{args...}
    {
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
    const std::vector<std::string_view> m_self;
};

}  // namespace own::db

#endif
