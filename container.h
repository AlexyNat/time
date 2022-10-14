#ifndef CONTAINER_H
#define CONTAINER_H

#include <QtWidgets>
#include "cube.h"

/* Контейнер для групп */
class Container : public QWidget
{
    Q_OBJECT

public:
    Container(QString file = "data.xml", QWidget *parent = nullptr);

private:
    void initializeFromXml(QString fileName);

    QPoint points[4]; /// позиции
    QColor colors[4]; /// цвета
    QSize cubeSize; /// размеры квадратов

    QColor setColor(QString str);
    QColor backgroundColor;

};

#endif // CONTAINER_H
