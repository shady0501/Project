#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>


class Window
{
public:
    Window();
    void setFormat(QWidget*, const QString&);//窗口名称，图标……
    void showCurrentTime(QWidget*);

};

#endif // WINDOW_H
