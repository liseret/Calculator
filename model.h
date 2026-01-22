#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QString>

class CalculatorModel : public QObject
{
    Q_OBJECT
public:
    explicit CalculatorModel(QObject *parent = nullptr);
    double add(double a, double b) const;
    double subtract(double a, double b) const;
    double multiply(double a, double b) const;
    double divide(double a, double b) const;
    double percent(double value) const;
    double changeSign(double value) const;
signals:
    void error(const QString &message);
};

#endif // MODEL_H
