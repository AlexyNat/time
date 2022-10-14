#ifndef CUBE_H
#define CUBE_H

#include <QtWidgets>
#include <QtXml>
#include <vector>
#include <set>
#include <QRandomGenerator>


class Cube : public QWidget
{
    Q_OBJECT

public:
    Cube(QColor color, QSize size, int h = 3, int w = 1, int number = 1, QWidget *parent = nullptr);
    ~Cube();

private slots:
    void slotTimerAlarm();

private:

    QColor color; /// цвет квадрата
    QSize size; /// размеры квадрата
    int h, w; /// число квадратов
    int number; /// номер группы
    std::vector<std::vector<QFrame *>> frames; /// квадраты
    QTimer *timer; /// таймер
    QRandomGenerator generator; /// генератор

};
#endif // CUBE_H
