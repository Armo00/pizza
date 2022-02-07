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
         * @param values are the data to bind
         */
        explicit Values(const std::vector<std::any>&& values)
            : m_self { std::move(values) }
        { }

        /** The read-only @c at method
         *
         * @tparam ValueType is the value type to cast
         * @param index is the index of values
         * @returns the value at @c index of values
         */
        template <typename ValueType>
        ValueType at(const size_t index) const
        {
            const auto value = m_self.at(index);
            return std::any_cast<ValueType>(value);
        }

    private:
        const std::vector<std::any> m_self;
    };

} // namespace own::db

#endif
