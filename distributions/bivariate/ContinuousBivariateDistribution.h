#ifndef CONTINUOUS_BIVARIATE_DISTRIBUTION_H
#define CONTINUOUS_BIVARIATE_DISTRIBUTION_H

#include "BivariateDistribution.h"
#include "../univariate/continuous/ContinuousDistribution.h"

/**
 * @brief The ContinuousBivariateDistribution class <BR>
 * Abstract class for all bivariate probability distributions
 * with marginal continuous distributions
 */
template < class T1, class T2 >
class RANDLIBSHARED_EXPORT ContinuousBivariateDistribution : public BivariateDistribution< T1, T2, DoublePair >
{
    static_assert(std::is_base_of<ContinuousDistribution, T1>::value, "T1 must be a descendant of ContinuousDistribution");
    static_assert(std::is_base_of<ContinuousDistribution, T2>::value, "T2 must be a descendant of ContinuousDistribution");

protected:
    ContinuousBivariateDistribution() {}
    virtual ~ContinuousBivariateDistribution() {}

public:
    virtual double f(const DoublePair &point) const = 0;
    virtual double logf(const DoublePair &point) const = 0;
};

#endif // CONTINUOUS_BIVARIATE_DISTRIBUTION_H
