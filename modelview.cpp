// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include <QDebug>
#include <QMouseEvent>
#include <QAction>
#include <typeinfo>
#include "modelview.h"
#include "scenesystem.h"
#include "ElementsSystem/device.h"
#include "joint.h"
#include "ElementsSystem/queueSystem.h"
#include "ElementsSystem/outputstream.h"
#include "ElementsSystem/inputstream.h"
#include "ElementsSystem/fifoqueue.h"
#include "ElementsSystem/lifoqueue.h"
#include "ElementsSystem/siroqueue.h"
#include <Gui/dialogdevice.h>
#include <Gui/dialogoutputstream.h>
#include <Gui/dialogqueue.h>

ModelView::ModelView(QWidget *parent) : QGraphicsView(parent)
{
    m_scene = new SceneSystem;
    setScene(m_scene);

    m_pointLastClick = QPoint(0, 0);

    connect(m_scene, SIGNAL(selectionChanged()), SLOT(updateActions()));
}

SceneSystem *ModelView::scene() const
{
    return m_scene;
}

void ModelView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        m_pointLastClick = event->pos();
        updateActions();
    }
    QGraphicsView::mousePressEvent(event);
}

void ModelView::addOutputStream()
{
    OutputStream *stream = new OutputStream;
    scene()->addItem(stream);
}

void ModelView::addSIRO()
{
    SIROQueue *queue = new SIROQueue;
    scene()->addItem(queue);
}

void ModelView::addLIFO()
{
    LIFOQueue *queue = new LIFOQueue;
    scene()->addItem(queue);
}

void ModelView::addFIFO()
{
    FIFOQueue *queue = new FIFOQueue;
    scene()->addItem(queue);
}

void ModelView::addDevice()
{
    Device *device = new Device;
    scene()->addItem(device);
}

void ModelView::addInputStream()
{
    InputStream *stream = new InputStream;
    scene()->addItem(stream);
}

void ModelView::updateActions()
{

    foreach (QAction *action, actions())
    {
         removeAction(action);
         action->deleteLater();
    }

    QGraphicsItem *item = itemAt(m_pointLastClick);
    if(!item)
        return;
    if(typeid(*item) == typeid(Joint))
    {
        Joint *joint = dynamic_cast<Joint*>(item);
        createActionJoint(joint);
    }
    else if(typeid(*item) == typeid(Device))
    {
        Device *device = dynamic_cast<Device*>(item);
        createActionDevice(device);
        createActionProperties();
    }
    else if(typeid(*item) == typeid(QueueSystem)||
           (typeid(*item) == typeid(FIFOQueue))||
           (typeid(*item) == typeid(LIFOQueue))||
           (typeid(*item) == typeid(SIROQueue)))
    {
        QueueSystem *queue = dynamic_cast<QueueSystem*>(item);
        createActionQueue(queue);
        createActionProperties();
    }
    else if(typeid(*item) == typeid(InputStream))
    {
        InputStream *inputStream = dynamic_cast<InputStream*>(item);
        createActionInputStream(inputStream);
    }
    else if(typeid(*item) == typeid(OutputStream))
    {
        OutputStream *outputStream = dynamic_cast<OutputStream*>(item);
        createActionOutputStream(outputStream);
        createActionProperties();
    }
}

void ModelView::createActionJoint(Joint *joint)
{
    QAction *actionDelete = new QAction("Удалить", this);
    addAction(actionDelete);
    connect(actionDelete, SIGNAL(triggered()), joint, SLOT(deleteJointWithAllElements()));
}

void ModelView::createActionDevice(Device *device)
{
    QAction *actionDelete = new QAction("Удалть", this);
    addAction(actionDelete);
    connect(actionDelete, SIGNAL(triggered()), device, SLOT(deleteElement()));
}

void ModelView::createActionQueue(QueueSystem *queue)
{
    QAction *actionDelete = new QAction("Удалть", this);
    addAction(actionDelete);
    connect(actionDelete, SIGNAL(triggered()), queue, SLOT(deleteElement()));
}

void ModelView::createActionOutputStream(OutputStream *stream)
{
    QAction *actionDelete = new QAction("Удалть", this);
    addAction(actionDelete);
    connect(actionDelete, SIGNAL(triggered()), stream, SLOT(deleteElement()));
}

void ModelView::createActionInputStream(InputStream *stream)
{
    QAction *actionDelete = new QAction("Удалть", this);
    addAction(actionDelete);
    connect(actionDelete, SIGNAL(triggered()), stream, SLOT(deleteElement()));
}

void ModelView::createActionProperties()
{
    QAction *actionProperties = new QAction("Свойства", this);
    addAction(actionProperties);
    connect(actionProperties, SIGNAL(triggered()), SLOT(openDialogProperties()));
}

void ModelView::openDialogProperties()
{
    QGraphicsItem *item = itemAt(m_pointLastClick);
    if(!item)
        return;

    if(typeid(*item) == typeid(Device))
    {
        Device *device = dynamic_cast<Device*>(item);
        DialogDevice *dialog = new DialogDevice(device, this);
        dialog->setModal(true);
        dialog->show();
    }
    else if(typeid(*item) == typeid(OutputStream))
    {
        OutputStream *stream = dynamic_cast<OutputStream*>(item);
        DialogOutputStream *dialog = new DialogOutputStream(stream, this);
        dialog->setModal(true);
        dialog->show();
    }
    else if(typeid(*item) == typeid(QueueSystem)||
            (typeid(*item) == typeid(FIFOQueue))||
            (typeid(*item) == typeid(LIFOQueue))||
            (typeid(*item) == typeid(SIROQueue)))
    {
        QueueSystem *queue = dynamic_cast<QueueSystem*>(item);
        DialogQueue *dialog = new DialogQueue(queue, this);
        dialog->setModal(true);
        dialog->show();
    }


}

