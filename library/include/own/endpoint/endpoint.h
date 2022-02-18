/**
 * @file own/endpoint/endpoint.h
 * @brief The Endpoint
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#pragma once

#include <external/cxxopts/all.h>
#include <own/endpoint/details.h>
#include <own/endpoint/handler.h>
#include <own/generic/support.h>
#include <own/logging/logging.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>

/**
 * @namespace own::endpoint
 */
namespace own::endpoint
{

/**
 * The Endpoint
 *
 * The Endpoint is where all endpoints get stored and registered, and sets up REST path for getting
 * invoked with HTTP requests
 *
 * This class also manages the Pistache HTTP endpoint object which runs the HTTP server
 */
class Endpoint final
{
    SINGLETON_CLASS(Endpoint)

   public:
    /** Add handler to endpoint
     *
     * @tparam Handler is the handler class
     * @returns the name of the handler added
     */
    template <typename Handler>
    [[nodiscard]] std::string_view addHandler() noexcept
    {
        auto handler = std::make_unique<Handler>();
        for (const auto& [method, path] : Handler::k_Api)
        {
            m_logger.debug("Registering {} on {} {}", Handler::k_Name,
                           magic_enum::enum_name(method), path);

            details::addHandler(m_router, *handler, method, path);
        }

        m_self.emplace_back(std::move(handler));
        return Handler::k_Name;
    }

    /** Serve the endpoint
     *
     * @param ip is the IP address on which the server listens on
     * @param port is the port on which the server listens on
     * @param threads means how many threads to open
     */
    void serveOn(const std::string_view ip, const uint16_t port, const int threads) noexcept
    {
        const Pistache::Address address{ip.data(), port};
        Pistache::Http::Endpoint endpoint{address};

        const auto options = Pistache::Http::Endpoint::options().threads(threads);
        endpoint.init(options);
        endpoint.setHandler(m_router.handler());

        m_logger.info("Serving on {}:{} with {} threads", ip, port, threads);
        endpoint.serve();
    }

   private:
    /// The Logger
    own::logging::Logger m_logger{"endpoint"};

    /// The Endpoint itself
    std::vector<std::unique_ptr<Handler>> m_self;

    /// The Pistache REST Router
    Pistache::Rest::Router m_router;
};

/** Add handler to endpoint
 *
 * @tparam Handler is the handler class
 * @returns the name of the handler added
 */
template <typename Handler>
[[nodiscard]] std::string_view addHandler() noexcept
{
    auto& endpoint = Endpoint::getEndpoint();
    return endpoint.addHandler<Handler>();
}

/** Serve the endpoint
 *
 * @param ip is the IP address on which the server listens on
 * @param port is the port on which the server listens on
 * @param threads means how many threads to open
 */
inline void serveOn(const std::string_view ip, const uint16_t port, const int threads) noexcept
{
    auto& endpoint = Endpoint::getEndpoint();
    endpoint.serveOn(ip, port, threads);
}

/** Parse command-line options
 *
 * @param endpointName is the name of the endpoint
 * @param endpointDescription is the description of the endpoint
 * @param mainArgc is the arguments count passed from main
 * @param mainArgv is the arguments vector passed from main
 *
 * @returns the parsed options
 */
[[nodiscard]] inline auto parseOptions(const std::string_view endpointName,
                                       const std::string_view endpointDescription,
                                       const int mainArgc, const char** mainArgv) noexcept
{
    cxxopts::Options options{endpointName.data(), endpointDescription.data()};
    {
        // clang-format off
        options.add_options()
            ("address", "Address to listen", cxxopts::value<std::string>()->default_value("127.0.0.1"))
            ("port", "Port to listen", cxxopts::value<uint16_t>()->default_value("8080"))
            ("threads", "Threads to serve", cxxopts::value<int>()->default_value("32"))
            ("help", "Print usage");
        // clang-format on
    }
    try
    {
        const auto result = options.parse(mainArgc, mainArgv);
        if (result.count("help") == 0)
        {
            return std::make_tuple(result["address"].as<std::string>(),
                                   result["port"].as<uint16_t>(), result["threads"].as<int>());
        }
        fmt::print(stdout, "\n{}\n", options.help());
        std::exit(0);  // NOLINT(concurrency-mt-unsafe)
    }
    catch (const cxxopts::option_not_exists_exception& e)
    {
        own::logging::fatal("endpoint", e.what());
        fmt::print(stderr, "\n{}\n", options.help());
        std::exit(1);  // NOLINT(concurrency-mt-unsafe)
    }
}

}  // namespace own::endpoint
