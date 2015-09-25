// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include <QPainter>
#include "ElementsSystem/inputstream.h"

InputStream::InputStream(QGraphicsItem *parent) : ElementSystem(parent)
{
    m_size = QSize(100, 100);
    m_raduisInput = 3;
    m_centerLeftInput = QPointF(m_raduisInput + 2, m_size.height() / 2);
    setNameElement("Входящий поток");
    m_countReceivingElements = 0;
}

QRectF InputStream::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void InputStream::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(getColorFrame()));
    painter->setBrush(QBrush(getColorBackground()));
    drawBackground(painter);
    drawName(painter);
    drawInput(painter);
    drawCountReceivingElements(painter);
}

bool InputStream::isFree()
{
    return true;
}

QPointF InputStream::getCenterLeftInput()
{
    return m_centerLeftInput;
}

QPointF InputStream::getCenterRightInput()
{
    return QPointF(0, 0);
}

QSize InputStream::getSize() const
{
    return m_size;
}

void InputStream::setSize(const QSize &size)
{
    prepareGeometryChange();
    m_size = size;
    updateCenterInputPosition();
    update();
}

void InputStream::addRequest(Request *request, ElementSystem *sender)
{
    m_countReceivingElements++;
    delete request;
    emit requestGotten(sender);
    update();
}

void InputStream::drawBackground(QPainter *painter)
{
    painter->save();
    painter->drawRoundedRect(boundingRect(), 3, 3);
    painter->restore();
}

void InputStream::drawName(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(0, 0, m_size.width(), m_size.height() / 3),
                      getNameElement(),
                      QTextOption(Qt::AlignHCenter | Qt::AlignTop));
    painter->restore();
}

void InputStream::drawInput(QPainter *painter)
{
    painter->save();
    painter->drawEllipse(m_centerLeftInput, m_raduisInput, m_raduisInput);
    painter->restore();
}

void InputStream::drawCountReceivingElements(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(0, m_size.height() / 3, m_size.width(), m_size.height() / 3),
                      QString(tr("Получено ")) + QString::number(m_countReceivingElements),
                      QTextOption(Qt::AlignHCenter | Qt::AlignTop));
    painter->restore();
}

void InputStream::updateCenterInputPosition()
{
    m_centerLeftInput = QPointF(m_raduisInput + 2, m_size.height() / 2);
}


