#include "ProbabilityDistribution.h"
#include <sstream>      /// std::ostringstream
#include <iomanip>      /// std::setprecision

template < typename T >
ProbabilityDistribution<T>::ProbabilityDistribution()
{
}

template < typename T >
std::string ProbabilityDistribution<T>::toStringWithPrecision(const double a_value, const int n) const
{
    std::ostringstream out;
    out << std::setprecision(n) << a_value;
    return out.str();
}

template < typename T >
void ProbabilityDistribution<T>::Sample(std::vector<T> &outputData) const
{
    for (T &var : outputData)
        var = this->Variate();
}

template < typename T >
void ProbabilityDistribution<T>::CumulativeDistributionFunction(const std::vector<T> &x, std::vector<double> &y) const
{
    size_t size = x.size();
    if (size > y.size())
        return;
    for (size_t i = 0; i != size; ++i)
        y[i] = F(x[i]);
}

template < typename T >
double ProbabilityDistribution<T>::S(const T &x) const
{
    return 1.0 - F(x);
}

template < typename T >
void ProbabilityDistribution<T>::SurvivalFunction(const std::vector<T> &x, std::vector<double> &y) const
{
    size_t size = x.size();
    if (size > y.size())
        return;
    for (size_t i = 0; i != size; ++i)
        y[i] = this->S(x[i]);
}

template < typename T >
constexpr char ProbabilityDistribution<T>::POSITIVITY_VIOLATION[];
template < typename T >
constexpr char ProbabilityDistribution<T>::UPPER_LIMIT_VIOLATION[];
template < typename T >
constexpr char ProbabilityDistribution<T>::LOWER_LIMIT_VIOLATION[];

template < typename T >
std::string ProbabilityDistribution<T>::fitError(ProbabilityDistribution::FIT_ERROR_TYPE fet, const std::string &explanation)
{
    std::string error = this->Name() + ": ";
    switch (fet) {
    case WRONG_SAMPLE:
        error += "Sample can't be returned by this distribution. ";
        break;
    case NOT_APPLICABLE:
        error += "Method can't be applied here. ";
        break;
    case WRONG_RETURN:
        error += "Method returns invalid parameters. ";
        break;
    case TOO_FEW_ELEMENTS:
        error += "Sample is too small. ";
        break;
    case WRONG_LEVEL:
        error += "Level alpha should be positive and less than one. ";
        break;
    case UNDEFINED_ERROR:
    default:
        error += "Unknown type of error. ";
    }
    return error + explanation;
}

/// Univariate
template class ProbabilityDistribution<double>;
template class ProbabilityDistribution<int>;

/// Bivariate
template class ProbabilityDistribution<DoublePair>;
