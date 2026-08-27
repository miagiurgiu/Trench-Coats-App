#pragma once
#include <string>
#include <iostream>
// using namespace std;

class Coat {
private:
    std::string size;
    std::string colour;
    double price;
    int quantity;
    std::string photo;
public:
    Coat(); //default constructor
    Coat(const std::string& size, const std::string& colour, double price, int quantity, const std::string& photo); // constructor with parameters
    ~Coat() = default; // default destructor

    bool operator==(const Coat& other) const;

    // getters -> const
    std::string get_size() const;
    std::string get_colour() const;
    double get_price() const;
    int get_quantity() const;
    std::string get_photo() const;

    // setters
    void set_price(double price);
    void set_quantity(int quantity);
    void set_colour(const std::string& colour);
    void set_size(const std::string& size);
    void set_photo(const std::string& photo);

};

std::ostream& operator<<(std::ostream& os, const Coat& c);
std::istream& operator>>(std::istream& is, Coat& c);