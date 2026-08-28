//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_GUI_H
#define TRENCH_COATS_APP_GUI_H

#include <QWidget>
#include <QTableView>
#include "BasketTableModel.h"
#include "../domain/Coat.h"
#include "../service/Service.h"
#include "ChartWidget.h"
#include "../validation/Validation.h"
#include <string>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(Service& service, QWidget *parent = nullptr);
    ~GUI() override;

private:
    Ui::GUI *ui=nullptr;
    Service& service;
    Validation validator;
    std::vector<Coat> userCoats; // NOT POLYMORPHISM, so only <Coat>, not <Coat*>
    int currentIndex=0;
    std::string currentAdminAction;

    QTableView* basketTableView;
    BasketTableModel* basketModel;
    ChartWidget* chartWidget;

    void configureUI();
    //void updateChart();
    void populateTable();
    void connectSignalsAndSlots();

    void addCoat();
    void deleteCoat();
    void updateCoat();

    void fillFieldsFromTable();
    void clearFields();
    int getSelectedRow() const;

    void filterCoats();
    void showCurrentCoat();
    void nextCoat();
    void addCurrentCoatToBasket();
    void populateBasketList();
    void openBasket();

    void showAddForm();
    void showDeleteForm();
    void showUpdateForm();
    void hideAdminForm();
    void confirmAdminAction();
    void showBasketTable();

    void undo();
    void redo();

    void initChartTab();
    void updateChart();
};


#endif //TRENCH_COATS_APP_GUI_H
