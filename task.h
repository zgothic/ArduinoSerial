#ifndef TASK_H
#define TASK_H

#include <QtWidgets>

class Task : public QWidget
{
    Q_OBJECT
private:
    int id;
    QString nameOfTask;
    QDateTime timeOfTask;
    QHBoxLayout *horizontalLayout;

public:
    Task(int id = 0, QString name = "", QDateTime time = QDateTime::currentDateTime(), QWidget *parent = 0)
        :QWidget(parent)
    {
        if(!name.isEmpty())
            nameOfTask = name;
        if(time >= QDateTime::currentDateTime())
            timeOfTask = time;
        else if(time < QDateTime::currentDateTime())
            timeOfTask = QDateTime::currentDateTime().addSecs(60*10);
        this->id = id;

        horizontalLayout = new QHBoxLayout;

        QVBoxLayout *verticalLayout = new QVBoxLayout;

        QLabel *timeLabel = new QLabel;
        timeLabel->setText("Время: " + timeOfTask.time().toString());
        verticalLayout->addWidget(timeLabel);

        QLabel *dateLabel = new QLabel;
        dateLabel->setText("Дата: " + timeOfTask.date().toString("dd MMMM yyyy"));
        verticalLayout->addWidget(dateLabel);

        horizontalLayout->addLayout(verticalLayout, 1);

        QLabel *textLabel = new QLabel;
        textLabel->setText(nameOfTask);
        horizontalLayout->addWidget(textLabel, 3, Qt::AlignLeft);

        QVBoxLayout *buttonLayout = new QVBoxLayout;

        QPushButton *edit = new QPushButton("&Edit");
        connect(edit, SIGNAL(clicked(bool)), this, SLOT( slotEditTask() ) );
        buttonLayout->addWidget(edit, 1);
        //edit->setSizePolicy(QSizePolicy::Minimum);

        QPushButton *finish = new QPushButton("&Finish");
        connect(finish, SIGNAL(clicked(bool)), this, SLOT(slotDeleteTask()) );
        buttonLayout->addWidget(finish, 1);

        horizontalLayout->addLayout( buttonLayout );

        this->setLayout(horizontalLayout);
        this->resize(300, 80);
        this->setMaximumHeight(80);

        QFile file(":/style.qss");
        file.open(QFile::ReadOnly);
        QString strStyle = QLatin1String(file.readAll());
        this->setStyleSheet(strStyle);
    }

    Task(const Task &object)
        :QWidget( qobject_cast<QWidget*>( object.parent() ) )
    {
        id = object.getIdOfTask();
        nameOfTask = object.getNameOfTask();
        timeOfTask = object.getTimeOfTask();
    }

    void setNameOfTask(const QString &name)
    {
        nameOfTask = name;
    }

    void setTimeOfTask(const QDateTime &time)
    {
        timeOfTask = time;
    }

    void setId(int value)
    {
        id = value;
    }

    QString getNameOfTask() const
    {
        return nameOfTask;
    }

    QDateTime getTimeOfTask() const
    {
        return timeOfTask;
    }

    int getIdOfTask() const
    {
        return id;
    }

    ~Task()
    {

    }

private:
    virtual void paintEvent(QPaintEvent *event)
    {
        //QWidget::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::black, 2, Qt::DotLine));
        painter.setBrush( QBrush("#dcff8a") );
        painter.drawRect( rect() );
        QWidget::paintEvent(event);
    }

signals:
    void signalTaskDelete(int);
    void signalTaskEdit(Task*);

public slots:
    void slotDeleteTask()
    {
        this->setHidden(true);
        emit signalTaskDelete(id);
        //delete this;
    }

    void slotEditTask()
    {
        emit signalTaskEdit(this);
    }
};

#endif // TASK_H
