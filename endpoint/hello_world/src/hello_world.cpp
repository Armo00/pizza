/**
 * @file hello_world.cpp
 * @brief Hello, World
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#include <external/cpr/all.h>
#include <own/endpoint/endpoint.h>
#include <own/endpoint/handler.h>
#include <own/generic/types.h>

namespace
{

    class HelloHandler : public own::endpoint::Handler
    {
    public:
        static constexpr std::string_view k_Name = "hello";

        static constexpr auto k_Api = std::to_array<ApiDesc>({
            { Request::Method::Get, "/hello" },
            { Request::Method::Post, "/hello" },
        });

        explicit HelloHandler()
            : own::endpoint::Handler { k_Name }
        { }

        void validateRequest(const Request& request) const override
        {
            if (request.getMethod() == Request::Method::Get)
            {
                m_logger.info("It works!");
                return;
            }

            if (request.getMethod() == Request::Method::Post)
            {
                m_logger.info(request.getBody());
                return;
            }

            {
                throw std::runtime_error { "Invalid request method." };
            }
        }

        void processRequest(const Request& request, Cake& cake) const override
        {
            static constexpr std::string_view k_Destination = "/data/result.html";

            if (request.getMethod() == Request::Method::Get)
            {
                auto responseText = downloadSomething();
                std::ofstream fileStream { k_Destination.data() };
                fileStream << responseText;

                /// Use @c cake to pass states to the next phase
                cake.emplace("downloadPath", k_Destination);
            }
        }

        void sendResponse(const Cake& cake, Response& response) const override
        {
            const auto downloadPath = cake.at<std::string_view>("downloadPath");
            if (downloadPath.empty())
            {
                throw std::runtime_error { "Download failed." };
            }

            static constexpr std::string_view k_Body { "File successfully stored to {} on server" };
            response.send(Response::Code::Ok, k_Body, downloadPath);
            m_logger.info(k_Body, downloadPath);
            return;
        }

    private:
        std::string downloadSomething() const
        {
            static constexpr std::string_view k_Url = "http://pistache.io/";

            auto response = cpr::Get(cpr::Url { k_Url.data() });
            return response.text;
        }
    };

    // Let the endpoint be aware of the existence of this handler, and
    // thereby be able to serve it
    auto& endpoint         = own::endpoint::Endpoint::getEndpoint();
    const auto handlerName = endpoint.addHandler<HelloHandler>();

} // namespace
