#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Calculator");
    setFocusPolicy(Qt::StrongFocus);
    setupConnections();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::setDisplayText(const QString &text){
    ui->label->setText(text);
}

QString MainWindow::getDisplayText() const{
    return ui->label->text();
}

void MainWindow::resetOperationButtons(){
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_ymnozit->setChecked(false);
    ui->pushButton_delenie->setChecked(false);
}

void MainWindow::setupConnections(){
    connect(ui->pushButton_0, &QPushButton::clicked, [this]() { emit digitClicked(0); });
    connect(ui->pushButton_1, &QPushButton::clicked, [this]() { emit digitClicked(1); });
    connect(ui->pushButton_2, &QPushButton::clicked, [this]() { emit digitClicked(2); });
    connect(ui->pushButton_3, &QPushButton::clicked, [this]() { emit digitClicked(3); });
    connect(ui->pushButton_4, &QPushButton::clicked, [this]() { emit digitClicked(4); });
    connect(ui->pushButton_5, &QPushButton::clicked, [this]() { emit digitClicked(5); });
    connect(ui->pushButton_6, &QPushButton::clicked, [this]() { emit digitClicked(6); });
    connect(ui->pushButton_7, &QPushButton::clicked, [this]() { emit digitClicked(7); });
    connect(ui->pushButton_8, &QPushButton::clicked, [this]() { emit digitClicked(8); });
    connect(ui->pushButton_9, &QPushButton::clicked, [this]() { emit digitClicked(9); });
    connect(ui->pushButton_plus, &QPushButton::clicked, [this]() {
        ui->pushButton_plus->setChecked(true);
        emit operationClicked("+");
    });
    connect(ui->pushButton_minus, &QPushButton::clicked, [this]() {
        ui->pushButton_minus->setChecked(true);
        emit operationClicked("-");
    });
    connect(ui->pushButton_ymnozit, &QPushButton::clicked, [this]() {
        ui->pushButton_ymnozit->setChecked(true);
        emit operationClicked("×");
    });
    connect(ui->pushButton_delenie, &QPushButton::clicked, [this]() {
        ui->pushButton_delenie->setChecked(true);
        emit operationClicked("÷");
    });
    connect(ui->pushButton_rawno, &QPushButton::clicked, this, &MainWindow::equalsClicked);
    connect(ui->pushButton_Clear, &QPushButton::clicked, this, &MainWindow::clearClicked);
    connect(ui->pushButton_zapitaia, &QPushButton::clicked, this, &MainWindow::decimalClicked);
    connect(ui->pushButton_plus_minus, &QPushButton::clicked, this, &MainWindow::plusMinusClicked);
    connect(ui->pushButton_procent, &QPushButton::clicked, this, &MainWindow::percentClicked);
}

void MainWindow::onDigitButton(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        int digit = button->text().toInt();
        emit digitClicked(digit);
    }
}

void MainWindow::onOperationButton(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        QString operation = button->text();
        resetOperationButtons();
        button->setChecked(true);
        emit operationClicked(operation);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    int key = event->key();
    if (key >= Qt::Key_0 && key <= Qt::Key_9) {
        emit digitClicked(key - Qt::Key_0);
    }
    else if (key == Qt::Key_Plus) {
        ui->pushButton_plus->setChecked(true);
        emit operationClicked("+");
    }
    else if (key == Qt::Key_Minus) {
        ui->pushButton_minus->setChecked(true);
        emit operationClicked("-");
    }
    else if (key == Qt::Key_Asterisk) {
        ui->pushButton_ymnozit->setChecked(true);
        emit operationClicked("×");
    }
    else if (key == Qt::Key_Slash) {
        ui->pushButton_delenie->setChecked(true);
        emit operationClicked("÷");
    }
    else if (key == Qt::Key_Enter || key == Qt::Key_Return || key == Qt::Key_Equal) {
        emit equalsClicked();
    }
    else if (key == Qt::Key_Escape || key == Qt::Key_Delete) {
        emit clearClicked();
    }
    else if (key == Qt::Key_Comma || key == Qt::Key_Period) {
        emit decimalClicked();
    }
}
