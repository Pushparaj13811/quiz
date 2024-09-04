#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <string>
#include <vector>
#include "models/user.hpp"

class UserController
{
public:
    // Constructor
    UserController();

    // Destructor
    ~UserController();

    // Create a new user
    bool createUser(const User &user);

    // Retrieve a user by ID
    User getUserById(const std::string &id) const;

    // List all users
    std::vector<User> listUsers() const;

    // Update an existing user
    bool updateUser(const std::string &id, const User &user);

    // Delete a user by ID
    bool deleteUser(const std::string &id);

private:
    // Helper methods for database operations
    void connectToDatabase();

    // Database connection
    mongocxx::client *client_;
    mongocxx::database db_;
};

#endif // USER_CONTROLLER_HPP
