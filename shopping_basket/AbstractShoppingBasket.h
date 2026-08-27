//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_ABSTRACTSHOPPINGBASKET_H
#define TRENCH_COATS_APP_ABSTRACTSHOPPINGBASKET_H
#include <vector>

#include "Coat.h"

class AbstractShoppingBasket {
protected:
    std::vector<Coat> elements;
public:
    void add(const Coat& c);
    const std::vector<Coat>& get_all() const;
    virtual void write()=0;
    virtual void open()=0;
    virtual ~AbstractShoppingBasket() = default;
};

#endif //TRENCH_COATS_APP_ABSTRACTSHOPPINGBASKET_H
