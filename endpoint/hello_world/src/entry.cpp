/**
 * @file entry.cpp
 * @brief The entrypoint, where the main function lives
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#include <external/cxxopts/all.h>
#include <own/endpoint/endpoint.h>
#include <own/generic/types.h>

int main(const int argc, const char** argv)
{
    cxxopts::Options options { "hello_world", "Serves the endpoint." };
    options.add_options()("a,address", "Address to listen",
                          cxxopts::value<std::string>()->default_value("127.0.0.1"));
    options.add_options()("p,port", "Port to listen",
                          cxxopts::value<uint16_t>()->default_value("8080"));
    options.add_options()("t,threads", "Threads to serve",
                          cxxopts::value<int>()->default_value("32"));
    options.add_options()("h,help", "Print usage");

    auto result = options.parse(argc, argv);
    if (result.count("help"))
    {
        fprintf(stdout, "%s", options.help().data());
        return 0;
    }

    auto& endpoint = own::endpoint::Endpoint::getEndpoint();
    endpoint.serveOn(result["address"].as<std::string>(), result["port"].as<uint16_t>(),
                     result["threads"].as<int>());
}
