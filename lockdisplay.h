#ifndef LOCKDISPLAY_H
#define LOCKDISPLAY_H

#include <QtWidgets>
#include <QtTest/QTest>

class LockDisplay : public QLabel
{
    Q_OBJECT
public:
    LockDisplay(QWidget *parent = 0)
        :QLabel(parent)
    {
        setAlignment(Qt::AlignCenter | Qt::AlignHCenter);
    }
private:
    virtual void paintEvent(QPaintEvent *event)
    {
        QSize screenRect = QApplication::desktop()->size();

        int width = screenRect.width();
        int height = screenRect.height();

        QPainter painter(this);
        QBrush brush(Qt::black);
        painter.setBrush(brush);
        QPixmap image(":/lock.png");
        painter.drawRect( 0, 0, width, height);
        //painter.drawImage(image.rect(), QImage(":/lock.png") );
        painter.drawImage(width/2  - image.rect().width()/2, height/2 - image.rect().height()/2, QImage(":/lock.png"));
    }

    virtual void keyPressEvent(QKeyEvent *event)
    {
        if( event->key() == Qt::Key_Z)
        {
            this->hide();
        }
    }

public slots:
    void slotLockScreen(bool lock)
    {
        if(!lock)
        {
            QTest::qSleep(3000);
            this->showFullScreen();
        }
        else
            this->hide();
    }
};

#endif // LOCKDISPLAY_H
