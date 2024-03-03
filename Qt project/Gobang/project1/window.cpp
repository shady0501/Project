#include "window.h"
#include <QTime>
#include <QLabel>

Window::Window()
{

}

void Window::showCurrentTime(QWidget *w)
{
    QTime qtime;
    qtime = QTime::currentTime();
    QString str = qtime.toString();

    QLabel* label1 = new QLabel(w);
    label1->setText(str);
    label1->move(0,w->height()-label1->height());

}

void Window::setFormat(QWidget *w, const QString& str)
{
    w->setWindowTitle(str);

    w->setWindowIcon(QPixmap());
}
