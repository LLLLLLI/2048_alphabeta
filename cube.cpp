#include <QtGui>

#include "cube.h"

Cube::Cube(QPointF pos, QString number)
{
    setPos(pos);
    this->number = number;
    createColorBox();
    this->color = colorBox.value(number.toInt());
    setFlag(QGraphicsItem::ItemIsFocusable);    //���Ա�presskey�Ȳ���
}

void Cube::createColorBox()
{
    colorBox.insert(0, tr("#ccc0b2"));
    colorBox.insert(2, tr("#eee4da"));
    colorBox.insert(4, tr("#ece0c8"));
    colorBox.insert(8, tr("#f2b179"));
    colorBox.insert(16, tr("#f59563"));
    colorBox.insert(32, tr("#f57c5f"));
    colorBox.insert(64, tr("#f65d38"));
    colorBox.insert(128, tr("#edc171"));
    colorBox.insert(256, tr("#edcc61"));
    colorBox.insert(512, tr("#ecc850"));
    colorBox.insert(1024, tr("#edc53f"));
    colorBox.insert(2048, tr("#efc4ef"));
    colorBox.insert(4096, tr("#ccc0b2"));
    colorBox.insert(8192, tr("#eee4da"));
    colorBox.insert(16384, tr("#ece0c8"));

}

void Cube::updatePos(QPointF pos)
{
    setPos(pos);
    update(boundingRect());
}

void Cube::updateNum(QString number)
{
    this->number = number;
    this->color = colorBox.value(number.toInt());
    update(boundingRect());
}

void Cube::updateBox(QPointF pos, QString number)
{
    setPos(pos);
    this->number = number;
    this->color = colorBox.value(number.toInt());
    update(boundingRect());
}

QRectF Cube::boundingRect() const
{
    int penWidth = 1;       //�߿�Ŀ��
    return QRectF(0-penWidth/2, 0-penWidth/2, 100 + penWidth, 100 + penWidth);  //���ǽ��߿�Ŀ��
}

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QColor(color));  //�����߿���ɫ
    painter->setBrush(QBrush(QColor(color)));
    painter->drawRect(QRectF(0, 0, 100, 100));
    switch(number.length())
    {
    case 1 :
        painter->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 50, QFont::Bold));   //Bold�ǼӴֵ���˼
        break;
    case 2 :
        painter->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 40, QFont::Bold));
        break;
    case 3 :
        painter->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 25, QFont::Bold));
        break;
    case 4 :
        painter->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 20, QFont::Bold));
        break;
    case 5 :
        painter->setFont(QFont(QString::fromLocal8Bit("΢���ź�"), 15, QFont::Bold));
        break;
    }
    if(number.toInt() == 2 || number.toInt() == 4)
    {
        painter->setPen(QColor("#7c736a"));      //����������ɫ
        painter->drawText(QRectF(0, 0, 100, 100), Qt::AlignCenter, number);   //�ڶ������������õ��м�
    }
    else if(number.toInt() >= 8)
    {
        painter->setPen(QColor("#fff7eb"));
        painter->drawText(QRectF(0, 0, 100, 100), Qt::AlignCenter, number);   //�ڶ������������õ��м�
    }                //0�Ͳ�����
}
