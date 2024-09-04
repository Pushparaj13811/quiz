#ifndef QUIZ_CONTROLLER_HPP
#define QUIZ_CONTROLLER_HPP

#include <string>
#include <vector>
#include "models/quiz.hpp"

class QuizController
{
public:
    // Constructor
    QuizController();

    // Destructor
    ~QuizController();

    // Create a new quiz
    bool createQuiz(const Quiz &quiz);

    // Retrieve a quiz by ID
    Quiz getQuizById(const std::string &id) const;

    // List all quizzes
    std::vector<Quiz> listQuizzes() const;

    // Update an existing quiz
    bool updateQuiz(const std::string &id, const Quiz &quiz);

    // Delete a quiz by ID
    bool deleteQuiz(const std::string &id);

private:
    // Helper methods for database operations
    void connectToDatabase();

    // Database connection
    mongocxx::client *client_;
    mongocxx::database db_;
};

#endif // QUIZ_CONTROLLER_HPP
