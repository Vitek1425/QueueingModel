// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void updateLabelIterations(int count);
private:
    void createConnections();

    Ui::MainWindow *ui;
    QSlider *m_sliderTime;
    QLabel *m_labelIterations;
};

#endif // MAINWINDOW_H
