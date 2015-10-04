// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <QJSEngine>
#include <random>

//Генератор случайных чисел

class RandomGenerator
{
public:
    RandomGenerator();
    RandomGenerator(qreal leftBorder, qreal rightBorder, const QString &distributionFunction);
    qreal getRandom();

    qreal getLeftBorder() const;
    void setLeftBorder(const qreal &leftBorder);

    qreal getRightBorder() const;
    void setRightBorder(const qreal &rightBorder);

    QString getDistributionFunction() const;
    void setDistributionFunction(const QString &distributionFunction);

private:
    //поиск обратного значения функции
    qreal computeInverseValue(qreal y);
    void updateFunction();

    static std::default_random_engine m_generator;

    qreal m_leftBorder;
    qreal m_rightBorder;
    QString m_distributionFunction;
    QJSValue m_fun;
    QJSEngine m_engine;
};

#endif // RANDOMGENERATOR_H
