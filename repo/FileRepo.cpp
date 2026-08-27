//
// Created by Maria on 27/08/2026.
//

#include "FileRepo.h"
#include "../domain/Coat.h"
#include "../validation/Exceptions.h"
#include <algorithm> // find, find_if
#include <fstream>
#include <iterator>

Repository::Repository(const std::string& filename):filename{filename} {
    this->load_from_file();
}
void Repository::add_coat(const Coat& c) {
    auto it = std::find(this->coats.begin(), this->coats.end(), c);
    if (it!=this->coats.end()) { // not reached the end => found element c => we don't wanna add it again
        throw RepositoryException("Coat already exists"); // how does the what() function work
    }
    this->coats.push_back(c);
    this->load_to_file();
    //return true;
}

void Repository::delete_coat(const std::string& size, const std::string& colour) { // works with the parameters
    auto it = std::find_if(this->coats.begin(), this->coats.end(),
        [&](const Coat& c) {
            return c.get_size() == size && c.get_colour() == colour;
        });
    if (it==this->coats.end()) { // did not find the desired coat - iterator works like some sort of pointer here?
        throw RepositoryException("Coat does not exist");
    }
    this->coats.erase(it);
    this->load_to_file();
    //return true;
}

void Repository::update_coat(const Coat& c) { // works with the object (created in ui before calling update)
    auto it = std::find_if(this->coats.begin(), this->coats.end(),
        [&](const Coat& coat) {
            return coat.get_size() == c.get_size() &&
                   coat.get_colour() == c.get_colour();
        });

    if (it == this->coats.end()) {
        throw RepositoryException("Coat does not exist");
    }

    *it = c;   // replace existing with the newly created object
    this->load_to_file();
}

std::vector<Coat> Repository::get_all() const {
    return this->coats;
}

void Repository::load_from_file() {
    /*
    this->coats.clear();
    std::ifstream fin(this->filename);
    Coat c;
    while (fin>>c) {
        this->coats.push_back(c);
    }
    fin.close();*/
    std::ifstream fin(this->filename);
    if (!fin.is_open())
        return;
    this->coats.clear();
    Coat c;
    while (fin >> c) {
        // Only add if the object actually has data (size isn't empty) so that we don't add empty lines
        if (!c.get_size().empty()) {
            this->coats.push_back(c);
        }
    }
    fin.close();
}

void Repository::load_to_file() {
    std::ofstream fout(this->filename);
    if (!fout.is_open()) return;

    std::copy(this->coats.begin(), this->coats.end(),
              std::ostream_iterator<Coat>(fout, "\n"));
    fout.close();
}