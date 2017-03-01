#ifndef PARETORAND_H
#define PARETORAND_H

#include "ExponentialRand.h"

/**
 * @brief The ParetoRand class
 */
class RANDLIBSHARED_EXPORT ParetoRand : public ContinuousDistribution
{
    double xm, alpha;
    double logAlpha, logXm;

public:
    ParetoRand(double shape = 1, double scale = 1);

    std::string Name() const override;
    SUPPORT_TYPE SupportType() const override { return RIGHTSEMIFINITE_T; }
    double MinValue() const override { return xm; }
    double MaxValue() const override { return INFINITY; }

    void SetShape(double shape);
    void SetScale(double scale);
    inline double GetShape() const { return alpha; }
    inline double GetScale() const { return xm; }
    inline double GetLogShape() const { return logAlpha; }
    inline double GetLogScale() const { return logXm; }

    double f(double x) const override;
    double logf(double x) const override;
    double F(double x) const override;
    double S(double x) const override;

private:
    static double variateForAlphaOne();
    static double variateForAlphaTwo();
    static double variateForCommonAlpha(double shape);

public:
    static double StandardVariate(double shape);
    static double Variate(double shape, double scale);
    double Variate() const override;
    void Sample(std::vector<double> &outputData) const override;

    double Mean() const override;
    double Variance() const override;
    double Median() const override;
    double Mode() const override;
    double Skewness() const override;
    double ExcessKurtosis() const override;

private:
    double quantileImpl(double p) const override;
    double quantileImpl1m(double p) const override;

public:
    inline double Entropy() const;

    void FitMLE(const std::vector<double> &sample);
};

#endif // PARETORAND_H
