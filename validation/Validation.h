//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_VALIDATION_H
#define TRENCH_COATS_APP_VALIDATION_H

#include <string>

class Validation {
private:
    static bool validate_size(const std::string& size);
    static bool validate_colour(const std::string& colour);
    static bool validate_price(double price);
    static bool validate_quantity(int quantity);
    static bool validate_photo(const std::string& photo);

public:
    void validate_add_input(const std::string& size, const std::string& colour, double price, int quantity, const std::string& photo);
    void validate_delete_input(const std::string& size, const std::string& colour);
    void validate_update_input(const std::string& size, const std::string& colour, double price, int quantity, const std::string& photo);
};


#endif //TRENCH_COATS_APP_VALIDATION_H
