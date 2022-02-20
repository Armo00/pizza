/**
 * @file hello_world.cpp
 * @brief Hello, World
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#include <pizza/generic/hash.h>
#include <pizza/log/logger.h>

int main() noexcept
{
    static constexpr std::string_view k_HelloOpenSsl{"Hello, OpenSSL"};

    pizza::log::Logger logger{"hash_test"};
    logger.info("md5sum of '{}' is {}", k_HelloOpenSsl,
                pizza::hash::computeMd5Hash(k_HelloOpenSsl));

    logger.info("sha256sum of '{}' is {}", k_HelloOpenSsl,
                pizza::hash::computeSha256Hash(k_HelloOpenSsl));
}
