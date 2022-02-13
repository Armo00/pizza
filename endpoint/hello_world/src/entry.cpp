/**
 * @file entry.cpp
 * @brief The entrypoint, where the main function lives
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#include <external/fmt/all.h>
#include <own/endpoint/endpoint.h>
#include <own/generic/types.h>

int main(const int argc, const char** argv)
{
    const auto result
        = own::endpoint::parseOptions("hello_world", "Serves the endpoint", argc, argv);

    own::endpoint::serveOn(result["address"].as<std::string>(), result["port"].as<uint16_t>(),
                           result["threads"].as<int>());
}
