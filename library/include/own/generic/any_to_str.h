/**
 * @file own/generic/any_to_str.h
 * @brief A `to_string` function for `std::any`
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#ifndef GENERIC_ANY_TO_STRING_INCLUDED
#define GENERIC_ANY_TO_STRING_INCLUDED

#include <own/generic/types.h>

/**
 * @namespace own
 *
 * In most cases these are some supplementary functions that
 * makes the development easier
 */
namespace own
{

    /** Cast whatever an `any` object holds to `string`
     *
     * @param obj is an `any` object
     *
     * @returns string representation of `obj`
     * @todo Can we make this more elegant?
     */
    inline std::string toString(const std::any& obj)
    {
        if (!obj.has_value())
        {
            return "NULL";
        }

        if (obj.type() == typeid(bool))
        {
            return std::any_cast<bool>(obj) ? "TRUE" : "FALSE";
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

        if (obj.type() == typeid(float))
        {
            return std::to_string(std::any_cast<float>(obj));
        }

        if (obj.type() == typeid(double))
        {
            return std::to_string(std::any_cast<double>(obj));
        }

        if (obj.type() == typeid(const char*))
        {
            return std::any_cast<const char*>(obj);
        }

        if (obj.type() == typeid(std::string_view))
        {
            return std::any_cast<std::string_view>(obj).data();
        }

        if (obj.type() == typeid(std::string))
        {
            return std::any_cast<std::string>(obj);
        }

        throw std::runtime_error { "`obj` cannot be casted to literal type." };
    }

} // namespace own

#endif
