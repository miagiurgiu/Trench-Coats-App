//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_BASKETTABLEMODEL_H
#define TRENCH_COATS_APP_BASKETTABLEMODEL_H
#include <qobject.h>
#include <vector>
#include <QAbstractTableModel>
#include "Coat.h"


class BasketTableModel:public QAbstractTableModel {
private:
    std::vector<Coat> coats;
public:
    BasketTableModel(const std::vector<Coat>& coats, QObject* parent=nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section,Qt::Orientation orientation,int role = Qt::DisplayRole) const override;
    void updateData(const std::vector<Coat>& newCoats);
};



#endif //TRENCH_COATS_APP_BASKETTABLEMODEL_H
