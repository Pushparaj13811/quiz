#include "database.hpp"
#include <bsoncxx/json.hpp>
#include <iostream>

// Constructor
Database::Database(const std::string& uri, const std::string& dbName) : uri_(uri), dbName_(dbName) {
    try {
        // Create a MongoDB client
        mongoClient_ = mongocxx::client{mongocxx::uri{uri_}};
        // Access the database
        database_ = mongoClient_[dbName_];
        std::cout << "Connected to MongoDB at " << uri_ << " and database " << dbName_ << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect to MongoDB: " << e.what() << std::endl;
        throw;
    }
}

// Get database instance
mongocxx::database Database::getDatabase() const {
    return database_;
}
