#include "mainwindow.h"
#include "ui_mainwindow.h"
double firstNum;
bool userTypingSecondNum=false;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
    setWindowTitle("Calculator");
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
    connect(ui->pushButton_plus_minus,SIGNAL(released()),this,SLOT(operation_pressed()));
    connect(ui->pushButton_procent,SIGNAL(released()),this,SLOT(operation_pressed()));

    connect(ui->pushButton_plus,SIGNAL(released()),this,SLOT(math_operation_pressed()));
    connect(ui->pushButton_minus,SIGNAL(released()),this,SLOT(math_operation_pressed()));
    connect(ui->pushButton_ymnozit,SIGNAL(released()),this,SLOT(math_operation_pressed()));
    connect(ui->pushButton_delenie,SIGNAL(released()),this,SLOT(math_operation_pressed()));
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_ymnozit->setCheckable(true);
    ui->pushButton_delenie->setCheckable(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::digit_pres(){
    QPushButton * button=(QPushButton*)sender();
    double Nomber;
    QString newNomber;
    if ((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() ||
         ui->pushButton_ymnozit->isChecked() || ui->pushButton_delenie->isChecked()) && (!userTypingSecondNum)){
        Nomber=button->text().toDouble();
        userTypingSecondNum=true;
        newNomber=QString::number(Nomber,'g',15);
    }
    else{
        if (ui->label->text().contains('.')&& button->text()=="0"){
            newNomber=ui->label->text()+button->text();
        }
        else{
            Nomber=(ui->label->text()+button->text()).toDouble();
            newNomber=QString::number(Nomber,'g',15);
        }

    }


    ui->label->setText(newNomber);
}

void MainWindow::on_pushButton_zapitaia_released()
{
    ui->label->setText(ui->label->text()+".");
}

void MainWindow::operation_pressed(){
    QPushButton * button=(QPushButton*)sender();
    double Nomber;
    QString newNomber;
    if (button->text()=="+/-"){
        Nomber=ui->label->text().toDouble();
        Nomber=Nomber*-1;
        newNomber=QString::number(Nomber,'g',15);
        ui->label->setText(newNomber);
    }
    if (button->text()=="%"){
        Nomber=ui->label->text().toDouble();
        Nomber=Nomber*0.01;
        newNomber=QString::number(Nomber,'g',15);
        ui->label->setText(newNomber);
    }
}

void MainWindow::on_pushButton_Clear_released()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_ymnozit->setChecked(false);
    ui->pushButton_delenie->setChecked(false);
    userTypingSecondNum=false;
    ui->label->setText("0");
}


void MainWindow::on_pushButton_rawno_released()
{
    double Number;
    double secondNum;
    QString newNum;
    secondNum=ui->label->text().toDouble();
    if (ui->pushButton_plus->isChecked()){
        Number=firstNum+secondNum;
        newNum=QString::number(Number,'g',15);
        ui->label->setText(newNum);
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked()){
        Number=firstNum-secondNum;
        newNum=QString::number(Number,'g',15);
        ui->label->setText(newNum);
        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_ymnozit->isChecked()){
        Number=firstNum*secondNum;
        newNum=QString::number(Number,'g',15);
        ui->label->setText(newNum);
        ui->pushButton_ymnozit->setChecked(false);
    }
    else if (ui->pushButton_delenie->isChecked()){
        Number=firstNum/secondNum;
        newNum=QString::number(Number,'g',15);
        ui->label->setText(newNum);
        ui->pushButton_delenie->setChecked(false);
    }

    userTypingSecondNum=false;

}
void MainWindow::math_operation_pressed(){
    QPushButton * button=(QPushButton*)sender();
    firstNum=ui->label->text().toDouble();
    button->setChecked(true);
}

