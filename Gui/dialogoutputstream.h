// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef DIALOGOUTPUTSTREAM_H
#define DIALOGOUTPUTSTREAM_H

#include <QDialog>

class OutputStream;

namespace Ui {
class DialogOutputStream;
}

class DialogOutputStream : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOutputStream(OutputStream *stream, QWidget *parent = 0);
    ~DialogOutputStream();
private slots:
    void setupValuesStream();
private:
    void loadValuesFromStream();

    Ui::DialogOutputStream *ui;
    OutputStream *m_stream;
};

#endif // DIALOGOUTPUTSTREAM_H
