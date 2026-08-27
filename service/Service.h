//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_SERVICE_H
#define TRENCH_COATS_APP_SERVICE_H
#include "../repo/AbstractRepo.h"
#include "../domain/Coat.h"
#include "../shopping_basket/AbstractShoppingBasket.h"
#include "UndoAction.h"
#include <vector>
#include <memory> // for undo/redo


// Uses polymorphism via AbstractRepo and AbstractShoppingBasket
class Service {
private:
    //Repository repo;
    AbstractRepo& arepo;
    //std::vector<Coat> basket; // private basket
    AbstractShoppingBasket& basket;
    //double total;

    // FOR UNDO/REDO
    // smart pointer - exclusive ownership = automatically deletes the object when the pointer goes out of scope
    // stores polymorphic UndoAction objects in a stack -> without losing their derived types
    // unique pointer manages memory of polymorphic undoaction subclasses - > automatically deleted when popped/stack is destroyed
    std::vector<std::unique_ptr<UndoAction>> undoStack;
    std::vector<std::unique_ptr<UndoAction>> redoStack;
    Coat findCoat(const std::string& size, const std::string& colour)const;
public:
    //Service(const Repository& r); // usage: Service serv{repo};
    //Service(const Repository& r, AbstractShoppingBasket& b); // NOT CONST FOR DATABASE!
    Service(AbstractRepo& r, AbstractShoppingBasket& b);

    // admin functionalities
    void add_coat(const Coat& c);
    void delete_coat(const std::string& size, const std::string& colour);
    void update_coat(const Coat& c);
    std::vector<Coat> get_all() const;

    // user functionalities
    std::vector<Coat> get_basket(); // shopping basket
    std::vector<Coat> get_coats_by_size(const std::string& size);
    void add_to_basket(const Coat& c);
    double get_total();

    void open_basket();

    void undo();
    void redo();
};



#endif //TRENCH_COATS_APP_SERVICE_H
