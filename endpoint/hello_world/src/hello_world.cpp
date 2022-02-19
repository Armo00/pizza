/**
 * @file hello_world.cpp
 * @brief Hello, World
 * @copyright Copyleft 2021-2022 "unrealinsanity". All rights reversed.
 */

#include <external/cpr/all.h>
#include <own/endpoint/endpoint.h>
#include <own/endpoint/handler.h>
#include <own/generic/support.h>

namespace
{

class HelloHandler : public own::endpoint::Handler
{
   public:
    static constexpr std::string_view k_Name = "hello";

    static constexpr auto k_Api = std::to_array<ApiDesc>({
        {Request::Method::Get,  "/hello"},
        {Request::Method::Post, "/hello"},
    });

    explicit HelloHandler() : Handler{k_Name} {}

    void validateRequest(const Request& request, Cake& cake) const override
    {
        switch (request.getMethod())
        {
            case Request::Method::Get:
            {
                m_logger.info("It works!");
                return;
            }
            case Request::Method::Post:
            {
                m_logger.info(request.getBody());
                cake.emplace("message", "Handler for POST requests is not implemented!");
                throw ErrorResponse{Response::Code::Method_Not_Allowed, cake};
            }
            default:
            {
                throw ErrorResponse{Response::Code::Bad_Request, "Invalid request method."};
            }
        }
    }

    void processRequest(const Request& /* unused */, Cake& cake) const override
    {
        static constexpr std::string_view k_Destination{"/data/result.html"};
        {
            const auto responseText = downloadSomething();
            std::ofstream fileStream{k_Destination.data()};
            fileStream << responseText;
        }

        // Use cake to pass states to the next phase
        cake.emplace("download_path", k_Destination);
        cake.emplace("time_stamp", std::time(nullptr));
        m_logger.debug("Content of cake is {}", cake.dump());
    }

    void sendResponse(const Cake& cake, Response& response) const override
    {
        response.send(Response::Code::Ok, cake);

        const auto& downloadPath = cake.at<std::string>("download_path");
        m_logger.info("File successfully stored to {} on server", downloadPath);
    }

   private:
    [[nodiscard]] static std::string downloadSomething()
    {
        const auto response = cpr::Get(cpr::Url{"http://pistache.io/"});
        return response.text;
    }
};

// Let the endpoint be aware of the existence of this handler, and
// thereby be able to serve it
const auto handlerName = own::endpoint::addHandler<HelloHandler>();

}  // namespace
