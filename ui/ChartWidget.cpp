//
// Created by Maria on 28/08/2026.
//

#include "ChartWidget.h"
#include <QPainter>
#include <QString>
#include <algorithm>
#include <QColor>

ChartWidget::ChartWidget(QWidget* parent):QWidget(parent) {
    this->setMinimumSize(400,300);
}

void ChartWidget::setData(const std::map<std::string,int>& data) {
    this->data=data;
    update();
}

void ChartWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setPen(Qt::white);
    painter.setRenderHint(QPainter::Antialiasing);

    if (this->data.empty()) {
        painter.drawText(this->rect(),Qt::AlignCenter,"No data available");
        return;
    }

    int maxQuantity=0;
    for (const auto& item:this->data) {
        maxQuantity=std::max(maxQuantity,item.second);
    }

    if (maxQuantity==0) {
        return;
    }

    int margin=40;
    int chartWidth=this->width()-2*margin;
    int chartHeight=this->height()-2*margin;
    int barSlotWidth=chartWidth/static_cast<int>(this->data.size());
    int barWidth=barSlotWidth*2/3;
    int index=0;

    for (const auto& item:this->data) {
        int barHeight=item.second*chartHeight/maxQuantity;
        int x=margin+index*barSlotWidth+(barSlotWidth-barWidth)/2;
        int y=this->height()-margin-barHeight;

        QColor colour(QString::fromStdString(item.first));
        if (!colour.isValid()) {
            colour=QColor(70,130,180);
        }

        painter.setPen(Qt::black);
        painter.setBrush(colour);
        painter.drawRect(x,y,barWidth,barHeight);

        painter.setPen(Qt::white);
        painter.drawText(x,y-20,barWidth,20,Qt::AlignCenter,QString::number(item.second));
        painter.drawText(x,this->height()-margin,barWidth,30,Qt::AlignCenter,QString::fromStdString(item.first));

        index++;
    }
}