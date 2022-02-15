/**
 * @file own/endpoint/cake.h
 * @brief Data bindings for request processing
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_ENDPOINT_CAKE_INCLUDED
#define OWN_ENDPOINT_CAKE_INCLUDED

#include <own/generic/types.h>

namespace own::endpoint
{

/** The Cake
 *
 * @details
 * This is a wrapper to @c unordered_map<string,json> with restricted set of operations.
 * This is a binding. This is not a lie. :P
 *
 * @note
 * Objects of @c Cake are used to pass states between different phases of request processing.
 */
class Cake final
{
    DEFAULT_DESTRUCTIBLE_FINAL_CLASS(Cake)

   public:
    /// Constructor
    explicit Cake() = default;

    /** The @c emplace method
     *
     * @tparam Value is the value type to cast (default: json)
     * @param key is the key
     * @param value is the value
     */
    template <typename Value = nlohmann::json>
    void emplace(const std::string_view key, const Value& value) noexcept
    {
        m_self.emplace(key, value);
    }

    /** The read-only @c at const-method
     *
     * @tparam Value is the value type to cast (default: json)
     * @param key is the key
     * @param def is the default value in case the key does not exist
     *
     * @returns the value for key if key is in the cake, otherwise the default value
     */
    template <typename Value = nlohmann::json>
    [[nodiscard]] const Value& at(const std::string_view key, const Value& def = {}) const noexcept
    {
        if (m_self.contains(key.data()))
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
        return def;
    }

    /** Dump the Cake into JSON-serialized string
     *
     * @returns the JSON-serialized string
     */
    [[nodiscard]] std::string dump() const noexcept
    {
        // We must use function-style constructor here, or else
        // nlohmann::json will be intepreting m_self as an array
        return nlohmann::json(m_self).dump();
    }

   private:
    std::unordered_map<std::string, nlohmann::json> m_self;
};

}  // namespace own::endpoint

#endif
