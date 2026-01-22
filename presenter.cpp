#include "presenter.h"
#include "mainwindow.h"
#include "model.h"
#include "historymanager.h"

#include <QString>

CalculatorPresenter::CalculatorPresenter(QObject *parent)
    : QObject(parent)
    , m_view(nullptr)
    , m_model(nullptr)
    , m_history(HistoryManager::getInstance())
    , m_firstNumber(0)
    , m_waitingForOperand(true)
    , m_currentDisplay("0")
{
}

CalculatorPresenter::~CalculatorPresenter() {}

void CalculatorPresenter::setView(MainWindow *view){
    m_view = view;
}
void CalculatorPresenter::setModel(CalculatorModel *model) {
    m_model = model;
    connect(m_model, &CalculatorModel::error, this, &CalculatorPresenter::onModelError);
}
void CalculatorPresenter::initialize() {
    if (!m_view || !m_model) return;
    connect(m_view, &MainWindow::digitClicked, this, &CalculatorPresenter::onDigitClicked);
    connect(m_view, &MainWindow::operationClicked, this, &CalculatorPresenter::onOperationClicked);
    connect(m_view, &MainWindow::equalsClicked, this, &CalculatorPresenter::onEqualsClicked);
    connect(m_view, &MainWindow::clearClicked, this, &CalculatorPresenter::onClearClicked);
    connect(m_view, &MainWindow::decimalClicked, this, &CalculatorPresenter::onDecimalClicked);
    connect(m_view, &MainWindow::plusMinusClicked, this, &CalculatorPresenter::onPlusMinusClicked);
    connect(m_view, &MainWindow::percentClicked, this, &CalculatorPresenter::onPercentClicked);

    reset();
}
void CalculatorPresenter::onDigitClicked(int digit) {
    if (m_waitingForOperand) {
        m_currentDisplay = QString::number(digit);
        m_waitingForOperand = false;
    } else {
        m_currentDisplay += QString::number(digit);
    }
    updateDisplay();
}

void CalculatorPresenter::onOperationClicked(const QString &operation) {
    if (!m_pendingOperation.isEmpty()) {
        calculate();
    }

    m_firstNumber = m_currentDisplay.toDouble();
    m_pendingOperation = operation;
    m_waitingForOperand = true;
}

void CalculatorPresenter::onEqualsClicked() {
    if (!m_pendingOperation.isEmpty()) {
        calculate();
        m_pendingOperation.clear();
    }
}

void CalculatorPresenter::onClearClicked() {
    reset();
    if (m_view) {
        m_view->setDisplayText("0");
    }
}

void CalculatorPresenter::onDecimalClicked() {
    if (m_waitingForOperand) {
        m_currentDisplay = "0.";
        m_waitingForOperand = false;
    } else if (!m_currentDisplay.contains('.')) {
        m_currentDisplay += ".";
    }
    updateDisplay();
}

void CalculatorPresenter::onPlusMinusClicked() {
    if (m_model) {
        double value = m_model->changeSign(m_currentDisplay.toDouble());
        m_currentDisplay = QString::number(value, 'g', 15);
        updateDisplay();
    }
}

void CalculatorPresenter::onPercentClicked() {
    if (m_model) {
        double value = m_model->percent(m_currentDisplay.toDouble());
        m_currentDisplay = QString::number(value, 'g', 15);
        updateDisplay();
    }
}

void CalculatorPresenter::onModelError(const QString &error) {
    if (m_view) {
        m_view->setDisplayText(error);
        reset();
    }
}

void CalculatorPresenter::updateDisplay() {
    if (m_view) {
        m_view->setDisplayText(m_currentDisplay);
    }
}

void CalculatorPresenter::reset() {
    m_currentDisplay = "0";
    m_firstNumber = 0;
    m_pendingOperation.clear();
    m_waitingForOperand = true;

    if (m_view){
        m_view->resetOperationButtons();
    }
}

void CalculatorPresenter::calculate() {
    if (!m_model || m_pendingOperation.isEmpty()){

        return;
    }

    double secondNumber = m_currentDisplay.toDouble();
    double result = 0;

    if (m_pendingOperation == "+"){
        result = m_model->add(m_firstNumber, secondNumber);
    }
    else if (m_pendingOperation == "-"){
        result = m_model->subtract(m_firstNumber, secondNumber);
    }
    else if (m_pendingOperation == "×"){
        result = m_model->multiply(m_firstNumber, secondNumber);
    }
    else if (m_pendingOperation == "÷"){
        result = m_model->divide(m_firstNumber, secondNumber);
    }

    m_currentDisplay = QString::number(result, 'g', 15);
    m_firstNumber = result;
    QString historyEntry = QString("%1 %2 %3 = %4")
                               .arg(m_firstNumber)
                               .arg(m_pendingOperation)
                               .arg(secondNumber)
                               .arg(result);
    m_history->addRecord(historyEntry);

    updateDisplay();
}
