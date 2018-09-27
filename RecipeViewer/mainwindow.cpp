#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set initial values
    setWindowTitle("Mijn Kookboek");
}

MainWindow::~MainWindow()
{
    delete ui;
}
