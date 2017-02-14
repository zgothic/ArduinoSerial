#ifndef NEWTASKWINDOW_H
#define NEWTASKWINDOW_H

#include <QtWidgets>
#include "task.h"

class NewTaskWindow : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *nameOfTask;
    QDateTimeEdit *dateOfTask;
    Task *bufferTask;
public:
    NewTaskWindow(QWidget *parent = 0)
        :QWidget(parent)
    {
        bufferTask = new Task;

        QVBoxLayout *layoutNewTask = new QVBoxLayout;

        nameOfTask = new QLineEdit;
        nameOfTask->setText("Enter your text here");
        nameOfTask->setMaxLength(256);

        QLabel *nameOfTaskLabel = new QLabel("&Name of task:");
        nameOfTaskLabel->setBuddy(nameOfTask);

        dateOfTask = new QDateTimeEdit;
        dateOfTask->setDateTime(QDateTime::currentDateTime().addSecs(60*10));

        QLabel *dateOfTaskLabel = new QLabel("&Date:");
        dateOfTaskLabel->setBuddy(nameOfTask);

        QPushButton *addTaskButton = new QPushButton("&OK");
        addTaskButton->setDefault(true);
        QPushButton *cancelTaskButton = new QPushButton("&Cancel");

        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(cancelTaskButton);
        buttonLayout->addWidget(addTaskButton);

        connect(addTaskButton, SIGNAL(clicked(bool)), SLOT( slotAddNewTask() ) );
        connect(cancelTaskButton, SIGNAL(clicked(bool)), SLOT( slotClose() ) );

        layoutNewTask->addWidget(nameOfTaskLabel);
        layoutNewTask->addWidget(nameOfTask);
        layoutNewTask->addWidget(dateOfTaskLabel);
        layoutNewTask->addWidget(dateOfTask);
        layoutNewTask->addLayout(buttonLayout);

        this->setLayout(layoutNewTask);
        this->resize(400, 150);
        this->setWindowTitle("Edit task");
        //this->show();
    }

    QString getNameOfTask() const
    {
        return nameOfTask->text();
    }

    QDateTime getTimeOfTask() const
    {
        return dateOfTask->dateTime();
    }

    int getIdOfTask() const
    {
        return bufferTask->getIdOfTask();
    }

signals:
    void signalAddNewTask(Task *);

private slots:
    void slotClose()
    {
        this->close();
        bufferTask->slotDeleteTask();
    }

public slots:
    void slotAddNewTask()
    {
        if(nameOfTask->text().length() >= 4)
        {
            qDebug() << "nameOfTask->text(): " << nameOfTask->text();
            bufferTask->setNameOfTask( nameOfTask->text() );
            bufferTask->setTimeOfTask( dateOfTask->dateTime() );
            emit signalAddNewTask(bufferTask);
        }
    }

    void slotEditTask(Task *object)
    {
        bufferTask = object;
        //bufferTask->setId( object->getIdOfTask() );
        //id->setId( object->getIdOfTask() );
        nameOfTask->setText( object->getNameOfTask() );
        dateOfTask->setDateTime( object->getTimeOfTask() );
        this->show();
    }
};

#endif // NEWTASKWINDOW_H
