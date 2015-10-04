// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef DIALOGDEVICE_H
#define DIALOGDEVICE_H

#include <QDialog>

class Device;

namespace Ui {
class DialogDevice;
}

class DialogDevice : public QDialog
{
    Q_OBJECT

public:
    explicit DialogDevice(Device *device, QWidget *parent = 0);
    ~DialogDevice();
private slots:
    void setupDefaultValues();
    void setupValuesDevice();
private:
    void loadValuesFromDevice();
    void createConnections();

    Ui::DialogDevice *ui;
    Device *m_device;
};

#endif // DIALOGDEVICE_H
