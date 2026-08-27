//
// Created by Maria on 27/08/2026.
//

#include "AbstractShoppingBasket.h"

void AbstractShoppingBasket::add(const Coat& c) {
    elements.push_back(c);
}

const std::vector<Coat>& AbstractShoppingBasket::get_all() const {
    return elements;
}