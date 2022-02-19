/**
 * @file entry.cpp
 * @brief The entrypoint, where the main function lives
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#include <own/endpoint/endpoint.h>
#include <own/generic/support.h>

int main(const int argc, const char** argv) noexcept
{
    try
    {
        const auto [address, port, threads] =
            own::endpoint::parseOptions("hello_world", "Serves the endpoint", argc, argv);

        own::endpoint::serveOn(address, port, threads);
    }
    catch (const std::exception& e)
    {
    }
}
