//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_FILEREPO_H
#define TRENCH_COATS_APP_FILEREPO_H
#include "../domain/Coat.h"
#include <vector>
#include "AbstractRepo.h"

// file-based repo
class Repository : public AbstractRepo {
private:
    std::vector<Coat> coats;
    std::string filename;
    void load_from_file();
    void load_to_file();
public:
    Repository(const std::string& filename);
    void add_coat(const Coat& c);
    void delete_coat(const std::string& size, const std::string& colour);
    void update_coat(const Coat& c);
    std::vector<Coat> get_all() const;
};


#endif //TRENCH_COATS_APP_FILEREPO_H
