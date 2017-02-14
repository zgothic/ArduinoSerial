#ifndef TASKLISTWIDGET_H
#define TASKLISTWIDGET_H

#include <QtWidgets>
#include "task.h"
#include "newtaskwindow.h"

class TaskListWidget : public QLabel
{
    Q_OBJECT
private:
    QMap<int, Task *> *listOfTasks;
    QVBoxLayout *layoutListOfTasks;
    NewTaskWindow *newTaskWindow;
public:
    TaskListWidget(QWidget *parent = 0)
        :QLabel(parent)
    {
        listOfTasks = new QMap<int, Task *>;

        newTaskWindow = new NewTaskWindow;
        //newTaskWindow->setHidden(true);

        connect(newTaskWindow, SIGNAL(signalAddNewTask(Task *)), this, SLOT(slotAddNewTaskToList(Task *) ) );

        QPushButton *addTaskButton = new QPushButton("&Add new task");
        addTaskButton->setDefault(true);
        connect(addTaskButton, SIGNAL(clicked(bool)), this, SLOT( slotNewTaskIfNotFull() ) );

        layoutListOfTasks = new QVBoxLayout();

        QVBoxLayout *layoutWindow = new QVBoxLayout;
        layoutWindow->addWidget(addTaskButton, 0, Qt::AlignTop);
        layoutWindow->addLayout(layoutListOfTasks, 1);

        this->setAlignment(Qt::AlignCenter | Qt::AlignHCenter);

        //this->isReadOnly();
        this->resize(800, 400);
        this->setMinimumSize( QSize(800, 400) );
        this->setLayout(layoutWindow);
        this->setAlignment(Qt::AlignTop);
    }

public slots:
    void slotAddNewTaskToList(Task *object)
    {
        QString name = newTaskWindow->getNameOfTask();//object->getNameOfTask();
        QDateTime time = newTaskWindow->getTimeOfTask();//object->getTimeOfTask();

        qDebug() << "object->getIdOfTask() " << object->getIdOfTask();

        if( listOfTasks->contains( object->getIdOfTask() ) )
        {
            Task *task = listOfTasks->value(object->getIdOfTask());
            task->setNameOfTask( name );
            task->setTimeOfTask( time );
            qDebug() << name << " " << listOfTasks->value( object->getIdOfTask() )->getNameOfTask();

        }
        else
        {
            connect(object, SIGNAL( signalTaskDelete(int) ), this, SLOT( slotDeleteTaskFromTask(int) ) );
            connect(object, SIGNAL( signalTaskEdit(Task*) ), newTaskWindow, SLOT( slotEditTask(Task*) ) );
            listOfTasks->insert(object->getIdOfTask(), object);
            layoutListOfTasks->addWidget(object, 0, Qt::AlignTop);
        }
        newTaskWindow->setHidden(true);
    }

    void slotNewTaskIfNotFull()
    {
        qDebug() << listOfTasks->size();
        for(int value = 1; value < 4; value++)
        {
            qDebug() << "listOfTasks->contains " << value << listOfTasks->contains(value) ;
            if( listOfTasks->contains(value) == false )
            {
                slotNewTask(value);
                break;
            }
        }
                /*
        else
        {
            emit signalListIsFull();
        }*/
    }

    void slotNewTask(int value)
    {
        if( listOfTasks->contains(value) == false )
        {
            Task *tempTask = new Task( value, QString("Task " + QString::number(value)),
                                       QDateTime::currentDateTime().addSecs(60*10) );
            slotAddNewTaskToList(tempTask);
            newTaskWindow->slotEditTask(tempTask);
        }
    }

    void slotDeleteTask(int value)
    {
        listOfTasks->take(value)->slotDeleteTask();
        listOfTasks->remove(value);
        if( !newTaskWindow->isHidden() )
            newTaskWindow->setHidden(true);
    }

    void slotDeleteTaskFromTask(int value)
    {
        //listOfTasks->take(value)->slotDeleteTask();
        listOfTasks->remove(value);
    }

    void slotShowTask(int value)
    {
        if( listOfTasks->value(value) )
            newTaskWindow->slotEditTask(listOfTasks->take(value));
        //else
          //  slotNewTaskIfNotFull();
    }


private:
    void updateList()
    {
       /* foreach (Task *item, *listOfTasks)
        {
            layoutListOfTasks->addWidget(item);
        }*/
    }
};

#endif // TASKLISTWIDGET_H
