#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include <QGraphicsItem>

class Cube : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    Cube(QPointF pos, QString number);

    QString getNum() {return number;}
    void updatePos(QPointF pos);
    void updateNum(QString number);
    void updateBox(QPointF pos, QString number);

private :
    void createColorBox();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QMap<int, QString> colorBox;
    QString number;
    QString color;
};


#endif // CUBE_H_INCLUDED
