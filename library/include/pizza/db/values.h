/**
 * @file pizza/db/base/values.h
 * @brief Immutable data bindings for database query
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/support.h>

namespace pizza::db
{

/**
 * Immutable data bindings for database query
 *
 * We call it Values because of the `INSERT INTO table VALUES (val1, val2,...)`
 */
class Values final
{
    DEFAULT_MOVEABLE_FINAL_CLASS(Values)

   public:
    /** Constructor
     *
     * @tparam Args are the types of arguments
     * @param args are the data to bind
     */
    template <typename... Args>
    [[nodiscard]] explicit Values(const Args&... args) noexcept
        : m_self{std::make_unique<const nlohmann::json>(nlohmann::json{args...})}
    {
        RUNTIME_ASSERT(m_self->is_array() && "Values is not an array")
    }

    /** The read-only at method
     *
     * @tparam Value is the value type to cast
     * @param index is the index of values
     * @returns the value at index of values
     */
    template <typename Value>
    [[nodiscard]] const Value& at(const size_t index) const noexcept
    {
        return m_self->at(index).get_ref<const Value&>();
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

    /** Dump values into JSON-serialized string
     *
     * @returns the JSON-serialized string
     */
    [[nodiscard]] std::string dump() const noexcept { return m_self->dump(); }

   private:
    /** The Values itself
     *
     * @note Warp it with unique_ptr so that the immutability can be guaranteed, but objects of
     * Values are still movable (aka ownership is still transferable)
     */
    std::unique_ptr<const nlohmann::json> m_self;
};

}  // namespace pizza::db
