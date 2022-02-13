/**
 * @file own/db/base/details.h
 * @brief Implementation details.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_DB_BASE_DETAILS_INCLUDED
#define OWN_DB_BASE_DETAILS_INCLUDED

#include <external/fmt/all.h>
#include <own/generic/types.h>

namespace own::db::base::details
{
    /** Deduce the type of an @c any object and return its SQL expression
     *
     * @param obj is the @c any object
     * @returns the "SQL-encoded" string
     */
    [[nodiscard]] inline std::string toSqlEncodedString(const std::any& obj)
    {
        /// Represents the @c NULL value
        static constexpr std::string_view k_NullValue { "NULL" };

        /// Represents a quoted string
        static constexpr std::string_view k_Quoted { "\'{}\'" };

        if (obj.type() == typeid(void))
        {
            return k_NullValue.data();
        }

        if (obj.type() == typeid(int8_t))
        {
            return std::to_string(std::any_cast<int8_t>(obj));
        }

        if (obj.type() == typeid(int16_t))
        {
            return std::to_string(std::any_cast<int16_t>(obj));
        }

        if (obj.type() == typeid(int32_t))
        {
            return std::to_string(std::any_cast<int32_t>(obj));
        }

        if (obj.type() == typeid(int64_t))
        {
            return std::to_string(std::any_cast<int64_t>(obj));
        }

        if (obj.type() == typeid(uint8_t))
        {
            return std::to_string(std::any_cast<uint8_t>(obj));
        }

        if (obj.type() == typeid(uint16_t))
        {
            return std::to_string(std::any_cast<uint16_t>(obj));
        }

        if (obj.type() == typeid(uint32_t))
        {
            return std::to_string(std::any_cast<uint32_t>(obj));
        }

        if (obj.type() == typeid(uint64_t))
        {
            return std::to_string(std::any_cast<uint64_t>(obj));
        }

        if (obj.type() == typeid(float))
        {
            return std::to_string(std::any_cast<float>(obj));
        }

        if (obj.type() == typeid(double))
        {
            return std::to_string(std::any_cast<double>(obj));
        }

        if (obj.type() == typeid(std::string))
        {
            return fmt::format(k_Quoted, std::any_cast<const std::string&>(obj));
        }

        if (obj.type() == typeid(std::string_view))
        {
            return fmt::format(k_Quoted, std::any_cast<std::string_view>(obj));
        }

        if (obj.type() == typeid(const char*))
        {
            return fmt::format(k_Quoted, std::any_cast<const char*>(obj));
        }

        throw std::runtime_error { "`obj' cannot be SQL encoded." };
    }

} // namespace own::db::base::details

#endif
