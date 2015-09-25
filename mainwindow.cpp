// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenesystem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->modelView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->modelView->addAction(new QAction("Текст", this));

    m_labelIterations = new QLabel;
    ui->statusbar->addPermanentWidget(m_labelIterations, 1);
    updateLabelIterations(0);

    m_sliderTime = new QSlider(this);
    m_sliderTime->setMaximum(200);
    m_sliderTime->setMinimum(1);
    m_sliderTime->setValue(100);
    m_sliderTime->setOrientation(Qt::Horizontal);
    m_sliderTime->setToolTip(tr("Скорость симуляции"));
    ui->statusbar->addPermanentWidget(m_sliderTime, 2);

    createConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateLabelIterations(int count)
{
    m_labelIterations->setText(QString(tr("Номер итерации ")) + QString::number(count));
}

void MainWindow::createConnections()
{
    connect(ui->actionAboutQt, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
    connect(ui->actionPlay, SIGNAL(triggered(bool)), ui->modelView->scene(), SLOT(play()));
    connect(ui->actionPause, SIGNAL(triggered(bool)), ui->modelView->scene(), SLOT(pause()));
    connect(m_sliderTime, SIGNAL(sliderMoved(int)), ui->modelView->scene(), SLOT(setCoefficentTimeStep(int)));
    connect(ui->modelView->scene(), SIGNAL(newCountSteps(int)), this, SLOT(updateLabelIterations(int)));
    connect(ui->actionNew, SIGNAL(triggered(bool)), ui->modelView->scene(), SLOT(clearModel()));
}

