//
// Created by Maria on 27/08/2026.
//

#include "DatabaseRepo.h"
#include "../repo/FileRepo.h"
#include "../validation/Exceptions.h"
#include <stdexcept>

DatabaseRepo::DatabaseRepo(const std::string& database_file) {
    if (sqlite3_open(database_file.c_str(), &this->db) != SQLITE_OK)
        //throw std::runtime_error("Cannot open database");
        throw RepositoryException("Runtime error");
    this->create_table();
    if (this->get_all().empty()) {
        Repository fileRepo{"../start/coats.csv"};
        for (const auto& coat : fileRepo.get_all())
            this->add_coat(coat);
    }
}

void DatabaseRepo::create_table()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS coats ("
        "size TEXT,"
        "colour TEXT,"
        "price REAL,"
        "quantity INTEGER,"
        "photo TEXT,"
        "PRIMARY KEY(size, colour)"
        ");";

    char* errMsg = nullptr;

    if (sqlite3_exec(this->db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        //throw std::runtime_error(error);
        throw RepositoryException("Runtime error");
    }
}

void DatabaseRepo::add_coat(const Coat& c) {
    std::string sql =
        "INSERT INTO coats(size, colour, price, quantity, photo) VALUES('" +
        c.get_size() + "', '" +
        c.get_colour() + "', " +
        std::to_string(c.get_price()) + ", " +
        std::to_string(c.get_quantity()) + ", '" +
        c.get_photo() + "');";

    char* errMsg = nullptr;

    if (sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        //throw std::runtime_error(error);
        throw RepositoryException("Runtime error");
    }
}

void DatabaseRepo::delete_coat(const std::string& size, const std::string& colour) {
    std::string sql =
        "DELETE FROM coats WHERE size='" + size +
        "' AND colour='" + colour + "';";

    char* errMsg = nullptr;

    if (sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        //throw std::runtime_error(error);
        throw RepositoryException("Runtime error");
    }
}

void DatabaseRepo::update_coat(const Coat& c) {
    std::string sql =
        "UPDATE coats SET price=" + std::to_string(c.get_price()) +
        ", quantity=" + std::to_string(c.get_quantity()) +
        ", photo='" + c.get_photo() +
        "' WHERE size='" + c.get_size() +
        "' AND colour='" + c.get_colour() + "';";

    char* errMsg = nullptr;

    if (sqlite3_exec(this->db, sql.c_str(), nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::string error = errMsg;
        sqlite3_free(errMsg);
        //throw std::runtime_error(error);
        throw RepositoryException("Runtime error");
    }
}

std::vector<Coat> DatabaseRepo::get_all() const {
    std::vector<Coat> coats;

    const char* sql = "SELECT size, colour, price, quantity, photo FROM coats;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(this->db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        //throw std::runtime_error("Could not select coats");
        throw RepositoryException("Runtime error");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        std::string size = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::string colour = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        double price = sqlite3_column_double(stmt, 2);
        int quantity = sqlite3_column_int(stmt, 3);
        std::string photo = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        coats.emplace_back(size, colour, price, quantity, photo);
    }

    sqlite3_finalize(stmt);
    return coats;
}

DatabaseRepo::~DatabaseRepo() {
    sqlite3_close(this->db);
}
