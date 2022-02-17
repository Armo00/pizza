/**
 * @file own/endpoint/endpoint.h
 * @brief The Endpoint
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_ENDPOINT_PISTACHE_INCLUDED
#define OWN_ENDPOINT_PISTACHE_INCLUDED

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
 * This singleton instance class is where all endpoints get stored and registered, and
 * set up REST path for getting invoked with HTTP requests
 *
 * This class also manages the HTTP endpoint object which runs the HTTP server
 */
class Endpoint final
{
    SINGLETON_CLASS(Endpoint)

   public:
    /** Add handler to endpoint
     *
     * @tparam MyHandler is the handler class
     * @returns the name of the handler added
     */
    template <typename MyHandler>
    [[nodiscard]] std::string_view addHandler() noexcept
    {
        auto handler = std::make_unique<MyHandler>();
        for (const auto& [method, path] : MyHandler::k_Api)
        {
            m_logger.debug("Registering {} on {} {}", MyHandler::k_Name,
                           magic_enum::enum_name(method), path);

            details::addHandler(m_router, *handler, method, path);
        }

        m_registry.emplace_back(std::move(handler));
        return MyHandler::k_Name;
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
        m_self = std::make_unique<Pistache::Http::Endpoint>(address);

        const auto options = Pistache::Http::Endpoint::options().threads(threads);
        m_self->init(options);
        m_self->setHandler(m_router.handler());

        m_logger.info("Serving on {}:{} with {} threads", ip, port, threads);
        m_self->serve();
    }

   private:
    /// The Logger
    own::logging::Logger m_logger{"endpoint"};

    /// The Registry for Handlers
    std::vector<std::unique_ptr<Handler>> m_registry;

    /// The Pistache REST Router
    Pistache::Rest::Router m_router;

    /// The Pistache HTTP Endpoint
    std::unique_ptr<Pistache::Http::Endpoint> m_self;
};

/** Add handler to endpoint
 *
 * @tparam MyHandler is the handler class
 * @returns the name of the handler added
 */
template <typename MyHandler>
[[nodiscard]] std::string_view addHandler() noexcept
{
    auto& endpoint = Endpoint::getEndpoint();
    return endpoint.addHandler<MyHandler>();
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
    options.add_options()("address", "Address to listen",
                          cxxopts::value<std::string>()->default_value("127.0.0.1"));
    options.add_options()("port", "Port to listen",
                          cxxopts::value<uint16_t>()->default_value("8080"));
    options.add_options()("threads", "Threads to serve",
                          cxxopts::value<int>()->default_value("32"));
    options.add_options()("help", "Print usage");

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
        fmt::print(stdout, "\n{}\n", options.help());
        std::exit(1);  // NOLINT(concurrency-mt-unsafe)
    }
}

}  // namespace own::endpoint

#endif
