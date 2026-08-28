//
// Created by Maria on 28/08/2026.
//

#ifndef TRENCH_COATS_APP_CHART_WIDGET_H
#define TRENCH_COATS_APP_CHART_WIDGET_H

#include <QWidget>
#include <map>
#include <string>

class ChartWidget:public QWidget {
public:
    explicit ChartWidget(QWidget* parent=nullptr);
    void setData(const std::map<std::string,int>& data);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::map<std::string,int> data;
};

#endif //TRENCH_COATS_APP_CHARTWIDGET_H
