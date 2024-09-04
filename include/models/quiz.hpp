#ifndef QUIZ_HPP
#define QUIZ_HPP

#include <string>
#include <vector>

// Define a structure for a question in a quiz
struct Question {
    std::string question;         // The question text
    std::vector<std::string> options;  // Possible answers
    std::string answer;           // Correct answer
};

// Define a class for a Quiz model
class Quiz {
public:
    // Default constructor
    Quiz();

    // Parameterized constructor
    Quiz(const std::string& id, const std::string& title, const std::vector<Question>& questions);

    // Getters and Setters
    std::string getId() const;
    void setId(const std::string& id);

    std::string getTitle() const;
    void setTitle(const std::string& title);

    std::vector<Question> getQuestions() const;
    void setQuestions(const std::vector<Question>& questions);

private:
    std::string id_;              // Unique identifier for the quiz
    std::string title_;           // Title of the quiz
    std::vector<Question> questions_;  // List of questions in the quiz
};

#endif // QUIZ_HPP
