#include "container.h"

/* Получить значения из XML и создать группы квадратов */
Container::Container(QString file, QWidget *parent) :
    QWidget(parent)
{
    initializeFromXml(file);

    std::pair<int,int> pr[]= {{3, 1}, {3, 3}, {3, 2}, {3, 3}};

    for(int i = 0;i < 4;i++) {
        Cube *cube = new Cube(colors[i], cubeSize, pr[i].first, pr[i].second, i, this);
        cube->move(points[i].x(), points[i].y());
    }

}

/* Получаем данные из XML */
void Container::initializeFromXml(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly)) {
        QXmlStreamReader sr(&file); /// парсер XML
        do {

            QXmlStreamReader::TokenType token = sr.readNext();

            if (token == QXmlStreamReader::StartElement) {

                if (sr.name() == QString("group")) {

                    points[sr.attributes().value("number").toInt() - 1] =
                            QPoint(sr.attributes().value("x").toInt(), sr.attributes().value("y").toInt());
                    colors[sr.attributes().value("number").toInt() - 1] = setColor(sr.attributes().value("color").toString());

                } else if (sr.name() == QString("background")) {

                    QPalette pal;
                    QColor color = setColor(sr.attributes().value("color").toString());
                    backgroundColor = color;
                    pal.setColor(this->backgroundRole(), color);
                    this->setPalette(pal);

                } else if(sr.name() == QString("back")) {
                    this->setFixedSize(sr.attributes().value("width").toInt(), sr.attributes().value("height").toInt());
                } else if(sr.name() == QString("cube")) {
                    cubeSize.setHeight(sr.attributes().value("height").toInt());
                    cubeSize.setWidth(sr.attributes().value("width").toInt());
                }
            }
        } while(!sr.atEnd());
        file.close();
    } else {
        qDebug() << file.errorString();
    }
}

/* получить цвет [с учетом расположения в Enum] */
QColor Container::setColor(QString str)
{
    QString colors[] = { "red", "green", "blue", "cyan", "magenta", "black", "white"};
    QColor color;
    for(size_t i = 0;i < 7;i++) {
        if(str == colors[i]) {
            if(i < 5) {
                color = QColor(Qt::GlobalColor(Qt::red + i));
            } else {
                color =  QColor(Qt::GlobalColor(Qt::black + i - 5));
            }
            break;
        }
    }
    return color;
}
