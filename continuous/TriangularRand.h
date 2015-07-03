#ifndef TRIANGULARRAND_H
#define TRIANGULARRAND_H

#include "ContinuousRand.h"
#include "UniformRand.h"

/**
 * @brief The TriangularRand class
 */
class RANDLIBSHARED_EXPORT TriangularRand : public ContinuousRand
{
    double a, b, c;
    double constForGenerator; /// (c - a) / (b - a)
    double coefGenerator1; /// (b - a) * (c - a)
    double coefGenerator2; /// (b - a) * (b - c)
    void setGeneratorConstants();

    UniformRand U;

public:
    TriangularRand(double lowerLimit = 0, double mode = 0.5, double upperLimit = 1);

    void setLowerLimit(double lowerLimit);
    void setMode(double mode);
    void setUpperLimit(double upperLimit);
    inline double getLowerLimit() { return a; }
    inline double getMode() { return c; }
    inline double getUpperLimit() { return b; }

    virtual double f(double x) const override;
    virtual double F(double x) const override;
    virtual double value() override;

    double M() const override { return (a + b + c) / 3; }
    double Var() const override { return (a * (a - b) + b * (b - c) + c * (c - a)) / 18; }
};

#endif // TRIANGULARRAND_H
