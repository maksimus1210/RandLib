# RandLib

With RandLib one can easily work with probability distributions.
* Fast sampling. For instance, generate million variates from standard normal distribution:
```c++
NormalRand distribution(0, 1);
std::vector<double> data(1e6);
distribution.Sample(data);
```
![alt tag](https://github.com/StochasticEngineer/RandLib/blob/master/images/standardNormal.png)

* Calculate moments and other properties:
```c++
LogNormalRand distribution(1, 1);
std::cout << " Mean = " << distribution.Mean()
          << " and Variance = " << distribution.Variance()
          << "\n Median = " << distribution.Median()
          << " and Mode = " << distribution.Mode()
          << "\n Skewness = " << distribution.Skewness()
          << " and Excess kurtosis = " << distribution.ExcessKurtosis();
```
![alt tag](https://github.com/StochasticEngineer/RandLib/blob/master/images/lognormal11.png)
```
Mean = 4.48169 and Variance = 34.5126
Median = 2.71828 and Mode = 1
Skewness = 6.18488 and Excess Kurtosis = 110.936
```
* Fitting parameters:
```c++
using std::cout;

NormalRand X(0, 1);
std::vector<double> data(10);
X.Sample(data);
cout << "True distribution: " << X.Name() << "\n";
cout << "Sample: ";
for (double var : data)
    cout << var << "  ";
cout << "\n";

/// Bayesian
NormalInverseGammaRand prior(0, 1, 1, 1);
X.FitBayes(data, prior);
cout << "Bayesian estimator: " << X.Name() << "\n";
cout << "(Posterior distribution: " << prior.Name() << ")\n";

/// Uniformly minimum variance unbiased
X.FitUMVU(data);
cout << "UMVU estimator: " << X.Name() << "\n";

/// Maximum-likelihood
X.FitMLE(data);
cout << "Maximum-likelihood estimator: " << X.Name() << "\n";
```
![alt tag](https://github.com/StochasticEngineer/RandLib/blob/master/images/normalFit.png)
```
True distribution: Normal(0, 1)
Sample: -0.328154  0.709122  -0.607214  1.11472  -1.23726  -0.123584  0.59374  -1.20573  -0.397376  -1.63173
Bayesian estimator: Normal(-0.283042, 0.951348)
(Posterior distribution: Normal-Inverse-Gamma(-0.283042, 11, 6, 4.75674))
UMVU estimator: Normal(-0.311347, 0.82504)
Maximum-likelihood estimator: Normal(-0.311347, 0.742536)
```
