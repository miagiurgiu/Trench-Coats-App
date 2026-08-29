//
// Created by Maria on 27/08/2026.
//

#include <iostream>
#include <string>
#include "../repo/FileRepo.h"
#include "service/Service.h"
#include "shopping_basket/CSVShoppingBasket.h"
#include <QApplication>
#include <QDialog>
#include "welcome.h"
#include "repo/DatabaseRepo.h"
#include "shopping_basket/HTMLShoppingBasket.h"
#include "ui/UI.h"
#include "ui/gui.h"

int runGUI(Service& service) {
    Welcome welcome;

    if (welcome.exec()!=QDialog::Accepted)
        return 0;

    GUI gui{service};
    gui.setInitialMode(welcome.getSelectedMode());
    gui.show();

    return QApplication::exec();
}

int main(int argc,char *argv[]) {
    QApplication application{argc,argv};
    std::string interface_option;
    while (true) {
        std::cout<<"Choose interface type (ui/gui): ";
        std::getline(std::cin,interface_option);
        if (interface_option=="ui" || interface_option =="gui") {
            break;
        }
        std::cout<<"Invalid option. Choose 'ui' or 'gui'.\n";
    }

    std::string repo_option;
    while (true) {
        std::cout<<"Choose repo type (file/database): ";
        std::getline(std::cin,repo_option);
        if (repo_option=="file" || repo_option=="database") {
            break;
        }
        std::cout<<"Invalid option. Choose 'file' or 'database'.\n";
    }

    std::string basket_option;
    while (true) {
        std::cout<<"Choose basket type (csv/html): ";
        std::getline(std::cin,basket_option);
        if (basket_option=="csv" || basket_option=="html") {
            break;
        }
        std::cout<<"Invalid option. Choose 'csv' or 'html'.\n";
    }

    if (repo_option=="file") {
        Repository repo("../start/coats.csv");
        if (basket_option=="csv") {
            CSVShoppingBasket basket{"../basket.csv"};
            Service service{repo,basket};
            if (interface_option=="ui") {
                UI ui{service};
                ui.runApplication();
            }
            else {
                return runGUI(service);
                // QApplication app{argc,argv};
                // GUI gui{service};
                // gui.show();
                // return app.exec();
                // //std::cout<<"To be implemented";
            }
        }
        else {
            HTMLShoppingBasket basket{"../start/basket.html"};
            Service service{repo,basket};
            if (interface_option=="ui") {
                UI ui{service};
                ui.runApplication();
            }
            else {
                return runGUI(service);
                // QApplication app{argc,argv};
                // GUI gui{service};
                // gui.show();
                // return app.exec();
                // //std::cout<<"To be implemented";
            }
        }
    }
    else {
        DatabaseRepo repo("../start/coats.db"); // INDEPENDENTLY
        if (basket_option == "csv") {
            CSVShoppingBasket basket{"../start/basket.csv"};
            Service service{repo, basket};
            if (interface_option=="ui") {
                UI ui{service};
                ui.runApplication();
            }
            else {
                return runGUI(service);
                // QApplication app(argc, argv);
                // GUI gui{service};
                // gui.show();
                // return app.exec();
                // //std::cout<<"To be implemented";
            }
        }
        else {
            HTMLShoppingBasket basket{"../start/basket.html"};
            Service service{repo, basket};
            if (interface_option=="ui") {
                UI ui{service};
                ui.runApplication();
            }
            else {
                return runGUI(service);
                // QApplication app(argc, argv);
                // GUI gui{service};
                // gui.show();
                // return app.exec();
                // //std::cout<<"To be implemented";
            }
        }
    }
    return 0;
}
