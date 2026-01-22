#include "model.h"
CalculatorModel::CalculatorModel(QObject *parent) : QObject(parent) {}

double CalculatorModel::add(double a, double b) const {
    return a + b;
}
double CalculatorModel::subtract(double a, double b) const {
    return a - b;
}
double CalculatorModel::multiply(double a, double b) const {
    return a * b;
}
double CalculatorModel::divide(double a, double b) const {
    if (b == 0) {
        return 0;
    }
    return a / b;
}
double CalculatorModel::percent(double value) const {
    return value * 0.01;
}
double CalculatorModel::changeSign(double value) const {
    return value*-1;
}
