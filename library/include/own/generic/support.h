/**
 * @file own/generic/support.h
 * @brief Generic supports for creative coding.
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/cppitertools/all.h>
#include <external/fmt/all.h>
#include <external/frozen/all.h>
#include <external/magic_enum/all.h>
#include <external/nlohmann_json/all.h>
#include <external/pystring/all.h>
#include <external/std/all.h>

/// Represents a default moveable class
/// @private
#ifndef DEFAULT_MOVEABLE_CLASS
#define DEFAULT_MOVEABLE_CLASS(ClassName) \
   public:                                \
    ClassName(ClassName&&) = default;     \
    ClassName& operator=(ClassName&&) = default;
#endif

/// Represents a not copyable class
/// @private
#ifndef NOT_COPYABLE_CLASS
#define NOT_COPYABLE_CLASS(ClassName)     \
   public:                                \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete;
#endif

/// Represents a immoveable class
/// @private
#ifndef IMMOVEABLE_CLASS
#define IMMOVEABLE_CLASS(ClassName)  \
   public:                           \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete;
#endif

/// Represents a default moveable final class
/// Most likely it would be a value class
#ifndef DEFAULT_MOVEABLE_FINAL_CLASS
#define DEFAULT_MOVEABLE_FINAL_CLASS(ClassName) \
    NOT_COPYABLE_CLASS(ClassName)               \
    DEFAULT_MOVEABLE_CLASS(ClassName)           \
                                                \
   public:                                      \
    ~ClassName() noexcept = default;
#endif

/// Represents a default destructible final class
/// Not copyable, immoveable, not deriveable (aka interface class)
#ifndef DEFAULT_DESTRUCTIBLE_FINAL_CLASS
#define DEFAULT_DESTRUCTIBLE_FINAL_CLASS(ClassName) \
    NOT_COPYABLE_CLASS(ClassName)                   \
    IMMOVEABLE_CLASS(ClassName)                     \
                                                    \
   public:                                          \
    ~ClassName() noexcept = default;
#endif

/// Represents a default destructible base class
/// Not copyable, immoveable, but deriveable (aka interface class)
#ifndef DEFAULT_DESTRUCTIBLE_BASE_CLASS
#define DEFAULT_DESTRUCTIBLE_BASE_CLASS(ClassName) \
    NOT_COPYABLE_CLASS(ClassName)                  \
    IMMOVEABLE_CLASS(ClassName)                    \
                                                   \
   public:                                         \
    virtual ~ClassName() noexcept = default;
#endif

/// Represents a singleton class
/// You can only get the instance through its static getter
#ifndef SINGLETON_CLASS
#define SINGLETON_CLASS(ClassName)                            \
    NOT_COPYABLE_CLASS(ClassName)                             \
    IMMOVEABLE_CLASS(ClassName)                               \
                                                              \
   public:                                                    \
    [[nodiscard]] static ClassName& get##ClassName() noexcept \
    {                                                         \
        static ClassName obj;                                 \
        return obj;                                           \
    }                                                         \
                                                              \
   private:                                                   \
    explicit ClassName() noexcept = default;                  \
    ~ClassName() noexcept = default;
#endif

/// Represents a static class
/// Not constructible, everything inside are static
#ifndef STATIC_CLASS
#define STATIC_CLASS(ClassName)             \
    NOT_COPYABLE_CLASS(ClassName)           \
    IMMOVEABLE_CLASS(ClassName)             \
                                            \
   public:                                  \
    explicit ClassName() noexcept = delete; \
    ~ClassName() noexcept = delete;
#endif

/// Represents the good-old runtime assert
/// At least it tries not to piss off the linter
#ifndef RUNTIME_ASSERT
#define RUNTIME_ASSERT(statement)                                                                  \
    /* NOLINTNEXTLINE(hicpp-no-array-decay,cppcoreguidelines-pro-bounds-array-to-pointer-decay) */ \
    assert(static_cast<bool>(statement)); /* NOLINT(cert-dcl03-c,hicpp-static-assert) */
#endif
