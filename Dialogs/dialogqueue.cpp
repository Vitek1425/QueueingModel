// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "dialogqueue.h"
#include "ui_dialogqueue.h"
#include "ElementsSystem/queueSystem.h"

DialogQueue::DialogQueue(QueueSystem *queue, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogQueue),
    m_queue(queue)
{
    ui->setupUi(this);
    loadValuesFromQueue();
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(setupValuesQueue()));
}

DialogQueue::~DialogQueue()
{
    delete ui;
}

void DialogQueue::setupValuesQueue()
{
    m_queue->setNameElement(ui->lineEditName->text());
    m_queue->setMaxCountRequests(ui->spinBoxMaxCountRequests->value());
}

void DialogQueue::loadValuesFromQueue()
{
    ui->lineEditName->setText(m_queue->getNameElement());
    ui->spinBoxMaxCountRequests->setValue(m_queue->getMaxCountRequests());
}
