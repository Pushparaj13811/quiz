#include "user_controller.hpp"
#include <bsoncxx/json.hpp>
#include <bsoncxx/oid.hpp>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <cpprest/uri_builder.h>
#include <cpprest/async.h>
#include <iostream>

// Constructor
UserController::UserController(Database &db) : db_(db) {}

// Get all users
void UserController::getAllUsers(const httplib::Request &req, httplib::Response &res)
{
    try
    {
        auto collection = db_.getDatabase()["users"];
        auto cursor = collection.find({});
        web::json::value jsonArray = web::json::value::array();

        size_t index = 0;
        for (auto &&doc : cursor)
        {
            jsonArray[index++] = web::json::value::parse(bsoncxx::to_json(doc).c_str());
        }

        res.set_content(jsonArray.serialize(), "application/json");
    }
    catch (const std::exception &e)
    {
        res.status = 500;
        res.set_content("Error fetching users: " + std::string(e.what()), "text/plain");
    }
}

// Create a new user
void UserController::createUser(const httplib::Request &req, httplib::Response &res)
{
    try
    {
        web::json::value jsonValue = web::json::value::parse(req.body);
        bsoncxx::document::value docValue = bsoncxx::from_json(jsonValue.serialize());

        auto collection = db_.getDatabase()["users"];
        collection.insert_one(docValue.view());

        res.status = 201;
        res.set_content("User created successfully", "text/plain");
    }
    catch (const std::exception &e)
    {
        res.status = 400;
        res.set_content("Error creating user: " + std::string(e.what()), "text/plain");
    }
}

// Get a user by ID
void UserController::getUserById(const httplib::Request &req, httplib::Response &res)
{
    try
    {
        auto collection = db_.getDatabase()["users"];
        auto doc = collection.find_one(bsoncxx::oid(req.matches[1]).view());

        if (doc)
        {
            res.set_content(bsoncxx::to_json(doc.value()), "application/json");
        }
        else
        {
            res.status = 404;
            res.set_content("User not found", "text/plain");
        }
    }
    catch (const std::exception &e)
    {
        res.status = 500;
        res.set_content("Error fetching user: " + std::string(e.what()), "text/plain");
    }
}

// Update a user by ID
void UserController::updateUser(const httplib::Request &req, httplib::Response &res)
{
    try
    {
        web::json::value jsonValue = web::json::value::parse(req.body);
        bsoncxx::document::value updateValue = bsoncxx::from_json(jsonValue.serialize());

        auto collection = db_.getDatabase()["users"];
        auto result = collection.update_one(
            bsoncxx::oid(req.matches[1]).view(),
            bsoncxx::builder::stream::document{} << "$set" << updateValue.view() << bsoncxx::builder::stream::finalize);

        if (result->modified_count() > 0)
        {
            res.set_content("User updated successfully", "text/plain");
        }
        else
        {
            res.status = 404;
            res.set_content("User not found", "text/plain");
        }
    }
    catch (const std::exception &e)
    {
        res.status = 400;
        res.set_content("Error updating user: " + std::string(e.what()), "text/plain");
    }
}

// Delete a user by ID
void UserController::deleteUser(const httplib::Request &req, httplib::Response &res)
{
    try
    {
        auto collection = db_.getDatabase()["users"];
        auto result = collection.delete_one(bsoncxx::oid(req.matches[1]).view());

        if (result->deleted_count() > 0)
        {
            res.set_content("User deleted successfully", "text/plain");
        }
        else
        {
            res.status = 404;
            res.set_content("User not found", "text/plain");
        }
    }
    catch (const std::exception &e)
    {
        res.status = 500;
        res.set_content("Error deleting user: " + std::string(e.what()), "text/plain");
    }
}
