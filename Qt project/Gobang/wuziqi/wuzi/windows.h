#ifndef WINDOWS_H
#define WINDOWS_H
#include "mainwindow.h"
#include <QWidget>

class Windows:public QWidget
{
public:
    Windows(QWidget*, const QString& = NULL, const QString& = NULL);
    void setButtonStatus(QWidget*, const QString& = NULL, int = 0, int = 0);
    void paintEvent(QPaintEvent*);

private:
    QString Qname;
};

#endif // WINDOWS_H
