#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "windows.h"
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);   
    ~MainWindow();

    void setWindowState(QWidget*, const QString& = NULL, const QString& = NULL);

    void setButtonState(QWidget*, const QString& = NULL, int = 0, int = 0, const QString& = NULL);

    void paintEvent(QPaintEvent*);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
