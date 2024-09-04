#include "quiz.hpp"
#include <bsoncxx/json.hpp>
#include <bsoncxx/oid.hpp>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <cpprest/uri_builder.h>
#include <cpprest/async.h>
#include <iostream>

// Constructor
Quiz::Quiz(const std::string &id, const std::string &name, const std::vector<std::string> &questions)
    : id_(id), name_(name), questions_(questions) {}

// Getters
std::string Quiz::getId() const
{
    return id_;
}

std::string Quiz::getName() const
{
    return name_;
}

std::vector<std::string> Quiz::getQuestions() const
{
    return questions_;
}

// Setters
void Quiz::setId(const std::string &id)
{
    id_ = id;
}

void Quiz::setName(const std::string &name)
{
    name_ = name;
}

void Quiz::setQuestions(const std::vector<std::string> &questions)
{
    questions_ = questions;
}

// Convert to BSON
bsoncxx::document::value Quiz::toBSON() const
{
    bsoncxx::builder::stream::document document{};
    document << "name" << name_;
    document << "questions" << bsoncxx::builder::stream::open_array;
    for (const auto &question : questions_)
    {
        document << question;
    }
    document << bsoncxx::builder::stream::close_array;
    return document << bsoncxx::builder::stream::finalize;
}

// Convert from BSON
Quiz Quiz::fromBSON(const bsoncxx::document::view &doc)
{
    std::string name;
    std::vector<std::string> questions;

    if (doc.find("name") != doc.end())
    {
        name = doc["name"].get_utf8().value.to_string();
    }

    if (doc.find("questions") != doc.end())
    {
        for (auto &&element : doc["questions"].get_array().value)
        {
            questions.push_back(element.get_utf8().value.to_string());
        }
    }

    // Assume that the ID is not stored in the BSON and is set externally
    return Quiz("", name, questions);
}
