//
// Created by Maria on 27/08/2026.
//

#include "UndoAction.h"

AddUndoAction::AddUndoAction(AbstractRepo &repo, const Coat &coat):repo{repo},coat{coat} {}

void AddUndoAction::undo() { // opposite operation
    repo.delete_coat(coat.get_size(),coat.get_colour());
}

void AddUndoAction::redo() {
    repo.add_coat(coat);
}

RemoveUndoAction::RemoveUndoAction(AbstractRepo &repo, const Coat &coat):repo{repo},coat{coat} {}

void RemoveUndoAction::undo() { // opposite operation
    repo.add_coat(coat);
}

void RemoveUndoAction::redo() {
    repo.delete_coat(coat.get_size(),coat.get_colour());
}

UpdateUndoAction::UpdateUndoAction(AbstractRepo &repo, const Coat &oldCoat, const Coat &newCoat):repo{repo},oldCoat{oldCoat},newCoat{newCoat} {}

void UpdateUndoAction::undo() {
    repo.update_coat(oldCoat);
}

void UpdateUndoAction::redo() {
    repo.update_coat(newCoat);
}
