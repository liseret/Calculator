#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QKeyEvent>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setDisplayText(const QString &text);
    QString getDisplayText() const;
    void resetOperationButtons();
signals:
    void digitClicked(int digit);
    void operationClicked(const QString &operation);
    void equalsClicked();
    void clearClicked();
    void decimalClicked();
    void plusMinusClicked();
    void percentClicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    Ui::MainWindow *ui;
    void setupConnections();
private slots:
    void onDigitButton();
    void onOperationButton();

};
#endif // MAINWINDOW_H
