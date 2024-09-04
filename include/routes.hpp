#ifndef ROUTES_HPP
#define ROUTES_HPP

#include <httplib.h>
#include "user_controller.hpp"
#include "quiz_controller.hpp"

class Routes {
public:
    // Constructor
    Routes();

    // Set up the routes for the application
    void setupRoutes(httplib::Server& server);

private:
    UserController user_controller_;
    QuizController quiz_controller_;
};

#endif // ROUTES_HPP
