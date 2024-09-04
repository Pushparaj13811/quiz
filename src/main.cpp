#include <cpprest/uri.h>
#include <cpprest/uri_builder.h>
#include <cpprest/http_listener.h>
#include <cpprest/experimental/listener.h>
#include <cpprest/async.h>
#include <cpprest/streambuf.h>
#include <cpprest/dispatcher.h>
#include <cpprest/response_writer.h>
#include <cpprest/json.h>
#include <iostream>
#include <memory>
#include "routes.hpp"
#include "database.hpp"
#include "logger.hpp"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

// Global objects
std::unique_ptr<Logger> logger;
std::unique_ptr<Database> database;

// Function to initialize and start the HTTP server
void start_server(const std::string& address, const std::string& port) {
    uri_builder uri(address);
    auto addr = uri.to_uri().to_string();
    auto listener = std::make_shared<http_listener>(addr);

    // Set up the request handling
    listener->support(methods::GET, [](const http_request& request) {
        auto path = uri::split_path(uri::decode(request.relative_uri().path()));
        auto query = uri::split_query(uri::decode(request.relative_uri().query()));

        // Handle different routes
        if (path[0] == "quizzes") {
            // Handle quiz-related requests
            handle_quiz_request(request);
        } else if (path[0] == "users") {
            // Handle user-related requests
            handle_user_request(request);
        } else {
            json::value response_data;
            response_data[U("message")] = json::value::string("Not Found");
            request.reply(status_codes::NotFound, response_data);
        }
    });

    // Start the listener
    try {
        listener->open().then([&listener](){ 
            std::cout << "Starting to listen at: " << listener->uri().to_string() << std::endl; 
        }).wait();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred while starting the server: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    // Check arguments for address and port
    std::string address = "http://localhost";
    std::string port = "8080";

    if (argc > 1) {
        address = argv[1];
    }
    if (argc > 2) {
        port = argv[2];
    }

    // Initialize logger
    logger = std::make_unique<Logger>("app.log");

    // Initialize database
    try {
        database = std::make_unique<Database>("mongodb://localhost:27017", "quizDB");
    } catch (const std::exception& e) {
        logger->logError("Failed to initialize database: " + std::string(e.what()));
        return 1;
    }

    // Start the server
    start_server(address, port);

    return 0;
}
