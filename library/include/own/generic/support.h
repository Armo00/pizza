/**
 * @file own/generic/support.h
 * @brief Generic supports for creative coding.
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#ifndef GENERIC_SUPPORT_INCLUDED
#define GENERIC_SUPPORT_INCLUDED

#include <external/cppitertools/all.h>
#include <external/frozen/all.h>
#include <external/magic_enum/all.h>
#include <external/nlohmann_json/all.h>
#include <external/pystring/all.h>
#include <external/std/all.h>

#ifndef NOT_COPYABLE_CLASS
#define NOT_COPYABLE_CLASS(ClassName)     \
   public:                                \
    ClassName(const ClassName&) = delete; \
    ClassName operator=(const ClassName&) = delete;
#endif

#ifndef IMMOVEABLE_CLASS
#define IMMOVEABLE_CLASS(ClassName)        \
   public:                                 \
    ClassName(const ClassName&&) = delete; \
    ClassName operator=(const ClassName&&) = delete;
#endif

#ifndef NOT_COPYABLE_AND_IMMOVEABLE_CLASS
#define NOT_COPYABLE_AND_IMMOVEABLE_CLASS(ClassName) \
   public:                                           \
    NOT_COPYABLE_CLASS(ClassName)                    \
    IMMOVEABLE_CLASS(ClassName)
#endif

#ifndef DESTRUCTIBLE_BASE_CLASS
#define DESTRUCTIBLE_BASE_CLASS(ClassName)       \
   public:                                       \
    NOT_COPYABLE_AND_IMMOVEABLE_CLASS(ClassName) \
   public:                                       \
    virtual ~ClassName() noexcept = default;
#endif

#ifndef DESTRUCTIBLE_FINAL_CLASS
#define DESTRUCTIBLE_FINAL_CLASS(ClassName)      \
   public:                                       \
    NOT_COPYABLE_AND_IMMOVEABLE_CLASS(ClassName) \
   public:                                       \
    ~ClassName() noexcept = default;
#endif

#ifndef SINGLETON_CLASS
#define SINGLETON_CLASS(ClassName)                            \
   public:                                                    \
    [[nodiscard]] static ClassName& get##ClassName() noexcept \
    {                                                         \
        static ClassName obj;                                 \
        return obj;                                           \
    }                                                         \
                                                              \
   public:                                                    \
    NOT_COPYABLE_AND_IMMOVEABLE_CLASS(ClassName)              \
   private:                                                   \
    explicit ClassName() noexcept = default;                  \
    ~ClassName() noexcept = default;
#endif

#ifndef STATIC_CLASS
#define STATIC_CLASS(ClassName)                  \
   public:                                       \
    NOT_COPYABLE_AND_IMMOVEABLE_CLASS(ClassName) \
   private:                                      \
    explicit ClassName() noexcept = default;     \
    ~ClassName() noexcept = default;
#endif

#ifndef RUNTIME_ASSERT
#define RUNTIME_ASSERT(Statement)                                                                  \
    /* NOLINTNEXTLINE(hicpp-no-array-decay,cppcoreguidelines-pro-bounds-array-to-pointer-decay) */ \
    assert(Statement);
#endif

#endif
