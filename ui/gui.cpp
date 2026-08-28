//
// Created by Maria on 27/08/2026.
//

#include "gui.h"
#include "ui_GUI.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QUrl>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QDesktopServices>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QShortcut>
#include <QKeySequence>
#include <map>

GUI::GUI(Service& service,QWidget* parent):
    QWidget(parent),ui(new Ui::GUI),service{service} {
    this->basketTableView=nullptr;
    this->basketModel=nullptr;
    this->chartWidget=nullptr;

    ui->setupUi(this);
    this->configureUI();
    this->initChartTab();
    this->connectSignalsAndSlots();

    QShortcut* undoShortcut=new QShortcut(QKeySequence::Undo,this);
    QObject::connect(undoShortcut,&QShortcut::activated,this,&GUI::undo);

    QShortcut* redoShortcut=new QShortcut(QKeySequence::Redo,this);
    QObject::connect(redoShortcut,&QShortcut::activated,this,&GUI::redo);
}

void GUI::configureUI() {
    this->setWindowTitle("Coats store");

    ui->table->setColumnCount(5);
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection);

    QStringList headers;
    headers<<"Size"<<"Colour"<<"Price"<<"Quantity"<<"Photo";
    ui->table->setHorizontalHeaderLabels(headers);

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    ui->table->horizontalScrollBar()->setVisible(true);
    ui->table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->table->setColumnWidth(0,80);
    ui->table->setColumnWidth(1,120);
    ui->table->setColumnWidth(2,80);
    ui->table->setColumnWidth(3,100);
    ui->table->setColumnWidth(4,900);

    ui->table->setRowCount(0);
    ui->table->hide();

    this->hideAdminForm();
}

void GUI::populateTable() {
    ui->table->show();
    std::vector<Coat> coats=this->service.get_all();
    ui->table->clearContents();
    ui->table->setRowCount(coats.size());

    for (int i=0;i<coats.size();i++) {
        Coat c=coats[i];
        ui->table->setItem(i,0,new QTableWidgetItem(QString::fromStdString(c.get_size())));
        ui->table->setItem(i,1,new QTableWidgetItem(QString::fromStdString(c.get_colour())));
        ui->table->setItem(i,2,new QTableWidgetItem(QString::number(c.get_price())));
        ui->table->setItem(i,3,new QTableWidgetItem(QString::number(c.get_quantity())));

        QTableWidgetItem* photoItem=new QTableWidgetItem(QString::fromStdString(c.get_photo()));
        photoItem->setToolTip(QString::fromStdString(c.get_photo()));
        ui->table->setItem(i,4,photoItem);
    }
}

void GUI::addCoat() {
    try {
        std::string size=ui->sizeEdit->text().toStdString();
        std::string colour=ui->colourEdit->text().toStdString();
        double price=ui->priceEdit->text().toDouble();
        int quantity=ui->quantityEdit->text().toInt();
        std::string photo=ui->photoEdit->text().toStdString();

        this->validator.validate_add_input(size,colour,price,quantity,photo);
        Coat coat{size,colour,price,quantity,photo};
        this->service.add_coat(coat);
        this->populateTable();
        this->updateChart();
        this->clearFields();
    }
    catch (std::exception& exception) {
        QMessageBox::warning(this,"Error",exception.what());
    }
}

void GUI::deleteCoat() {
    try {
        std::string size=ui->sizeEdit->text().toStdString();
        std::string colour=ui->colourEdit->text().toStdString();

        this->validator.validate_delete_input(size,colour);
        this->service.delete_coat(size,colour);
        this->populateTable();
        this->updateChart();
        this->clearFields();
    }
    catch (std::exception& exception) {
        QMessageBox::warning(this,"Error",exception.what());
    }
}

void GUI::updateCoat() {
    try {
        std::string size=ui->sizeEdit->text().toStdString();
        std::string colour=ui->colourEdit->text().toStdString();
        double price=ui->priceEdit->text().toDouble();
        int quantity=ui->quantityEdit->text().toInt();
        std::string photo=ui->photoEdit->text().toStdString();

        this->validator.validate_update_input(size,colour,price,quantity,photo);
        Coat coat{size,colour,price,quantity,photo};
        this->service.update_coat(coat);
        this->populateTable();
        this->updateChart();
        this->clearFields();
    }
    catch (std::exception& exception) {
        QMessageBox::warning(this,"Error",exception.what());
    }
}

