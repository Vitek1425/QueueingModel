// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef ELEMENTSYSTEM_H
#define ELEMENTSYSTEM_H

#include <QGraphicsObject>
#include <QSet>

class Request;

class ElementSystem : public QGraphicsObject
{
    Q_OBJECT
public:
    ElementSystem(QGraphicsItem * parent = 0);
    virtual void addChildElement(ElementSystem *child);
    virtual void addParentElement(ElementSystem *parent);
    virtual void deleteChildElement(ElementSystem *child);
    virtual void deleteParentElement(ElementSystem *parent);
    virtual bool isFree() = 0;
    virtual QPointF getCenterLeftInput() = 0;
    virtual QPointF getCenterRightInput() = 0;
    virtual bool isChild(ElementSystem *element);
    virtual bool isParent(ElementSystem *element);
    virtual QSize getSize() const = 0;
    virtual void setSize(const QSize &size) = 0;
    virtual void addRequest(Request *request, ElementSystem *sender) = 0;

    QString getNameElement() const;
    void setNameElement(const QString &nameElement);

    QColor getColorBackground() const;
    void setColorBackground(const QColor &colorBackground);

    QColor getColorFrame() const;
    void setColorFrame(const QColor &colorFrame);

    QColor getColorText() const;
    void setColorText(const QColor &colorText);

public slots:
    void deleteElement();

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    QSet<ElementSystem*> m_parents;
    QSet<ElementSystem*> m_children;

    bool m_isModeAddChild;
    QGraphicsLineItem *m_lineModeAddChild;
signals:
    void positionChanged();
    void requestGotten(ElementSystem *sender);
private:
    QString m_nameElement;
    QColor m_colorBackground;
    QColor m_colorFrame;
    QColor m_colorText;
};

#endif // ELEMENTSYSTEM_H
