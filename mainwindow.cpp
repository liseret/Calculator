#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_1,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_2,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_3,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_4,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_5,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_6,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_7,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_8,SIGNAL(released()),this,SLOT(digit_pres()));
    connect(ui->pushButton_9,SIGNAL(released()),this,SLOT(digit_pres()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::digit_pres(){
    QPushButton * button=(QPushButton*)sender();
    double Nomber;
    QString newNomber;
    Nomber=(ui->label->text()+button->text()).toDouble();
    newNomber=QString::number(Nomber,'g',15);
    ui->label->setText(newNomber);
}
