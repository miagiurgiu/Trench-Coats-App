//
// Created by Maria on 27/08/2026.
//

#include "HTMLShoppingBasket.h"
#include <fstream>

HTMLShoppingBasket::HTMLShoppingBasket(const std::string& file): filename{file} {}

void HTMLShoppingBasket::open() {
    std::string command = "open \"" + this->filename + "\"";
    system(command.c_str());
}

void HTMLShoppingBasket::write() {
    std::ofstream out(this->filename);

    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "    <meta charset=\"UTF-8\">\n";
    out << "    <title>Shopping Basket</title>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<table border=\"1\">\n";

    // header
    out << "    <tr>\n";
    out << "        <td>Size</td>\n";
    out << "        <td>Colour</td>\n";
    out << "        <td>Price</td>\n";
    out << "        <td>Quantity</td>\n";
    out << "        <td>Photo</td>\n";
    out << "    </tr>\n";

    // data
    for (const auto& c : this->elements) {
        std::string link = c.get_photo();
        while (!link.empty() && (link.back() == '\r' || link.back() == '\n' || link.back() == ' ')) {
            link.pop_back();
        }
        size_t pos = 0;
        while ((pos = link.find('&', pos)) != std::string::npos) {
            link.replace(pos, 1, "&amp;");
            pos += 5;
        }

        out << "    <tr>\n";
        out << "        <td>" << c.get_size() << "</td>\n";
        out << "        <td>" << c.get_colour() << "</td>\n";
        out << "        <td>" << c.get_price() << "</td>\n";
        out << "        <td>" << c.get_quantity() << "</td>\n";
        out << "        <td><a href=\"" << link << "\" target=\"_blank\" rel=\"noopener noreferrer\">Open photo</a></td>\n";
        out << "    </tr>\n";
    }
    out << "</table>\n";
    out << "</body>\n";
    out << "</html>\n";
    out.close();
}