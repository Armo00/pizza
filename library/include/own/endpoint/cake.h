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
     * This is a wrapper to @c unordered_map<string,any> with restricted set of operations.
     * This is a binding. This is not a lie. :P
     *
     * @note
     * Objects of @c Cake are used to pass states between different phases of request processing.
     */
    class Cake final
    {
    public:
        /** The @c emplace method
         *
         * @param key is the key
         * @param value is the value
         */
        void emplace(const std::string_view key, const std::any& value) noexcept
        {
            m_self.emplace(key, value);
        }

        /** The read-only @c at const-method
         *
         * @param key is the key
         * @param def is the def value
         * @returns the value for key if key is in the cake, otherwise def value
         */
        const std::any& at(const std::string_view key, const std::any& def = {}) const noexcept
        {
            return m_self.contains(key.data()) ? m_self.at(key.data()) : def;
        }

    private:
        std::unordered_map<std::string, std::any> m_self;
    };

} // namespace own::endpoint

#endif
