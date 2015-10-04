// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef DIALOGQUEUE_H
#define DIALOGQUEUE_H

#include <QDialog>

class QueueSystem;

namespace Ui {
class DialogQueue;
}

class DialogQueue : public QDialog
{
    Q_OBJECT

public:
    explicit DialogQueue(QueueSystem *queue, QWidget *parent = 0);
    ~DialogQueue();
private slots:
    void setupValuesQueue();
private:
    void loadValuesFromQueue();

    Ui::DialogQueue *ui;
    QueueSystem *m_queue;
};

#endif // DIALOGQUEUE_H
