//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_UNDOACTION_H
#define TRENCH_COATS_APP_UNDOACTION_H
#include "repo/AbstractRepo.h"


class UndoAction {
public:
    virtual void undo()=0;
    virtual void redo()=0;
    virtual ~UndoAction()=default;
};

class AddUndoAction:public UndoAction {
private:
    AbstractRepo& repo;
    Coat coat;
public:
    AddUndoAction(AbstractRepo& repo, const Coat& coat);
    void undo() override;
    void redo() override;
};

class RemoveUndoAction:public UndoAction {
private:
    AbstractRepo& repo;
    Coat coat;
public:
    RemoveUndoAction(AbstractRepo& repo,const Coat& coat);
    void undo() override;
    void redo() override;
};

class UpdateUndoAction:public UndoAction {
private:
    AbstractRepo& repo;
    Coat oldCoat;
    Coat newCoat;
public:
    UpdateUndoAction(AbstractRepo& repo, const Coat& oldCoat,const Coat& newCoat);
    void undo() override;
    void redo() override;
};



#endif //TRENCH_COATS_APP_UNDOACTION_H
