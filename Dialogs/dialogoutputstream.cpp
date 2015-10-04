// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "dialogoutputstream.h"
#include "ui_dialogoutputstream.h"
#include "ElementsSystem/outputstream.h"

DialogOutputStream::DialogOutputStream(OutputStream *stream, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOutputStream),
    m_stream(stream)
{
    ui->setupUi(this);
    loadValuesFromStream();
    connect(ui->buttonBox, SIGNAL(accepted()), SLOT(setupValuesStream()));
}

DialogOutputStream::~DialogOutputStream()
{
    delete ui;
}

void DialogOutputStream::setupValuesStream()
{
    m_stream->setDensity(ui->spinBoxDensity->value());
}

void DialogOutputStream::loadValuesFromStream()
{
    ui->spinBoxDensity->setValue(m_stream->getDensity());
}
