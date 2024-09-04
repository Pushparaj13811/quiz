#include "user.hpp"
#include <bsoncxx/json.hpp>
#include <bsoncxx/oid.hpp>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <cpprest/uri_builder.h>
#include <cpprest/async.h>
#include <iostream>

// Constructor
User::User(const std::string& id, const std::string& username, const std::string& email)
    : id_(id), username_(username), email_(email) {}

// Getters
std::string User::getId() const {
    return id_;
}

std::string User::getUsername() const {
    return username_;
}

std::string User::getEmail() const {
    return email_;
}

// Setters
void User::setId(const std::string& id) {
    id_ = id;
}

void User::setUsername(const std::string& username) {
    username_ = username;
}

void User::setEmail(const std::string& email) {
    email_ = email;
}

// Convert to BSON
bsoncxx::document::value User::toBSON() const {
    bsoncxx::builder::stream::document document{};
    document << "username" << username_;
    document << "email" << email_;
    return document << bsoncxx::builder::stream::finalize;
}

// Convert from BSON
User User::fromBSON(const bsoncxx::document::view& doc) {
    std::string username;
    std::string email;

    if (doc.find("username") != doc.end()) {
        username = doc["username"].get_utf8().value.to_string();
    }

    if (doc.find("email") != doc.end()) {
        email = doc["email"].get_utf8().value.to_string();
    }

    // Assume that the ID is not stored in the BSON and is set externally
    return User("", username, email);
}
