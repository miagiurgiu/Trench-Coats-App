//
// Created by Maria on 29/08/2026.
//

#ifndef TRENCH_COATS_APP_WELCOME_H
#define TRENCH_COATS_APP_WELCOME_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class Welcome; }
QT_END_NAMESPACE

class Welcome : public QDialog {
Q_OBJECT

public:
    explicit Welcome(QWidget *parent = nullptr);
    ~Welcome() override;
    int getSelectedMode() const;

private:
    Ui::Welcome *ui;
    int selectedMode=-1;
};


#endif //TRENCH_COATS_APP_WELCOME_H
