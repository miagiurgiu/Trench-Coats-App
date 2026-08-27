//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_ABSTRACTREPO_H
#define TRENCH_COATS_APP_ABSTRACTREPO_H

#include "../domain/Coat.h"
#include <vector>
#include <string>

class AbstractRepo {
public:
    virtual void add_coat(const Coat& c) = 0;
    virtual void delete_coat(const std::string& size, const std::string& colour) = 0;
    virtual void update_coat(const Coat& c) = 0;
    virtual std::vector<Coat> get_all() const = 0;
    virtual ~AbstractRepo() = default;
};




#endif //TRENCH_COATS_APP_ABSTRACTREPO_H
