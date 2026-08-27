//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_HTMLSHOPPINGBASKET_H
#define TRENCH_COATS_APP_HTMLSHOPPINGBASKET_H
#include "AbstractShoppingBasket.h"


class HTMLShoppingBasket : public AbstractShoppingBasket {
private:
    std::string filename;
public:
    HTMLShoppingBasket(const std::string& file);
    void write() override;
    void open() override;
};


#endif //TRENCH_COATS_APP_HTMLSHOPPINGBASKET_H
