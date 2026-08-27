//
// Created by Maria on 27/08/2026.
//

#ifndef TRENCH_COATS_APP_GUI_H
#define TRENCH_COATS_APP_GUI_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class GUI; }
QT_END_NAMESPACE

class GUI : public QWidget {
Q_OBJECT

public:
    explicit GUI(QWidget *parent = nullptr);
    ~GUI() override;

private:
    Ui::GUI *ui;
};


#endif //TRENCH_COATS_APP_GUI_H
