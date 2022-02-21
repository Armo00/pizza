/**
 * @file pizza/hash.h
 * @brief Hashing with ease.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/openssl/hash.h>
#include <pizza/support.h>

namespace pizza::hash
{

/**
 * Packages together the hash functions
 *
 * This class is not meant to be constructed, but to hide some details
 */
class Hash final
{
    STATIC_CLASS(Hash)

   public:
    /// Indicates whether hashes should be lowercase or uppercase
    enum class NeedLowerCase : bool
    {
        No,  ///< Hash would be in lowercase
        Yes  ///< Hash would be in uppercase
    };

   private:
    /** Make printable hash from binary hash
     *
     * @param rawHash is the binary hash
     * @param needLower indicates if the output should be lower cased
     * @returns the printable hash
     */
    [[nodiscard]] static auto makePrintableHash(const std::span<const u_char> rawHash,
                                                const Hash::NeedLowerCase needLower)
    {
        std::string result;
        result.resize(rawHash.size() * 2);
        for (size_t index = 0; index < rawHash.size(); ++index)
        {
            sprintf(&result.at(index * 2), "%02x", rawHash[index]);
        }
        return (needLower == NeedLowerCase::Yes) ? pystring::lower(result)
                                                 : pystring::upper(result);
    }

   public:
    /** Compute MD5 hash
     *
     * @param message is the message to be hashed
     * @param needLower indicates if the output should be lower cased
     * @returns the hashed message
     */
    [[nodiscard]] static auto computeMd5Hash(const std::string_view message,
                                             const Hash::NeedLowerCase needLower) noexcept
    {
        std::vector<u_char> result;
        result.resize(MD5_DIGEST_LENGTH);

/// @todo Take other compiler extension into account
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        MD5(reinterpret_cast<const u_char* const>(message.data()), message.size(), result.data());
#pragma clang diagnostic pop

        return makePrintableHash(result, needLower);
    }

    /** Compute SHA256 hash
     *
     * @param message is the message to be hashed
     * @param needLower indicates if the output should be lower cased
     * @returns the hashed message
     */
    [[nodiscard]] static auto computeSha256Hash(const std::string_view message,
                                                const Hash::NeedLowerCase needLower) noexcept
    {
        std::vector<u_char> result;
        result.resize(SHA256_DIGEST_LENGTH);

        SHA256(reinterpret_cast<const u_char* const>(message.data()), message.size(),
               result.data());

        return makePrintableHash(result, needLower);
    }
};

/** Compute MD5 hash
 *
 * @param message is the message to be hashed
 * @param needLower indicates if the output should be lower cased
 * @returns the hashed message
 */
[[nodiscard]] inline auto computeMd5Hash(
    const std::string_view message,
    const Hash::NeedLowerCase needLower = Hash::NeedLowerCase::Yes) noexcept
{
    return Hash::computeMd5Hash(message, needLower);
}

/** Compute SHA256 hash
 *
 * @param message is the message to be hashed
 * @param needLower indicates if the output should be lower cased
 * @returns the hashed message
 */
[[nodiscard]] inline auto computeSha256Hash(
    const std::string_view message,
    const Hash::NeedLowerCase needLower = Hash::NeedLowerCase::Yes) noexcept
{
    return Hash::computeSha256Hash(message, needLower);
}

}  // namespace pizza::hash
