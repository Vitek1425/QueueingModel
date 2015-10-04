// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "dialogdevice.h"
#include "ui_dialogdevice.h"
#include "ElementsSystem/device.h"

DialogDevice::DialogDevice(Device *device, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDevice),
    m_device(device)
{
    ui->setupUi(this);

    loadValuesFromDevice();
    createConnections();
}

DialogDevice::~DialogDevice()
{
    delete ui;
}

void DialogDevice::setupDefaultValues()
{
    ui->spinBoxLeftRange->setValue(10);
    ui->spinBoxRightRange->setValue(20);
    ui->textEditFunction->setText("(function(x) { return (x-10)/10; })");
    ui->lineEditName->setText(m_device->getNameElement());
}

void DialogDevice::setupValuesDevice()
{
    m_device->setLeftBorderDistribution(ui->spinBoxLeftRange->value());
    m_device->setRightBorderDistribution(ui->spinBoxRightRange->value());
    m_device->setDistributionFunction(ui->textEditFunction->toPlainText());
    m_device->setNameElement(ui->lineEditName->text());
}

void DialogDevice::loadValuesFromDevice()
{
    if(m_device->getRightBorderDistribution() <= m_device->getLeftBorderDistribution())
        return;
    ui->spinBoxLeftRange->setValue(m_device->getLeftBorderDistribution());
    ui->spinBoxRightRange->setValue(m_device->getRightBorderDistribution());
    ui->textEditFunction->setText(m_device->getDistributionFunction());
    ui->lineEditName->setText(m_device->getNameElement());
}

void DialogDevice::createConnections()
{
    connect(ui->buttonDefault, SIGNAL(clicked(bool)), SLOT(setupDefaultValues()));
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(setupValuesDevice()));
}

