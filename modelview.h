// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef MODELVIEW_H
#define MODELVIEW_H

#include <QGraphicsView>

class SceneSystem;
class Device;
class Joint;
class OutputStream;
class InputStream;
class QueueSystem;

class ModelView : public QGraphicsView
{
    Q_OBJECT
public:
    ModelView(QWidget * parent = 0);
    SceneSystem *scene() const;
protected:
    virtual void mousePressEvent(QMouseEvent *);
public slots:
    void addOutputStream();
    void addSIRO();
    void addLIFO();
    void addFIFO();
    void addDevice();
    void addInputStream();
private slots:
    void updateActions();
    void createActionJoint(Joint *joint);
    void createActionDevice(Device *device);
    void createActionQueue(QueueSystem *queue);
    void createActionOutputStream(OutputStream *stream);
    void createActionInputStream(InputStream *stream);
    void createActionProperties();

    void openDialogProperties();
private:
    SceneSystem *m_scene;
    QPoint m_pointLastClick;
};

#endif // MODELVIEW_H
