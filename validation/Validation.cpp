//
// Created by Maria on 27/08/2026.
//

#include "Validation.h"
#include "../validation/Exceptions.h"
#include <string>
#include <vector>
#include <cctype>

bool Validation::validate_size(const std::string& size) {
    return size == "XXS" || size == "XS" || size == "S" || size == "M" ||
       size == "L" || size == "XL" || size == "XXL";
}

bool Validation::validate_colour(const std::string& colour) {
    if (colour.empty())
        return false;
    for (char c : colour) {
        if (std::isdigit(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

bool Validation::validate_price(double price) {
    return price >=0;
}

bool Validation::validate_quantity(int quantity) {
    return quantity>=0;
}

bool Validation::validate_photo(const std::string& photo) {
    return !photo.empty();
}

void Validation::validate_add_input(const std::string& size, const std::string& colour, double price, int quantity, const std::string& photo) {
    std::vector<std::string> errors;
    if (!validate_size(size))
        errors.push_back("Invalid size");
    if (!validate_colour(colour))
        errors.push_back("Invalid colour");
    if (!validate_price(price))
        errors.push_back("Invalid price");
    if (!validate_quantity(quantity))
        errors.push_back("Invalid quantity");
    if (!validate_photo(photo))
        errors.push_back("Invalid photo");
    if (!errors.empty())
        throw ValidationException(errors);
}
void Validation::validate_delete_input(const std::string& size, const std::string& colour) {
    std::vector<std::string> errors;
    if (!validate_size(size))
        errors.push_back("Invalid size");
    if (!validate_colour(colour))
        errors.push_back("Invalid colour");
    if (!errors.empty())
        throw ValidationException(errors);
}
void Validation::validate_update_input(const std::string& size, const std::string& colour, double price, int quantity, const std::string& photo) {
    std::vector<std::string> errors;
    if (!validate_size(size))
        errors.push_back("Invalid size");
    if (!validate_colour(colour))
        errors.push_back("Invalid colour");
    if (!validate_price(price))
        errors.push_back("Invalid price");
    if (!validate_quantity(quantity))
        errors.push_back("Invalid quantity");
    if (!validate_photo(photo))
        errors.push_back("Invalid photo");
    if (!errors.empty())
        throw ValidationException(errors);
}