/**
 * @file own/endpoint/endpoint.h
 * @brief The Endpoint
 * @copyright Copyleft 2022 "unrealinsanity". All rights reversed.
 */

#ifndef OWN_ENDPOINT_PISTACHE_INCLUDED
#define OWN_ENDPOINT_PISTACHE_INCLUDED

#include <own/endpoint/details.h>
#include <own/endpoint/handler.h>
#include <own/generic/types.h>
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
    public:
        /** Get endpoint
         *
         * @returns endpoint
         */
        static auto& getEndpoint() noexcept
        {
            static Endpoint endpoint;

            return endpoint;
        }

        /** Add handler to endpoint
         *
         * @returns the name of the handler added
         */
        template <typename HandlerType>
        auto addHandler() noexcept
        {
            auto handler = std::make_unique<HandlerType>();
            for (const auto& [method, path] : HandlerType::k_Api)
            {
                m_logger.debug("Registering {} on {} {}", HandlerType::k_Name,
                               magic_enum::enum_name(method), path);

                details::addHandler(m_router, *handler, method, path, m_logger);
            }

            m_registry.emplace_back(std::move(handler));
            return HandlerType::k_Name;
        }

        /** Serve the endpoint
         *
         * @param ip is the IP address on which the server listens on
         * @param port is the port on which the server listens on
         * @param threads means how many threads to open
         */
        void serveOn(const std::string_view ip, const uint16_t port, const int threads)
        {
            const Pistache::Address address { ip.data(), port };
            m_self = std::make_unique<Pistache::Http::Endpoint>(address);

            const auto options = Pistache::Http::Endpoint::options().threads(threads);
            m_self->init(options);
            m_self->setHandler(m_router.handler());

            m_logger.info("Serving on {}:{} with {} threads", ip, port, threads);
            m_self->serve();
        }

    private:
        explicit Endpoint() noexcept = default;

        /// The logger
        own::logging::Logger m_logger { "endpoint" };

        /// The registry itself
        std::vector<std::unique_ptr<Handler>> m_registry;

        /// The Pistache router
        Pistache::Rest::Router m_router;

        /// The Pistache HTTP handler
        std::unique_ptr<Pistache::Http::Endpoint> m_self;
    };

} // namespace own::endpoint

#endif
