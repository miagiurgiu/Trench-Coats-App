//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_CSVSHOPPINGBASKET_H
#define TRENCH_COATS_APP_CSVSHOPPINGBASKET_H
#include "AbstractShoppingBasket.h"


class CSVShoppingBasket : public AbstractShoppingBasket {
private:
    std::string filename;
public:
    CSVShoppingBasket(const std::string& file);
    void write() override;
    void open() override;
};



#endif //TRENCH_COATS_APP_CSVSHOPPINGBASKET_H