int GUI::getSelectedRow() const {
    QModelIndexList selectedIndexes=ui->table->selectionModel()->selectedIndexes();

    if (selectedIndexes.empty()) {
        return -1;
    }

    return selectedIndexes.at(0).row();
}

void GUI::fillFieldsFromTable() {
    int row=this->getSelectedRow();

    if (row==-1) {
        return;
    }

    ui->sizeEdit->setText(ui->table->item(row,0)->text());
    ui->colourEdit->setText(ui->table->item(row,1)->text());
    ui->priceEdit->setText(ui->table->item(row,2)->text());
    ui->quantityEdit->setText(ui->table->item(row,3)->text());
    ui->photoEdit->setText(ui->table->item(row,4)->text());
}

void GUI::clearFields() {
    ui->sizeEdit->clear();
    ui->colourEdit->clear();
    ui->priceEdit->clear();
    ui->quantityEdit->clear();
    ui->photoEdit->clear();
}

void GUI::filterCoats() {
    std::string size=ui->userSizeEdit->text().toStdString();
    this->userCoats=this->service.get_coats_by_size(size);
    this->currentIndex=0;
    this->showCurrentCoat();
}

void GUI::showCurrentCoat() {
    if (this->userCoats.empty()) {
        ui->currentCoatLabel->setText("No coats found.");
        return;
    }

    Coat coat=this->userCoats[this->currentIndex];

    QString text=QString::fromStdString(
        "Showing coat "+std::to_string(this->currentIndex+1)+" of "+std::to_string(this->userCoats.size())+"\n"+
        "Size: "+coat.get_size()+"\n"+
        "Colour: "+coat.get_colour()+"\n"+
        "Price: "+std::to_string(coat.get_price())+"\n"+
        "Quantity: "+std::to_string(coat.get_quantity())+"\n"+
        "Photo: "+coat.get_photo()
    );

    ui->currentCoatLabel->setText(text);
    QDesktopServices::openUrl(QUrl(QString::fromStdString(coat.get_photo())));
}

void GUI::nextCoat() {
    if (this->userCoats.empty()) {
        return;
    }

    this->currentIndex++;

    if (this->currentIndex==this->userCoats.size()) {
        this->currentIndex=0;
    }

    this->showCurrentCoat();
}

void GUI::addCurrentCoatToBasket() {
    try {
        if (this->userCoats.empty()) {
            return;
        }

        Coat coat=this->userCoats[this->currentIndex];
        this->service.add_to_basket(coat);
        this->populateBasketList();

        if (this->basketModel!=nullptr) {
            this->basketModel->updateData(this->service.get_basket());
        }
    }
    catch (std::exception& exception) {
        QMessageBox::warning(this,"Error",exception.what());
    }
}

void GUI::populateBasketList() {
    ui->basketList->clear();
    std::vector<Coat> basket=this->service.get_basket();

    for (const Coat& coat:basket) {
        std::string text=coat.get_size()+" | "+
                         coat.get_colour()+" | "+
                         std::to_string(coat.get_price())+" | "+
                         std::to_string(coat.get_quantity());

        ui->basketList->addItem(QString::fromStdString(text));
    }

    ui->totalLabel->setText(QString::fromStdString("Total: "+std::to_string(this->service.get_total())));

    if (this->basketModel!=nullptr) {
        this->basketModel->updateData(this->service.get_basket());
    }
}

void GUI::openBasket() {
    try {
        this->service.open_basket();
    }
    catch (std::exception& exception) {
        QMessageBox::warning(this,"Error",exception.what());
    }
}

void GUI::connectSignalsAndSlots() {
    QObject::connect(ui->displayButton,&QPushButton::clicked,this,&GUI::populateTable);
    QObject::connect(ui->addButton,&QPushButton::clicked,this,&GUI::showAddForm);
    QObject::connect(ui->deleteButton,&QPushButton::clicked,this,&GUI::showDeleteForm);
    QObject::connect(ui->updateButton,&QPushButton::clicked,this,&GUI::showUpdateForm);
    QObject::connect(ui->confirmButton,&QPushButton::clicked,this,&GUI::confirmAdminAction);

    QObject::connect(ui->table,&QTableWidget::itemSelectionChanged,this,&GUI::fillFieldsFromTable);

    QObject::connect(ui->filterButton,&QPushButton::clicked,this,&GUI::filterCoats);
    QObject::connect(ui->nextButton,&QPushButton::clicked,this,&GUI::nextCoat);
    QObject::connect(ui->addToBasketButton,&QPushButton::clicked,this,&GUI::addCurrentCoatToBasket);
    QObject::connect(ui->openBasketButton,&QPushButton::clicked,this,&GUI::openBasket);
    QObject::connect(ui->undoButton,&QPushButton::clicked,this,&GUI::undo);
    QObject::connect(ui->redoButton,&QPushButton::clicked,this,&GUI::redo);
    QObject::connect(ui->basketTableButton,&QPushButton::clicked,this,&GUI::showBasketTable);
}

