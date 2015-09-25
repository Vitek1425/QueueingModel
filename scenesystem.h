// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef SCENESYSTEM_H
#define SCENESYSTEM_H

#include <QGraphicsScene>

class Joint;
class Device;
class QTimer;

class SceneSystem : public QGraphicsScene
{
    Q_OBJECT
public:
    SceneSystem(QObject * parent = 0);    
public slots:
    void setCoefficentTimeStep(int coefficentTimeStep);
    void play();
    void pause();
    void clearModel();
private slots:
    void intCountSteps();
signals:
    void newCountSteps(int);
private:
    QTimer *m_timer;
    int m_timeStep;
    int m_coefficentTimeStep;
    int m_maxCoefficentTimeStep;
    int m_countSteps;
};

#endif // SCENESYSTEM_H
