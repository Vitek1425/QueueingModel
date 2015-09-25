// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include <QProgressBar>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QPainter>
#include <QDebug>
#include "ElementsSystem/queueSystem.h"

QueueSystem::QueueSystem(QGraphicsItem *parent) : ElementSystem(parent)
{
    m_countRequests = 0;
    m_maxCountRequests = 10;

    m_progressBar = new QProgressBar;
    m_progressBar->setOrientation(Qt::Vertical);
    m_progressBar->setMaximum(m_maxCountRequests);
    m_progressBar->setValue(m_countRequests);
    m_size = QSize(150, 100);
    m_raduisInput = 3;
    m_centerLeftInput = QPointF(m_raduisInput + 2, m_size.height()/2);
    m_centerRightInput = QPointF(m_size.width() - m_raduisInput - 2, m_size.height()/2);

    m_proxyBar = new QGraphicsProxyWidget(this);
    m_proxyBar->setWidget(m_progressBar);
    m_proxyBar->setGeometry(QRectF(10, 3, 20, m_size.height() - 5));
    updateGeometryProgressBar();
    setNameElement("Очередь");
}

QRectF QueueSystem::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void QueueSystem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(getColorFrame()));
    painter->setBrush(QBrush(getColorBackground()));
    drawBackground(painter);
    drawInputs(painter);
    drawName(painter);
    drawNameType(painter);
    drawCountsRequests(painter);
}

bool QueueSystem::isFree()
{
    if (m_countRequests < m_maxCountRequests)
        return true;
    //else
        return false;
}

QPointF QueueSystem::getCenterLeftInput()
{
    return m_centerLeftInput;
}

QPointF QueueSystem::getCenterRightInput()
{
    return m_centerRightInput;
}


QSize QueueSystem::getSize() const
{
    return m_size;
}

void QueueSystem::setSize(const QSize &size)
{
    prepareGeometryChange();
    m_size = size;
    updateCenterInputPosition();
    updateGeometryProgressBar();
    update();
}

int QueueSystem::getCountRequests() const
{
    return m_countRequests;
}

void QueueSystem::setCountRequests(int countRequests)
{
    m_countRequests = countRequests;
    update();
    m_progressBar->setValue(countRequests);
}

int QueueSystem::getMaxCountRequests() const
{
    return m_maxCountRequests;
}

void QueueSystem::setMaxCountRequests(int maxCountRequest)
{
    m_maxCountRequests = maxCountRequest;
    update();
    m_progressBar->setMaximum(maxCountRequest);
}

QString QueueSystem::getNameTypeQueue() const
{
    return m_nameTypeQueue;
}

void QueueSystem::setNameTypeQueue(const QString &nameTypeQueue)
{
    m_nameTypeQueue = nameTypeQueue;
    update();
}


void QueueSystem::drawBackground(QPainter *painter)
{
    painter->save();
    painter->drawRoundedRect(boundingRect(), 3, 3);
    painter->restore();
}

void QueueSystem::drawName(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(26, 0, m_size.width() - 26, m_size.height() / 3),
                      getNameElement(),
                      QTextOption(Qt::AlignCenter));
    painter->restore();
}

void QueueSystem::drawInputs(QPainter *painter)
{
    painter->save();
    painter->drawEllipse(m_centerLeftInput, m_raduisInput, m_raduisInput);
    painter->drawEllipse(m_centerRightInput, m_raduisInput, m_raduisInput);
    painter->restore();
}

void QueueSystem::drawNameType(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(35, m_size.height() / 4, m_size.width() - 35, m_size.height() / 3),
                      m_nameTypeQueue,
                      QTextOption(Qt::AlignLeft));
    painter->restore();
}

void QueueSystem::drawCountsRequests(QPainter *painter)
{
    painter->save();
    painter->setPen(getColorText());
    painter->drawText(QRect(35, m_size.height() / 2, m_size.width() - 35, m_size.height() / 3),
                      QString(tr("Число элемнтов ")) + QString::number(m_countRequests),
                      QTextOption(Qt::AlignLeft));
    painter->drawText(QRect(35, 3 * m_size.height() / 4, m_size.width() - 35, m_size.height() / 3),
                      QString(tr("Максимум ")) + QString::number(m_maxCountRequests),
                      QTextOption(Qt::AlignLeft));
    painter->restore();
}

void QueueSystem::updateCenterInputPosition()
{
    m_centerLeftInput = QPointF(m_raduisInput + 2, m_size.height()/2);
    m_centerRightInput = QPointF(m_size.width() - m_raduisInput - 2, m_size.height()/2);
}

void QueueSystem::updateGeometryProgressBar()
{
    int margin = 3;
    m_proxyBar->setGeometry(QRectF(3 * m_raduisInput + 1,
                                   margin,
                                   20,
                                   m_size.height() - 2 * margin));
}


