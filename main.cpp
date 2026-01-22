#include "mainwindow.h"
#include "model.h"
#include "presenter.h"
#include "historymanager.h"
#include <QIcon>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString iconPath;
#ifdef Q_OS_WINDOWS
    iconPath = ":/icons/icon.ico";
#else
    iconPath = ":/icons/icon.png";
#endif
    MainWindow view;
    CalculatorModel model;
    CalculatorPresenter presenter;
    presenter.setView(&view);
    presenter.setModel(&model);
    presenter.initialize();

    view.show();
    return a.exec();
}
