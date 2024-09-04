#ifndef USER_HPP
#define USER_HPP

#include <string>

// Define a class for a User model
class User
{
public:
    // Default constructor
    User();

    // Parameterized constructor
    User(const std::string &id, const std::string &name, const std::string &email, const std::string &password);

    // Getters and Setters
    std::string getId() const;
    void setId(const std::string &id);

    std::string getName() const;
    void setName(const std::string &name);

    std::string getEmail() const;
    void setEmail(const std::string &email);

    std::string getPassword() const;
    void setPassword(const std::string &password);

private:
    std::string id_;       // Unique identifier for the user
    std::string name_;     // Name of the user
    std::string email_;    // Email address of the user
    std::string password_; // Password of the user
};

#endif // USER_HPP
