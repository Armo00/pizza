/**
 * @file pizza/endpoint/cake.h
 * @brief Data bindings for request processing
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <pizza/generic/support.h>

namespace pizza::endpoint
{

/**
 * The Cake
 *
 * @details
 * This is a wrapper to json with restricted set of operations.
 * This is a binding. This is not a lie. :P
 *
 * @note
 * Objects of Cake are used to pass states between different phases of request processing.
 */
class Cake final
{
    DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Cake)

   public:
    /// Constructor
    explicit Cake() noexcept : m_self{nlohmann::json::object()}
    {
        RUNTIME_ASSERT(m_self.is_object() && "Cake is not an object")
    }

    /** The emplace method
     *
     * @tparam Value is the value type to cast (default: json)
     * @param key is the key
     * @param value is the value
     */
    template <typename Value = nlohmann::json>
    void emplace(const std::string_view key, const Value& value) noexcept
    {
        m_self.emplace(key.data(), value);
    }

    /** The read-only at const-method
     *
     * @tparam Value is the value type to cast (default: json)
     * @param key is the key (intolerant if the key does not exist)
     * @returns the value for key in the cake
     */
    template <typename Value = nlohmann::json>
    [[nodiscard]] const Value& at(const std::string_view key) const noexcept
    {
        const auto& value = m_self.at(key.data());
        if constexpr (std::is_same_v<Value, nlohmann::json>)
        {
            return value;
        }
        else
        {
            return value.get_ref<const Value&>();
        }
    }

    /** Dump the Cake into JSON-serialized string
     *
     * @returns the JSON-serialized string
     */
    [[nodiscard]] std::string dump() const noexcept { return m_self.dump(); }

    /** Get a const-reference of the cake
     *
     * @returns a const-reference of the cake
     */
    [[nodiscard]] const nlohmann::json& operator*() const noexcept { return m_self; }

   private:
    /// The Cake itself
    nlohmann::json m_self;
};

}  // namespace pizza::endpoint
