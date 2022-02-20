/**
 * @file entry.cpp
 * @brief The entrypoint, where the main function lives
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#include <pizza/endpoint/endpoint.h>
#include <pizza/generic/support.h>

int main(const int argc, const char** argv) noexcept
{
    const auto [address, port, threads] =
        pizza::endpoint::parseOptions("hello_world", "Serves the endpoint", argc, argv);

    pizza::endpoint::serveOn(address, port, threads);
}