void GUI::hideAdminForm() {
    ui->sizeLabel->hide();
    ui->colourLabel->hide();
    ui->priceLabel->hide();
    ui->quantityLabel->hide();
    ui->photoLabel->hide();

    ui->sizeEdit->hide();
    ui->colourEdit->hide();
    ui->priceEdit->hide();
    ui->quantityEdit->hide();
    ui->photoEdit->hide();

    ui->confirmButton->hide();
}

void GUI::showAddForm() {
    this->currentAdminAction="add";
    this->clearFields();

    ui->sizeLabel->show();
    ui->colourLabel->show();
    ui->priceLabel->show();
    ui->quantityLabel->show();
    ui->photoLabel->show();

    ui->sizeEdit->show();
    ui->colourEdit->show();
    ui->priceEdit->show();
    ui->quantityEdit->show();
    ui->photoEdit->show();

    ui->confirmButton->show();
}

void GUI::showDeleteForm() {
    this->currentAdminAction="delete";
    this->clearFields();

    ui->sizeLabel->show();
    ui->colourLabel->show();

    ui->sizeEdit->show();
    ui->colourEdit->show();

    ui->priceLabel->hide();
    ui->quantityLabel->hide();
    ui->photoLabel->hide();

    ui->priceEdit->hide();
    ui->quantityEdit->hide();
    ui->photoEdit->hide();

    ui->confirmButton->show();
}

void GUI::showUpdateForm() {
    this->currentAdminAction="update";

    ui->sizeLabel->show();
    ui->colourLabel->show();
    ui->priceLabel->show();
    ui->quantityLabel->show();
    ui->photoLabel->show();

    ui->sizeEdit->show();
    ui->colourEdit->show();
    ui->priceEdit->show();
    ui->quantityEdit->show();
    ui->photoEdit->show();

    ui->confirmButton->show();
}

void GUI::confirmAdminAction() {
    if (this->currentAdminAction=="add") {
        this->addCoat();
    }
    else if (this->currentAdminAction=="delete") {
        this->deleteCoat();
    }
    else if (this->currentAdminAction=="update") {
        this->updateCoat();
    }

    this->hideAdminForm();
}

void GUI::showBasketTable() {
    if (this->basketTableView==nullptr) {
        this->basketTableView=new QTableView{};
        this->basketModel=new BasketTableModel{this->service.get_basket(),this->basketTableView};

        this->basketTableView->setModel(this->basketModel);
        this->basketTableView->resize(900,400);
        this->basketTableView->setWindowTitle("Shopping basket table");
    }

    this->basketModel->updateData(this->service.get_basket());
    this->basketTableView->show();
}

void GUI::undo() {
    try {
        this->service.undo();
        this->populateTable();
    }
    catch (std::exception& exception) {
        QMessageBox::warning(this,"Error",exception.what());
    }
}

void GUI::redo() {
    try {
        this->service.redo();
        this->populateTable();
    }
    catch (std::exception& exception) {
        QMessageBox::warning(this,"Error",exception.what());
    }
}

void GUI::initChartTab() {
    this->chartWidget=new ChartWidget{};

    QVBoxLayout* chartLayout=new QVBoxLayout{};
    chartLayout->addWidget(this->chartWidget);

    ui->chartTab->setLayout(chartLayout);

    this->updateChart();
}

void GUI::updateChart() {
    std::map<std::string,int> data;
    std::vector<Coat> coats=this->service.get_all();

    for (const Coat& coat:coats) {
        data[coat.get_colour()]+=coat.get_quantity();
    }

    this->chartWidget->setData(data);
}

GUI::~GUI() {
    delete this->basketTableView;
    delete ui;
}