//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_EXCEPTIONS_H
#define TRENCH_COATS_APP_EXCEPTIONS_H

#include <exception>
#include <string>
#include <vector>

class ValidationException: public std::exception {
private:
    std::vector<std::string> errors;
    std::string message;
public:
    ValidationException(const std::vector<std::string>& errors) : errors(errors) {
        for (const auto& error : errors) {
            this->message += error + "\n";
        }
    }
    const char* what() const noexcept override {
        return this->message.c_str();
    }
};

class RepositoryException: public std::exception {
private:
    std::string message;
public:
    RepositoryException(const std::string& message) : message(message) {}
    const char* what() const noexcept override {
        return this->message.c_str();
    }
};

#endif //TRENCH_COATS_APP_EXCEPTIONS_H
