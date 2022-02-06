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
     *
     * @param hasher is the hasher from Crypto++
     * @param digestSize is the length of hash digest
     * @param rawMessage is the message to be hashed
     *
     * @returns the hashed message
     */
    template <typename Hasher>
    auto computeHash(const std::string_view rawMessage)
    {
        Hasher hasher;
        CryptoPP::byte digest[Hasher::DIGESTSIZE];
        hasher.CalculateDigest(digest, (const CryptoPP::byte*)rawMessage.data(), rawMessage.size());

        CryptoPP::HexEncoder encoder;
        std::string output;

        encoder.Attach(new CryptoPP::StringSink(output));
        encoder.Put(digest, sizeof(digest));
        encoder.MessageEnd();

        return pystring::lower(output);
    }

    /** Compute MD5 hash
     *
     * @param rawMessage is the message to be hashed
     * @returns the hashed message
     */
    inline auto computeMd5Hash(const std::string_view rawMessage)
    {
        return computeHash<CryptoPP::Weak::MD5>(rawMessage);
    }

} // namespace own

#endif
