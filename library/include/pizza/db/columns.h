/**
 * @file pizza/db/base/columns.h
 * @brief Immutable data container for storing database columns
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/support.h>

namespace pizza::db
{

/**
 * Immutable data bindings for iterating table columns
 *
 * We call it Columns because sqlitecpp call it Column as well.
 */
class Columns final
{
    DEFAULT_MOVEABLE_FINAL_CLASS(Columns)

   public:
    /** Constructor
     *
     * @tparam Args are the types of arguments
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] explicit Columns(const Args&... args) noexcept
        : m_self{std::make_unique<const std::vector<std::string_view>>(
              std::vector<std::string_view>{args...})}
    {
    }

    /** Get begin const-iterator
     *
     * @returns the begin const-iterator
     */
    [[nodiscard]] auto begin() const noexcept { return m_self->begin(); }

    /** Get end const-iterator
     *
     * @returns the end const-iterator
     */
    [[nodiscard]] auto end() const noexcept { return m_self->end(); }

    /** Get a view of the columns
     *
     * @returns a view of the columns
     */
    [[nodiscard]] std::span<const std::string_view> operator*() const noexcept { return *m_self; }

   private:
    /** The Columns itself
     *
     * @note Warp it with unique_ptr so that the immutability can be guaranteed, but objects of
     * Values are still movable (aka ownership is still transferable)
     */
    std::unique_ptr<const std::vector<std::string_view>> m_self;
};

}  // namespace pizza::db
