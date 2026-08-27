//
// Created by Maria on 27/08/2026.
//

#include "CSVShoppingBasket.h"
#include <fstream>
CSVShoppingBasket::CSVShoppingBasket(const std::string& file):filename{file} {}

void CSVShoppingBasket::write() {
    std::ofstream out(this->filename);

    for (const auto& c: this->elements) {
        out << c.get_size() << ","
            << c.get_colour()<<","
            << c.get_price()<<","
            << c.get_quantity()<<","
            << c.get_photo()<<"\n";
    }
}

void CSVShoppingBasket::open() {
    std::string command = "open " + this->filename;
    system(command.c_str());
}