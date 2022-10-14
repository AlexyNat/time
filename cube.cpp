#include "cube.h"

Cube::Cube(QColor color,QSize size, int h, int w, int number, QWidget *parent)
    : QWidget(parent), color(color), size(size), h(h), w(w), number(number), frames(h), timer(new QTimer())
{
    for(int i = 0;i < h; i++) {
        frames[i].resize(w);
        for(int j = 0;j < w;j++) {
            frames[i][j] = new QFrame(this);
            frames[i][j]->setFrameStyle(QFrame::Box | QFrame::Plain);
            frames[i][j]->resize(size.width(), size.height());
            frames[i][j]->move(j * size.width(), i * size.height());
            frames[i][j]->setAutoFillBackground(true);
        }
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    timer->start(1000);
}

/* Событие таймера */
void Cube::slotTimerAlarm()
{

    for(int i = 0;i < h; i++) {
        for(int j = 0;j < w;j++) {
            QPalette pal = frames[i][j]->palette();
            QWidget *prnt = qobject_cast<QWidget*>(parent());
            pal.setColor(frames[i][j]->backgroundRole(), prnt->palette().color(prnt->backgroundRole()));
            frames[i][j]->setPalette(pal);
        }
    }

    QTime time = QTime::currentTime();
    size_t cnt = 0;
    std::set<int> s; /// множество для уникальности
    switch(number) { /// рабираем время на разряды
        case 0: cnt = time.hour() / 10; break;
        case 1: cnt = time.hour() % 10; break;
        case 2: cnt = time.minute() / 10; break;
        default:
            cnt = time.minute() % 10;
    }
    while(s.size() != cnt) { /// заполняем множество случайными позициями
        s.insert(generator.bounded(0, h * w));
    }

    for(int val : s) {
        QPalette pal; /// меняем цвета
        pal.setColor(frames[val % h][val / h]->backgroundRole(), color);
        frames[val % h][val / h]->setPalette(pal);
    }
}


Cube::~Cube()
{
    delete timer;
}

