#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/database.hpp>
#include <bsoncxx/json.hpp>
#include <string>

class Database {
public:
    // Constructor
    Database(const std::string& uri, const std::string& db_name);

    // Destructor
    ~Database();

    // Connect to the MongoDB database
    void connect();

    // Get the database object
    mongocxx::database getDatabase() const;

private:
    // MongoDB client instance
    mongocxx::client* client_;

    // MongoDB database
    mongocxx::database db_;

    // MongoDB URI and database name
    std::string uri_;
    std::string db_name_;
};

#endif // DATABASE_HPP
