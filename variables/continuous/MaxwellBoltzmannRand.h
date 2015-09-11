#ifndef MAXWELLBOLTZMANNRAND_H
#define MAXWELLBOLTZMANNRAND_H

#include "ContinuousRand.h"
#include "ChiSquaredRand.h"

/**
 * @brief The MaxwellBoltzmannRand class
 */
class RANDLIBSHARED_EXPORT MaxwellBoltzmannRand : public ContinuousRand
{
    double a;

    ChiSquaredRand C;

public:
    explicit MaxwellBoltzmannRand(double scale);
    virtual std::string name() override;

    void setScale(double scale);
    inline double getScale() const { return a; }

    double f(double x) const override;
    double F(double x) const override;
    double variate() const override;

    double E() const override;
    double Var() const override;
    
    double Mode() const override;
    double Skewness() const override;
    double ExcessKurtosis() const override;
};

#endif // MAXWELLBOLTZMANNRAND_H
