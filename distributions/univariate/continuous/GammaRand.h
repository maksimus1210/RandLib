#ifndef GAMMARAND_H
#define GAMMARAND_H

#include "ContinuousDistribution.h"

/**
 * @brief The GammaDistribution class <BR>
 * Abstract class for Gamma distribution
 *
 * f(x | α, β) = β^α / Γ(α) * x^(α-1) * exp(-βx),
 * where Γ(α) denotes Gamma function
 *
 * Notation X ~ Γ(α, β)
 *
 * Related distributions: <BR>
 * σX ~ Γ(α, σβ) <BR>
 * If X ~ Γ(1, β), then X ~ Exp(β) <BR>
 * If X ~ Γ(0.5 * n, 0.5), then X ~ χ^2(n) <BR>
 * If X ~ Γ(k, β) for integer k, then X ~ Erlang(k, β)
 */
class RANDLIBSHARED_EXPORT GammaDistribution : public ContinuousDistribution
{
protected:
    double alpha = 1; ///< shape α
    double beta = 1; ///< rate β
    double theta = 1; ///< scale θ = 1/β
    double lgammaAlpha = 0; ///< log(Γ(α))
    double pdfCoef = 0; ///< α * log(β) - log(Γ(α))
    double logAlpha = 0; ///< log(α)
    double logBeta = 0; ///< log(β)

private:
    /// constants for faster sampling
    struct genCoef_t {
        double t, b;
    } genCoef = {0, 0};

protected:
    GammaDistribution(double shape, double rate);
    virtual ~GammaDistribution() {}

public:
    SUPPORT_TYPE SupportType() const override { return RIGHTSEMIFINITE_T; }
    double MinValue() const override { return 0; }
    double MaxValue() const override { return INFINITY; }

protected:
    /**
     * @fn SetParameters
     * @param shape α
     * @param rate β
     */
    void SetParameters(double shape, double rate);
    /**
     * @brief SetShape
     * @param shape α
     */
    void SetShape(double shape);

public:
    /**
     * @fn GetShape
     * @return α
     */
    inline double GetShape() const { return alpha; }
    /**
     * @fn GetScale
     * @return θ = 1/β
     */
    inline double GetScale() const { return theta; }
    /**
     * @fn GetRate
     * @return β
     */
    inline double GetRate() const { return beta; }
    /**
     * @fn GetLogGammaShape
     * @return log(Γ(α))
     */
    inline double GetLogGammaShape() const { return lgammaAlpha; }
    /**
     * @fn GetLogShape
     * @return log(α)
     */
    inline double GetLogShape() const { return logAlpha; }
    /**
     * @fn GetLogRate
     * @return log(β)
     */
    inline double GetLogRate() const { return logBeta; }

    double f(const double & x) const override;
    double logf(const double & x) const override;
    double F(const double & x) const override;
    double logF(const double &x) const;
    double S(const double & x) const override;
    double logS(const double & x) const;
    
private:

    enum GENERATOR_ID {
        INTEGER_SHAPE, ///< Erlang distribution for α = 1, 2, 3
        ONE_AND_A_HALF_SHAPE, ///< α = 1.5
        SMALL_SHAPE, ///< α < 0.34
        FISHMAN, ///< 1 < α < 1.2
        MARSAGLIA_TSANG ///< 0.34 < α < 1 or α >= 1.2
    };

    /**
     * @fn getIdOfUsedGenerator
     * @param shape α
     * @return id of used variate generator according to the shape
     */
    static GENERATOR_ID getIdOfUsedGenerator(double shape);
    /**
     * @fn variateThroughExponentialSum
     * @param shape α
     * @return gamma variate, generated by sum of exponentially distributed random variables
     */
    static double variateThroughExponentialSum(int shape, RandGenerator& randGenerator);
    /**
     * @fn variateForShapeOneAndAHalf
     * @return gamma variate for α = 1.5
     */
    static double variateForShapeOneAndAHalf(RandGenerator& randGenerator);
    /**
     * @fn variateBest
     * @return gamma variate for small α, using Best algorithm
     */
    double variateBest(RandGenerator& randGenerator) const;
    /**
     * @fn variateAhrensDieter
     * @param shape α
     * @return gamma variate for small α, using Ahrens-Dieter algorithm (if we have no pre-calculated values)
     */
    static double variateAhrensDieter(double shape, RandGenerator& randGenerator);
    /**
     * @fn variateFishman
     * @param shape α
     * @return gamma variate, using Fishman algorithm
     */
    static double variateFishman(double shape, RandGenerator& randGenerator);
    /**
     * @fn variateMarsagliaTsang
     * @param shape α
     * @return gamma variate, using Marsaglia-Tsang algorithm
     */
    static double variateMarsagliaTsang(double shape, RandGenerator& randGenerator);
    
public:
    /**
     * @fn StandardVariate
     * @param shape α
     * @return gamma variate with shape α and unity rate
     */
    static double StandardVariate(double shape, RandGenerator &randGenerator = staticRandGenerator);
    /**
     * @fn Variate
     * @param shape α
     * @param rate β
     * @return gamma variate with shape α and rate β
     */
    static double Variate(double shape, double rate, RandGenerator &randGenerator = staticRandGenerator);

