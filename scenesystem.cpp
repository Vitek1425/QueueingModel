// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <typeinfo>
#include <QTimer>
#include "scenesystem.h"
#include "ElementsSystem/device.h"
#include "joint.h"
#include "ElementsSystem/queueSystem.h"
#include "ElementsSystem/outputstream.h"
#include "ElementsSystem/inputstream.h"
#include "ElementsSystem/fifoqueue.h"
#include "ElementsSystem/lifoqueue.h"
#include "ElementsSystem/siroqueue.h"

SceneSystem::SceneSystem(QObject *parent) : QGraphicsScene(parent)
{
    m_timeStep = 100;
    m_coefficentTimeStep = 100;
    m_maxCoefficentTimeStep = 200;

    m_timer = new QTimer;
    connect(m_timer, SIGNAL(timeout()), SLOT(advance()));
    connect(m_timer, SIGNAL(timeout()), SLOT(intCountSteps()));
}

void SceneSystem::setCoefficentTimeStep(int coefficentTimeStep)
{
    if ((coefficentTimeStep < 1)||
       (coefficentTimeStep > m_maxCoefficentTimeStep))
        return;
    pause();
    m_coefficentTimeStep = coefficentTimeStep;
    play();
}

void SceneSystem::play()
{
    m_timer->start(m_coefficentTimeStep * m_timeStep / m_maxCoefficentTimeStep);
}

void SceneSystem::pause()
{
    m_timer->stop();
}

void SceneSystem::clearModel()
{
    clear();
    m_timer->stop();
    m_countSteps = 0;
    newCountSteps(m_countSteps);
}

void SceneSystem::intCountSteps()
{
    m_countSteps++;
    emit newCountSteps(m_countSteps);
}

