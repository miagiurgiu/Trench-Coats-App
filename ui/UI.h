//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_UI_H
#define TRENCH_COATS_APP_UI_H
#include "service/Service.h"
#include "validation/Validation.h"

class UI
{
private:
    Service& service;
    Validation validator;
    // admin functionalities
    void menu();
    void add_coat_ui();
    void delete_coat_ui();
    void update_coat_ui();
    void display_coat_ui();
    // user functionalities
    void user_menu();
    void see_coats_ui();
    void add_to_basket_ui();
    void total_ui();

public:
    UI(Service& s);
    void runApplication();

};

#endif //TRENCH_COATS_APP_UI_H
