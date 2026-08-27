//
// Created by Maria on 27/08/2026.
//

#include "Service.h"

Service::Service(AbstractRepo& r, AbstractShoppingBasket& b):arepo{r},basket{b} {}

Coat Service::findCoat(const std::string &size, const std::string &colour) const {
    for (const auto& coat:this->arepo.get_all()) {
        if (coat.get_size()==size && coat.get_colour()==colour) {
            return coat;
        }
    }
    throw std::runtime_error("coat not found");
}


void Service::add_coat(const Coat& c)
{
    // this->repo.add_coat(c); // for text-file repo
    this->arepo.add_coat(c);

    this->undoStack.push_back(std::make_unique<AddUndoAction>(this->arepo,c));
    this->redoStack.clear();
}

void Service::delete_coat(const std::string& size, const std::string& colour)
{
    //this->repo.delete_coat(size, colour); // for text-file repo
    Coat deletedCoat=this->findCoat(size,colour);
    this->arepo.delete_coat(size, colour);
    this->undoStack.push_back(std::make_unique<RemoveUndoAction>(this->arepo, deletedCoat));
    this->redoStack.clear();
}

void Service::update_coat(const Coat& c)
{
    Coat oldCoat=this->findCoat(c.get_size(),c.get_colour());
    //this->repo.update_coat(c); // for text-file repo
    this->arepo.update_coat(c);

    this->undoStack.push_back(std::make_unique<UpdateUndoAction>(this->arepo, oldCoat, c)); // !!!
    this->redoStack.clear();
}

std::vector<Coat> Service::get_all() const
{
    // return this->repo.get_all(); // for text-file repo
    return this->arepo.get_all();
}

std::vector<Coat> Service::get_coats_by_size(const std::string& size) {
    // std::vector<Coat> all_coats = this->repo.get_all(); // for text-file repo
    std::vector<Coat> all_coats = this->arepo.get_all();
    std::vector<Coat> filtered;

    if(size=="")
    {
        return all_coats;
    }

    std::copy_if(all_coats.begin(), all_coats.end(), std::back_inserter(filtered),
        [&](const Coat& c) {
            return c.get_size()==size;
        });

    return filtered;
}

void Service::add_to_basket(const Coat& c) {
    std::vector<Coat> basketCoats = this->basket.get_all();

    for (const Coat& coat : basketCoats) {
        if (coat.get_size() == c.get_size() &&
            coat.get_colour() == c.get_colour()) {
            throw std::runtime_error("Coat already exists in basket!");
            }
    }
    this->basket.add(c);
    //this->total += c.get_price();
    this->basket.write();
}
double Service::get_total() {
    //return this->basket.get_all();
    double sum = 0;
    for (const auto& coat: this->basket.get_all()) {
        sum += coat.get_price();
    }
    return sum;
}

std::vector<Coat> Service::get_basket() {
    return this->basket.get_all();
}

void Service::open_basket() {
    this->basket.open();
}

void Service::undo() {
    if (this->undoStack.empty()) {
        throw std::runtime_error("No more undos!");
    }

    std::unique_ptr<UndoAction> action = std::move(this->undoStack.back()); // retrieve last action from the top of the stack
    // action - new local variable that is smart pointer capable ofr holding an object d
    this->undoStack.pop_back(); // remove last action from stack

    action->undo(); // execute operation
    this->redoStack.push_back(std::move(action)); // move in the other stack
}

void Service::redo() {
    if (this->redoStack.empty()) {
        throw std::runtime_error("No more redos!");
    }

    std::unique_ptr<UndoAction> action = std::move(this->redoStack.back()); // take last operation from redo stack
    this->redoStack.pop_back();

    action->redo(); // execute operation
    this->undoStack.push_back(std::move(action)); // move in the other stack
}