    double Variate() const override;
    void Sample(std::vector<double> &outputData) const override;

    /**
     * @fn Mean
     * @return E[X]
     */
    double Mean() const override;
    /**
     * @fn GeometricMean
     * @return E[ln(X)]
     */
    double GeometricMean() const;
    /**
     * @fn Variance
     * @return Var(X)
     */
    double Variance() const override;
    /**
     * @fn GeometricVariance
     * @return Var(ln(X))
     */
    double GeometricVariance() const;
    double Mode() const override;
    double Median() const override;
    double Skewness() const override;
    double ExcessKurtosis() const override;

private:
    /// quantile auxiliary functions
    double initRootForSmallP(double r) const;
    double initRootForLargeP(double logQ) const;
    double initRootForSmallShape(double p) const;
    double initRootForLargeShape(double p) const;
    double initRootForLargeShape1m(double p) const;
    double quantileInitialGuess(double p) const;
    double quantileInitialGuess1m(double p) const;

    /**
     * @fn df
     * derivative of probability density function
     * @param x
     * @return f'(x)
     */
    double df(double x) const;
    /**
     * @fn dfDivf
     * derivative of pdf, divided by pdf
     * @param x
     * @return f'(x) / f(x)
     */
    double dfDivf(double x) const;
    double quantileImpl(double p, double initValue) const override;
    double quantileImpl(double p) const override;
    double quantileImpl1m(double p, double initValue) const override;
    double quantileImpl1m(double p) const override;

    std::complex<double> CFImpl(double t) const override;
};

class RANDLIBSHARED_EXPORT GammaRand;

/**
 * @brief The FreeScaleGammaDistribution class <BR>
 * Abstract class for Gamma distribution with arbitrary scale/rate
 */
class RANDLIBSHARED_EXPORT FreeScaleGammaDistribution : public GammaDistribution
{
protected:
    FreeScaleGammaDistribution(double shape, double rate) : GammaDistribution(shape, rate) {}

public:
    /**
     * @fn SetRate
     * set rate β
     * @param rate
     */
    void SetRate(double rate);

    /**
     * @fn SetScale
     * set scale θ = 1/β
     * @param scale
     */
    void SetScale(double scale);

    /**
     * @fn FitRate
     * set rate, estimated via maximum-likelihood method if unbiased = false,
     * otherwise set rate, returned by uniformly minimum variance unbiased estimator
     * @param sample
     */
    void FitRate(const std::vector<double> &sample, bool unbiased = false);

    /**
     * @fn FitRateBayes
     * set rate, returned by bayesian estimation
     * @param sample
     * @param priorDistribution
     * @return posterior distribution
     */
    GammaRand FitRateBayes(const std::vector<double> &sample, const GammaDistribution &priorDistribution, bool MAP = false);
};

/**
 * @brief The GammaRand class <BR>
 * Gamma distribution
 */
class RANDLIBSHARED_EXPORT GammaRand : public FreeScaleGammaDistribution
{
public:
    GammaRand(double shape = 1, double rate = 1) : FreeScaleGammaDistribution(shape, rate) {}
    String Name() const override;

    using GammaDistribution::SetParameters;
    using GammaDistribution::SetShape;

    /**
     * @fn FitShape
     * set shape, estimated via maximum-likelihood method
     * @param sample
     */
    void FitShape(const std::vector<double> &sample);

    /**
     * @fn Fit
     * set shape and rate, estimated via maximum-likelihood method
     * @param sample
     */
    void Fit(const std::vector<double> &sample);
};


/**
 * @brief The ChiSquaredRand class <BR>
 * Chi-squared distribution
 *
 * Notation: X ~ χ^2(k)
 *
 * Related distributions: <BR>
 * X ~ Γ(0.5 * k, 0.5)
 */
class RANDLIBSHARED_EXPORT ChiSquaredRand : public GammaDistribution
{
public:
    explicit ChiSquaredRand(size_t degree = 1) : GammaDistribution(0.5 * degree, 0.5) {}
    String Name() const override;
    void SetDegree(size_t degree);
    inline size_t GetDegree() const { return static_cast<int>(2 * alpha); }
};


/**
 * @brief The ErlangRand class <BR>
 * Erlang distibution
 *
 * Notation: X ~ Erlang(k, β)
 *
 * Related distributions: <BR>
 * X ~ Y_1 + Y_2 + ... + Y_k, where Y_i ~ Exp(β) <BR>
 * X ~ Γ(k, β)
 */
class RANDLIBSHARED_EXPORT ErlangRand : public FreeScaleGammaDistribution
{
public:
    ErlangRand(int shape = 1, double rate = 1) : FreeScaleGammaDistribution(shape, rate) {}
    String Name() const override;
    void SetParameters(size_t shape, double rate);
    void SetShape(size_t shape);
};


#endif // GAMMARAND_H
