//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_DATABASEREPO_H
#define TRENCH_COATS_APP_DATABASEREPO_H

#include "../repo/AbstractRepo.h"
#include <string>
#include <vector>
#include <sqlite3.h>

class DatabaseRepo : public AbstractRepo {
private:
    sqlite3* db;
    void create_table();
public:
    DatabaseRepo(const std::string& database_file);
    void add_coat(const Coat& c) override;
    void delete_coat(const std::string& size, const std::string& colour) override;
    void update_coat(const Coat& c) override;
    std::vector<Coat> get_all() const override;
    ~DatabaseRepo();
};

#endif //TRENCH_COATS_APP_DATABASEREPO_H
