// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "randomgenerator.h"
#include <QDebug>

std::default_random_engine RandomGenerator::m_generator;

RandomGenerator::RandomGenerator() : RandomGenerator(10, 20, "(function(x) { return (x-10)/10; })")
{

}

RandomGenerator::RandomGenerator(qreal leftBorder, qreal rightBorder, const QString &distributionFunction):
    m_leftBorder(leftBorder),
    m_rightBorder(rightBorder),
    m_distributionFunction(distributionFunction)
{
    m_fun = m_engine.evaluate(m_distributionFunction);
}

qreal RandomGenerator::getRandom()
{
    std::uniform_real_distribution<double> distribution(0,1);
    double y = distribution(m_generator);
    if(y == 0) return m_leftBorder;
    if(y == 1) return m_rightBorder;
    return computeInverseValue(y);
}

qreal RandomGenerator::getLeftBorder() const
{
    return m_leftBorder;
}

void RandomGenerator::setLeftBorder(const qreal &leftBorder)
{
    m_leftBorder = leftBorder;
}

qreal RandomGenerator::getRightBorder() const
{
    return m_rightBorder;
}

void RandomGenerator::setRightBorder(const qreal &rightBorder)
{
    m_rightBorder = rightBorder;
}

QString RandomGenerator::getDistributionFunction() const
{
    return m_distributionFunction;
}

void RandomGenerator::setDistributionFunction(const QString &distributionFunction)
{
    m_distributionFunction = distributionFunction;
    updateFunction();
}


qreal RandomGenerator::computeInverseValue(qreal y)
{
    //поиск обратного значения методом бисекции
    double tempValue = 0;
    double precision = 0.001;
    double leftBorder = m_leftBorder;
    double rightBorder = m_rightBorder;
    while(rightBorder - leftBorder > precision)
    {
        tempValue = (rightBorder + leftBorder)/2;
        QJSValueList firstValue;
        QJSValueList secondValue;
        firstValue << rightBorder;
        secondValue << tempValue;
        if (((m_fun.call(firstValue).toNumber() - y) * (m_fun.call(secondValue).toNumber() - y)< 0))
            leftBorder = tempValue;
        else
            rightBorder = tempValue;
    }
    return (rightBorder + leftBorder)/2;
}

void RandomGenerator::updateFunction()
{
    m_fun = m_engine.evaluate(m_distributionFunction);
}
