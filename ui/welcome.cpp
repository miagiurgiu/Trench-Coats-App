//
// Created by Maria on 29/08/2026.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Welcome.h" resolved

#include "welcome.h"
#include "ui_Welcome.h"
#include <QPushButton>

Welcome::Welcome(QWidget *parent) :
    QDialog(parent), ui(new Ui::Welcome) {
    ui->setupUi(this);
    connect(ui->adminModeButton,&QPushButton::clicked,this,[this](){
        selectedMode=0;
        accept();
    });

    connect(ui->userModeButton,&QPushButton::clicked,this,[this](){
        selectedMode=1;
        accept();
    });
}

int Welcome::getSelectedMode() const {
    return selectedMode;
}

Welcome::~Welcome() {
    delete ui;
}
