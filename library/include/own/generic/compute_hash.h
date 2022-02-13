/**
 * @file own/generic/compute_hash.h
 * @brief Compute hash.
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_GENERIC_COMPUTE_HASH_INCLUDED
#define OWN_GENERIC_COMPUTE_HASH_INCLUDED

#include <external/cryptopp/hash.h>
#include <own/generic/types.h>

/**
 * @namespace own
 *
 * In this unit, some self-made OpenSSL C++ bindings were introduced such
 * that they are capable of C++'s std containers... you get the point.
 */
namespace own
{

    /** Compute hash
     *
     * @tparam Hasher is the hasher class from Crypto++
     * @param rawMessage is the message to be hashed
     * @returns the hashed message
     *
     * @todo Consider replace this cryptopp...
     */
    template <typename Hasher>
    [[nodiscard]] std::string computeHash(const std::string_view rawMessage) noexcept
    {
        std::string output;
        auto sink = std::make_unique<CryptoPP::StringSink>(output);

        Hasher hasher;
        std::array<CryptoPP::byte, Hasher::DIGESTSIZE> digest {};
        hasher.CalculateDigest(
            // NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
            digest.data(), reinterpret_cast<const CryptoPP::byte*>(rawMessage.data()),
            rawMessage.size());

        CryptoPP::HexEncoder encoder;
        encoder.Attach(sink.get());
        encoder.Put(digest.data(), sizeof(digest));
        encoder.MessageEnd();

        return pystring::lower(output);
    }

    /** Compute MD5 hash
     *
     * @param rawMessage is the message to be hashed
     * @returns the hashed message
     */
    [[nodiscard]] inline auto computeMd5Hash(const std::string_view rawMessage) noexcept
    {
        return computeHash<CryptoPP::Weak::MD5>(rawMessage);
    }

} // namespace own

#endif
