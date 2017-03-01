#ifndef LAPLACERAND_H
#define LAPLACERAND_H

#include "ExponentialRand.h"
#include "GeometricStableRand.h"

/**
 * @brief The LaplaceRand class
 * Laplace distribution
 *
 * Notation: X ~ Laplace(m, σ, k)
 *
 * Related distributions:
 * X = m + σ (Y / k - W * k), where Y, W ~ Exp(1)
 * If X ~ Laplace(m, σ, k), then X - m ~ GeometricStable(2, 0, σ, σ(1 - k^2) / k)
 */
class RANDLIBSHARED_EXPORT LaplaceRand : public GeometricStableRand
{
    double m;

public:
    LaplaceRand(double shift = 0, double scale = 1, double asymmetry = 1);
    std::string Name() const override;

    void SetShift(double shift);
    void SetAsymmetry(double asymmetry);
    inline double GetShift() const { return m; }
    inline double GetAsymmetry() const { return k; }

    double f(double x) const override;
    double logf(double x) const override;
    double F(double x) const override;
    double S(double x) const override;

    double Variate() const override;
    static double Variate(double location, double scale);
    static double Variate(double location, double scale, double asymmetry);
    void Sample(std::vector<double> &outputData) const override;

    double Mean() const override;
    double Median() const override;
    double Mode() const override;

private:
    double quantileImpl(double p) const override;
    double quantileImpl1m(double p) const override;

    std::complex<double> CFImpl(double t) const override;

public:
    double Entropy() const;

    /// Maximum likelihood estimation
    /// One parameter
    void FitLocationMLE(const std::vector<double> &sample);
    void FitScaleMLE(const std::vector<double> &sample);
    void FitAsymmetryMLE(const std::vector<double> &sample);
    /// Two parameters
    void FitLocationAndScaleMLE(const std::vector<double> &sample);
    void FitLocationAndAsymmetryMLE(const std::vector<double> &sample);
    void FitScaleAndAsymmetryMLE(const std::vector<double> &sample);
    /// All parameters
    void FitMLE(const std::vector<double> &sample);

private:
    /**
     * @brief GetAsymmetryFromSkewness
     * @param sample
     * @return numeric solution of equation Skewness() = skewness
     */
    double GetAsymmetryFromSkewness(double skewness);
public:
    /// Method of moments
    /// One parameter
    void FitLocationMM(const std::vector<double> &sample);
    void FitScaleMM(const std::vector<double> &sample);
    void FitAsymmetryMM(const std::vector<double> &sample);
    /// Two parameters
    void FitLocationAndScaleMM(const std::vector<double> &sample);
    void FitLocationAndAsymmetryMM(const std::vector<double> &sample);
    void FitScaleAndAsymmetryMM(const std::vector<double> &sample);
    /// All parameters
    void FitMM(const std::vector<double> &sample);
};

#endif // LAPLACERAND_H
