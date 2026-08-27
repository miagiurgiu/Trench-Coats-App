//
// Created by Maria on 27/08/2026.
//

#include "BasketTableModel.h"
BasketTableModel::BasketTableModel(const std::vector<Coat>& coats,QObject* parent):QAbstractTableModel{parent},coats{coats}{}

int BasketTableModel::rowCount(const QModelIndex&) const {
    return coats.size();
}

int BasketTableModel::columnCount(const QModelIndex&) const {
    return 5;
}

QVariant BasketTableModel::data(const QModelIndex& index,int role) const {

    if (!index.isValid() ||
        role != Qt::DisplayRole) {
        return QVariant{};
        }

    const Coat& coat = coats[index.row()];

    if (index.column() == 0)
        return QString::fromStdString(coat.get_size());

    if (index.column() == 1)
        return QString::fromStdString(coat.get_colour());

    if (index.column() == 2)
        return QString::number(coat.get_price());

    if (index.column() == 3)
        return QString::number(coat.get_quantity());

    if (index.column() == 4)
        return QString::fromStdString(coat.get_photo());

    return QVariant{};
}


QVariant BasketTableModel::headerData(int section,Qt::Orientation orientation,int role) const {

    if (role != Qt::DisplayRole) {
        return QVariant{};
    }

    if (orientation == Qt::Horizontal) {
        if (section == 0) return "Size";
        if (section == 1) return "Colour";
        if (section == 2) return "Price";
        if (section == 3) return "Quantity";
        if (section == 4) return "Photo";
    }

    return QVariant{};
}

void BasketTableModel::updateData(const std::vector<Coat> &newCoats) {
    beginResetModel();
    this->coats = newCoats;
    endResetModel();
}
