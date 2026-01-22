#ifndef PRESENTER_H
#define PRESENTER_H

#include <QObject>

class MainWindow;
class CalculatorModel;
class HistoryManager;

class CalculatorPresenter : public QObject
{
    Q_OBJECT

public:
    explicit CalculatorPresenter(QObject *parent = nullptr);
    ~CalculatorPresenter();
    void setView(MainWindow *view);
    void setModel(CalculatorModel *model);
    void initialize();

private slots:
    void onDigitClicked(int digit);
    void onOperationClicked(const QString &operation);
    void onEqualsClicked();
    void onClearClicked();
    void onDecimalClicked();
    void onPlusMinusClicked();
    void onPercentClicked();
    void onModelError(const QString &error);

private:
    MainWindow *m_view;
    CalculatorModel *m_model;
    HistoryManager *m_history;
    double m_firstNumber;
    QString m_pendingOperation;
    bool m_waitingForOperand;
    QString m_currentDisplay;
    void updateDisplay();
    void reset();
    void calculate();
};
#endif // PRESENTER_H
