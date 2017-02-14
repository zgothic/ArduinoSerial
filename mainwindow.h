#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "smarttable.h"
#include "task.h"
#include "tasklistwidget.h"
#include "lockdisplay.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSystemTrayIcon *tray;
    TaskListWidget *listOfTasks;
    QTabWidget *tab;
    LockDisplay *display;

    QAction *minimize;

public:
    MainWindow(SmartTable *table, QWidget *parent = 0)
        :QMainWindow(parent)
    {
        setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowCancelButtonHint );
        this->setWindowIcon( QIcon( QPixmap(":/ztable_icon0.png") ) );
        //this->setWindowFlags(Qt::Window);

        tab = new QTabWidget;
        display = new LockDisplay;

        listOfTasks = new TaskListWidget;
        //listOfTasks->setHidden(true);

        QAction *exit = new QAction("Exit", 0);
        exit->setText("&Exit");
        exit->setStatusTip("Exit the applicatioon");
        exit->setShortcut(QKeySequence("CTRL+E"));
        QObject::connect(exit, SIGNAL(triggered(bool)), qApp, SLOT( quit() ));

        minimize = new QAction("Minimize the window", 0);
        minimize->setText("Minimize the window");
        QObject::connect(this, SIGNAL( signalMinimize(bool) ), this, SLOT( setTextMinimize(bool) ));
        QObject::connect(minimize, SIGNAL( triggered(bool) ), this, SLOT( slotShowHide() ));
        //Object::connect(this, SIGNAL(), this, SLOT( setTextMinimize(bool) ));

        QAction *tasks = new QAction("&Tasks", 0);
        tasks->setText("&My tasks");
        tasks->setStatusTip("List of my tasks");
        tasks->setShortcut(QKeySequence("CTRL+T"));
        QObject::connect(tasks, SIGNAL(triggered(bool)), this, SLOT( slotShowListOfTasks() ));

        QMenu *menuTray = new QMenu;
        menuTray->addAction(minimize);
        menuTray->addAction(tasks);
        menuTray->addSeparator();
        menuTray->addAction(exit);


        tray = new QSystemTrayIcon;
        tray->setToolTip("The smart office table - zTable");
        tray->setIcon(QIcon(QPixmap(":/ztable_icon0.png")));
        tray->setContextMenu(menuTray);
        tray->show();

        tab->addTab(listOfTasks, "Tasks list");

        setCentralWidget(tab);

        connect(table, SIGNAL( signalBlue(bool) ), SLOT( slotHumanHasBeenConnected(bool) ));
        connect(table, SIGNAL( signalOrange() ), SLOT( slotOrange() ) );
        connect(table, SIGNAL( signalRed() ), SLOT( slotRed() ) );
        connect(table, SIGNAL( signalLight() ), SLOT( slotLight() ) );
        connect(table, SIGNAL( signalNewTask(int) ), listOfTasks, SLOT( slotNewTask(int) ) );
        connect(table, SIGNAL( signalDeleteTask(int) ), listOfTasks, SLOT( slotDeleteTask(int) ) );
        connect(table, SIGNAL( signalShowTask(int) ), listOfTasks, SLOT( slotShowTask(int) ) );
        connect(table, SIGNAL( signalBlue(bool)), display, SLOT( slotLockScreen(bool) ));

        this->setWindowTitle("The smart office table - zTable");

    }

signals:
    void signalMinimize(bool);
private slots:

    void setTextMinimize(bool min)
    {
        if(min)
        {
            minimize->setText("Maximize the window");
        }
        else
        {
            minimize->setText("Minimize the window");
        }
    }

    void slotShowHide()
    {
        if(this->isHidden())
        {
            show();
            signalMinimize(false);
        }
        else
        {
            hide();
            signalMinimize(true);
        }
    }

    virtual void hideEvent(QHideEvent *event)
    {
        signalMinimize(true);
    }

private slots:
    void slotHumanHasBeenConnected(bool imHere)
    {
        if(imHere)
            tray->showMessage("Blue", "You connected", QSystemTrayIcon::NoIcon, 3000);
        if(!imHere)
            tray->showMessage("Blue", "You disconnected", QSystemTrayIcon::NoIcon, 3000);
    }

    void slotOrange()
    {
        tray->showMessage("Orange", "Recommended safe while in a sitting position left. We offer you a little move.", QSystemTrayIcon::Information, 3000);
    }

    void slotRed()
    {
        tray->showMessage("Red", "Attention! A further condition in the sitting position is harmful to health!", QSystemTrayIcon::Information, 3000);
    }

    void slotLight()
    {
        tray->showMessage("Light", "Light is low", QSystemTrayIcon::Information, 3000);
    }

    void slotShowListOfTasks()
    {
        listOfTasks->show();
    }

private:
    virtual void closeEvent(QCloseEvent *event)
    {
        this->hide();
        signalMinimize(true);
        event->ignore();
    }

};

#endif // MAINWINDOW_H
