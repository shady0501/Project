#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "window.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Window windows;
    windows.showCurrentTime(this);

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

