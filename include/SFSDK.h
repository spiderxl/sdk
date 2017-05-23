/**
*  \addtogroup SFSDK 
*  @{
*  @file SFSDK.h
* 
*  @brief  Header file for the public API of SFSDK library 
*  @details function declaration for NumXL SDK Econometric and statistical APIs 
*  @copyright &copy; Spider Financial Corp - All rights reserved.
*  Unauthorized copying of this file, via any medium is strictly prohibited
*   Proprietary and confidential

*  @author Spider Financial Corp
*  @version 1.62
*  @see http://www.spiderfinancial.com
*  $Date: 2017-04-18 15:37:49 -0500 (Tue, 18 Apr 2017) $
*/
#pragma once

extern "C"
{

  /*!
  *   
  *   \brief Data structure to capture X-12-ARIMA options
   */
  typedef struct __X12ARIMA_OPTIONS__
  {
    // Data section
    long    lStartDate;   ///< is the serial date number for the start date of the time series.
    BOOL    monthly;      ///< is a flag to indicate whether data is monthly/quarterly.
    size_t  nObs;         ///< is the number of observations in the input time series.

    
    int   transform;      ///< Transform section (1=Log, 2=Auto and 3=None)

    // Outlier
    BOOL  AOOutlier;      ///< additive outlier adjustment
    BOOL  TCOutlier;      ///< temporary 
    BOOL  LSOutlier;      ///< level shift outlier adjustment
    int   LSRun;          ///< level shift run

    // Regression section
    BOOL  tradingDayRegression;   ///< Calendar adjustment: trading days
    BOOL  EasterRegression;       ///< Calendar adjustment: easter holidays
    BOOL  ConstantIntercept;      ///< Add a linear trend?

    // ARIMA Modeling
    BOOL  AutoSelect;             ///< RegARIMA Modeling: Automodeling?
    int   P;                      ///< RegARIMA Modeling: Manual, set the order of AR process
    int   Q;                      ///< RegARIMA Modeling: Manual, set the order of MA process
    int   D;                      ///< RegARIMA Modeling: Manual, differencing
    int   PP;                     ///< RegARIMA Modeling: Manual, the order of seasonal AR process
    int   QQ;                     ///< RegARIMA Modeling: Manual, the order of seasonal MA process
    int   DD;                     ///< RegARIMA Modeling: Manual, Seasonal differencing

    // Forecast
    int     nForecastYears;       ///< [in] is the number of years to forecast for.
    double  fAlpha;               ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 

    // Seasonal Adjustment
    BOOL  bSeasonalAdjustFilter;  ///< is a switch to include seasonal adjustment in the analysis.
    int   nX11Mode;               ///< 1=mult, 2=add, 3=pseudoadd, 4=logadd
    int   nX11Options;            ///< 1= x11default, 2=s3x1, 3=s3x3, 4=s3x5, 5=s3x9, 6=s3x15, 7=stable

    int   henderson;              ///< henderson filter setting, default=13

  }X12ARIMA_OPTIONS;

  /*!
  * \sa NDK_GLM_GOF()
  */
  typedef enum
  {
    GOF_LLF=1,  ///<  Log-likelihood goodness of fit measure
    GOF_AIC=2,  ///<  Akaike information criterion goodness of fit measure
    GOF_BIC=3,  ///<  Bayesian or Schwartz information criterion goodness of fit measure
    GOF_HQC=4,  ///<  Hannan–Quinn information criterion goodness of fit measure
    GOF_RSQ=5,  ///<  R-squared goodness of fit measure
    GOF_ARSQ=6  ///<  Adjusted R-squared goodness of fit measure
  }GOODNESS_OF_FIT_FUNC;

  /*!
  * \sa NDK_ARMA_FIT()
  */
  typedef enum
  {
    FIT_MEAN=1,     ///<  Fitted conditional mean
    FIT_STDEV=2,    ///<  Fitted conditional volatility or standard deviation
    FIT_RESID=3,    ///<  Raw residuals (actual - fitted mean)
    FIT_STD_RESID=4 ///<  Standardized residuals - (actual - fitted mean)/fitted volatility
  }FIT_RETVAL_FUNC;

  /*!
  * \sa NDK_ARMA_RESID()
  */
  typedef enum
  {
    RESIDS_STD=1,   ///<  Standardized residuals 
    RESIDS_RAW=2    ///<  Raw residuals
  }RESID_RETVAL_FUNC;

  /*!
  * \sa NDK_ARMA_PARAM()
  */
  typedef enum
  {
    PARAM_GUESS=1,      ///<  Quick guess (non-optimal) of parameters values
    PARAM_CALIBRATE=2,  ///<  Run a calibration process to find optimal values for the model's parameters
    PARAM_ERROR=3       ///<  Compute the standard error of the parameters' values
  }MODEL_RETVAL_FUNC;

  /*!
  * \sa NDK_ARMA_FORE()
  */
  typedef enum
  {
    FORECAST_MEAN=1,      ///<  Mean forecast value
    FORECAST_STDEV=2,     ///<  Forecast standard error (aka local volatility)
    FORECAST_TS_STDEV=3,  ///<  Volatility term structure
    FORECAST_LL=4,        ///<  Lower limit of the forecast confidence interval
    FORECAST_UL=5         ///<  Upper limit of the forecast confidence interval
  }FORECAST_RETVAL_FUNC;

  /*!
  * \ingroup statistical testing
  * \brief Supported statistical test outputs
  * \sa NDK_MEANTEST()
  */
  typedef enum
  {
    TEST_PVALUE=1,        ///< P-value
    TEST_SCORE=2,         ///< Test statistics (aka score)
    TEST_CRITICALVALUE=3  ///< Critical value
  }TEST_RETURN;


  /*!
  * \ingroup statistical testing
  * \sa NDK_NORMALTEST()
  */
  typedef enum 
  {
    NORMALTEST_JB=1,      ///< Jacque-Berra
    NORMALTEST_WS=2,      ///< Shapiro-Wilson
    NORMALTEST_CHISQ=3    ///< Chi-Square test - Doornik and Hansen, "An Omnibus Test for Normality", 1994.
  }NORMALTEST_METHOD;


  /*!
  * \ingroup statistical testing
  * \sa NDK_ADFTEST()
  */
  typedef enum 
  {
    ADFTEST_DRIFT_ONLY=1,                   ///< Model 1: A stochastic drift
    ADFTEST_DRIFT_N_CONST=2,                ///< Model II: A deterministic constant and stochastic drift
    ADFTEST_DRIFT_N_TREND =3,               ///< Model III: A deterministic trend and stochastic drift
    ADFTEST_DRIFT_N_CONST_N_TREND =4,       ///< Model IV: A deterministic constant, trend and stochastic drift
    ADFTEST_DRIFT_N_CONST_TREND_TREND2 =5   ///< Model V: A deterministic constant, trend, trend^2 and stochastic drift
  }ADFTEST_OPTION;



/*!
  * \brief Support correlation methods
  * \sa NDK_XCFTEST(), NDK_XCF()
  */
  typedef enum 
  {
    XCF_PEARSON=1,      ///< Pearson
    XCF_SPEARMAN=2,     ///< Spearman
    XCF_KENDALL=3       ///< Kendall
  }CORRELATION_METHOD;


  /*!
  * \brief Supported Link function
  * \sa NDK_GLM_GOF()
  */
  typedef enum
  {
    GLM_LVK_IDENTITY=1,     ///<  Identity (default)
    GLM_LVK_LOG=2,          ///<  Log
    GLM_LVK_LOGIT=3,        ///<  Logit
    GLM_LVK_PROBIT=4,       ///<  Probit
    GLM_LVK_CLOGLOG=5       ///<  Complementary log-log
  }GLM_LINK_FUNC;

  /*!
  * \brief Supported innovation types
  * \sa NDK_GARCH_PARAM(), 
  */
  typedef enum
  {
    INNOVATION_GAUSSIAN=1,  ///<  Gaussian or normal distribution
    INNOVATION_TDIST=2,     ///<  Standardized student's T-distribution
    INNOVATION_GED=3        ///<  Standardized generalized error distribution (GED)
  }INNOVATION_TYPE;

  /*!
  * \brief Supported innovation types
  * \sa NDK_TREND()
  */
  typedef enum
  {
    TREND_LINEAR=1,       ///<  Linear time trend
    TREND_POLYNOMIAL=2,   ///<  Polynomial time trend
    TREND_EXPONENTIAL=3,  ///<  Exponential time trend
    TREND_LOGARITHMIC=4,  ///<  Logarithmic time trend
    TREND_POWER=5         ///<  Power time trend
  }TREND_TYPE;

  /*!
  * \brief multi-colinearity test method
  * \sa NDK_COLNRTY_TEST()
  */
  typedef enum
  {
    COLNRTY_CN=1,   ///<  Condition Number
    COLNRTY_VIF=2,  ///<  Variation Inflation Factor (VIF)
    COLNRTY_DET=3,  ///<  Determinant
    COLNRTY_EIGEN=4 ///<  Eigenvalues
  }COLNRTY_TEST_TYPE;

  /*!
  * \brief Periodogram method options
  * \sa NDK_PERIODOGRAM()
  */
  typedef enum
  {
    PERIODOGRAM_NONE=1,         ///<  don't process the input data
    PERIODOGRAM_DETREND=2,      ///<  detrend the input data
    PERIODOGRAM_DIFFERENCE=3,   ///<  difference the time series (1,1)
    PERIODOGRAM_AUTOPROC=4      ///<  Auto-process (e.g. detrend, difference, etc.) the input data.
  }PERIODOGRAM_OPTION_TYPE;


  /*!
  * \brief Imputation methods for resampling
  * \sa NDK_RESAMPLE()
  */
  typedef enum
  {
    IMPUTATION_NONE = 0,                 ///<  don't process the input data
    IMPUTATION_INTERPOLATE_FWD =     1,  ///<  flat forward
    IMPUTATION_INTERPOLATE_BKWD =    2,  ///<  flat backward
    IMPUTATION_INTERPOLATE_LINEAR =  3,  ///<  Linear interpolation
    IMPUTATION_INTERPOLATE_CSPLINE = 4,  ///<  cubic spline
    IMPUTATION_FFT = 5                   ///<  Fast Fourier transform
  }IMPUTATION_METHOD;

  typedef enum
  {
    X13TRANSFOR_NONE = 0,                ///<  don't process the input data
    X13TRANSFOR_AUTO = 1,                ///<  don't process the input data
    X13TRANSFOR_LOG = 2,                 ///<  don't process the input data
    X13TRANSFOR_SQRT = 3,                ///<  don't process the input data
    X13TRANSFOR_INV = 4,                 ///<  don't process the input data
    X13TRANSFOR_LOGIST = 5,              ///<  don't process the input data
    X13TRANSFOR_BOXCOX = 6               ///<  don't process the input data
  }X13TRANSFORM_METHOD;

  typedef enum
  {
    X13PRIORADJUST_RATIO = 0,             ///< 
    X13PRIORADJUST_PERCENT = 1,           ///< 
    X13PRIORADJUST_DIFF = 2               ///< 
  }X13PRIORADJUST_TYPE;

  typedef enum
  {
    X11_MODE_MULT = 0,            ///< 
    X11_MODE_ADD = 1,             ///< 
    X11_MODE_PSEUDOADD = 2,       ///< 
    X11_MODE_LOGADD = 3           ///< 
  }X11_MODE_TYPE;


  typedef enum
  {
    X11_SEASONALMA_3x1 = 0,            ///< 
    X11_SEASONALMA_3x3 = 1,            ///< 
    X11_SEASONALMA_3x5 = 2,            ///< 
    X11_SEASONALMA_3x9 = 3,            ///< 
    X11_SEASONALMA_3x15 = 4,           ///< 
    X11_SEASONALMA_STABLE = 5,         ///< 
    X11_SEASONALMA_DEFAULT = 6,        ///< 3x3 MA and 3x5
    X11_SEASONALMA_MSR=7               ///< X-11-ARIMA88
  }X11_SEASONALMA_TYPE;



}

// Functions API
extern "C"
{

  /// \name Initialization APIs
  /// @{
  /*! 
  *   @brief  Initializes the SFSDK Library
  *   @details This function should be the first API called in the SDK; It initializes the SDK library dependencies:
  *      1. Logging system
  *      2. License system
  *      3. Database system
  *   
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *
  *   \sa SFMacros.h, NDK_Shutdown()
  */
  /*! 
    @note 1. This is the first SDK API

    @code
      int nRet = NDK_FAILED;

      char szAppName[]="MyApp";
      nRet = NDK_Init( szAppName,   // we have a MyApp.conf file
                        NULL,       // use the license key in the license file (NumXL.lic)
                        NULL,       // use the activation code in the license file (NumXL.lic)
                        NULL);      // use the temp directory in current user's profile 
                                    // (Windows 7)  (c:\users\(username)\AppData\Local\MyApp)
                                    // (Windows XP) (c:\Local Settings\(username)\AppData\Local\MyApp)

      if( nRet >= NDK_SUCCES){
        ...
        ....
      }
      @endcode
  */
  int   __stdcall NDK_Init( LPCTSTR szAppName,   ///<  [in] is the application name (user-defined), but must match the configuration base filename.
                            LPCTSTR szKey,       ///<  [in, optional] is the NumXL license key. If missing (NULL), NDK_Init will attempt to locate the license key & activation code in the system.
                            LPCTSTR szActCode,   ///<  [in, optional] is the license activation code. If missing (NULL), NDK_Init will attempt to locate the license key & activation code in the system.
                            LPCTSTR szTmpPath    ///<  [in, optional] is the full path of the log file directory. If NULL, NDK reverts to the temporary directory in the current user's profile.
                            );  
  
  
  /*! 
  *   @brief Shutdown and release resources used by the SFSDK Library
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful
  *   \retval Others see \ref SFMacros.h
  *   \sa SFMacros.h, NDK_Init()
  */
  /*! 
      @code
      int nRet = NDK_FAILED;

      ...
      nRet= NDK_Shutdown();   // This is the last SDK API called.
      // Check for error
      if( nRet < NDK_SUCCESS){
        ...
      }

      @endcode
  */
  int   __stdcall NDK_Shutdown(void); 

  // Examples
  /// \example sdk_init.cpp

  /// @}

  /// \name Descriptive Statistics
  /// @{

  // Time series statistics
  // General statistics
  /*! 
  *   \brief Calculates the sample excess kurtosis.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  The time series is homogeneous or equally spaced. 
  *   \note 1. The data sample may include missing values (e.g. #N/A).
  *   \note 2. The test hypothesis for the population excess kurtosis:
				\f$H_{o}: K=0\f$
				\f$H_{1}: K\neq 0\f$, where:
					\f$H_{o}\f$ is the null hypothesis.
					\f$H_{1}\f$ is the alternate hypothesis.
  *   \note 3. For the case in which the underlying population distribution is normal, the sample excess kurtosis also has a normal sampling distribution:
				\f$\hat K \sim N(0,\frac{24}{T})\f$, where:
					\f$\hat k\f$ is the sample excess kurtosis (i.e. 4th moment).
					\f$T\f$ is the number of non-missing values in the data sample.
					\f$N(.)\f$ is the normal (i.e. gaussian) probability distribution function.
  *   \note 4. Using a given data sample, the sample excess kurtosis is calculated as:
				\f$\hat K (x)= \frac{\sum_{t=1}^T(x_t-\bar x)^4}{(T-1)\hat \sigma^4}-3\f$, where:
					\f$\hat K(x)\f$ is the sample excess kurtosis.
					\f$x_i\f$ is the i-th non-missing value in the data sample.
					\f$T\f$ is the number of non-missing values in the data sample.
					\f$\hat \sigma\f$ is the sample standard deviation.
  *   \note 5. The underlying population distribution is assumed normal (gaussian)..
  *   \note 6. This is a two-sides (i.e. two-tails) test, so the computed p-value should be compared with half of the significance level \f$\frac{\alpha}{2}\f$.

  *   \sa NDK_XKURTTEST(), NDK_GED_XCF(), NDK_TDIST_XKURT()
  */
  int __stdcall NDK_XKURT(double* X,      ///< [in] is the input data sample (a one dimensional array).
                          size_t N,       ///< [in] is the number of observations in X.
                          WORD reserved,  ///< [in] This parameter is reserved and must be 1.
                          double* retVal  ///< [out] is the calculated sample excess-kurtosis value.
                          );
  /*! 
  *   \brief Calculates the sample skewness.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF_SKEWTEST()
  */
  int __stdcall NDK_SKEW( double* X,      ///< [in] is the input data sample (a one dimensional array).
                          size_t N,       ///< [in] is the number of observations in X.
                          WORD reserved,  ///< [in] This parameter is reserved and must be 1.
                          double* retVal  ///< [out] is the calculated sample skew value.
                          );
  /*! 
  *   \brief Calculates the sample average.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF_MEANTEST()
  */
  int __stdcall NDK_AVERAGE(double* X,      ///< [in] is the input data sample (a one dimensional array).
                            size_t N,       ///< [in] is the number of observations in X.
                            WORD reserved,  ///< [in] This parameter is reserved and must be 1.
                            double* retVal  ///< [out] is the calculated average value.
                            );

  /*!
  *   \brief Calculates the geometric mean of the sample
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_AVERAGE()
  */
  int __stdcall NDK_GMEAN(double* X,      ///< [in] is the input data sample (a one dimensional array).
                          size_t N,       ///< [in] is the number of observations in X.
                          WORD reserved,  ///< [in] This parameter is reserved and must be 1.
                          double* retVal  ///< [out] is the calculated geometric average value.
                        );

  /*! 
  *   \brief Calculates the sample variance.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF_STDEVTEST()
  */
  int __stdcall NDK_VARIANCE(double* X,     ///< [in] is the input data sample (a one dimensional array).
                            size_t N,       ///< [in] is the number of observations in X.
                            WORD reserved,  ///< [in] This parameter is reserved and must be 1.
                            double* retVal  ///< [out] is the calculated variance value.
                            );

  /*! 
  *   \brief Calculates the minimum value in a given sample.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_MAX(), NDK_QAUNTILE(), NDK_IQR()
  */
  int __stdcall NDK_MIN(  double* X,      ///< [in] is the input data sample (a one dimensional array).
                          size_t N,       ///< [in] is the number of observations in X.
                          WORD reserved,  ///< [in] This parameter is reserved and must be 1.
                          double* retVal  ///< [out] is the calculated minimum value.
                          );
  /*! 
  *   \brief Calculates the maximum value in a given sample.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_MIN(), NDK_QAUNTILE()
  */
  int __stdcall NDK_MAX(double* X,        ///< [in] is the input data sample (a one dimensional array).
                        size_t N,         ///< [in] is the number of observations in X.
                        WORD reserved,  ///< [in] This parameter is reserved and must be 1.
                        double* retVal    ///< [out] is the calculated maximum value.
                        );
  /*! 
  *   \brief Returns the sample p-quantile of the non-missing observations (i.e. divides the sample data into equal parts determined by the percentage p). 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series may include missing values (NaN), but they will not be included in the calculations.
  *   \note 2. The quantile function for any distribution is defined between 0 and 1. Its function is the inverse of the cumulative distribution function (CDF).
  *   \note 3. The quantile function returns the sample median when \f$p=0.5\f$.
  *   \note 4. The quantile function returns the sample minimum when \f$p=0\f$.
  *   \note 5. The quantile function returns the sample maximum when \f$p=1\f$.
  *   \note 6. For any probability distribution, the following holds true for the probability \f$p\f$:
				-\f$P(X< q)\geq p\f$, where: 
					-\f$q\f$ is the sample \f$p\f$-quantile.
  *   \sa NDK_IQR(), NDK_MIN(), NDK_MAX()
  */
  int __stdcall NDK_QUANTILE( double* X,        ///< [in] is the input data sample (a one dimensional array).
                              size_t N,         ///< [in] is the number of observations in X.
                              double p,         ///< [in] is a scalar value between 0 and 1 (exclusive).
                              double* retVal    ///< [out] is the calculated p-th quantile value.
                              );
  /*! 
  *   \brief Returns the interquartile range (IQR), also called the midspread or middle fifty. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The input time series data may include missing values (NaN), but they will not be included in the calculations.
  *   \note 2. The interquartile range is defined as follows:
				-\f$\textup{IQR}=Q_3-Q_1\f$, where:
					-\f$Q_3\f$ is the third quartile.
					-\f$Q_1\f$ is the first quartile.
  *   \note 3. Interquartile range (IQR) is a robust statistic because it has a break down point of 25%. It is often preferred to the total range.
  *   \sa NDK_QUANTILE(), NDK_MIN(), NDK_MAX()
  */
  int __stdcall NDK_IQR(double* X,      ///< [in] is the input data sample (a one dimensional array).
                        size_t N,       ///< [in] is the number of observations in X.
                        double* retVal  ///< [out] is the calculated IQR value.
                        );

  /*! 
  *   \brief Returns the sorted sample data
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_SORT_ASC( double* X,    ///< [inout] is the input data sample (a one dimensional array).
                              size_t N      ///< [in] is the number of observations in X.
                              );
  /*! 
  *   \brief Calculates the Hurst exponent (a measure of persistence or long memory) for time series.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  */
  /*!
  *   \htmlonly
  *   <h3>References</h3>
  *   <ul>
  *   <li>[1] A.A.Anis, E.H.Lloyd (1976) The expected value of the adjusted rescaled Hurst range of independent normal summands, Biometrica 63, 283-298.</li>
  *   <li>[2] H.E.Hurst (1951) Long-term storage capacity of reservoirs, Transactions of the American Society of Civil Engineers 116, 770-808.</li>
  *   <li>[3] E.E.Peters (1994) Fractal Market Analysis, Wiley.</li>
  *   <li>[4] R.Weron (2002) Estimating long range dependence: finite sample properties and confidence intervals, Physica A 312, 285-299.</li>
  *   </ul>
  *   \endhtmlonly 
  */
  /*!
  *	  \note 1. The input data series must have at least 9 non-missing values. Otherwise, Hurst function returns #NDK_FAILED.
  *   \note 2. The input data series may include missing values (NaN), but they will not be included in the calculations. 
  *   \note 3. The Hurst exponent, \f$h\f$, is defined in terms of the rescaled range as follows:
				\f$E \left [ \frac{R(n)}{S(n)} \right ]=Cn^H  \textup{ as } n \to \infty \f$
  *   \note 4. Where:
				-\f$\left [ \frac{R(n)}{S(n)} \right ]\f$ is the Rescaled Range. 
				-\f$E \left [x \right ]\f$ is the expected value.
				-\f$n\f$ is the time of the last observation (e.g. it corresponds to \f$X_n\f$ in the input time series data.) 
				-\f$h\f$ is a constant. of
  *   \note 5. The Hurst exponent is a measure  autocorrelation (persistence and long memory):
				-A value of \f$0<H<0.5\f$ indicates a time series with negative autocorrelation (e.g. a decrease between values will probably be followed by another decrease). 
				-A value of \f$0.5<H<1\f$ indicates a time series with positive autocorrelation (e.g. an increase between values will probably be followed by another increase). 
				-A value of \f$H=0.5\f$ indicates a "true random walk," where it is equally likely that a decrease or an increase will follow from any particular value (e.g. the time series has no memory of previous values).
  *   \note 6. The Hurst exponent's namesake, Harold Edwin Hurst (1880-1978), was a British hydrologist who researched reservoir capacity along the Nile river. 
  *   \note 7. The rescaled range is calculated for a time series, \f$X=X_1,X_2,\dots, X_n\f$, as follows:
				1. Calculate the mean:<BR>
				\f$m=\dfrac{1}{n} \sum_{i=1}^{n} X_i\f$
				2. Create a mean adjusted series:<BR>
				\f$Y_t=X_{t}-m \textup{  for } t=1,2, \dots ,n\f$
				3. Calculate the cumulative deviate series Z:<BR>
				\f$Z_t= \sum_{i=1}^{t} Y_{i}  \textup{  for }  t=1,2, \dots ,n\f$
				4. Create a range series R:<BR>
				\f$R_t = max\left (Z_1, Z_2, \dots, Z_t  \right )- min\left (Z_1, Z_2, \dots, Z_t  \right ) \textup{  for } t=1,2, \dots, n\f$
				5.  Create a standard deviation series R:<BR>
				\f$S_{t}= \sqrt{\dfrac{1}{t} \sum_{i=1}^{t}\left ( X_{i} - u \right )^{2}}  \textup{  for } t=1,2, \dots ,n\f$
				Where:<BR>
				\f$h\f$ is the mean for the time series values \f$X_1,X_2, \dots, X_t\f$
  *   \note 8. Calculate the rescaled range series (R/S):<BR>
				\f$\left ( R/S \right )_{t} = \frac{R_{t}}{S_{t}} \textup{  for } t=1,2, \dots, n\f$
  *   \sa NDK_GINI()
  */
  int __stdcall NDK_HURST_EXPONENT( double* X,        ///< [in] is the input data sample (a one dimensional array). 
                                    size_t N,         ///< [in] is the number of observations in X.
                                    double alpha,     ///< [in] is the statistical significance level (1%, 5%, 10%). If missing, a default of 5% is assumed.
                                    WORD retType,     ///< [in] is a number that determines the type of return value: 
                                                      /// 1 = Empirical Hurst exponent (R/S method)
                                                      /// 2 = Anis-Lloyd/Peters corrected Hurst exponent
                                                      /// 3 = Theoretical Hurst exponent
                                                      /// 4 = Upper limit of the confidence interval
                                                      /// 5 = Lower limit of the confidence interval
                                    double* retVal    ///< [out] is the calculated value of this function.
                                    );

  /*! 
  *   \brief Returns the sample Gini coefficient, a measure of statistical dispersion. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *	  \note 1. A low Gini coefficient indicates a more equal distribution, with 0 corresponding to complete equality. Higher Gini coefficients indicate more unequal distributions, with 1 corresponding to complete inequality. 
  *   \note 2. The input data series may include missing values (NaN), but they will not be included in the calculations. 
  *   \note 3. The values in the input data series must be non-negative.
  *   \note 4. The Gini coefficient is computed as follows:
               \f$G(S)=1-\frac{2}{n-1}\left ( n-\frac{\sum_{i=1}^{n}iy_i}{\sum_{i=1}^{n}y_i} \right )\f$
  *   \note 5. Where:
				- \f$h\f$ is the input data series (\f$h\f$) arranged in descending order, so that \f$y_i\leq y_{i+1}\f$. 
				- \f$n\f$ is the number of non-missing values in the input time series data sample. 

  *   \note 6. The Gini coefficient value can range from 0 to 1 and is half the NDK_RMD().
  *   \note 7. \f$G(S)\f$ is a consistent estimator of the population Gini coefficient, but is generally unbiased (except when the population mean is known).
  *   \note 8. Developed by the Italian statistician Corrado Gini in 1912, the Gini coefficient is commonly used as a measure of comparative income or wealth. Where zero (0) corresponds to complete equality and one (1) to complete inequality.
  *   \sa NDK_HURST_EXPONENT()
  */
  int __stdcall NDK_GINI(double* x,     ///< [in] is the input data sample (must be non-negative) (a one dimensional array of values). 
						 size_t N,                  ///< [in] is the number of observations in X.
						 double* retVal             ///< [out] is the calculated value of this function.
             );

  /*! 
  *   \brief Calculates the cross-correlation function between two time series. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series is homogeneous or equally spaced. 
  *   \note 2. The two time series must be identical in size. 
  *   \note 3. The Pearson correlation, \f$r_{xy}\f$, is defined as follows:
				-\f$r_{xy}= \frac{\sum_{i=1}^N(x_i-\bar{x})(y_i-\bar{y})}{\sqrt{\sum_{i=1}^N(x_i-\bar{x})^2\times\sum_{i=1}^N(y_i-\bar{y})^2}}\f$, where:
					-\f$\bar{x}\f$ is the sample average of time series X.
					-\f$\bar{y}\f$ is the sample average of time series Y.
					-\f$x_i \in X\f$ is a value from the first input time series data.
					-\f$y_i \in Y\f$ is a value from the second input time series data.
					-\f$N\f$ is the number of pairs \f$\left ( x_i,y_i \right )\f$ that do not contain a missing observation.
  *   \sa NDK_ACF(), NDK_XCF()
  */
  int __stdcall NDK_XCF(double* X,     ///< [in] is the first univariate time series data (a one dimensional array). 
						double* Y,     ///< [in] is the second univariate time series data (a one dimensional array). 
						size_t N,      ///< [in] is the number of observations in X.
						size_t K,      ///< [in] is the lag order (e.g. 0=no lag, 1=1st lag, etc.) to use with the second time series input (X). If missing, a default lag order of zero (i.e. no-lag) is assumed. 
						WORD method,   ///< [in] is the algorithm to use for calculating the correlation (see #CORRELATION_METHOD)
						WORD retType,  ///< [in] is a switch to select the return output (1 = correlation value(default), 2 = std error).
						double* retVal ///< [out] is the calculated value of this function.
                        );   

  /*! 
  *   \brief Returns the sample root mean square (RMS).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The input time series data may include missing values (NaN), but they will not be included in the calculations. 
  *   \note 2. The root mean square (RMS) is defined as follows for a set of \f$n\f$ values \f${x_1,x_2,...,x_n}\f$:
				- \f$\textrm{RMS}=\sqrt{\frac{x_1^2+x_2^2+\cdots +x_N^2}{N}} =\sqrt{\frac{\sum_{i=1}^N {x_i^2}}{N}}\f$
  *   \note 3.  Where:
				- \f$x_i\f$ is the value of the i-th non-missing observation.
				- \f$N\f$ is the number of non-missing observations in the input sample data.
  *   \note 4. The root mean square (RMS) is a statistical measure of the magnitude of a varying quantity.
  *   \note 5. The root mean square (RMS) has an interesting relationship to the mean (\f$\bar{x}\f$) and the population standard deviation (\f$\sigma\f$), such that:
				- \f$\textrm{RMS}^2=\bar{x}^2+\sigma^2\f$
  *   \sa NDK_MD(), NDK_RMD()
  */
  int __stdcall NDK_RMS(double* X,       ///< [in] is the input data sample (a one/two dimensional array).
                        size_t N,        ///< [in] is the number of observations in X.
                        WORD reserved,   ///< [in] This parameter is reserved and must be 1.
                        double* retVal   ///< [out] is the calculated value of this function.
                        );

  /*! 
  *   \brief Returns the mean difference of the input data series.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
      \note 1. The time series may include missing values (NaN), but they will not be included in the calculations. 
  *   \note 2. The sample mean difference (MD) is computed as follows:
				- \f$\Delta = \textup{MD} = \frac{\sum_{i=1}^n \sum_{j=1}^n \| x_i - x_j \|}{n \times \left ( n-1 \right )}\f$
  *   \note 3. Where:
				- \f$x_i\f$ is the value of the i-th non-missing observation.
				- \f$n\f$ is the number of non-missing observations in the sample.
  *   \note 4. The mean difference is the product of the sample mean and the relative mean difference (RMD) and so can also be expressed in terms of the NDK_GINI:
				- \f$\textup{MD}= 2 \times G \times \bar{x}\f$
  *   \note 5. Where:
				- \f$\bar{x}\f$ is the arithmetic sample mean. 
				- \f$G\f$ is the NDK_GINI.
  *   \note 6. Because of its ties to the Gini coefficient, the mean difference is also called the "Gini mean difference." It is also known as the "absolute mean difference." 
  *   \note 7. The sample mean difference is not dependent on a specific measure of central tendency like the standard deviation. 
  *   \note 8. The mean difference of a sample is an unbiased and consistent estimator of the population mean difference. 
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_MD(double* pData,    ///< [in] is the input data series (one/two dimensional array).
					   size_t nSize,     ///< [in] is the number of observations in pData.
					   WORD reserved,    ///< [in] This parameter is reserved and must be 1.
					   double* retVal    ///< [out] is the computed value.
					   );

  /*! 
  *   \brief Returns the sample relative mean difference.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series may include missing values (NaN), but they will not be included in the calculations.
  *   \note 2. The relative mean difference is defined in terms of the NDK_MD as follows:
				- \f$\textup{RMD}= \frac{\textup{MD}}{\bar{x}}\f$

  *   \note 3: Where:
				-\f$\bar{x}\f$ is the sample mean (average) of the time series.
				-\f$\textup{MD}\f$ is the mean difference of the time series.
  *   \note 4: The RMD is also equal to twice the NDK_GINI. 
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_RMD(double* X,       ///< [in] is the input data sample (a one/two dimensional array).
						size_t N,        ///< [in] is the number of observations in X.
						WORD reserved,   ///< [in] This parameter is reserved and must be 1.
						double* retVal   ///< [out] is the calculated value of this function.
						);

  /*! 
  *   \brief Returns the sample median of absolute deviation (MAD).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The input data series may include missing values (NaN), but they will not be included in the calculations.
  *   \note 2. The median of absolute deviation (MAD) is defined as follows:
				-\f$\operatorname{MAD} = \operatorname{median}_{i}\left(\ \left| X_{i} - \operatorname{median}_{j} (X_{j}) \right|\ \right)\f$
  *   \note 3. In short, starting with the deviations from the data's median, the MAD is the median of their absolute values.
  *   \note 4. The median of absolute deviation (MAD) is a measure of statistical dispersion.
  *   \note 5. MAD is a more robust estimator of scale than the sample variance or standard deviation.
  *   \note 6. MAD is especially useful with distributions that have neither mean nor variance (e.g. the Cauchy distribution.)
  *   \note 7. MAD is a robust statistic because it is less sensitive to outliers in a data series than standard deviation.
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_MAD(double* X,       ///< [in] is the input data sample (a one/two dimensional array).
						size_t N,        ///< [in] is the number of observations in X.
						WORD reserved,   ///< [in] This parameter is reserved and must be 1.
						double* retVal ///< [out] is the calculated value of this function.
						);

  /*! 
  *   \brief Returns the long-run variance using a Bartlett kernel with window size k.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The input time series data may include missing values (NaN), but they will not be included in the calculations.
  *   \note 2. The long-run variance is computed as follows:
				-\f$\sigma^2=\frac{1}{T}\sum_{t=k}^{T-k}\sum_{i=-k}^k w_i(x_t-\bar{x})(x_{t-i}-\bar{x})\f$
  *   \note 3. Where:
				-\f$x_{t} \in X\f$ is a value from the input time series data.
				-\f$\bar{x}\f$ is the mean of the input time series data. 
				-The weight \f$w_i\f$ in Bartlett kernel is defined as follows:
					-\f$w_i= 1- \frac{\left | i \right |}{k+1}\f$
				-\f$k\f$ is the input window size for the Bartlett kernel.
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_LRVAR(double* X,     ///< [in] is the input data sample (a one/two dimensional array).
					      size_t N,      ///< [in] is the number of observations in X.
						  size_t w,      ///< [in] is the input Bartlett kernel window size. If omitted, the default value is the cubic root of the sample data size.
						  double* retVal ///< [out] is the calculated value of this function.
						  );

  /*! 
  *   \brief Calculates the sum of absolute errors (SAE) between the forecast and the eventual outcomes.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series is homogeneous or equally spaced.
  *   \note 2. The two time series must be identical in size.
  *   \note 3. A missing value (say \f$x_k\f$ or \f$\hat x_k\f$) in either time series will exclude the data point \f$(x_k,\hat x_k)\f$ from the SSE.
  *   \note 4. The sum of absolute errors (SAE) or deviations (SAD), is defined as follows:
				-\f$\mathrm{SAE}=\mathrm{SAD}=\sum_{i=1}^N \left | x_i-\hat x_i  \right |\f$, where:
					-\f$\{x_i\}\f$ is the actual observations time series.
					-\f$\{\hat x_i\}\f$ is the estimated or forecasted time series.
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_SAD(double* X,       ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
						double* Y,       ///< [in] is the forecast time series data (a one dimensional array). 
						size_t N,        ///< [in] is the number of observations in X.
						double* retVal   ///< [out] is the calculated value of this function.
						);

  /*! 
  *   \brief Calculates the mean absolute error function for the forecast and the eventual outcomes.     
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The mean absolute error is a common measure of forecast error in time series analysis.
  *   \note 2. The time series is homogeneous or equally spaced.
  *   \note 3. The two time series must be identical in size.
  *   \note 4. The mean absolute error is given by:
				-\f$\mathrm{MAE}=\frac{\mathrm{SAE}}{N}=\frac{\sum_{i=1}^N \left | x_i - \hat x_i \right |}{N}\f$, where:
					-\f$\{x_i\}\f$ is the actual observations time series.
					-\f$\{\hat x_i\}\f$ is the estimated or forecasted time series.
					-\f$\mathrm{SAE}\f$ is the sum of the absolute errors (or deviations).
					-\f$N\f$ is the number of non-missing data points.
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_MAE(double* X,       ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
						double* Y,       ///< [in] is the forecast time series data (a one dimensional array). 
						size_t N,        ///< [in] is the number of observations in X.
						double* retVal   ///< [out] is the calculated value of this function.
						);


  int __stdcall NDK_MASE(double* X,      ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
                        double* Y,       ///< [in] is the forecast time series data (a one dimensional array). 
                        size_t N,        ///< [in] is the number of observations in X.
                        size_t M,        ///< [in] is the seasonal period (for non-seasonal time series, set M=1).
                        double* retVal   ///< [out] is the calculated value of this function.
                      );




  /*! 
  *   \brief Calculates the mean absolute percentage error (deviation) function for the forecast and the eventual outcomes.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. MAPE is also referred to as MAPD. 
  *   \note 2. The time series is homogeneous or equally spaced. 
  *   \note 3. For a plain MAPE calculation, in the event that an observation value (i.e. \f$x_k\f$) is equal to zero, the MAPE function skips that data point. 
  *   \note 4. The mean absolute percentage error (MAPE), also known as mean absolute percentage deviation (MAPD), measures the accuracy of a method for constructing fitted time series values in statistics. 
  *   \note 5. The two time series must be identical in size. 
  *   \note 6. The mean absolute percentage error (MAPE) is defined as follows:
				-\f$\mathrm{MAPE}=\frac{100}{N}\times \sum_{i=1}^N \left | \frac{x_i - \hat x_i}{x_i} \right |\f$, where:
					-\f$\{x_i\}\f$ is the actual observations time series. 
					-\f$\{\hat x_i\}\f$ is the estimated or forecasted time series.
					-\f$N\f$ is the number of non-missing data points.
  *   \note 7. When calculating the average MAPE for a number of time series, you may encounter a problem: a few of the series that have a very high MAPE might distort a comparison between the average MAPE of a time series fitted with one method compared to the average MAPE when using another method. 
  *   \note 8. In order to avoid this problem, other measures have been defined, for example the SMAPE (symmetrical MAPE), weighted absolute percentage error (WAPE), real aggregated percentage error and relative measure of accuracy (ROMA). 
  *   \note 9. The symmetrical mean absolute percentage error (SMAPE) is defined as follows:
				-\f$\mathrm{SMAPE}=\frac{200}{N}\times \sum_{i=1}^N \left | \frac{x_i - \hat x_i}{x_i+\hat x_i} \right |\f$
  *   \note 10. The SMAPE is easier to work with than MAPE, as it has a lower bound of 0% and an upper bound of 200%. 
  *   \note 11. The SMAPE does not treat over-forecast and under-forecast equally.
  *   \note 12. For a SMAPE calculation, in the event the sum of the observation and forecast values (i.e. \f$x_k + \hat x_k\f$) equals zero, the MAPE function skips that data point. 
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_MAPE(double* X,       ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
						 double* Y,       ///< [in] is the forecast time series data (a one dimensional array). 
						 size_t N,        ///< [in] is the number of observations in X.
						 BOOL   SMAPE,    ///< [in] is a switch to select the return output (FALSE=MAPE (default), TRUE=Symmetric MAPE (SMAPI)). 
						 double* retVal   ///< [out] is the calculated value of this function.
						 );


  int __stdcall NDK_MdAPE(double* X,     ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
                        double* Y,       ///< [in] is the forecast time series data (a one dimensional array). 
                        size_t N,        ///< [in] is the number of observations in X.
                        BOOL   SMAPE,    ///< [in] is a switch to select the scale to divide on: FALSE = Actual obs., TRUE= Average (Actual, Forecast)
                        double* retVal   ///< [out] is the calculated value of this function.
                      );

  int __stdcall NDK_MAAPE(double* X,     ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
                        double* Y,       ///< [in] is the forecast time series data (a one dimensional array). 
                        size_t N,        ///< [in] is the number of observations in X.
                        double* retVal   ///< [out] is the calculated value of this function.
                      );



  /*! 
  *   \brief Calculates the root mean squared error (aka root mean squared deviation (RMSD)) function.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The RMSE is also known as root mean squared deviation (RMSD). 
  *   \note 2. Please see NDK_RMSD for definition and notes. 
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_RMSE(double* X,        ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array).
						 double* Y,        ///< [in] is the forecast time series data (a one dimensional array). 
						 size_t N,         ///< [In] is the number of observations in X.
						 WORD retType,     ///< [In] is a switch to select the return output (1=RMSE (default), 2=NRMSE, 3=CV(RMSE)).
						 double* retVal    ///< [out] is the calculated value of this function.
						 );

  
  
  int __stdcall NDK_GRMSE(double* X,        ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array).
                          double* Y,        ///< [in] is the forecast time series data (a one dimensional array). 
                          size_t N,         ///< [In] is the number of observations in X.
                          double* retVal    ///< [out] is the calculated value of this function.
                        );
  
  
  /*! 
  *   \brief Calculates the sum of the squared errors of the prediction function.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *	  \note 1. The time series is homogeneous or equally spaced. 
  *	  \note 2. The two time series must be identical in size. 
  *   \note 3. A missing value (e.g. \f$x_k\f$ or \f$\hat x_k\f$) in either time series will exclude the data point \f$(x_k,\hat x_k)\f$ from the SSE. 
  *   \note 4. The sum of the squared errors, \f$\mathrm{SSE}\f$, is defined as follows:
				\f$\mathrm{SSE}=\sum_{i=1}^N \left(x_i-\hat x_i \right )^2\f$, where:
					-\f$\{x_i\}\f$ is the actual observations time series.
					-\f$\{\hat x_i\}\f$ is the estimated or forecasted time series.
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_SSE(double* X,		    ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
						double* Y,		    ///< [in] is the forecasted time series data (a one dimensional array). 
						size_t N,		    ///< [in] is the number of observations in X.
						double* retVal	    ///< [out] is the calculated sum of squared errors.
						);


  /*!
  *   \brief Calculates the mean squared errors of the prediction function.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *	  \note 1. The two data sets must be identical in size.
  *   \note 2. A missing value (e.g. \f$x_k\f$ or \f$\hat x_k\f$) in either time series will exclude the data point \f$(x_k,\hat x_k)\f$ from the MSE.
  *   \sa NDK_SSE()
  */
  int __stdcall NDK_MSE(double* X,		  ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
                        double* Y,		  ///< [in] is the forecasted time series data (a one dimensional array). 
                        size_t N,		    ///< [in] is the number of observations in X.
                        double* retVal	///< [out] is the calculated mean of squared errors.
                      );


  int __stdcall NDK_GMSE(double* X,		  ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
                        double* Y,		  ///< [in] is the forecasted time series data (a one dimensional array). 
                        size_t N,		    ///< [in] is the number of observations in X.
                        double* retVal	///< [out] is the calculated mean of squared errors.
                      );




  int __stdcall NDK_MRAE(double* X,		  ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
    double* Y,		                      ///< [in] is the forecasted time series data (a one dimensional array). 
    size_t N,		                        ///< [in] is the number of observations in X.
    size_t period,                      ///< [in] is the seasonal period (for non-seasonal time series, set M=1).
    double* retVal	                    ///< [out] is the calculated mean of relative absolute error
  );

  int __stdcall NDK_MdRAE(double* X,		///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
    double* Y,		                      ///< [in] is the forecasted time series data (a one dimensional array). 
    size_t N,		                        ///< [in] is the number of observations in X.
    size_t period,                      ///< [in] is the seasonal period (for non-seasonal time series, set M=1).
    double* retVal	                    ///< [out] is the calculated median of relative absolute error
  );



  int __stdcall NDK_GMRAE(double* X,		  ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
      double* Y,		                      ///< [in] is the forecasted time series data (a one dimensional array). 
      size_t N,		                        ///< [in] is the number of observations in X.
      size_t period,                      ///< [in] is the seasonal period (for non-seasonal time series, set M=1).
      double* retVal	                    ///< [out] is the calculated geometric mean of relative absolute error
      );



  int __stdcall NDK_PB(double* X,		    ///< [in] is the original (eventual outcomes) time series sample data (a one dimensional array). 
    double* Y,		                      ///< [in] is the forecasted time series data (a one dimensional array). 
    size_t N,		                        ///< [in] is the number of observations in X.
    size_t period,                      ///< [in] is the seasonal period (for non-seasonal time series, set M=1).
    WORD basis,                         ///< [in] is the switch to specify the metric used for comparison: 0=absolute error, 1=MAE, 2=MSE
    double* retVal	                    ///< [out] is the calculated geometric mean of relative absolute error
  );



  /*! 
  *   \brief Calculates the sample autocorrelation function (ACF) of a stationary time series.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series is homogeneous or equally spaced. 
  *   \note 2. The time series may include missing values (NaN) at either end. 
  *   \note 3. The lag order (k) must be less than the time series size or else an error value (#NDK_FAILED) is returned. 
  *   \note 4. The ACF values are bound between -1 and 1, inclusive.
  *   \note 5. The sample autocorrelation is computed as:
				-\f$\hat{\rho}(h)=\frac{\sum_{k=h}^T{(y_{k}-\bar y)(y_{k-h}-\bar y)}}{\sum_{k=h}^T(y_{k}-\bar y)^2}\f$, where:
					-\f$y_{t}\f$ is the value of the time series at time t.
					-\f$h\f$ is the lag order.
					-\f$T\f$ is the number of non-missing values in the time series data.
					-\f$\bar y\f$ is the sample average/mean of the time series.
  *   \note 6. Special cases:
				-By definition, \f$\hat{\rho}(0)  \equiv 1.0\f$
  *   \sa NDK_ACF_ERROR(), NDK_XCF()
  */
  int __stdcall NDK_ACF(double* X,      ///< [in] is the univariate time series data (a one dimensional array).
                        size_t N,       ///< [in] is the number of observations in X. 
                        size_t K,       ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                        WORD method,    ///< [in] is the method selecor (0 = sample autocorrelation, 1= periodogram-based estimate, 2= cross-correlation based estimate).
                        double* retVal  ///< [out] is the calculated sample autocorrelation value. 
                        );


  /*! 
  *   \brief Calculates the standard error in the sample autocorrelation function.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF(), NDK_ACFCI()
  */
  int __stdcall NDK_ACF_ERROR(double* X,      ///< [in] is the univariate time series data (a one dimensional array).
                              size_t N,       ///< [in] is the number of observations in X. 
                              size_t K,       ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                              WORD method,    ///< [in] is the method selecor (0 = sample autocorrelation, 1= periodogram-based estimate, 2= cross-correlation based estimate).
                              double* retVal  ///< [out] is the standard error in the sample autocorrelation value. 
                              );


  /*! 
  *   \brief Calculates the confidence interval limits (upper/lower) for the autocorrelation function.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series is homogeneous or equally spaced. 
  *   \note 2. The time series may include missing values (NaN) at either end. 
  *   \note 3. The lag order (k) must be less than the time series size, or else an error value (#NDK_FAILED) is returned. 
  *   \note 4. The ACFCI function calculates the confidence limits as:
				-\f$\hat\rho_k - Z_{\alpha/2}\times \sigma_{\rho_k} \leq \rho_k \leq \hat\rho_k+ Z_{\alpha/2}\times \sigma_{\rho_k}\f$, where:
					-\f$\rho_k\f$ is the population autocorrelation function.
					-\f$\sigma_{\rho_k}\f$ is the standard error of the sample autocorrelation.
					-\f$\hat{\rho_{k}}\f$ is the sample autocorrelation function for lag k.
					-\f$Z\sim N(0,1)\f$
					-\f$P(\left|Z\right|\geq Z_{\alpha/2}) = \alpha\f$
  *   \note 5. For the case in which the underlying population distribution is normal, the sample autocorrelation also has a normal distribution: 
				-\f$\hat \rho_k \sim N(\rho_k,\sigma_{\rho_k}^2)\f$, where:
					-\f$\hat \rho_k\f$ is the sample autocorrelation for lag k.
					-\f$\rho_k\f$ is the population autocorrelation for lag k.
					-\f$\sigma_{\rho_k}\f$ is the standard error of the sample autocorrelation for lag k.
  *   \note 6. Bartlett proved that the variance of the sample autocorrelation of a stationary normal stochastic process (i.e. independent, identically normal distributed errors) can be formulated as:
				-\f$\sigma_{\rho_k}^2 = \frac{\sum_{j=-\infty}^{\infty}\rho_j^2+\rho_{j+k}\rho_{j-k}-4\rho_j\rho_k\rho_{i-k}+2\rho_j^2\rho_k^2}{T}\f$
  *   \note 7. Furthermore, the variance of the sample autocorrelation is reformulated: 
				-\f$\sigma_{\rho_k}^2 = \frac{1+\sum_{j=1}^{k-1}\hat\rho_j^2}{T}\f$, where:
					-\f$\sigma_{\rho_k}\f$ is the standard error of the sample autocorrelation for lag k. 
					-\f$T\f$ is the sample data size.
					-\f$\hat\rho_j\f$ is the sample autocorrelation function for lag j.
					-\f$k\f$ is the lag order. 
  *   \sa NDK_ACF(), NDK_ACF_ERROR()
  */
  int __stdcall NDK_ACFCI(double* X,      ///< [in] is the univariate time series data (a one dimensional array).
                          size_t N,       ///< [in] is the number of observations in X. 
                          size_t K,       ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                          WORD method,    ///< [in] is the method selecor (0 = sample autocorrelation, 1= periodogram-based estimate, 2= cross-correlation based estimate).
                          double alpha,   ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                          double* ULCI,   ///< [out] is the upper limit value of the confidence interval 
                          double* LLCI    ///< [out] is the lower limit value of the confidence interval.
                          );

  /*! 
  *   \brief Calculates the sample partial autocorrelation function (PACF). 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF(), NDK_PACF_ERROR(),NDK_PACFCI() 
  */
  int __stdcall NDK_PACF( double* X,      ///< [in] is the univariate time series data (a one dimensional array).
                          size_t N,       ///< [in] is the number of observations in X. 
                          size_t K,       ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                          double* retVal  ///< [out] is the calculated sample partial-autocorrelation value.
                          );
  /*! 
  *   \brief Calculates the standard error of the sample partial autocorrelation function (PACF). 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_PACF(), NDK_PACFCI()
  */
  int __stdcall NDK_PACF_ERROR( double* X,      ///< [in] is the univariate time series data (a one dimensional array).
                                size_t N,       ///< [in] is the number of observations in X. 
                                size_t K,       ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                                double* retVal  ///< [out] is the standard error in the sample partial-autocorrelation value. 
                                );

  /*! 
  *   \brief Calculates the confidence interval limits (upper/lower) for the partial-autocorrelation function.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF(), NDK_ACF_ERROR()
  */
  int __stdcall NDK_PACFCI( double* X,      ///< [in] is the univariate time series data (a one dimensional array).
                            size_t N,       ///< [in] is the number of observations in X. 
                            size_t K,       ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                            double alpha,   ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                            double* ULCI,   ///< [out] is the upper limit value of the confidence interval.
                            double* LLCI    ///< [out] is the lower limit value of the confidence interval.
                            );



  /*! 
  *   \brief Calculates the periodgram value for different lags.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ACF(), NDK_PACF()
  */
  int __stdcall NDK_PERIODOGRAM(double* pData,            ///< [in] is the univariate time series data (a one dimensional array).
                                size_t  nSize,            ///< [in] is the number of observations in pData. 
                                PERIODOGRAM_OPTION_TYPE option, ///< [in] is the pre-processing option to the time series (e.g. detrend, difference, auto, etc.)
                                double alpha,             ///< [in] is the statistical significance level (used in the auto-process procedure). If missing, a default of 5% is assumed.
                                double* retVal,           ///< [out] is the periodogram values for this series
                                size_t  nOutSize          ///< [in] is the size of the output buffer (i.e. retVal)
                                );


  /*! 
  *   \brief Calculates the estimated value of the exponential-weighted volatility (EWV).  
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series is homogeneous or equally spaced. 
  *   \note 2. The time series may include missing values (NaN) at either end. 
  *   \note 3. The EWMA function assumes that the time series has an average equal to zero. 
  *   \note 4. The exponential-weighted moving average is calculated as:
				-\f$\sigma_t^2=\lambda \sigma_{t-1}^2+(1-\lambda)x_{t-1}^2\f$, where:
					-\f$x_t\f$ is the value of the time series value at time t. 
					-\f$\lambda\f$ is the smoothing parameter (i.e. a non-negative constant between 0 and 1).
  *   \note 5. The size of the EWMA time series is equal to the input time series, but with the first observation (or last, if the original series is reversed) set to missing (NaN). 
  *   \sa NDK_WMA(), NDK_EWXCF()
  */
  int  __stdcall NDK_EWMA(double *X,        ///< [in] is the univariate time series data (a one dimensional array).
                          size_t N,         ///< [in] is the number of observations in X. 
                          double lambda,    ///< [in] is the smoothing parameter used for the exponential-weighting scheme. If missing, a default value of 0.94 is assumed 
                          size_t step,      ///< [in] is the forecast time/horizon (expressed in terms of steps beyond the end of the time series X). If missing, a default value of 0 is assumed. 
                          double* retVal    ///< [out] is the estimated value of the exponential-weighted volatility.
                          );

  /*! 
  *   \brief Computes the correlation factor using the exponential-weighted correlation function.
  *   \details NDK_EWXCF computes the correlation estimate using the exponential-weighted covariance (EWCOV) and volatility (EWMA/EWV) method for each time series.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \note 1. The time series is homogeneous or equally spaced.
  *   \note 2. The two time series must have identical size and time order. 
  *   \note 3. The correlation is defined as:
				-\f$\rho^{(xy)}_t=\frac{\sigma_t^{(xy)}}{{_x\sigma_t}\times{_y\sigma_t}}\f$
				-\f$\sigma_t^{(xy)} = \lambda\sigma_{t-1}^{(xy)}+(1-\lambda)x_{t-1}y_{t-1}\f$
				-\f$_x\sigma_t^2=\lambda\times{_x\sigma_{t-1}^2}+(1-\lambda)x_{t-1}^2\f$
				-\f$_y\sigma_t^2=\lambda\times{_y\sigma_{t-1}^2}+(1-\lambda)y_{t-1}^2\f$, where:
					-\f$\rho^{(xy)}_t\f$ is the sample correlation between X and Y at time t.
					-\f$\sigma_t^{(xy)}\f$ is the sample exponential-weighted covariance between X and Y at time t.
					-\f$_x\sigma_t\f$ is the sample exponential-weighted volatility for the time series X at time t.
					-\f$_y\sigma_t\f$ is the sample exponential-weighted volatility for the time series Y at time t.
					-\f$\lambda\f$ is the smoothing factor used in the exponential-weighted volatility and covariance calculations.
  *   \sa SFMacros.h, NDK_WMA(), NDK_EWMA()
  */
  int  __stdcall NDK_EWXCF( double *X,      ///< [in] is the first univariate time series data (a one dimensional array).
                            double *Y,      ///< [in] is the second univariate time series data (a one dimensional array).
                            size_t N,       ///< [in] is the number of observations in X (or Y).
                            double lambda,  ///< [in] is the smoothing parameter used for the exponential-weighting scheme. If missing, a default value of 0.94 is assumed. 
                            size_t step,    ///< [in] is the forecast time/horizon (expressed in terms of steps beyond the end of the time series X). If missing, a default value of 0 is assumed. 
                            double* retVal  ///< [out] is the estimated value of the correlation factor.
                            );


  ///@}

  /// \name Statistical Distribution
  /// Statistical distribution
  /// @{

  /*! 
  *   \brief Calculates the excess kurtosis of the generalized error distribution (GED).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_TDIST_XKURT(), NDK_XKURTTEST()
  */
  int __stdcall NDK_GED_XKURT(double df,        ///< [in]   is the shape parameter (or degrees of freedom) of the distribution (V > 1).  
                              double* retVal    ///< [out] is the computed value
                              );

  /*! 
  *   \brief Calculates the excess kurtosis of the student's t-distribution.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_TDIST_XKURT(), NDK_XKURTTEST()
  */
  int __stdcall NDK_TDIST_XKURT(double df,        ///< [in] is the degrees of freedom of the student's t-distribution (v > 4).  
                                double* retVal    ///< [out] is the computed value.
                                );

  /*! 
  *   \brief Calculates the empirical distribution function (or empirical cdf) of the sample data.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_KERNEL_DENSITY_ESTIMATE(), NDK_HISTOGRAM()
  */
  int __stdcall NDK_EDF(double* pData,    ///< [in] is the input data series (one/two dimensional array). 
                        size_t nSize,     ///< [in] is the number of elements in pData.
                        double targetVal, ///< [in] is the target value to compute the underlying cdf for. 
                        WORD retType,     ///< [in] is a switch to select the return output (1=CDF (default), 2=Inverse CDF). 
                        double* retVal    ///< [out] is the computed value.
                        );

  /*! 
  *   \brief Returns the number of histogram bins using a given method. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_HIST_BIN_LIMIT(), NDK_HISTOGRAM()
  */
  int __stdcall NDK_HIST_BINS(double* pData,  ///< [in] is the input data series (one/two dimensional array).
                              size_t nSize,   ///< [in] is the number of elements in pData.
                              WORD argMethod, ///< [in] is a switch to select the calculation method (1=Sturges's formula, 2=Square-root, 3=Scott's Choice, 4=Freedman-Diaconis choice, 5=Optimal (default)). 
                              size_t* retVal  ///< [out] is the computed value.
                              );

  /*! 
  *   \brief Returns the upper/lower limit or center value of the k-th histogram bin. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_HIST_BINS(), NDK_HISTOGRAM()
  */
  int __stdcall NDK_HIST_BIN_LIMIT( double* pData,  ///< [in] is the input data series (one/two dimensional array).
                                    size_t nSize,   ///< [in] is the number of elements in pData.
                                    size_t nBins,   ///< [in] is the input number of bins for the histogram.
                                    size_t index,   ///< [in] is the bin index or order; e.g. 0=1st bin (default),1=2nd bin,..., N-1. 
                                    WORD argRetTYpe, ///< [in] is a switch to select the return output (0=lower limit (default), 1=upper limit of the bin, 2=center of the bin). 
                                    double* retVal  ///< [out] is the computed value.
                                    );

  /*! 
  *   \brief Calculates the histogram or cumulative histogram function for a given bin. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_HIST_BINS(), NDK_HISTOGRAM()
  */
  int __stdcall NDK_HISTOGRAM(  double* pData,    ///< [in] is the input data series (one/two dimensional array).
                                size_t nSize,     ///< [in] is the number of elements in pData.
                                size_t nBins,     ///< [in] is the input number of bins for the histogram.
                                size_t index,     ///< [in] is the bin index or order; e.g. 0=1st bin (default),1=2nd bin,..., N. 
                                WORD argRetTYpe,  ///< [in] is a switch to select the return output:
                                                  ///     0. histogram 
                                                  ///     1. cumulative histogram (default)). 
                                double* retVal    ///< [out] is the computed value.
                                );


  /*! 
  *   \brief Returns the upper/lower limit or center value of the k-th histogram bin. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_HIST_BINS(), NDK_HISTOGRAM()
  */
  int __stdcall NDK_KERNEL_DENSITY_ESTIMATE(double* pData,        ///< [in] is the input data series (one/two dimensional array).
                                            size_t nSize,         ///< [in] is the number of elements in pData.
                                            double targetVal,     ///< [in] is the target value to compute the underlying cdf for. 
                                            double bandwidth,     ///< [in] is the smoothing parameter (bandwidth) of the kernel density estimator. If missing, the KDE function calculates an optimal value.
                                            WORD argKernelFunc,   ///< [in] is a switch to select the kernel function:
                                                                  ///   1=Gaussian (default),
                                                                  ///   2=Uniform
                                                                  ///   3=Triangular 
                                                                  ///   4=Biweight (Quatric)
                                                                  ///   5=Triweight
                                                                  ///   6=Epanechnikov
                                            double* retVal        ///< [out] is the computed value.
                                            );


  /*! 
  *   \brief Returns a sequence of random numbers drawn from Normal distribution
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_GAUSS_FORECI()
  */
  int __stdcall NDK_GAUSS_RNG( double mean,       ///< [in] is the mean of the Gaussian distribution.
                               double sigma,      ///< [in] is the standard deviation of the Gaussian distribution.
                               UINT seed,         ///< [in] is a number to initialize the psuedorandom number generator. 
                               double* retArray,  ///< [out] are the generated random values.
                               UINT nArraySize    ///< [in] is the number of elements in retArray
                              );


  /*! 
  *   \brief Returns the upper & lower limit of the confidence interval for the Gaussian distribution.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_TSTUDENT_FORECI(), NDK_GED_FORECI()
  */
  int __stdcall NDK_GAUSS_FORECI( double mean,    ///< [in] is the mean of the Gaussian distribution.
                                  double sigma,   ///< [in] is the standard deviation of the Gaussian distribution.
                                  double alpha,   ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                                  BOOL upper,     ///< [in] is a switch to select the limit (upper/lower).
                                  double* retVal  ///< [out] is the computed value.
                                  );

  /*! 
  *   \brief Returns the upper & lower limit of the confidence interval for the student\'s t-distribution
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_GAUSS_FORECI(), NDK_GED_FORECI()
  */
  int __stdcall NDK_TSTUDENT_FORECI(double mean,      ///< [in] is the mean of the student's t-distribution.
                                    double sigma,     ///< [in] is the standard deviation of the student's t-distribution.
                                    double df,        ///< [in] is the degrees of freedom (nu) of the student's t-distribution.
                                    double alpha,     ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                                    BOOL upper,       ///< [in] is a switch to select the limit (upper/lower).
                                    double* retVal    ///< [out] is the computed value.
                                    );



  /*! 
  *   \brief Returns the upper & lower limit of the confidence interval for the Generalized Error Distribution (GED) distribution
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_TSTUDENT_FORECI(), NDK_GAUSS_FORECI()
  */
  int __stdcall NDK_GED_FORECI( double mean,      ///< [in] is the mean of the GED distribution.
                                double sigma,     ///< [in] is the standard deviation of the GED distribution.
                                double df,        ///< [in] is the degrees of freedom (nu) of the GED distribution.
                                double alpha,     ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                                BOOL upper,       ///< [in] is a switch to select the limit (upper/lower).
                                double* retVal    ///< [out] is the computed value.
                                );
  ///@}


  /// \name Statistical Testing
  /// Statistical/hypothesis testing is a common method of drawing inferences about a population based on statistical evidence from a sample.
  /// @{

  /*! 
  *   \brief Calculates the p-value of the statistical test for the population autocorrelation function.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, NDK_WMA(), NDK_EWMA()
  */
  int __stdcall NDK_ACFTEST(double* X,        ///< [in] is the univariate time series data (a one dimensional array).
                            size_t N,         ///< [in] is the number of observations in X. 
                            int K,            ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                            WORD method,      ///< [in] is the type of test: parametric or non-parametric.
                            double target,    ///< [in] is the assumed autocorrelation function value. If missing, the default of zero is assumed.
                            double alpha,     ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                            WORD retType,     ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                              ///       1. P-value
                                              ///       2. Test statistics (aka score)
                                              ///       3. Critical value
                            double* retVal    ///< [out] is the calculated test statistics.
                            );

  /*! 
  *   \brief Returns the p-value of the normality test (i.e. whether a data set is well-modeled by a normal distribution).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_MEANTEST(), NDK_SKEWTEST(), #NORMALTEST_METHOD, #TEST_RETURN
  */
  int __stdcall NDK_NORMALTEST( double* X,      ///< [in] is the sample data (a one dimensional array).
                                size_t N,       ///< [in] is the number of observations in X.
                                double alpha,   ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                                WORD method,    ///< [in] is the statistical test to perform (1=Jarque-Bera, 2=Shapiro-Wilk, 3=Chi-Square (Doornik and Hansen)). 
                                WORD retType,   ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                                ///       1. P-value
                                                ///       2. Test statistics (aka score)
                                                ///       3. Critical value
                                double* retVal  ///< [out] is the calculated test statistics.
                                );

  /*! 
  *   \brief Computes the p-value of the statistical portmanteau test (i.e. whether any of a group of autocorrelations of a time series are different from zero).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_NORMALTEST(), NDK_ARCHTEST()
  */
  int __stdcall NDK_WNTEST( double* X,        ///< [in] is the univariate time series data (a one dimensional array).
                            size_t N,         ///< [in] is the number of observations in X. 
                            size_t K,         ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                            double alpha,     ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                            WORD method,      ///< [in] is the statistical test to perform (1=Ljung-Box). 
                            WORD retType,     ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                              ///       1. P-value
                                              ///       2. Test statistics (aka score)
                                              ///       3. Critical value
                            double* retVal    ///< [out] is the calculated test statistics.
                            );

  /*! 
  *   \brief Calculates the p-value of the ARCH effect test (i.e. the white-noise test for the squared time series).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_NORMALTEST(), NDK_ARCHTEST(), 
  */
  int __stdcall NDK_ARCHTEST( double* X,        ///< [in] is the univariate time series data (a one dimensional array).
                              size_t N,         ///< [in] is the number of observations in X. 
                              size_t K,         ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                              double alpha,     ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                              WORD method,      ///< [in] is the statistical test to perform (1=Ljung-Box).
                              WORD retType,     ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                                ///       1. P-value
                                                ///       2. Test statistics (aka score)
                                                ///       3. Critical value
                              double* retVal    ///< [out] is the calculated test statistics.
                              );
  /*! 
  *   \brief Calculates the p-value of the statistical test for the population mean.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_SKEWTEST(), NDK_STDEVTEST()
  */
  int __stdcall NDK_MEANTEST( double* X,      ///< [in] is the sample data (a one dimensional array).
                              size_t N,       ///< [in] is the number of observations in X.
                              double target,  ///< [in] is the assumed mean value. If missing, a default of zero is assumed.
                              double alpha,   ///< [in] is the statistical significance level. If missing, the default of 5% is assumed.
                              WORD method,    ///< [in] is the statistical test to perform (1=parametric).
                              WORD retType,   ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                              ///       1. P-value
                                              ///       2. Test statistics (aka score)
                                              ///       3. Critical value
                              double* retVal  ///< [out] is the calculated test statistics.
                              );
  /*! 
  *   \brief Calculates the p-value of the statistical test for the population standard deviation.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_MEANTEST(), NDK_SKEWTEST(), NDK_XKURTTEST()
  */
  int __stdcall NDK_STDEVTEST(double* X,        ///< [in] is the sample data (a one dimensional array).
                              size_t N,         ///< [in] is the number of observations in X. 
                              double target,    ///< [in] is the assumed standard deviation value. If missing, a default of one is assumed
                              double alpha,     ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                              WORD method,      ///< [in] is the statistical test to perform (1=parametric). 
                              WORD retType,     ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                                ///       1. P-value
                                                ///       2. Test statistics (aka score)
                                                ///       3. Critical value
                              double* retVal    ///< [out] is the calculated test statistics.
                              );

  /*! 
  *   \brief Calculates the p-value of the statistical test for the population skew (i.e. 3rd moment).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_NORMALTEST(), NDK_MEANTEST(), NDK_STDEVTEST(), NDK_XKURTTEST()
  */
  int __stdcall NDK_SKEWTEST( double* X,        ///< [in] is the sample data (a one dimensional array).
                              size_t N,         ///< [in] is the number of observations in X.
                              double alpha,     ///< [in] is the statistical significance level. If missing, the default of 5% is assumed.
                              WORD method,      ///< [in] is the statistical test to perform (1=parametric). 
                              WORD retType,     ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                                ///       1. P-value
                                                ///       2. Test statistics (aka score)
                                                ///       3. Critical value
                              double* retVal    ///< [out] is the calculated test statistics.
                              );

  /*! 
  *   \brief Calculates the p-value of the statistical test for the population excess kurtosis (4th moment).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa SFMacros.h, NDK_NORMALTEST(), NDK_MEANTEST(), NDK_STDEVTEST(), NDK_SKEWTEST()
  */
  int __stdcall NDK_XKURTTEST(double* X,        ///< [in] is the sample data (a one dimensional array).
                              size_t N,         ///< [in] is the number of observations in X. 
                              double alpha,     ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                              WORD method,      ///< [in] is the statistical test to perform (1=parametric). 
                              WORD retType,     ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                                ///       1. P-value
                                                ///       2. Test statistics (aka score)
                                                ///       3. Critical value
                              double* retVal    ///< [out] is the calculated test statistics.
                              );
  /*! 
  *   \brief Calculates the test stats, p-value or critical value of the correlation test.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_NORMALTEST(), NDK_MEANTEST(), NDK_STDEVTEST(), NDK_SKEWTEST()
  */
  int __stdcall NDK_XCFTEST(double* X,      ///< [in] is the first univariate time series data (a one dimensional array).
                            double *Y,      ///< [in] is the second univariate time series data (a one dimensional array).
                            size_t N,       ///< [in] is the number of observations in X (or Y).
                            int K,          ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                            double target,  ///< [in] is the assumed correlation value. If missing, a default of zero is assumed.
                            double alpha,   ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                            WORD method,    ///< [in] is the desired correlation coefficient (1=Pearson (default), 2=Spearman, 3=Kendall). If missing, a Pearson coefficient is assumed.
                            WORD retType,   ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                            ///       1. P-value
                                            ///       2. Test statistics (aka score)
                                            ///       3. Critical value
                            double* retVal  ///< [out] is the calculated test statistics.
                            );


  /*! 
  *   \brief Returns the p-value of the Augmented Dickey-Fuller (ADF) test, which tests for a unit root in the time series sample.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_NORMALTEST(), NDK_MEANTEST(), NDK_STDEVTEST(), NDK_SKEWTEST()
  */
  int __stdcall NDK_ADFTEST(double* X,      ///< [in] is the univariate time series data (a one dimensional array).
                            size_t N,       ///< [in] is the number of observations in X.
                            WORD K,         ///< [in] is the lag length of the autoregressive process. If missing, an initial value equal to the cubic root of the input data size is used.
                            ADFTEST_OPTION options,   ///< [in] is the model description flag for the Dickey-Fuller test variant (1=no constant, 2=contant-only, 3=trend only,  4=constant and trend, 5=const, trend and trend squared). 
                            BOOL testDown,  ///< [in] is the mode of testing. If set to TRUE (default), ADFTest performs a series of tests. The test starts with the input length lag, but the actual length lag order used is obtained by testing down. 
                            double alpha,   ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                            WORD method,    ///< [in] is the statistical test to perform (1=ADF).
                            WORD retType,   ///< [in] is a switch to select the return output: (\ref #TEST_RETURN)
                                            ///       1. P-value
                                            ///       2. Test statistics (aka score)
                                            ///       3. Critical value

                            double* retVal  ///< [inout] is the calculated test statistics.
                            );
  int __stdcall NDK_KPSSTEST(double* pData, size_t nSize, WORD maxOrder, WORD option, BOOL testDown, WORD argMethod, WORD retType, double alpha, double* retVal);


  /*! 
  *   \brief Returns the Johansen (cointegration) test statistics for two or more time series.
  *   \note 1. Each column in the input matrix corresponds to a separate time series variable.
  *   \note 2. The input matrix can have no more than twelve (12) columns (or variables).
  *   \note 3. Each row in the input matrix corresponds to an observation.
  *   \note 4. The number of cointegrating relationships should be no greater than the number of input variables.
  *   \note 5. The time series data are homogeneous or equally spaced.
  *   \note 6. The time series may include missing values (e.g. NaN) at either end.
  *   \note 7. There are two types of Johansen tests - with trace or with eigenvalue - and the inferences might be a bit different for each.
  *             - The null hypothesis for the trace test is the number of cointegration vectors r <= ?
  *             - The null hypothesis for the eigenvalue test is r = ?
  *   \note 8. The function was added in version 1.62 DEWDROP.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_ADFTEST(), NDK_MEANTEST(), NDK_STDEVTEST(), NDK_SKEWTEST()
  *   
  */
  int __stdcall NDK_JOHANSENTEST(double** XX,         ///< [in] is the multivariate time series matrix data (two dimensional).
                                 size_t N,            ///< [in] is the number of observations in XX.
                                 size_t M,            ///< [in] is the number of variables in XX.
                                 size_t K,            ///< [in] is the number of lagged difference terms used when computing the estimator.
                                 short nPolyOrder,    ///< [in] is the order of the polynomial: (-1=no constant, 0=contant-only (default), 1=constant and trend).
                                 BOOL tracetest,      ///< [in] is a flag to select test: TRUE=trace, FALSE=maximal eignvalue test.
                                 WORD R,              ///< [in] is the assumed number of cointegrating relationships between the variables (if missing, r=1). 
                                 double alpha,        ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                                 double* retStat,     ///< [out] is the calculated test statistics score.
                                 double *retCV        ///< [out] is the calculated test critical value.
                                 );                   /// \example sdk_cointegration.cpp

  /*! 
  *   \brief Returns the collinearity test statistics for a set of input variables.
  *   \note 1. Each column in the input matrix corresponds to a separate time series variable.
  *   \note 2. The input matrix can have no more than twelve (12) columns (or variables).
  *   \note 3. Each row in the input matrix corresponds to an observation.
  *   \note 4. The input data may include missing values (e.g. NaN).
  *   \note 5. In the variance inflation factor (VIF) method, a series of regressions models are constructed, where one variable is the dependent variable against the remaining predictors.
  *   \note 6. A tolerance of less than 0.20 or 0.10 and/or a VIF of 5 or 10 and above indicates a multicollinearity problem. 
  *   \note 7. As a rule of thumb, a condition number (\f$\kappa\f$) greater or equal to 30 indicates a severe multi-collinearity problem.
  *   \note 8. The CollinearityTest function is available starting with version 1.60 APACHE.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_CHOWTEST()
  *   
  */
  int __stdcall	NDK_COLNRTY_TEST (double** XX,      ///< [in] is the input variables matrix data (two dimensional).
                                  size_t N,         ///< [in] is the number of rows (observations) in XX.
                                  size_t M,         ///< [in] is the number of columns (variables) in XX.
                                  LPBYTE mask,      ///< [in] is the boolean array to select a subset of the input variables in X. If NULL, all variables in X are included.
                                  size_t nMaskLen,              ///< [in] is the number of elements in the mask. Must be zero or equal to M.
                                  COLNRTY_TEST_TYPE nMethod,    ///< [in] is the multi-colinearity measure to compute (see #COLNRTY_TEST_TYPE).
                                  WORD nColIndex,               ///< [in] is a switch to designate the explanatory variable to examine (not required for condition number).
                                  double* retVal    ///< [out] is the calculated statistics of collinearity.
                                  );
  /*! 
  *   \brief Returns the p-value of the regression stability test (i.e. whether the coefficients in two linear regressions on different data sets are equal). 
  *   \note 1. Each column in the input matrix corresponds to a separate time series variable.
  *   \note 2. The input matrix can have no more than twelve (12) columns (or variables). 
  *   \note 3. Each row in the input matrix corresponds to an observation.
  *   \note 4. The input data may include missing values (e.g. NaN).
  *   \note 5. Observations (i.e. row) with missing values in X or Y are removed.
  *   \note 6. The number of observations of each data set must be larger than the number of explanatory variables. 
  *   \note 8. The CollinearityTest function is available starting with version 1.60 APACHE.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful. see \ref SFMacros.h
  *   \sa NDK_COLNRTY_TEST()
  *   
  */
  int __stdcall NDK_CHOWTEST( double** XX1,         ///< [in] is the independent variables data matrix of the first data set (two dimensional).
                              size_t M,             ///< [in] is the number of variables (columns) in XX1 and XX2.
                              double* Y1,           ///< [in] is the response or the dependent variable data array for the first data set (one dimensional array).
                              size_t N1,            ///< [in] is the number of observations (rows) in the first data set.
                              double** XX2,         ///< [in] is the independent variables data matrix of the second data set, such that each column represents one variable.
                              double* Y2,           ///< [in] is the response or the dependent variable data array of the second data set (one dimensional array).
                              size_t N2,            ///< [in] is the number of observations (rows) in the second data set.
                              LPBYTE mask,          ///< [in] is the boolean array to select a subset of the input variables in X. If NULL, all variables in X are included. 
                              size_t nMaskLen,      ///< [in] is the number of elements in the mask, which must be zero or equal to M.
                              double intercept,     ///< [in] is the regression constant or the intercept value (e.g. zero). If missing, an intercept is not fixed and will be computed from the data set.
                              TEST_RETURN retType,  ///< [in] is a switch to select the return output (see #TEST_RETURN for more details).
                              double* retVal        ///< [in] is the calculated Chow test statistics.
                              );


  ///@}


  /*!
  * \name Transfom
  * @{
  */
  /*! 
  *   \brief Returns an array of cells for the backward shifted, backshifted or lagged time series.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_DIFF()
  */
  int   __stdcall NDK_LAG(double* X,    ///< [inout] is the univariate time series data (a one dimensional array).
                          size_t  N,    ///< [in] is the number of observations in X. 
                          size_t  K     ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                          );
  /*! 
  *   \brief Returns an array of cells for the differenced time series (i.e. (1-L^S)^D).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_LAG(), NDK_INTEG
  */
  int   __stdcall NDK_DIFF( double* X,  ///< [inout] is the univariate time series data (a one dimensional array).
                            size_t N,   ///< [in] is the number of observations in X. 
                            size_t S,   ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                            size_t D    ///< [in] is the number of repeated differencing (e.g. d=0 (none), d=1 (difference once), 2=(difference twice), etc.).
                            );
  /*! 
  *   \brief Returns an array of cells for the integrated time series (inverse operator of NDK_DIFF).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_LAG(), NDK_DIFF
  */
  int   __stdcall NDK_INTEG(double* X,  ///< [inout] is the univariate time series data (a one dimensional array).
                            size_t N,   ///< [in] is the number of observations in X.
                            size_t S,   ///< [in] is the lag order (e.g. k=0 (no lag), k=1 (1st lag), etc.).
                            size_t D,   ///< [in] is the number of repeated differencing (e.g. d=0 (none), d=1 (difference once), 2=(difference twice), etc.).
                            double* X0, ///< [in,optional] is the initial (un-differenced) univariate time series data (a one dimensional array). If missing (i.e. NULL), zeros are assumed.
                            size_t N0   ///< [in] is the number of observations in X0.
                            );


  /*! 
  *   \brief Returns an array of cells of a time series after removing all missing values. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_LAG(), NDK_DIFF
  */
  int   __stdcall NDK_RMNA( double *X,    ///< [inout] is the univariate sample data (a one dimensional array).
                            size_t* N     ///< [inout] is the number of observations in X.
                            );

  /*! 
  *   \brief Returns the time-reversed order time series (i.e. the first observation is swapped with the last observation, etc.): both missing and non-missing values.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_LAG(), NDK_DIFF
  */
  int   __stdcall NDK_REVERSE(double *X,  ///< [inout] is the univariate time series data (a one dimensional array).
                              size_t N    ///< [in] is the number of observations in X.
                              );

  /*! 
  *   \brief Returns an array of cells for the scaled time series.  
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ADD(), NDK_SUB()
  */
  int   __stdcall NDK_SCALE(double *X,  ///< [inout] is the univariate time series data (a one dimensional array).
                            size_t N,   ///< [in] is the number of observations in X. 
                            double K    ///< [in] is the scalar/multiplier value.
                            );


  /*! 
  *   \brief Returns an array of the difference between two time series.  
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_ADD(), NDK_SCALE()
  */
  int   __stdcall NDK_SUB(double *X,          ///< [inout] is the univariate time series data (a one dimensional array).
                          size_t N1,          ///< [in] is the number of observations in X. 
                          const double *Y,    ///< [in] is the second univariate time series data (a one dimensional array).
                          size_t N2           ///< [in] is the number of observations in Y. 
                          );

  /*! 
  *   \brief Returns an array of cells for the sum of two time series.  
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_SUB(), NDK_SCALE()
  */
  int   __stdcall NDK_ADD(double *X,        ///< [inout] is the univariate time series data (a one dimensional array).
                          size_t N1,        ///< [in] is the number of observations in X. 
                          const double *Y,  ///< [in] is the second univariate time series data (a one dimensional array).
                          size_t N2         ///< [in] is the number of observations in Y. 
                          );       



  /*! 
  *   \brief Computes the complementary log-log transformation, including its inverse.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_HodrickPrescotFilter(), NDK_DFT(), NDK_IDFT()
  */
  int   __stdcall NDK_CLOGLOG(double *X,        ///< [inout] is the univariate time series data (a one dimensional array).
                              size_t N,         ///< [in] is the number of observations in X. 
                              WORD retTYpe      ///< [in] is a number that determines the type of return value: 1 (or missing)=C-log-log , 2=inverse C-log-log.
                              );

  /*! 
  *   \brief Computes the probit transformation, including its inverse.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_HodrickPrescotFilter(), NDK_DFT(), NDK_IDFT()
  */
  int   __stdcall NDK_PROBIT(double *X,       ///< [inout] is the univariate time series data (a one dimensional array).
                             size_t N,        ///< [in] is the number of observations in X.
                             WORD retTYpe     ///< [in] is a number that determines the type of return value: 1 (or missing)=probit , 2=inverse probit.
                             );

  /*! 
  *   \brief Computes the complementary log-log transformation, including its inverse.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_PROBIT(), NDK_BOXCOX(), NDK_CLOGLOG()
  */
  int   __stdcall NDK_LOGIT(double *X,        ///< [inout] is the univariate time series data (a one dimensional array).
                            size_t N,         ///< [in] is the number of observations in X. 
                            WORD retTYpe      ///< [in] is a number that determines the type of return value: 1 (or missing)=logit, 2=inverse logit.
                            );


  /*! 
  *   \brief Computes the complementary log-log transformation, including its inverse.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_LOGIT(), NDK_PROBIT(), NDK_CLOGLOG()
  */
  int   __stdcall NDK_BOXCOX( double *X,      ///< [inout] is the univariate time series data (a one dimensional array).
                              size_t N,       ///< [in] is the number of observations in X. 
                              double* lambda, ///< [in] is the input power parameter of the transformation, on a scale from 1 to 0. If omitted, a default value of 0 is assumed. 
                              double* alpha,  ///< [in] is the input shift parameter for X. If omitted, the default value is 0. 
                              int retTYpe,    ///< [in] is a number that determines the type of return value: 1 (or missing)=Box-Cox, 2=inverse Box-Cox, 3= LLF of Box-Cox.
                              double *retVal  ///< [out] is the calculated log-likelihood value of the transform (retType=3).
                              );

  /*! 
  *   \brief Detrends a time series using a regression of y against a polynomial time trend of order p.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_BOXCOX(), NDK_RMSEASONAL(), NDK_DIFF()
  */
  int   __stdcall NDK_DETREND(double *X,      ///< [inout] is the univariate time series data (a one dimensional array).
                              size_t N,       ///< [in] is the number of observations in X.
                              WORD polyOrder  ///< [in] is the order of the polynomial time trend:
                                              ///       0. subtracts mean (default)
                                              ///       1. constant plus trend model
                                              ///       2. constant plus trend and squared trend model
                              );

  /*! 
  *   \brief Returns an array of the deseasonalized time series, assuming a linear model.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_DETREND(), NDK_DIFF()
  */
  int   __stdcall NDK_RMSEASONAL( double *X,    ///< [inout] is the univariate time series data (a one dimensional array).
                                  size_t N,     ///< [in] is the number of observations in X.
                                  size_t period ///< [in] is the number of observations(i.e. points) in one season.
                                  );



  /*! 
  *   \brief Returns an array of a time series after substituting all missing values with the mean/median.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_RMNA(), NDK_INTERPOLATE()
  */
  int   __stdcall	NDK_INTERP_NAN( double* X,      ///< [inout] is the univariate time series data (a one dimensional array).
                                  size_t N,       ///< [in] is the number of observations in X. 
                                  WORD  nMethod,  ///< [in] is an identifier for the method used to generate values for any missing data:
                                                  ///       1. Mean (default)
                                                  ///       2. Median
                                                  ///       3. Constant
                                                  ///       4. Forward flat 
                                                  ///       5. Backward flat
                                                  ///       6. Linear
                                                  ///       7. Cubic spline
                                                  ///       8. Weighted moving average
                                                  ///       9. Exponential smoothing
                                                  ///       10. Brownian bridge
                                  double plug     ///< [in]  is the data argument related to the selected treatment method (if applicable). For instance, if the method is constant, then the value would be the actual value.
                                  );

  /*! 
  *   \brief Examine whether the given array has one or more missing values.
  *   \return status code of the operation
  *   \retval #NDK_TRUE One or more missing value are detected.
  *   \retval #NDK_FALSE No missing value is found.
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa NDK_RMNA(), NDK_INTERP_NAN()
  */
  int   __stdcall	NDK_HASNA(const double* X,    ///< [in] is the univariate time series data (a one dimensional array).
                            size_t nSize,       ///< [in] is the number of observations in X.
                            BOOL   intermediate ///< [in] is a switch to tune the search for missng values:
                                                ///       - TRUE = Only search for intermediate missing values.
                                                ///       - FALSE = Search for all missing values in X.
                            );


  /// \name Resampling
  /// resampling API functions calls
  /// @{

  /*!
  *   \brief Returns the resampled time series.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SESMTH(), NDK_EWMA(), NDK_DESMTH(), NDK_TESMTH, NDK_LESMTH()
  */
  int   __stdcall NDK_RESAMPLE(double* pData, size_t nSize, BOOL isStock, double relSampling, IMPUTATION_METHOD method, double* pOutData, size_t *newSize);

  int   __stdcall	NDK_INTERP_BROWN(double* pData , size_t nSize);
  ///@}


  /// \name Smoothing
  /// Smoothing API functions calls
  /// @{

  /*! 
  *   \brief Returns the weighted moving (rolling/running) average using the previous m data points.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SESMTH(), NDK_EWMA(), NDK_DESMTH(), NDK_TESMTH, NDK_LESMTH()
  */
  int   __stdcall NDK_WMA(double *pData,      ///< [in] is the univariate time series data (a one dimensional array).
                          size_t nSize,       ///< [in] is the number of elements in pData.
                          BOOL bAscending,    ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)). 
                          double* weights,    ///< [in] is the size of the equal-weighted window or an array of multiplying factors (i.e. weights) of the moving/rolling window. 
                          size_t nwSize,      ///< [in] is the number of elements in the weights array.
                          int nHorizon,       ///< [in] is the forecast time/horizon beyond the end of X. If missing, a default value of 0 (Latest or end of X) is assumed.
                          double* retVal      ///< [out] is the calculated value of the weighted moving average.
                          );


  /*! 
  *   \brief Returns the (Brown's) simple exponential (EMA) smoothing estimate of the value of X at time t+m (based on the raw data up to time t).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_WMA(), NDK_EWMA(), NDK_DESMTH(), NDK_TESMTH, NDK_LESMTH()
  */
  int   __stdcall NDK_SESMTH(double *pData,           ///< [in] is the univariate time series data (a one dimensional array).
                              size_t nSize,           ///< [in] is the number of elements in pData.
                              BOOL bAscending,        ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)).
                              double* alpha,          ///< [inout] is the smoothing factor (alpha should be between zero and one (exclusive)). If missing or omitted, a value of 0.333 is used.
                              int nHorizon,           ///< [in] is the forecast time horizon beyond the end of X. If missing, a default value of 0 (latest or end of X) is assumed.
                              BOOL bOptimize,         ///< [in] is a flag (True/False) for searching and using the optimal value of the smoothing factor. If missing or omitted, optimize is assumed false.
                              double* internals,      ///< [out,opt] is an array of the intermediate forecast calculation.
                              size_t  nInternalsSize, ///< [inout,opt] size of the output buffer, and number or values to return.
                              double* retVal          ///< [out] is the calculated value of this function.
                              );

  /*! 
  *   \brief Returns the (Holt-Winter's) double exponential smoothing estimate of the value of X at time T+m.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_WMA(), NDK_EWMA(), NDK_SESMTH(), NDK_TESMTH, NDK_LESMTH()
  */
  int   __stdcall NDK_DESMTH(double *pData,     ///< [in] is the univariate time series data (a one dimensional array).
                            size_t nSize,       ///< [in] is the number of elements in pData.
                            BOOL bAscending,    ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)).
                            double *alpha,      ///< [in] is the data smoothing factor (alpha should be between zero and one (exclusive)).
                            double *beta,       ///< [in] is the trend smoothing factor (beta should be between zero and one (exclusive)).
                            int xlHorizon,      ///< [in] is the forecast time horizon beyond the end of X. If missing, a default value of 0 (latest or end of X) is assumed.
                            BOOL bOptimize,     ///< [in] is a flag (True/False) for searching and using the optimal value of the smoothing factor. If missing or omitted, optimize is assumed false. 
                            double* internals,      ///< [out,opt] is an array of the intermediate forecast calculation.
                            size_t  nInternalsSize, ///< [in,opt] size of the output buffer, and number or values to return.
                            WORD  wInternalSeries,  ///< [in, opt] a switch to select the series to return in internals ( 0 = Smoothing forecast, 1=level, 2=trend)
                            double* retVal      ///< [out] is the calculated value of this function.
                            );

  /*! 
  *   \brief Returns the (Brown's) linear exponential smoothing estimate of the value of X at time T+m (based on the raw data up to time t).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_WMA(), NDK_EWMA(), NDK_SESMTH(), NDK_TESMTH, NDK_DESMTH()
  */
  int   __stdcall NDK_LESMTH( double *pData,          ///< [in] is the univariate time series data (a one dimensional array).
                              size_t nSize,           ///< [in] is the number of elements in pData.
                              BOOL bAscending,        ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)).
                              double *alpha,          ///< [in] is the smoothing factor (alpha should be between zero and one (exclusive)). If missing or omitted, a value of 0.333 is used.
                              int xlHorizon,          ///< [in] is the forecast time horizon beyond the end of X. If missing, a default value of 0 (latest or end of X) is assumed.
                              BOOL bOptimize,         ///< [in] is a flag (True/False) for searching and using the optimal value of the smoothing factor. If missing or omitted, optimize is assumed false. 
                              double* internals,      ///< [out,opt] is an array of the intermediate forecast calculation.
                              size_t  nInternalsSize, ///< [in,opt] size of the output buffer, and number or values to return.
                              WORD  wInternalSeries,  ///< [in, opt] a switch to select the series to return in internals ( 0 = Smoothing forecast, 1=level, 2=trend)
                              double* retVal          ///< [out] is the calculated value of this function.
                              );

  /*! 
  *   \brief Returns the (Winters's) triple exponential smoothing estimate of the value of X at time T+m.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_WMA(), NDK_EWMA(), NDK_SESMTH(), NDK_LESMTH, NDK_DESMTH()
  */
  int   __stdcall NDK_TESMTH(double *pData,           ///< [in] is the univariate time series data (a one dimensional array).
                              size_t nSize,           ///< [in] is the number of elements in pData.
                              BOOL bAscending,        ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)).
                              double *alpha,          ///< [in] is the data smoothing factor (alpha should be between zero and one (exclusive)).
                              double *beta,           ///< [in] is the trend smoothing factor (beta should be between zero and one (exclusive)).
                              double *gamma,          ///< [in] is the seasonal change smoothing factor (Gamma should be between zero and one (exclusive)).
                              int L,                  ///< [in] is the season length.
                              int nHorizon,           ///< [in] is the forecast time horizon beyond the end of X. If missing, a default value of 0 (latest or end of X) is assumed.
                              BOOL bOptimize,         ///< [in] is a flag (True/False) for searching and using optimal value of the smoothing factor. If missing or omitted, optimize is assumed false. 
                              double* internals,      ///< [out,opt] is an array of the intermediate forecast calculation.
                              size_t  nInternalsSize, ///< [in,opt] size of the output buffer, and number or values to return.
                              WORD  wInternalSeries,  ///< [in, opt] a switch to select the series to return in internals ( 0 = Smoothing forecast, 1=level, 2=trend)
                              double* retVal          ///< [out] is the calculated value of this function.
                              );


  /*!
  *   \brief Returns the (Winters's) triple exponential smoothing estimate of the value of X at time T+m.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_WMA(), NDK_EWMA(), NDK_SESMTH(), NDK_LESMTH, NDK_DESMTH()
  */
  int   __stdcall NDK_GESMTH(double *pData,          ///< [in] is the univariate time series data (a one dimensional array).
    size_t nSize,             ///< [in] is the number of elements in pData.
    BOOL bAscending,          ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)).
    double *alpha,            ///< [in] is the data smoothing factor (alpha should be between zero and one (exclusive)).
    double *beta,             ///< [in] is the trend smoothing factor (beta should be between zero and one (exclusive)).
    double *gamma,            ///< [in] is the seasonal change smoothing factor (Gamma should be between zero and one (exclusive)).
    double *phi,              ///< [in] is the damping coefficient for the trend.
    double *lambda,           ///< [in] is the coefficient value for the autocorrelation adjustment
    WORD  TrendType,          ///< [in] is the type of trend in the model (0=none, 1=additive, 2- damped additive, 3=multiplicative, 4=damped multiplicative)
    WORD  SeasonalityType,    ///< [in] is the type of seasonality in the modem (0=none, 1=additive, 2=multiplicative)
    int seasonLength,         ///< [in] is the season length.
    int nHorizon,             ///< [in] is the forecast time horizon beyond the end of X. If missing, a default value of 0 (latest or end of X) is assumed.
    BOOL bOptimize,           ///< [in] is a flag (True/False) for searching and using optimal value of the smoothing factor. If missing or omitted, optimize is assumed false. 
    BOOL bAutoCorrelationAdj, ///< [in] is a flag (True/False) for adding a correction term for the 1st ourder autocorrelation in the
    BOOL bLogTransform,       ///< [in] is a flag (True/False) for applying natural log transform to the input data prior to smoothing.
    double* internals,        ///< [out,opt] is an array of the intermediate forecast calculation.
    size_t  nInternalsSize,   ///< [in,opt] size of the output buffer, and number or values to return.
    WORD  wInternalSeries,    ///< [in, opt] a switch to select the series to return in internals ( 0 = one-step forecasting, 1=level, 2=trend, 3=seasonality)
    double* retVal            ///< [out] is the calculated value of this function.
  );

  /*! 
  *   \brief Returns values along a trend curve (e.g. linear, quadratic, exponential, etc.) at time T+m.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_WMA(), NDK_EWMA(), NDK_SESMTH(), NDK_LESMTH, NDK_DESMTH(), NDK_TESMTH
  */
  int   __stdcall NDK_TREND(double *pData,      ///< [in] is the univariate time series data (a one dimensional array).
                            size_t nSize,       ///< [in] is the number of elements in pData.
                            BOOL bAscending,    ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)).
                            WORD nTrendType,    ///< [in] is the model description flag for the trend function:
                                                ///   1. Linear
                                                ///   2. Polynomial
                                                ///   3. Exponential
                                                ///   4. Logarithmic
                                                ///   5. Power

                            WORD argPolyOrder,    ///< [in] is the polynomial order. This is only relevant for a polynomial trend type and is ignored for all others. If missing, POrder = 1. 
                            BOOL AllowIntercep,   ///< [in] is a switch to include or exclude an intercept in the regression.
                            double InterceptVal,  ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                            int nHorizon,         ///< [in] is the forecast time horizon beyond the end of X. If missing, a default value of 0 (latest or end of X) is assumed.
                            WORD retType,         ///< [in] is a switch to select the return output: 
                                                  ///       1. Forecast value
                                                  ///       2. Upper limit of the confidence interval
                                                  ///       3. Lower limit of the confidence interval
                                                  ///       4. R-Squared
                            double argAlpha,      ///< [in] is the statistical significance or confidence level (i.e. alpha). If missing or omitted, an alpha value of 5% is assumed.
                            double* retVal        ///< [out] is the calculated value of this function.
                            );
  ///@}




  /// \name Multiple Linear Regression (MLR)
  /// @{
  int __stdcall	NDK_SLR_PARAM (double* pXData, size_t nXSize, 
                                double* pYData, size_t nYSize,
                                double intercept,
                                double alpha,
                                WORD nRetType,
                                WORD ParamIndex,
                                double* retVal);
  int __stdcall	NDK_SLR_FORE (double* pXData, size_t nXSize, 
                                double* pYData, size_t nYSize,
                                double intercept,
                                double target,
                                double alpha,
                                WORD nRetType,
                                double* retVal);
  int __stdcall	NDK_SLR_FITTED (double* pXData, size_t nXSize, 
                                double* pYData, size_t nYSize,
                                double intercept,
                                WORD nRetType);
  int __stdcall	NDK_SLR_ANOVA ( double* pXData, size_t nXSize, 
                                double* pYData, size_t nYSize,
                                double intercept,
                                WORD nRetType,
                                double* retVal);
  int __stdcall	NDK_SLR_GOF ( double* pXData, size_t nXSize, 
                                double* pYData, size_t nYSize,
                                double intercept,
                                WORD nRetType,
                                double* retVal);
  
  /*! 
  *   \brief Calculates the OLS regression coefficients values.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_MLR_FORE(), NDK_MLR_FITTED(), NDK_MLR_ANOVA(), NDK_MLR_GOF, NDK_MLR_PRFTest, NDK_MLR_STEPWISE
  */
  int __stdcall	NDK_MLR_PARAM (double** X,          ///< [in] is the independent (explanatory) variables data matrix, such that each column represents one variable.
                               size_t nXSize,       ///< [in] is the number of observations (rows) in X.
                               size_t nXVars,       ///< [in] is the number of independent (explanatory) variables (columns) in X.
                                LPBYTE mask,        ///< [in] is the boolean array to choose the explanatory variables in the model. If missing, all variables in X are included.
                                size_t nMaskLen,    ///< [in] is the number of elements in the "mask."
                                double* Y,          ///< [in] is the response or the dependent variable data array (one dimensional array of cells).
                                size_t nYSize,      ///< [in] is the number of observations in Y.
                                double intercept,   ///< [in] is the constant or intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                                double alpha,       ///< [in] is the statistical significance of the test (i.e. alpha). If missing or omitted, an alpha value of 5% is assumed.
                                WORD nRetType,      ///< [in] is a switch to select the return output (1=value (default), 2=std. error, 3=t-stat, 4=P-value, 5=upper limit (CI), 6=lower limit (CI)):
                                                    ///       1. Value (mean)
                                                    ///       2. Std error
                                                    ///       3. Test score
                                                    ///       4. P-value
                                                    ///       5. Upper limit of the confidence interval
                                                    ///       6. Lower limit of the confidence interval
                                WORD nParamIndex,   ///< [in] is a switch to designate the target parameter (0=intercept (default), 1=first variable, 2=2nd variable, etc.).
                                double* retVal      ///< [out] is the computed statistics of the regression coefficient.
                                );

  /*! 
  *   \brief Calculates the forecast mean, error and confidence interval. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_MLR_PARAM(), NDK_MLR_FITTED(), NDK_MLR_ANOVA(), NDK_MLR_GOF, NDK_MLR_PRFTest, NDK_MLR_STEPWISE
  */
  int __stdcall	NDK_MLR_FORE (double** X,           ///< [in] is the independent (explanatory) variables data matrix, such that each column represents one variable.
                              size_t nXSize,        ///< [in] is the number of observations (rows) in X.
                              size_t nXVars,        ///< [in] is the number of independent (explanatory) variables (columns) in X.
                              LPBYTE mask,          ///< [in] is the boolean array to choose the explanatory variables in the model. If missing, all variables in X are included.
                              size_t nMaskLen,      ///< [in] is the number of elements in the "mask."
                              double* Y,            ///< [in] is the response or the dependent variable data array (one dimensional array of cells).
                              size_t nYSize,        ///< [in] is the number of observations in Y.
                              double intercept,     ///< [in] is the constant or intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                              double* target,       ///< [in] is the value of the explanatory variables (a one dimensional array).
                              double alpha,         ///< [in] is the statistical significance of the test (i.e. alpha). If missing or omitted, an alpha value of 5% is assumed.
                              WORD nRetType,        ///< [in] is a switch to select the return output (1=forecast (default), 2=error, 3=upper limit, 4=lower limit):
                                                    ///       1. Forecast (mean)
                                                    ///       2. Std error
                                                    ///       3. Upper limit of the confidence interval
                                                    ///       4. Lower limit of the conficence interval
                              double* retVal        ///< [out] is the computed forecast statistics.

                              );

  /*! 
  *   \brief Returns the fitted values of the conditional mean, residuals or leverage measures.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_MLR_FORE(), NDK_MLR_PARAM(), NDK_MLR_ANOVA(), NDK_MLR_GOF, NDK_MLR_PRFTest, NDK_MLR_STEPWISE
  */
  int __stdcall	NDK_MLR_FITTED (double** X,           ///< [in] is the independent (explanatory) variables data matrix, such that each column represents one variable.
                                size_t nXSize,        ///< [in] is the number of observations (rows) in X.
                                size_t nXVars,        ///< [in] is the number of independent (explanatory) variables (columns) in X.
                                LPBYTE mask,          ///< [in] is the boolean array to choose the explanatory variables in the model. If missing, all variables in X are included.
                                size_t nMaskLen,      ///< [in] is the number of elements in the "mask."
                                double* Y,            ///< [in] is the response or dependent variable data array (one dimensional array of cells).
                                size_t nYSize,        ///< [in] is the number of observations in Y.
                                double intercept,     ///< [in] is the constant or intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                                WORD nRetType         ///< [in] is a switch to select the return output (1=fitted values (default), 2=residuals, 3=standardized residuals, 4=leverage, 5=Cook's distance).
                                                      ///       1. Fitted/conditional mean
                                                      ///       2. Residuals
                                                      ///       3. Standardized residuals
                                                      ///       4. Leverage factor (H)
                                                      ///       5. Cook's distance (D)
                                );

  /*! 
  *   \brief Calculates the regression model analysis of the variance (ANOVA) values. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_MLR_FORE(), NDK_MLR_PARAM(), NDK_MLR_FITTED(), NDK_MLR_GOF, NDK_MLR_PRFTest, NDK_MLR_STEPWISE
  */
  int __stdcall	NDK_MLR_ANOVA (double** pXData,     ///< [in] is the independent (explanatory) variables data matrix, such that each column represents one variable.
                                size_t nXSize,      ///< [in] is the number of observations (rows) in X
                                size_t nXVars,      ///< [in] is the number of independent (explanatory) variables (columns) in X.
                                LPBYTE mask,        ///< [in] is the boolean array to choose the explanatory variables in the model. If missing, all variables in X are included.
                                size_t nMaskLen,    ///< [in] is the number of elements in the "mask."
                                double* Y,          ///< [in] is the response or dependent variable data array (one dimensional array of cells).
                                size_t nYSize,      ///< [in] is the number of observations in Y.
                                double intercept,   ///< [in] is the constant or intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                                WORD nRetType,      ///< [in] is a switch to select the output (1=SSR (default), 2=SSE, 3=SST, 4=MSR, 5=MSE, 6=F-stat, 7=P-value):
                                                    /// 1. SSR (sum of squares of the regression)
                                                    /// 2. SSE (sum of squares of the residuals)
                                                    /// 3. SST (sum of squares of the dependent variable)
                                                    /// 4. MSR (mean squares of the regression)
                                                    /// 5. MSE (mean squares error or residuals)
                                                    /// 6. F-stat (test score)
                                                    /// 7. Significance F (P-value of the test)
                                double* retVal      ///< [out] is the calculated statistics ANOVA output.
                                );

    /*! 
  *   \brief Calculates a measure for the goodness of fit (e.g. R^2). 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_MLR_FORE(), NDK_MLR_PARAM(), NDK_MLR_FITTED(), NDK_MLR_GOF, NDK_MLR_PRFTest, NDK_MLR_STEPWISE
  */
  int __stdcall	NDK_MLR_GOF ( double** X,         ///< [in] is the independent (explanatory) variables data matrix, such that each column represents one variable.
                              size_t nXSize,      ///< [in] is the number of observations (rows) in X.
                              size_t nXVars,      ///< [in] is the number of independent (explanatory) variables (columns) in X.
                              LPBYTE mask,        ///< [in] is the boolean array to choose the explanatory variables in the model. If missing, all variables in X are included.
                              size_t nMaskLen,    ///< [in] is the number of elements in the "mask."
                              double* Y,          ///< [in] is the response or dependent variable data array (one dimensional array of cells).
                              size_t nYSize,      ///< [in] is the number of observations in Y.
                              double intercept,   ///< [in] is the constant or intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                              WORD nRetType,      ///< [in] is a switch to select a fitness measure (1=R-square (default), 2=adjusted R-square, 3=RMSE, 4=LLF, 5=AIC, 6=BIC/SIC):
                                                  /// 1. R-square (coefficient of determination)
                                                  /// 2. Adjusted R-square
                                                  /// 3. Regression Error (RMSE)
                                                  /// 4. Log-likelihood (LLF)
                                                  /// 5. Akaike information criterion (AIC)
                                                  /// 6. Schwartz/Bayesian information criterion (SIC/BIC)
                              double* retVal      ///< [out] is the calculated goodness-of-fit statistics.
                              );
  /*! 
  *   \brief Calculates the p-value and related statistics of the partial f-test (used for testing the inclusion/exclusion variables).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_MLR_FORE(), NDK_MLR_PARAM(), NDK_MLR_ANOVA(), NDK_MLR_GOF, NDK_MLR_FITTED, NDK_MLR_STEPWISE
  */
  int __stdcall	NDK_MLR_PRFTest ( double** X,         ///< [in] is the independent (explanatory) variables data matrix, such that each column represents one variable.
                                  size_t nXSize,      ///< [in] is the number of observations (rows) in X.
                                  size_t nXVars,      ///< [in] is the number of independent (explanatory) variables (columns) in X.
                                  double* Y,          ///< [in] is the response or dependent variable data array (one dimensional array of cells).
                                  size_t nYSize,      ///< [in] is the number of observations in Y.
                                  double intercept,   ///< [in] is the constant or intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                                  LPBYTE mask1,       ///< [in] is the boolean array to choose the explanatory variables in model 1. If missing, all variables in X are included.
                                  size_t nMaskLen1,   ///< [in] is the number of elements in "mask1."
                                  LPBYTE mask2,       ///< [in] is the boolean array to choose the explanatory variables in model 2. If missing, all variables in X are included.
                                  size_t nMaskLen2,   ///< [in] is the number of elements in "mask2."
                                  double alpha,       ///< [in] is the statistical significance of the test (i.e. alpha). If missing or omitted, an alpha value of 5% is assumed.
                                  WORD nRetType,      ///< [in] is a switch to select the return output (1 = P-Value (default), 2 = Test Stats, 3 = Critical Value.) 
                                  double* retVal      ///< [out] is the calculated test statistics/
                                );

  /*! 
  *   \brief Returns a list of the selected variables after performing the stepwise regression.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_MLR_FORE(), NDK_MLR_PARAM(), NDK_MLR_ANOVA(), NDK_MLR_GOF, NDK_MLR_PRFTest, NDK_MLR_STEPWISE
  */
  int __stdcall	NDK_MLR_STEPWISE (double** X,         ///< [in] is the independent (explanatory) variables data matrix, such that each column represents one variable.
                                  size_t nXSize,      ///< [in] is the number of observations (rows) in X.
                                  size_t nXVars,      ///< [in] is the number of independent (explanatory) variables (columns) in X.
                                  LPBYTE mask,        ///< [inout] is the boolean array to choose the explanatory variables in the model. If missing, all variables in X are included.
                                  size_t nMaskLen,    ///< [in] is the number of elements in the "mask."
                                  double* Y,          ///< [in] is the response or dependent variable data array (one dimensional array of cells).
                                  size_t nYSize,      ///< [in] is the number of observations in Y.
                                  double intercept,   ///< [in] is the constant or intercept value to fix (e.g. zero). If missing (i.e. NaN), an intercept will not be fixed and is computed normally.
                                  double alpha,       ///< [in] is the statistical significance of the test (i.e. alpha). If missing or omitted, an alpha value of 5% is assumed.
                                  WORD nMode          ///< [in] is a switch to select the variable's inclusion/exclusion approach (1=forward selection (default), 2=backward elimination , 3=bi-directional elimination):
                                                      /// 1. Forward selection
                                                      /// 2. Bacward elemination
                                                      /// 3. Bi-directional elemination
                                  );
  ///@}


  /// \name Principal Component Analysis (PCA)  
  /// @{
  /*! 
  *   \brief Returns an array of cells for the i-th principal component (or residuals).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCA_COMP (double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                              size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                              size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                              LPBYTE mask,        ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                              size_t nMaskLen,    ///< [in] is the number of elements in 
                              WORD standardize,   ///< [in]  is a flag or switch to standardize the input variables prior to the analysis:
                                                  ///     1. standardize ((subtract mean and divide by standard deviation)
                                                  ///     2. subtract mean. 
                              WORD nCompIndex,    ///< [in] is the component number to return.
                              WORD retType,       ///< [in]  is a switch to select the return output 
                                                  ///   1. proportion of variance, 
                                                  ///   2. variance, 
                                                  ///   3. eigenvalue, 
                                                  ///   4. loadings, 
                                                  ///   5. Principal Component (PC) data. 
                              double* retVal,     ///< [out] is the calculated value or data
                              size_t nOutSize     ///< [in] is the size of retVal
                              );

  /*! 
  *   \brief Returns an array of cells for the fitted values of the i-th input variable.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCA_VAR ( double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                              size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                              size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                              LPBYTE varMask,     ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                              size_t nMaskLen,    ///< [in] is the number of elements in mask
                              WORD standardize,   ///< [in] is a flag or switch to standardize the input variables prior to the analysis:
                                                  ///     1. standardize ((subtract mean and divide by standard deviation)
                                                  ///     2. subtract mean. 
                              WORD nVarIndex,     ///< [in] is  the input variable number
                              WORD wMacPC,        ///< [in] is the number of principal components (PC) to include
                              WORD retType,       ///< [in]  is a switch to select the return output:
                                                  ///     1. final communality 
                                                  ///     2. loading/weights
                                                  ///     3. fitted values 
                                                  ///     4. residuals
                              double* retVal,     ///< [out] is the calculated value or data
                              size_t nOutSize     ///< [in] is the size of retVal
                              );
  /*! 
  *   \brief Calculates the regression coefficients values for a given input variable.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCR_PARAM ( double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                                size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                                LPBYTE mask,        ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                                size_t nMaskLen,    ///< [in] is the number of elements in mask
                                double* Y,          ///< [in] is the response or the dependent variable data array (one dimensional array)
                                size_t nYSize,      ///< [in] is the number of elements in Y
                                double intercept,   ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally
                                double alpha,       ///< [in] is the statistical significance of the test (i.e. alpha)
                                WORD nRetType,      ///< [in] is a switch to select the return output:
                                                    ///   1. Value (default), 
                                                    ///   2. Std. Error 
                                                    ///   3. t-stat 
                                                    ///   4. P-Value
                                                    ///   5. Upper Limit (CI)
                                                    ///   6. Lower Limit (CI)) 
                                WORD nParamIndex,   ///< [in] is a switch to designate the target parameter (0 = intercept (default), 1 = first variable, 2 = 2nd variable, etc.). 
                                double* retVal      ///< [out] is the calculated parameter value or statistics.
                                );

  /*! 
  *   \brief Calculates the model's estimated values, std. errors and related statistics.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCR_FORE (double** X,           ///< [in] is the independent variables data matrix, such that each column represents one variable
                              size_t nXSize,        ///< [in] is the number of observations (i.e. rows) in X
                              size_t nXVars,        ///< [in] is the number of variables (i.e. columns) in X
                              LPBYTE mask,          ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                              size_t nMaskLen,      ///< [in] is the number of elements in mask
                              double* Y,            ///< [in] is the response or the dependent variable data array (one dimensional array)
                              size_t nYSize,        ///< [in] is the number of elements in Y 
                              double intercept,     ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally
                              double* target,       ///< [in] is the value of the explanatory variables (a one dimensional array) 
                              double alpha,         ///< [in] is the statistical significance of the test (i.e. alpha)
                              WORD nRetType,        ///< [in] is a switch to select the return output (1 = forecast (default), 2 = error, 3 = upper limit, 4 = lower limit). 
                              double* retVal        ///< [out] is the calculated forecast value or statistics.  
                              );

  /*! 
  *   \brief Returns an array of cells for the i-th principal component (or residuals).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCR_FITTED (double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                                size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                                LPBYTE mask,        ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                                size_t nMaskLen,    ///< [in] is the number of elements in mask
                                double* Y,          ///< [inout] is the response or the dependent variable data array (one dimensional array)
                                size_t nYSize,      ///< [in] is the number of elements in Y 
                                double intercept,   ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally
                                WORD nRetType       ///< [in]  is a switch to select the return output 
                                                    ///   1. fitted values (default), 
                                                    ///   2. residuals, 
                                                    ///   3. standardized residuals, 
                                                    ///   4. leverage (H), 
                                                    ///   5. Cook's distance. 
                                );

  /*! 
  *   \brief Returns an array of cells for the i-th principal component (or residuals).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCR_ANOVA ( double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                                size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                                LPBYTE mask,        ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                                size_t nMaskLen,    ///< [in] is the number of elements in mask
                                double* Y,          ///< [in] is the response or the dependent variable data array (one dimensional array)
                                size_t nYSize,      ///< [in] is the number of elements in Y 
                                double intercept,   ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally
                                WORD nRetType,      ///< [in] is a switch to select the return output:
                                                    /// 1. SSR (sum of squares of the regression)
                                                    /// 2. SSE (sum of squares of the residuals)
                                                    /// 3. SST (sum of squares of the dependent variable)
                                                    /// 4. MSR (mean squares of the regression)
                                                    /// 5. MSE (mean squares error or residuals)
                                                    /// 6. F-stat (test score)
                                                    /// 7. Significance F (P-value of the test)
                                double* retVal      ///< [out] is the calculated statistics ANOVA output.
                                );

  /*! 
  *   \brief Returns an array of cells for the i-th principal component (or residuals).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCR_GOF ( double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                              size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                              size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                              LPBYTE mask,        ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                              size_t nMaskLen,    ///< [in] is the number of elements in mask
                              double* Y,          ///< [in] is the response or the dependent variable data array (one dimensional array)
                              size_t nYSize,      ///< [in] is the number of elements in Y 
                              double intercept,   ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally
                              WORD nRetType,      ///< [in]  is a switch to select a fitness measure (1 = R-Square (default), 2 = Adjusted R Square, 3 = RMSE, 4 = LLF, 5 = AIC, 6 = BIC/SIC ). 
                                                  /// 1. R-square (coefficient of determination)
                                                  /// 2. Adjusted R-square
                                                  /// 3. Regression Error (RMSE)
                                                  /// 4. Log-likelihood (LLF)
                                                  /// 5. Akaike information criterion (AIC)
                                                  /// 6. Schwartz/Bayesian information criterion (SIC/BIC)
                              double* retVal      ///< [out] is the calculated goodness of fit measure
                              );
  /*! 
  *   \brief Returns an array of cells for the i-th principal component (or residuals).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCR_PRFTest ( double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                                  size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                                  size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                                  double* Y,          ///< [in] is the response or the dependent variable data array (one dimensional array)
                                  size_t nYSize,      ///< [in] is the number of elements in Y 
                                  double intercept,   ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally
                                  LPBYTE mask1,       ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                                  size_t nMaskLen1,   ///< [in] is the number of elements in mask1
                                  LPBYTE mask2,       ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                                  size_t nMaskLen2,   ///< [in] is the number of elements in mask2
                                  double alpha,       ///< [in] is the statistical significance of the test (i.e. alpha)
                                  WORD nRetType,      ///< [in] is a switch to select the return output (1 = P-Value (default), 2 = Test Stats, 3 = Critical Value.) 
                                  double* retVal      ///< [out] is the calculated test statistics/
                                  );

  /*! 
  *   \brief Returns an array of cells for the i-th principal component (or residuals).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_PCA_VAR(), NDK_PCR_PARAM(), NDK_PCR_FORE(), NDK_PCR_FITTED(), NDK_PCR_ANOVA(), NDK_PCR_GOF(), NDK_PCR_PRFTest(), NDK_PCR_STEPWISE()
  */
  int __stdcall	NDK_PCR_STEPWISE (double** X,         ///< [in] is the independent variables data matrix, such that each column represents one variable
                                  size_t nXSize,      ///< [in] is the number of observations (i.e. rows) in X
                                  size_t nXVars,      ///< [in] is the number of variables (i.e. columns) in X
                                  LPBYTE mask,        ///< [in] is the boolean array to select a subset of the input variables in X. If missing (i.e. NULL), all variables in X are included. 
                                  size_t nMaskLen,    ///< [in] is the number of elements in mask
                                  double* Y,          ///< [in] is the response or the dependent variable data array (one dimensional array)
                                  size_t nYSize,      ///< [in] is the number of elements in Y 
                                  double intercept,   ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally
                                  double alpha,       ///< [in] is the statistical significance of the test (i.e. alpha)
                                  WORD nMode          ///< [in] is a switch to select the variable's inclusion/exclusion approach (1=forward selection (default), 2=backward elimination , 3=bi-directional elimination):
                                                      /// 1. Forward selection
                                                      /// 2. Bacward elemination
                                                      /// 3. Bi-directional elemination
                                  );
  ///@}





  /// \name GLM
  /// Gneralized Linear Model Functions
  /// @{
  

  /*! 
  * \brief Examines the model's parameters for constraints (e.g. positive variance, etc.).
  * \details
  * \htmlonly
    <h4>Notes</h4>
    <ol>
      <li>The number of betas must be equal to the number of explanatory variables (i.e. X) plus one (intercept). </li>
      <li>
        For GLM with Poisson distribution:
        <ul>
          <li>The values of the response variables must be non-negative integers.</li>
          <li>The value of the dispersion factor (Phi) value must be either missing or equal to one.</li>
        </ul>
      </li>
      <li>
        For GLM with Binomial distribution,
        <ul>
          <li>The values of the response variable must be non-negative fractions between zero and one, inclusive.</li>
          <li>The value of the dispersion factor (Phi) must be a positive fraction (greater than zero, and less than one).</li>
        </ul>
      </li>
      <li>For GLM with Guassian distribution, the dispersion factor (Phi) value must be positive.</li>
    </ol>
  * \endhtmlonly
  *   \return status code of the operation
  *   \retval #NDK_TRUE GLM model is valid
  *   \retval #NDK_FALSE GLM model in invalid. For other return values, see \ref SFMacros.h
  *   \sa NDK_GLM_FITTED(), NDK_GLM_RESID(), NDK_GLM_PARAM(), NDK_GLM_FORE
  */
  int __stdcall NDK_GLM_VALIDATE(double* betas, ///< [in] are the coefficients of the GLM model (a one dimensional array)
                                 size_t nBetas, ///< [in] is the number of the coefficients in betas. Note that nBetas must be equal to nVars+1
                                 double  phi,   ///< [in]  is the GLM dispersion paramter. Phi is only meaningful for Binomial (1/batch or trial size) and for Guassian (variance). 
                                                ///     - Binomial : phi = Reciprocal of the batch/trial size.
                                                ///     - Gaussion : phi = variance.
                                                ///     - Poisson :  phi = 1.0
                                 WORD  Lvk      ///< [in]  is the link function that describes how the mean depends on the linear predictor (see #GLM_LINK_FUNC). 
                                                ///       1. Identity (default)
                                                ///       2. Log
                                                ///       3. Logit
                                                ///       4. Probit
                                                ///       5. Complementary log-log
                                 );



  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit function of the GLM model.   
  * 
    \htmlonly
    <h4>Notes</h4>
    <ol>
      <li>Missng values (i.e. #N/A!) are not allowed in the either response(Y) or the explanatory input arrays.</li>
      <li>The number of rows in response variable (Y) must be equal to number of rows of the explanatory variables (X).</li>
      <li>The number of betas must equal to the number of explanatory variables (i.e. X) plus one (intercept). </li>
      <li>
        For GLM with Poisson distribution,
        <ul>
          <li>The values of response variable must be non-negative integers.</li>
          <li>The value of the dispersion factor (Phi) value must be either missing or equal to one.</li>
        </ul>
      </li>
      <li>
        For GLM with Binomial distribution,
        <ul>
          <li>The values of the response variable must be non-negative fractions between zero and one, inclusive.</li>
          <li>The value of the dispersion factor (Phi) must be a positive fraction (greater than zero, and less than one).</li>
        </ul>
      </li>
      <li>For GLM with Guassian distribution, the dispersion factor (Phi) value must be positive.</li>
    </ol>
    \endhtmlonly
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GLM_FITTED(), NDK_GLM_RESID(), NDK_GLM_PARAM(), NDK_GLM_FORE
  */
  int __stdcall NDK_GLM_GOF(    double* Y,      ///< [in] is the response or the dependent variable data array (one dimensional array)
                                size_t nSize,   ///< [in] is the number of observations 
                                double** X,     ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nVars,   ///< [in] is the number of independent variables (or columns in X)
                                double* betas,  ///< [in] are the coefficients of the GLM model (a one dimensional array)
                                size_t nBetas,  ///< [in] is the number of the coefficients in betas. Note that nBetas must be equal to nVars+1
                                double  phi,    ///< [in]  is the GLM dispersion paramter. Phi is only meaningful for Binomial (1/batch or trial size) and for Guassian (variance). 
                                                ///     - Binomial : phi = Reciprocal of the batch/trial size.
                                                ///     - Gaussion : phi = variance.
                                                ///     - Poisson :  phi = 1.0
                                WORD  Lvk,      ///< [in]  is the link function that describes how the mean depends on the linear predictor (see #GLM_LINK_FUNC). 
                                                ///       1. Identity (default)
                                                ///       2. Log
                                                ///       3. Logit
                                                ///       4. Probit
                                                ///       5. Complementary log-log
                                WORD retType,   ///< [in]  is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC)
                                double* retVal  ///< [out] is the calculated goodness of fit measure.
                                );

  /*! 
  * \brief Returns the standardized residuals/errors of a given GLM.   
  * 
    \htmlonly
    <h4>Notes</h4>
    <ol>
      <li>Missng values (i.e. #N/A!) are not allowed in the either response(Y) or the explanatory input arrays.</li>
      <li>The number of rows in response variable (Y) must be equal to number of rows of the explanatory variables (X).</li>
      <li>The number of betas must equal to the number of explanatory variables (i.e. X) plus one (intercept). </li>
      <li>
        For GLM with Poisson distribution,
        <ul>
          <li>The values of response variable must be non-negative integers.</li>
          <li>The value of the dispersion factor (Phi) value must be either missing or equal to one.</li>
        </ul>
      </li>
      <li>
        For GLM with Binomial distribution,
        <ul>
          <li>The values of the response variable must be non-negative fractions between zero and one, inclusive.</li>
          <li>The value of the dispersion factor (Phi) must be a positive fraction (greater than zero, and less than one).</li>
        </ul>
      </li>
      <li>For GLM with Guassian distribution, the dispersion factor (Phi) value must be positive.</li>
    </ol>
    \endhtmlonly
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GLM_FITTED(), NDK_GLM_RESID(), NDK_GLM_PARAM(), NDK_GLM_FORE
  */
  int __stdcall NDK_GLM_RESID(     double* Y,   ///< [in] is the response or the dependent variable data array (one dimensional array)
                                size_t nSize,   ///< [in] is the number of observations 
                                double** X,     ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nVars,   ///< [in] is the number of independent variables (or columns in X)
                                double* betas,  ///< [in] are the coefficients of the GLM model (a one dimensional array)
                                size_t nBetas,  ///< [in] is the number of the coefficients in betas. Note that nBetas must be equal to nVars+1
                                double  phi,    ///< [in]  is the GLM dispersion paramter. Phi is only meaningful for Binomial (1/batch or trial size) and for Guassian (variance). 
                                                ///     - Binomial : phi = Reciprocal of the batch/trial size.
                                                ///     - Gaussion : phi = variance.
                                                ///     - Poisson :  phi = 1.0
                                WORD  Lvk,      ///< [in]  is the link function that describes how the mean depends on the linear predictor (see #GLM_LINK_FUNC). 
                                                ///       1. Identity (default)
                                                ///       2. Log
                                                ///       3. Logit
                                                ///       4. Probit
                                                ///       5. Complementary log-log
                                WORD retType    ///< [in]  is a switch to select a residuals-type:raw or standardized. see \ref #RESID_RETVAL_FUNC
                                );

  /*! 
  * \brief Returns an array of cells for the initial (non-optimal), optimal or standard errors of the model's parameters   
  * 
    \htmlonly
    <h4>Notes</h4>
    <ol>
      <li>Missng values (i.e. #N/A!) are not allowed in the either response(Y) or the explanatory input arrays.</li>
      <li>The number of rows in response variable (Y) must be equal to number of rows of the explanatory variables (X).</li>
      <li>The number of betas must equal to the number of explanatory variables (i.e. X) plus one (intercept). </li>
      <li>
        For GLM with Poisson distribution,
        <ul>
          <li>The values of response variable must be non-negative integers.</li>
          <li>The value of the dispersion factor (Phi) value must be either missing or equal to one.</li>
        </ul>
      </li>
      <li>
        For GLM with Binomial distribution,
        <ul>
          <li>The values of the response variable must be non-negative fractions between zero and one, inclusive.</li>
          <li>The value of the dispersion factor (Phi) must be a positive fraction (greater than zero, and less than one).</li>
        </ul>
      </li>
      <li>For GLM with Guassian distribution, the dispersion factor (Phi) value must be positive.</li>
    </ol>
    \endhtmlonly
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GLM_FITTED(), NDK_GLM_RESID(), NDK_GLM_GOF(), NDK_GLM_FORE
  */
  int __stdcall NDK_GLM_PARAM(  double* Y,       ///< [in] is the response or the dependent variable data array (one dimensional array)
                                size_t nSize,   ///< [in] is the number of observations 
                                double** X,     ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nVars,   ///< [in] is the number of independent variables (or columns in X)
                                double* betas,  ///< [inout] are the coefficients of the GLM model (a one dimensional array)
                                size_t nBetas,  ///< [in] is the number of the coefficients in betas. Note that nBetas must be equal to nVars+1
                                double* phi,    ///< [inout]  is the GLM dispersion paramter. Phi is only meaningful for Binomial (1/batch or trial size) and for Guassian (variance). 
                                                ///     - Binomial : phi = Reciprocal of the batch/trial size.
                                                ///     - Gaussion : phi = variance.
                                                ///     - Poisson :  phi = 1.0
                                WORD  Lvk,      ///< [in]  is the link function that describes how the mean depends on the linear predictor (see #GLM_LINK_FUNC). 
                                                ///       1. Identity (default)
                                                ///       2. Log
                                                ///       3. Logit
                                                ///       4. Probit
                                                ///       5. Complementary log-log
                                WORD retType,   ///< [in]  is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC)
                                size_t maxIter  ///< [in]   is the maximum number of iterations used to calibrate the model. If missing, the default maximum of 100 is assumed. 
                                );
    

  /*! 
  * \brief calculates the expected response (i.e. mean) value; given the GLM model and the values of the explanatory variables.  
  *
  * \htmlonly
    <h4>Notes</h4>
    <ol>
      <li>Missng values (i.e. #N/A!) are not allowed in the either response(Y) or the explanatory input arrays.</li>
      <li>The number of rows in response variable (Y) must be equal to number of rows of the explanatory variables (X).</li>
      <li>The number of betas must equal to the number of explanatory variables (i.e. X) plus one (intercept).</li>
      <li>For GLM with Poisson distribution,
        <ul>
          <li>The values of response variable must be non-negative integers.</li>
          <li>The value of the dispersion factor (Phi) value must be either missing or equal to one.</li>
        </ul>
      </li>
      <li>For GLM with Binomial distribution,
        <ul>
          <li>The values of the response variable must be non-negative fractions between zero and one, inclusive.</li>
          <li>The value of the dispersion factor (Phi) must be a positive fraction (greater than zero, and less than one).</li>
        </ul>
      </li>
      <li>For GLM with Guassian distribution, the dispersion factor (Phi) value must be positive.</li>
    </ol>
    \endhtmlonly
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GLM_FITTED(), NDK_GLM_RESID(), NDK_GLM_GOF(), NDK_GLM_FORE
  */
  int __stdcall NDK_GLM_FORE(   double* X,      ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nVars,   ///< [in] is the number of independent variables (or columns in X)
                                double* betas,  ///< [inout] are the coefficients of the GLM model (a one dimensional array)
                                size_t nBetas,  ///< [in] is the number of the coefficients in betas. Note that nBetas must be equal to nVars+1
                                double phi,    ///< [inout]  is the GLM dispersion paramter. Phi is only meaningful for Binomial (1/batch or trial size) and for Guassian (variance). 
                                                ///     - Binomial : phi = Reciprocal of the batch/trial size.
                                                ///     - Gaussion : phi = variance.
                                                ///     - Poisson :  phi = 1.0
                                WORD  Lvk,      ///< [in]  is the link function that describes how the mean depends on the linear predictor (see #GLM_LINK_FUNC). 
                                                ///       1. Identity (default)
                                                ///       2. Log
                                                ///       3. Logit
                                                ///       4. Probit
                                                ///       5. Complementary log-log
                                WORD retType,   ///< [in]  is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref # FORECAST_RETVAL_FUNC)
                                double  alpha,  ///< [in]  is the statistical significance level. If missing, a default of 5% is assumed. 
                                double* retval  ///< [out] is the calculated forecast value
                                );


  int __stdcall NDK_GLM_FITTED( double* Y,      ///< [inout] is the response or the dependent variable data array (one dimensional array)
                                size_t nSize,   ///< [in] is the number of observations 
                                double** X,     ///< [in] is the independent variables data matrix, such that each column represents one variable
                                size_t nVars,   ///< [in] is the number of independent variables (or columns in X)
                                double* betas,  ///< [in] are the coefficients of the GLM model (a one dimensional array)
                                size_t nBetas,  ///< [in] is the number of the coefficients in betas. Note that nBetas must be equal to nVars+1
                                double  phi,    ///< [in]  is the GLM dispersion paramter. Phi is only meaningful for Binomial (1/batch or trial size) and for Guassian (variance). 
                                                ///     - Binomial : phi = Reciprocal of the batch/trial size.
                                                ///     - Gaussion : phi = variance.
                                                ///     - Poisson :  phi = 1.0
                                WORD  Lvk,      ///< [in]  is the link function that describes how the mean depends on the linear predictor (see #GLM_LINK_FUNC). 
                                                ///       1. Identity (default)
                                                ///       2. Log
                                                ///       3. Logit
                                                ///       4. Probit
                                                ///       5. Complementary log-log
                                WORD retType    ///< [in]  is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC)
                                );
  ///@}

  /// \name ARMA
  /// The ARMA model is a tool for understanding and forecasting future values in a given time series. The model consists of two parts: an autoregressive component, i.e. AR(p), and a moving average component, i.e. MA(q), and it is referred to as ARMA(p,q). 
  /// @{
  
  /*! 
  * \brief Computes the log-likelihood (LLF), Akaike Information Criterion (AIC) or other goodness of fit functions of the ARMA model.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARMA_PARAM(), NDK_ARMA_VALIDATE(), NDK_ARMA_FORE(), NDK_ARMA_RESID()
  */
  int __stdcall NDK_ARMA_GOF( double* pData,    ///< [in] is the univariate time series data (a one dimensional array).
                              size_t nSize,     ///< [in] is the number of observations in X.
                              double mean,      ///< [in] is the ARMA model mean (i.e. mu).
                              double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                              double* phis,     ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                              size_t p,         ///< [in] is the number of elements in phis (order of AR component).
                              double* thetas,   ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                              size_t q,         ///< [in] is the number of elements in thetas (order of MA component).
                              WORD retType,     ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC).
                              double* retVal    ///< [out] is the calculated goodness of fit value.
                              );

  /*! 
  * \brief Returns the standardized residuals of a given ARMA model 
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \deprecated this function is being replaced by NDK_ARMA_FITTED()
  *   \sa NDK_ARMA_PARAM(), NDK_ARMA_VALIDATE(), NDK_ARMA_FORE(), NDK_ARMA_GOF()
  */
  int __stdcall NDK_ARMA_RESID( double* pData,    ///< [inout] is the univariate time series data (a one dimensional array).
                                size_t nSize,     ///< [in] is the number of observations in X. 
                                double mean,      ///< [in] is the ARMA model mean (i.e. mu). 
                                double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations. 
                                double* phis,     ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag). 
                                size_t p,         ///< [in] is the number of elements in phis (order of AR component)
                                double* thetas,   ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag). 
                                size_t q,         ///< [in] is the number of elements in thetas (order of MA component)
                                WORD retType      ///< [in] is a switch to select a residuals-type:raw or standardized. see \ref #RESID_RETVAL_FUNC
                                );


  /*! 
  * \brief Returns the initial (non-optimal), optimal or standard errors of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARMA_GOF(), NDK_ARMA_VALIDATE(), NDK_ARMA_FORE(), NDK_ARMA_RESID()
  */
  int __stdcall NDK_ARMA_PARAM( double* pData,    ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,     ///< [in] is the number of observations in X.
                                double* mean,     ///< [inout] is the ARMA model mean (i.e. mu).
                                double* sigma,    ///< [inout] is the standard deviation of the model's residuals/innovations.
                                double* phis,     ///< [inout] are the parameters of the AR(p) component model (starting with the lowest lag).
                                size_t p,         ///< [in] is the number of elements in phis (order of AR component).
                                double* thetas,   ///< [inout] are the parameters of the MA(q) component model (starting with the lowest lag).
                                size_t q,         ///< [in] is the number of elements in thetas (order of MA component).
                                MODEL_RETVAL_FUNC retType,     ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC).
                                size_t maxIter    ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed. 
                                );


  /*! 
  * \brief Calculates the out-of-sample forecast statistics.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARMA_PARAM(), NDK_ARMA_VALIDATE(), NDK_ARMA_GOF(), NDK_ARMA_RESID()
  */
  int __stdcall NDK_ARMA_FORE(  double* pData,    ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,     ///< [in] is the number of observations in X.
                                double mean,      ///< [in] is the ARMA model mean (i.e. mu).
                                double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                double* phis,     ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                                size_t p,         ///< [in] is the number of elements in phis (order of AR component).
                                double* thetas,   ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                                size_t q,         ///< [in] is the number of elements in thetas (order of MA component).
                                size_t nStep,     ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series).
                                FORECAST_RETVAL_FUNC retType,     ///< [in] is a switch to select the type of value returned (FORECAST_MEAN, FORECAST_STDEV , ..)
                                                                  ///       (see \ref #FORECAST_RETVAL_FUNC).
                                double  alpha,    ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                                double* retVal    ///< [out] is the calculated forecast value.
                                );


  /*! 
  * \brief Returns the fitted values (i.e. mean, volatility and residuals).
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARMA_PARAM(), NDK_ARMA_VALIDATE(), NDK_ARMA_GOF(), NDK_ARMA_RESID(), NDK_ARMA_GOF()
  */
  int __stdcall NDK_ARMA_FITTED( double* pData,   ///< [inout] is the univariate time series data (a one dimensional array).
                                size_t nSize,     ///< [in] is the number of observations in X.
                                double mean,      ///< [in] is the ARMA model mean (i.e. mu).
                                double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                double* phis,     ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                                size_t p,         ///< [in] is the number of elements in phis (order of AR component).
                                double* thetas,   ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                                size_t q,         ///< [in] is the number of elements in thetas (order of MA component).
                                FIT_RETVAL_FUNC retType      ///< [in]  is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC).
                                );

  /*! 
  * \brief Examines the model's parameters for stability constraints (e.g. stationarity, invertibility, causality, etc.). 
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_TRUE model is stable
  *   \retval #NDK_FALSE model is instable
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARMA_PARAM(), NDK_ARMA_VALIDATE(), NDK_ARMA_GOF(), NDK_ARMA_RESID(), NDK_ARMA_GOF()
  */
  int __stdcall NDK_ARMA_VALIDATE(double mean,      ///< [in] is the ARMA model mean (i.e. mu).
                                  double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                  double* phis,     ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                                  size_t p,         ///< [in] is the number of elements in phis (order of AR component).
                                  double* thetas,   ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                                  size_t q          ///< [in] is the number of elements in thetas (order of MA component).
                                  );

  /*! 
  * \brief Returns the simulated values.
  * 
  * \note 1. ARMA_SIM returns an array of one simulation path starting from the end of the input data.
  * \note 2. The input data argument (i.e. latest observations) is optional. If omitted, an array of zeroes is assumed.
  * \note 3. The time series is homogeneous or equally spaced.
  * \note 4. The time series may include missing values (e.g. NaN) at either end.
  * \note 5. The long-run mean can take any value or be omitted, in which case a zero value is assumed.
  * \note 6. The residuals/innovations standard deviation (sigma) must be greater than zero.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARMA_PARAM(), NDK_ARMA_VALIDATE(), NDK_ARMA_GOF(), NDK_ARMA_RESID(), NDK_ARMA_GOF()
  */
  int __stdcall NDK_ARMA_SIM(double mean,         ///< [in] is the ARMA model long-run mean (i.e. mu).
                            double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                            double* phis,         ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                            size_t p,             ///< [in] is the number of elements in phis (order of AR component).
                            double* thetas,       ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                            size_t q,             ///< [in] is the number of elements in thetas (order of MA component).
                            double* pData,        ///< [in] are the values of the latest (most recent) observations.
                            size_t nSize,         ///< [in] is the number elements in pData.
                            UINT nSeed,           ///< [in] is an unsigned integer to initialize the psuedorandom number generator.
                            double* retArray,     ///< [out] is the output array to hold nSteps future simulations.
                            size_t  nSteps        ///< [in] is the number of future steps to simulate for.
                            );

  ///@}

  /// \name ARIMA
  /// ARIMA model functions
  /// @{

  /*! 
  * \brief   Examines the model's parameters for stability constraints (e.g. stationarity, invertibility, causality, etc.).
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The integration order argument (d) must be a positive integer.
  * \note 3. The time series may include missing values (e.g. NaN) at either end.
  * \note 4. The long-run mean can take any value or may be omitted, in which case a zero value is assumed.
  * \note 5. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARIMA_GOF(), NDK_ARIMA_PARAM(), NDK_ARIMA_FORE(), NDK_ARIMA_FITTED(), NDK_ARIMA_SIM()
  */

  int __stdcall NDK_ARIMA_VALIDATE( double mean,      ///< [in] is the ARMA model mean (i.e. mu).
                                    double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                    WORD nIntegral,   ///< [in] is the integration order.
                                    double* phis,     ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                                    size_t p,         ///< [in] is the number of elements in phis (order of AR component).
                                    double* thetas,   ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                                    size_t q         ///< [in] is the number of elements in thetas (order of MA component).
                                    );
  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit functions of the ARIMA model.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARIMA_VALIDATE(), NDK_ARIMA_PARAM(), NDK_ARIMA_FORE(), NDK_ARIMA_FITTED(), NDK_ARIMA_SIM()
  */
  int __stdcall NDK_ARIMA_GOF( double* X,             ///< [in] is the univariate time series data (a one dimensional array).
                               size_t nSize,          ///< [in] is the number of observations in X.
                               double mean,           ///< [in] is the ARMA model mean (i.e. mu).
                               double sigma,          ///< [in] is the standard deviation of the model's residuals/innovations.
                               WORD nIntegral,        ///< [in] is the model's integration order.
                               double* phis,          ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                               size_t p,              ///< [in] is the number of elements in phis (order of AR component).
                               double* thetas,        ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                               size_t q,              ///< [in] is the number of elements in thetas (order of MA component).
                               GOODNESS_OF_FIT_FUNC retType,          ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC).
                               double* retVal         ///< [out] is the calculated GOF return value.
                               );
  /*! 
  * \brief  Returns the quick guess, optimal (calibrated) or std. errors of the values of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The integration order argument (d) must be a positive integer.
  * \note 4. The long-run mean can take any value or may be omitted, in which case a zero value is assumed.
  * \note 5. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARIMA_VALIDATE(), NDK_ARIMA_GOF(), NDK_ARIMA_FORE(), NDK_ARIMA_FITTED(), NDK_ARIMA_SIM()
  */
  int __stdcall NDK_ARIMA_PARAM( double* pData,       ///< [in] is the univariate time series data (a one dimensional array).
                                 size_t nSize,        ///< [in] is the number of observations in X.
                                 double* mean,        ///< [inout] is the ARMA model mean (i.e. mu).
                                 double* sigma,       ///< [inout] is the standard deviation of the model's residuals/innovations.
                                 WORD nIntegral,      ///< [in] is the model's integration order.
                                 double* phis,        ///< [inout] are the parameters of the AR(p) component model (starting with the lowest lag).
                                 size_t p,            ///< [in] is the number of elements in phis (order of AR component).
                                 double* thetas,      ///< [inout] are the parameters of the MA(q) component model (starting with the lowest lag).
                                 size_t q,            ///< [in] is the number of elements in thetas (order of MA component).
                                 MODEL_RETVAL_FUNC retType,   ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC).
                                 size_t maxIter       ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed.
                                 );


  /*! 
  * \brief Calculates the out-of-sample simulated values. 
  * 
  * \note 1. The input data argument (i.e. latest observations) is optional. If omitted, an array of zeroes is assumed. 
  * \note 2. The time series is homogeneous or equally spaced.
  * \note 3. The time series may include missing values (e.g. NaN) at either end.
  * \note 4. The input data argument (i.e. latest observations) is optional. If omitted, an array of zeroes is assumed. 
  * \note 5. The residuals/innovations standard deviation (sigma) must be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARIMA_VALIDATE(), NDK_ARIMA_GOF(), NDK_ARIMA_FORE(), NDK_ARIMA_FITTED(), NDK_ARIMA_PARAM()
  */
  int __stdcall NDK_ARIMA_SIM(  double mean,        ///< [in] is the ARMA model mean (i.e. mu).
                                double sigma,       ///< [in] is the standard deviation of the model's residuals/innovations.
                                WORD nIntegral,     ///< [in] is the model's integration order.
                                double* phis,       ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                                size_t p,           ///< [in] is the number of elements in phis (order of AR component).
                                double* thetas,     ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                                size_t q,           ///< [in] is the number of elements in thetas (order of MA component).
                                double* pData,      ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,       ///< [in] is the number of observations in X.
                                UINT nSeed,       ///< [in] is an unsigned integer for setting up the random number generators.
                                double* retVal,   ///< [out] is the calculated simulation value.
                                size_t nSteps     ///< [in] is the number of future steps to simulate for.
                                );
  /*! 
  * \brief   Calculates the out-of-sample conditional forecast (i.e. mean, error, and confidence interval).
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The integration order argument (d) must be a positive integer.
  * \note 4. The long-run mean can take any value or may be omitted, in which case a zero value is assumed.
  * \note 5. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARIMA_VALIDATE(), NDK_ARIMA_GOF(), NDK_ARIMA_SIM(), NDK_ARIMA_FITTED(), NDK_ARIMA_PARAM()
  */
  int __stdcall NDK_ARIMA_FORE( double* pData,      ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,       ///< [in] is the number of observations in X.
                                double mean,        ///< [in] is the ARMA model mean (i.e. mu).
                                double sigma,       ///< [in] is the standard deviation of the model's residuals/innovations.
                                WORD nIntegral,     ///< [in] is the model's integration order.
                                double* phis,       ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                                size_t p,           ///< [in] is the number of elements in phis (order of AR component).
                                double* thetas,     ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                                size_t q,           ///< [in] is the number of elements in thetas (order of MA component).
                                size_t nStep,       ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series).
                                FORECAST_RETVAL_FUNC retType, ///< [in] is a switch to select the type of value returned (see \ref #FORECAST_RETVAL_FUNC).
                                double  alpha,                ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                                double* retVal                ///< [out] is the calculated forecast value.
                                );
  /*! 
  * \brief   Returns the in-sample model fitted values of the conditional mean, volatility or residuals.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The integration order argument (d) must be a positive integer.
  * \note 4. The long-run mean can take any value or may be omitted, in which case a zero value is assumed.
  * \note 5. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_ARIMA_VALIDATE(), NDK_ARIMA_GOF(), NDK_ARIMA_SIM(), NDK_ARIMA_FORE(), NDK_ARIMA_PARAM()
  */
  int __stdcall NDK_ARIMA_FITTED( double* pData,      ///< [inout] is the univariate time series data (a one dimensional array).
                                  size_t nSize,       ///< [in] is the number of observations in X.
                                  double mean,        ///< [in] is the ARMA model mean (i.e. mu).
                                  double sigma,       ///< [in] is the standard deviation of the model's residuals/innovations.
                                  WORD nIntegral,     ///< [in] is the model's integration order.
                                  double* phis,       ///< [in] are the parameters of the AR(p) component model (starting with the lowest lag).
                                  size_t p,           ///< [in] is the number of elements in phis (order of AR component).
                                  double* thetas,     ///< [in] are the parameters of the MA(q) component model (starting with the lowest lag).
                                  size_t q,           ///< [in] is the number of elements in thetas (order of MA component).
                                  FIT_RETVAL_FUNC retType ///< [in]  is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC).
                                  );
  ///@}


  /// \name FARIMA
  /// Fractional ARIMA model functions
  /// @{
  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit function of the FARIMA model.   
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_RESID(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_FARIMA_GOF( double* pData, size_t nSize,  double mean, double sigma, double nIntegral, double* phis, size_t p, double* thetas, size_t q,  WORD retType, double* retVal);
  /*! 
  * \brief  Returns the standardized residuals of a given FARIMA model    
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_FARIMA_RESID( double* pData/*IN-OUT*/, size_t nSize, double mean, double sigma, double nIntegral, double* phis, size_t p, double* thetas, size_t q, WORD retType);
  /*! 
  * \brief  Returns the initial (non-optimal), optimal or standard errors of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_FARIMA_PARAM( double* pData, size_t nSize, double* mean, double* sigma, double nIntegral, double* phis, size_t p, double* thetas, size_t q, WORD retType, size_t maxIter);

  /*! 
  * \brief  Returns a simulated data series the underlying FARIMA process.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_FARIMA_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_FARIMA_SIM(  double* pData, size_t nSize, double mean, double sigma, double nIntegral, double* phis, size_t p, double* thetas, size_t q,  size_t nStep , size_t nSeed, double* retVal);

  /*! 
  * \brief   Calculates the out-of-sample forecast statistics.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_FARIMA_GOF(), NDK_FARIMA_RESID(), NDK_FARIMA_PARAM(), NDK_FARIMA_FITTED(), NDK_FARIMA_VALIDATE()
  */
  int __stdcall NDK_FARIMA_FORE( double* pData, size_t nSize, double mean, double sigma, double nIntegral, double* phis, size_t p, double* thetas, size_t q,  size_t nStep , WORD retType, double* retVal);
  /*! 
  * \brief   Returns an array of cells for the fitted values (i.e. mean, volatility and residuals)
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_FARIMA_GOF(), NDK_FARIMA_RESID(), NDK_FARIMA_PARAM(), NDK_FARIMA_FORE(), NDK_FARIMA_VALIDATE()
  */
  int __stdcall NDK_FARIMA_FITTED( double* pData, size_t nSize, double mean, double sigma, double nIntegral,  double* phis, size_t p, double* thetas, size_t q,  WORD retType);
  ///@}


  /// \name SARIMA
  /// Seasonal ARIMA model functions
  /// @{

  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit function of the SARIMA model.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 4. The maximum likelihood estimation (MLE) is a statistical method for fitting a model to the data and provides estimates for the model's parameters.
  * \note 5. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 6. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed to be zero.
  * \note 7. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed to be zero.
  * \note 8. The season length - s - is optional and can be omitted, in which case s is assumed to be zero (i.e. plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_RESID(), NDK_SARIMA_PARAM(), NDK_SARIMA_FORE(), NDK_SARIMA_FITTED(), NDK_SARIMA_VALIDATE()
  */
  int __stdcall NDK_SARIMA_GOF( double* pData,      ///< [in] is the univariate time series data (a one dimensional array).
                              size_t nSize,         ///< [in] is the number of observations in X.
                              double mean,          ///< [in] is the model mean (i.e. mu).
                              double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                              WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                              double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                              size_t p,             ///< [in] is the order of the non-seasonal AR component.
                              double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                              size_t q,             ///< [in] is the order of the non-seasonal MA component.
                              WORD nSIntegral,      ///< [in] is the seasonal difference.
                              WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                              double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                              size_t sP,            ///< [in] is the order of the seasonal AR component.
                              double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                              size_t sQ,            ///< [in] is the order of the seasonal MA component.
                              GOODNESS_OF_FIT_FUNC retType,   ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC).
                              double* retVal        ///< [out] is the calculated goodness of fit value.
                              );
  /*! 
  * \brief  Returns the quick guess, optimal (calibrated) or std. errors of the values of model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed to be zero.
  * \note 6. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed to be zero.
  * \note 7. The season length - s - is optional and can be omitted, in which case s is assumed to be zero (i.e. plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_FORE(), NDK_SARIMA_FITTED(), NDK_SARIMA_VALIDATE()
  */
  int __stdcall NDK_SARIMA_PARAM( double* pData,    ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,     ///< [in] is the number of observations in X.
                                  double* mean,     ///< [inout] is the mean of the ARMA process.
                                  double* sigma,    ///< [inout] is the standard deviation of the model's residuals/innovations.
                                  WORD nIntegral,   ///< [in] is the non-seasonal difference order.
                                  double* phis,     ///< [inout] are the coefficients's values of the non-seasonal AR component.
                                  size_t p,         ///< [in] is the order of the non-seasonal AR component.
                                  double* thetas,   ///< [inout] are the coefficients's values of the non-seasonal MA component.
                                  size_t q,         ///< [in] is the order of the non-seasonal MA component.
                                  WORD nSIntegral,  ///< [in] is the seasonal difference.
                                  WORD nSPeriod,    ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                  double* sPhis,    ///< [inout] are the coefficients's values of the seasonal AR component.
                                  size_t sP,        ///< [in] is the order of the seasonal AR component.
                                  double* sThetas,  ///< [inout] are the coefficients's values of the seasonal MA component.
                                  size_t sQ,        ///< [in] is the order of the seasonal MA component.
                                  MODEL_RETVAL_FUNC retType,     ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC).
                                  size_t maxIter    ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed.
                                  );


  /*! 
  * \brief  Returns the initial (non-optimal), optimal or standard errors of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. SARIMA_SIM returns an array of one simulation path starting from the end of the input data.
  * \note 3. The time series may include missing values (e.g. NaN) at either end.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The input data argument (i.e. latest observations) is optional. If omitted, an array of zeroes is assumed.
  * \note 6. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 7. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed to be zero.
  * \note 8. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed to be zero.
  * \note 9. The season length - s - is optional and can be omitted, in which case s is assumed to be zero (i.e. Plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_FORE(), NDK_SARIMA_FITTED(), NDK_SARIMA_VALIDATE()
  */
  int __stdcall NDK_SARIMA_SIM( double mean,        ///< [in] is the model mean (i.e. mu).
                                double sigma,       ///< [in] is the standard deviation of the model's residuals/innovations.
                                WORD nIntegral,     ///< [in] is the non-seasonal difference order.
                                double* phis,       ///< [in] are the coefficients's values of the non-seasonal AR component.
                                size_t p,           ///< [in] is the order of the non-seasonal AR component.
                                double* thetas,     ///< [in] are the coefficients's values of the non-seasonal MA component.
                                size_t q,           ///< [in] is the order of the non-seasonal MA component.
                                WORD nSIntegral,    ///< [in] is the seasonal difference.
                                WORD nSPeriod,      ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                double* sPhis,      ///< [in] are the coefficients's values of the seasonal AR component.
                                size_t sP,          ///< [in] is the order of the seasonal AR component.
                                double* sThetas,    ///< [in] are the coefficients's values of the seasonal MA component.
                                size_t sQ,          ///< [in] is the order of the seasonal MA component.
                                double* pData,      ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,       ///< [in] is the number of observations in X.
                                size_t nSeed,       ///< [in] is an unsigned integer for setting up the random number generators.
                                double* retVal,     ///< [out] is the simulated value.
                                size_t nStep        ///< [in] is the simulation time/horizon (expressed in terms of steps beyond end of the time series).
                                );
    /*! 
  * \brief   Calculates the out-of-sample conditional forecast (i.e. mean, error, and confidence interval).
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed to be zero.
  * \note 6. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed to be zero.
  * \note 7. The season length - s - is optional and can be omitted, in which case s is assumed to be zero (i.e. plain ARIMA). 
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_PARAM(), NDK_SARIMA_FITTED(), NDK_SARIMA_VALIDATE()
  */
  int __stdcall NDK_SARIMA_FORE(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.
                                double mean,          ///< [in] is the model mean (i.e. mu).
                                double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                                WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                                size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                                size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                WORD nSIntegral,      ///< [in] is the seasonal difference.
                                WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                                size_t sP,            ///< [in] is the order of the seasonal AR component.
                                double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                                size_t sQ,            ///< [in] is the order of the seasonal MA component.
                                size_t nStep,         ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series).
                                FORECAST_RETVAL_FUNC retType, ///< [in] is a switch to select the type of value returned (see \ref #FORECAST_RETVAL_FUNC).
                                double  alpha,        ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                                double* retVal        ///< [out] is the calculated forecast value.
                                );
  /*! 
  * \brief   Returns the in-sample model fitted values of the conditional mean, volatility or residuals.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed to be zero.
  * \note 6. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed to be zero.
  * \note 7. The season length - s - is optional and can be omitted, in which case s is assumed to be zero (i.e. plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_PARAM(), NDK_SARIMA_FORE(), NDK_SARIMA_VALIDATE()
  */
  int __stdcall NDK_SARIMA_FITTED(double* pData,        ///< [inout] is the univariate time series data (a one dimensional array).
                                  size_t nSize,         ///< [in] is the number of observations in X.
                                  double mean,          ///< [in] is the model mean (i.e. mu).
                                  double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                                  WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                  double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                                  size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                  double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                                  size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                  WORD nSIntegral,      ///< [in] is the seasonal difference.
                                  WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                  double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                                  size_t sP,            ///< [in] is the order of the seasonal AR component.
                                  double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                                  size_t sQ,            ///< [in] is the order of the seasonal MA component.
                                  FIT_RETVAL_FUNC retType          ///< [in]  is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC).
                                  );
  /*! 
  * \brief   Examines the model's parameters for stability constraints (e.g. stationarity, invertibility, causality, etc.).
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 4. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 5. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed to be zero.
  * \note 6. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed to be zero.
  * \note 7. The season length - s - is optional and can be omitted, in which case s is assumed to be zero (i.e. plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_PARAM(), NDK_SARIMA_FORE(), NDK_SARIMA_FITTED()
  */
  int __stdcall NDK_SARIMA_VALIDATE(double mean,          ///< [in] is the model mean (i.e. mu).
                                    double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                                    WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                    double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                                    size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                    double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                                    size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                    WORD nSIntegral,      ///< [in] is the seasonal difference.
                                    WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                    double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                                    size_t sP,            ///< [in] is the order of the seasonal AR component.
                                    double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                                    size_t sQ             ///< [in] is the order of the seasonal MA component.
                                    );
  ///@}

  /// \name AirLine
  ///AirLine model functions
  /// @{

  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit functions of the AirLine model.
  * 
  * \note 1. The Airline model is a special case of multiplicative seasonal ARIMA model, and it assumes independent and normally distributed residuals with constant variance.
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_RESID(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_AIRLINE_GOF(double* pData,    ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,     ///< [in] is the number of observations in X.
                                double mean,      ///< [in] is the model mean (i.e. \f$\mu\f$).
                                double sigma,     ///< [in] is the standard deviation (\f$\sigma\f$) of the model's residuals/innovations.
                                WORD    S,        ///< [in] is the length of seasonality (expressed in terms of lags, where s > 1).
                                double  theta,    ///< [in] is the coefficient of first-lagged innovation (\f$\theta\f$)(see model description).
                                double  theta2,   ///< [in] is the coefficient of s-lagged innovation (\f$\Theta\f$) (see model description).
                                GOODNESS_OF_FIT_FUNC retType,     ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC).
                                double* retVal    ///< [out] is the calculated value of the goodness of fit.
                                );

  /*! 
  * \brief  Returns an array of cells for the standardized residuals of a given AirLine model.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \deprecated this function is being replaced by NDK_AIRLINE_FITTED()
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_AIRLINE_RESID(  double* pData,    ///< [inout] is the univariate time series data (a one dimensional array).
                                    size_t nSize,     ///< [in] is the number of observations in X.
                                    double mean,      ///< [in] is the model mean (i.e. mu).
                                    double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                    WORD    S,        ///< [in] is the length of seasonality (expressed in terms of lags, where s > 1).
                                    double  theta,    ///< [in] is the coefficient of first-lagged innovation (see model description).
                                    double  theta2,   ///< [in] is the coefficient of s-lagged innovation (see model description).
                                    RESID_RETVAL_FUNC retType      ///< [in] is a switch to select a residuals-type:raw or standardized. see \ref #RESID_RETVAL_FUNC.
                                   );


  /*! 
  * \brief  Returns the initial/quick guess of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_AIRLINE_PARAM(  double* pData,    ///< [inout] is the univariate time series data (a one dimensional array).
                                    size_t nSize,     ///< [in] is the number of observations in X.
                                    double* mean,     ///< [inout] is the model mean (i.e. mu).
                                    double* sigma,    ///< [inout] is the standard deviation of the model's residuals/innovations.
                                    WORD    S,        ///< [in] is the length of seasonality (expressed in terms of lags, where s > 1).
                                    double*  theta,   ///< [inout] is the coefficient of first-lagged innovation (see model description).
                                    double*  theta2,  ///< [inout] is the coefficient of s-lagged innovation (see model description.
                                    MODEL_RETVAL_FUNC retType,     ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC).
                                    size_t maxIter    ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed. 
                                    );

  /*! 
  * \brief   Calculates the out-of-sample forecast statistics.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The season length must be greater than one.
  * \note 6. The input argument for the non-seasonal MA parameter - theta - is optional and can be omitted, in which case no non-seasonal MA component is included.
  * \note 7. The input argument for the seasonal MA parameter - theta2 - is optional and can be omitted, in which case no seasonal MA component is included.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_AIRLINE_FORE( double* pData,    ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,     ///< [in] is the number of observations in X.
                                  double mean,      ///< [in] is the model mean (i.e. mu).
                                  double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                  WORD    S,        ///< [in] is the length of seasonality (expressed in terms of lags, where s > 1).
                                  double  theta,    ///< [in] is the coefficient of first-lagged innovation (see model description).
                                  double  theta2,   ///< [in] is the coefficient of s-lagged innovation (see model description).
                                  size_t nStep,     ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series).
                                  FORECAST_RETVAL_FUNC retType,     ///< [in] is a switch to select the type of value returned  (see \ref #FORECAST_RETVAL_FUNC).
                                  double  alpha,    ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                                  double* retVal    ///< [out] is the calculated forecast value.
                                  );

  /*! 
  * \brief Calculates the out-of-sample conditional mean forecast.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The input data argument (i.e. latest observations) is optional. If omitted, a value of zero is assumed.
  * \note 3. The time series may include missing values (e.g. NaN) at either end.
  * \note 4. The \f$\epsilon\f$ are normally distributed with mean zero and unit standard deviation.
  * \note 5. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 6. The value of the residuals/innovations standard deviation (sigma) must be positive.
  * \note 7. The season length must be greater than one.
  * \note 8. The input argument for the non-seasonal MA parameter - theta - is optional and can be omitted, in which case no non-seasonal MA component is included.
  * \note 9. The input argument for the seasonal MA parameter - theta2 - is optional and can be omitted, in which case no seasonal MA component is included. 
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_VALIDATE(), NDK_AIRLINE_GOF(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED(), NDK_AIRLINE_PARAM()
  */
  int __stdcall NDK_AIRLINE_SIM(  double* pData,    ///< [in] is a univariate time series of the initial values (a one dimensional array).
                                  size_t nSize,     ///< [in] is the number of observations in X.
                                  double mean,      ///< [in] is the model mean (i.e. mu).
                                  double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                  WORD    S,        ///< [in] is the length of seasonality (expressed in terms of lags, where s > 1).
                                  double  theta,    ///< [in] is the coefficient of first-lagged innovation (see model description).
                                  double  theta2,   ///< [in] is the coefficient of s-lagged innovation (see model description).
                                  UINT nSeed,       ///< [in] is an unsigned integer for setting up the random number generators.
                                  double* retArray,   ///< [out] is the calculated simulation value.
                                  size_t nSteps     ///< [in] is the number of future steps to simulate for.
                                  );



  /*! 
  * \brief   Returns the fitted values of the conditional mean.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run mean argument (mean) can take any value or be omitted, in which case a zero value is assumed.
  * \note 4. The season length must be greater than one.
  * \note 5. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 6. The input argument for the non-seasonal MA parameter - theta - is optional and can be omitted, in which case no non-seasonal MA component is included.
  * \note 7. The input argument for the seasonal MA parameter - theta2 - is optional and can be omitted, in which case no seasonal MA component is included.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_VALIDATE()
  */
  int __stdcall NDK_AIRLINE_FITTED( double* pData,    ///< [in] is the univariate time series data (a one dimensional array).
                                    size_t nSize,     ///< [in] is the number of observations in X.
                                    double mean,      ///< [in] is the model mean (i.e. mu).
                                    double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                    WORD    S,        ///< [in] is the length of seasonality (expressed in terms of lags, where s > 1).
                                    double  theta,    ///< [in] is the coefficient of first-lagged innovation (see model description).
                                    double  theta2,   ///< [in] is the coefficient of s-lagged innovation (see model description).
                                    FIT_RETVAL_FUNC retType      ///< [in]  is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC).
                                    );

  /*! 
  * \brief   Examines the model's parameters for stability constraints (e.g. stationarity, etc.).
  * 
  * \note 1. The Airline model is a special case of multiplicative seasonal ARIMA model, and it assumes independent and normally distributed residuals with constant variance.
  * \note 2. The time series is homogeneous or equally spaced.
  * \note 3. The time series may include missing values (e.g. NaN) at either end.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED()
  */
  int __stdcall NDK_AIRLINE_VALIDATE( double mean,      ///< [in] is the model mean (i.e. mu).
                                      double sigma,     ///< [in] is the standard deviation of the model's residuals/innovations.
                                      WORD    S,        ///< [in] is the length of seasonality (expressed in terms of lags, where s > 1).
                                      double  theta,    ///< [in] is the coefficient of first-lagged innovation (see model description).
                                      double  theta2    ///< [in] is the coefficient of s-lagged innovation (see model description).
                                        );
  ///@}

  /// \name X12-ARIMA
  /// Seasonal ajustments using X12-ARIMA API functions calls
  /// @{

  /*! 
  * \brief   Initialize the filesystem environment on the local machine for the current user 
  * 
  * \note 1. This function creates a subfolder under the current user local profile for X12ARIMA models, and copy all the scripts needed to run the x12a program.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_ENV_INIT(BOOL   override ///< [in] is a boolean flag to wipe our existing files and copy new ones.
                                  );
  /*! 
  * \brief   Finalize the X12A environment and release any resources allocated 
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_ENV_CLEANUP(void);

  /*! 
  * \brief   Initialize the required files for the given scenario/model
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_SCEN_INIT(LPCTSTR szScenarioName,    ///< [in] is the scenario name, must be unique
                                  LPVOID X12Options         ///< [in] (optional) is an instance of #X12ARIMA_OPTIONS structure with all X12 model options.
                                  );
  /*! 
  * \brief   Finalize the given scenario/model and free allocated resources
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_SCEN_CLEAUP(LPCTSTR szScenarioName /*!< [in] is the scenario name or the model unique identifier */);


  /*! 
  * \brief   Write the given data into an X12a formatted data file
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_DATA_FILE(  LPCTSTR szScenarioName, 
                                    double* X,            ///< [in] is the univariate time series data (a one dimensional array).
                                    size_t nLen,          ///< [in] is the number of observations in X
                                    BOOL monthly,         ///< [in] is a boolean flag for whether the data is monthly/quartelry sampled.
                                    LONG startDate,       ///< [in] is the serial date number of the 1st observation in the series
                                    WORD reserved         ///< [in] is a reserved argument for future releases. must be set to 1
                                    );
  /*! 
  * \brief   Create or updates the x12a specification file using the options selected 
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_SPC_FILE(LPCTSTR szScenarioName, LPVOID X12Options);

  /*! 
  * \brief   Run a batch file in x12a environment
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_RUN_BATCH(LPCTSTR szScenarioName, LPCTSTR szBatchFile, LPWORD status);

  /*! 
  * \brief   Run a x12a program for the given model or scenrio
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_RUN_SCENARIO(LPCTSTR szScenarioName, LPWORD status);

  /*! 
  * \brief   Read the status file generated by x12a program
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_RUN_STAT(LPCTSTR szScenarioName, LPWORD status, LPTSTR szMsg, size_t* nLen);

  /*! 
  * \brief   Return the full path of the output file generated by x12a program
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_OUT_FILE(LPCTSTR szScenarioName,       ///< [in] is the scenaio.model name
                                        WORD retType,         ///< [in] is a switch to designate the desired specific output file.
                                                              ///       0. The X12 specification file (*.spc)
                                                              ///       1. The X12 log file
                                                              ///       2. The output file
                                                              ///       3. The error file
                                        LPTSTR szOutFile,      ///< [out] is a buffer to hold the return full path
                                        size_t* nLen,         ///< [inout] is the length of the szOutFile. Upon return, this argument stores the actual number of bytes used.
                                        BOOL OpenFileFlag     ///< [in] is a switch to instruct the functiona whether it should open the file using system default editor (e.g. notepad)
                                        );
  /*! 
  * \brief   Read the output time series (e.g. seasonal adjusted data) generated by x12a program
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X12_OUT_SERIES(LPCTSTR szScenarioName,   ///< [in] is the given scenario/model
                                    WORD nComponent,        ///< [in] is the desired output of the X12a output
                                                            /// 1. Final seasonal factors (d11)
                                                            /// 2. final trend-cycle (d12)
                                                            /// 3. final irregular component (d13)
                                                            /// 4. final seasonal factors (d10)
                                                            /// 5. combined holiday and trading day factors (d18)
                                                            /// 6. combined seasonal and trading day factors (d16)
                                    double* pData,          ///< [out] is the output buffer to hold the data series
                                    size_t* nLen            ///< [inout] is the original size of the output buffer. Upon return, nLen will have the actual number of data copied.
                                    );

  /*! 
  * \brief   Read the output forecaste series generated by x12a program
  * 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_SCEN_CLEAUP(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES()
  */
  int __stdcall NDK_X12_FORE_SERIES(  LPCTSTR szScenarioName,    ///< [in] is the given X12-ARIMA scenario/model identifier
                                      size_t nStep,             ///< [in] is the forecast horizon
                                      WORD retType,             ///< [in] is the switch to designate desired output
                                                                ///   1. Mean
                                                                ///   2. Lower limit value of the conficent interval
                                                                ///   3. Upper limit value of the confidence interval
                                      double* pData             ///< [out] is the forecast output value
                                      );
  ///@}


  /// \name X13ARIMA-SEATS
  /// X13ARIMA-SEATS model functions
  /// @{

  /*!
  * \brief   Initialize the filesystem environment on the local machine for the current user
  *
  * \note 1. This function creates a subfolder under the current user local profile for X13ARIMA models, and copy all the scripts needed to run the x13as program.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X13_ENV_CLEANUP()
  */
  int __stdcall NDK_X13_ENV_INIT(BOOL   override    ///< [in] is a boolean flag to wipe our existing files and copy new ones.
    );

  /*!
  * \brief   Finalize the X13AS environment and release any resources allocated
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X13_ENV_INIT()
  */
  int __stdcall NDK_X13_ENV_CLEANUP(void);

  /*!
  * \brief   Initialize the required files for the given scenario/model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X13_ENV_INIT(), NDK_X13_ENV_CLEANUP(), NDK_X13_SCEN_CLEAUP()
  */
  int __stdcall NDK_X13_SCEN_INIT(LPCTSTR szScenarioName,     ///< [in] is the scenario name, must be unique
                                  LPVOID X13Options           ///< [in] (optional) is an instance of #X13ARIMA_OPTIONS structure with all X13 model options.
                                  );


  /*!
  * \brief   reconstruct the different (input/intermediate/output) files
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X13_ENV_INIT(), NDK_X13_ENV_CLEANUP(), NDK_X13_SCEN_CLEAUP()
  */
  int __stdcall NDK_X13_SCEN_REFRESH(LPCTSTR szScenarioName);

  /*!
  * \brief   Finalize the given scenario/model and free allocated resources
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X12_ENV_INIT(), NDK_X12_ENV_CLEANUP(), NDK_X12_SCEN_INIT(), NDK_X12_DATA_FILE(), NDK_X12_SPC_FILE(), NDK_X12_RUN_BATCH(), NDK_X12_RUN_SCENARIO(), NDK_X12_RUN_STAT(), NDK_X12_OUT_FILE(), NDK_X12_OUT_SERIES(), NDK_X12_FORE_SERIES()
  */
  int __stdcall NDK_X13_SCEN_CLEAUP(LPCTSTR szScenarioName  /*!< [in] is the scenario name or the model unique identifier */
                                    );


  /*!
  * \brief   Write the given data into an X13as formatted data file
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X13_ENV_INIT(), NDK_X13_ENV_CLEANUP(), NDK_X13_SCEN_INIT(), NDK_X13_SCEN_CLEAUP()
  */
  int __stdcall NDK_X13_DATA_FILE(LPCTSTR szScenarioName, LPCTSTR szOutputFile,
    double* X,            ///< [in] is the univariate time series data (a one dimensional array).
    size_t nLen,          ///< [in] is the number of observations in X
    BOOL monthly,         ///< [in] is a boolean flag for whether the data is monthly/quartelry sampled.
    LONG startDate,       ///< [in] is the serial date number of the 1st observation in the series
    WORD reserved         ///< [in] is a reserved argument for future releases. must be set to 1
    );

  /*!
  * \brief   Write the actual holidays dates into an genhol formatted data file
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X13_ENV_INIT(), NDK_X13_ENV_CLEANUP(), NDK_X13_SCEN_INIT(), NDK_X13_SCEN_CLEAUP()
  */
  int __stdcall NDK_X13_HOLIDAY_FILE( LPCTSTR szScenarioName, ///< [in] is the scenario name or the model unique identifier
                                      LPCTSTR szHoliday,      ///< [in] is the holiday code (unique identifier) to get dates for.
                                      LONG startDate,         ///< [in] is the serial date number of the beginning of the search interval
                                      LONG endDate            ///< [in] is the serial date number of the end of the search interval
                                      );


  /*!
  * \brief   Write the (user) holidays dates into an genhol formatted data file
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_X13_HOLIDAY_FILE(), NDK_X13_SCEN_INIT(), NDK_X13_SCEN_CLEAUP()
  */
  int __stdcall NDK_X13_USER_EVENT_FILE(LPCTSTR szScenarioName,   ///< [in] is the scenario name or the model unique identifier
                                        LPCTSTR szName,           ///< [in] is the user-defined name (unique identifier) of the event.
                                        PLONG holidays,           ///< [in] is an array of dates serial numbers.
                                        size_t nLen               ///< [in] is the number of elements in the [holidays] array.
                                        );


  int __stdcall NDK_X13_ADD_EVENT_FACTOR( LPCTSTR szScenarioName, ///< [in] is the scenario name or the model unique identifier
                                          LPCTSTR szName,         ///< [in] is the user-defined name (unique identifier) of the event.
                                          PLONG holidays,         ///< [in] (optional, uer-defined only) is an array of dates serial numbers.
                                          size_t nLen,            ///< [in] (optional, uer-defined only) is the number of elements in the [holidays] array.
                                          double begbefore,       ///< [in] Denotes the position relative to the holiday of the beginning of the window used to generate the before-holiday regressor. This value should be negative, and less than or equal to the value for the endbefore argument. The minimum value that can be specified is -42.
                                          double endbefore,       ///< [in] Denotes the position relative to the holiday of the end of the window used to generate the before-holiday regressor. This value should be negative.
                                          double begAfter,        ///< [in] Denotes the position relative to the holiday of the beginning of the window used to generate the after-holiday regressor. Since this effect occurs after the holiday, the value should be non-negative.
                                          double endAfter,        ///< [in] Denotes the position relative to the holiday of the end of the window used to generate the after-holiday regressor. This value should be positive, and greater than or equal to the value for the begafter argument. The maximum value that can be specified is 49
                                          double zeroBefore,      ///< [in] Defines the year before which all values in the regressor are set to be zero. If this argument is set, first < zerobefore <= last, and if zeroafter is set, then zerobefore < zeroafter.
                                          double zeroAfter,       ///< [in] Defines the year on or after which all values in the regressor are set to be zero. If this argument is set, first < zeroafter <= last, and if zeroafter is set, then zerobefore < zeroafter.
                                          WORD   wCenter          ///< [in] Specifies the removal of the (sample) mean or the seasonal means from the user-defined regression variables.
                                          ///<  0 = None, 1=mean, 2=calendar (only with ratio type of data)
                                          );


  int __stdcall NDK_X13_REGRESSORS_SETTING( LPCTSTR szScenarioName, ///< [in] is the scenario name or the model unique identifier
                                            double   dwFirstYear,
                                            double   dwLastYear,
                                            double   dwFirstMeanYear,
                                            double   dwLastMeanYear,
                                            DWORD    dwPeriod,
                                            BOOL     bRatio,
                                            double   dwStockDay
                                            );
                                            
  int __stdcall NDK_X13_RUN_GENHOL(LPCTSTR szScenarioName);
  int __stdcall NDK_X13_RUN_BATCH(LPCTSTR szScenarioName, LPCTSTR szBatchFile, LPWORD status);
  int __stdcall NDK_X13_SPC_SERIES_SETTING(LPCTSTR szScenarioName, LPCTSTR szSeriesName, double* pData, size_t nLen, BOOL stock, BOOL monthly, LONG startDate, WORD fileType);
  int __stdcall NDK_X13_SPC_TRANSFORM_SETTING(LPCTSTR szScenarioName, X13TRANSFORM_METHOD zTransform, double zPower);
  int __stdcall NDK_X13_SPC_PRIOR_ADJUST_SETTING( LPCTSTR szScenarioName, BOOL lom, BOOL loq, BOOL leapYear,
                                                  double* pTempData, size_t nTempLen, LONG zTempStartDate, X13PRIORADJUST_TYPE nTempDataType,
                                                  double* pPermData, size_t nPermLen, LONG zPermStartDate, X13PRIORADJUST_TYPE nPermDataType);
  int __stdcall NDK_X13_SPC_X11_SETTING(LPCTSTR szScenarioName, BOOL enable, X11_MODE_TYPE mode, X11_SEASONALMA_TYPE seasonalma, int trendma, double sigmaLL, double sigmaUL);
  int __stdcall NDK_X13_SPC_SEATS_SETTING(LPCTSTR szScenarioName, BOOL enable, BOOL hpCycle, BOOL infiniteFilter, BOOL bAdmissableCompositionApprox, BOOL bAcceptSeasonStationary, double maxLBQStat);
  int __stdcall NDK_X13_WRITE_SPC_FILE(LPCTSTR szScenarioName);
  int __stdcall NDK_X13_RUN_SPC_FILE(LPCTSTR szScenarioName);
  int __stdcall NDK_X13AS_OUT_FILE(LPCTSTR szScenarioName, WORD retType, LPTSTR szOutFile, size_t* nLen, BOOL OpenFileFlag);
  int __stdcall NDK_X13AS_OUT_SERIES(LPCTSTR szScenarioName, LPCTSTR szComponent, double* pData, size_t* nLen);

  ///@}

  /// \name SARIMAX
  /// Seasonal ARIMA-X model functions
  /// @{

  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit functions of the SARIMA-X model.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 4. The maximum likelihood estimation (MLE) is a statistical method for fitting a model to the data and provides estimates for the model's parameters.
  * \note 5. The intercept or the regression constant term input argument is optional. If omitted, a zero value is assumed. 
  * \note 6. The long-run mean argumen (mean) of the differenced regression residuals can take any value. If omitted, a zero value is assumed.
  * \note 7. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed zero.
  * \note 8. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed zero.
  * \note 9. The season length - s - is optional and can be omitted, in which case s is assumed zero (i.e. Plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMAX_FITTED(), NDK_SARIMAX_PARAM(), NDK_SARIMAX_FORE(), NDK_SARIMAX_FORE(), NDK_SARIMAX_VALIDATE()
  */
  int __stdcall NDK_SARIMAX_GOF(double*  pData,       ///< [in] is the response univariate time series data (a one dimensional array).
                                double** pFactors,    ///< [in] is the exogneous factors time series data (each column is a separate factor, and each row is an observation).
                                size_t nSize,         ///< [in] is the number of observations.
                                size_t   nFactors,    ///< [in] is the number of exognous factors.
                                double*  fBetas,      ///< [in] is the weights or loading of the exogneous factors.
                                double   mean,        ///< [in] is the ARIMA/SARIMA model's long-run mean/trend (i.e. mu). If missing (i.e. NaN), then it is assumed zero.
                                double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                                WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                                size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                                size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                WORD nSIntegral,      ///< [in] is the seasonal difference.
                                WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                                size_t sP,            ///< [in] is the order of the seasonal AR component.
                                double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                                size_t sQ,            ///< [in] is the order of the seasonal MA component.
                                GOODNESS_OF_FIT_FUNC retType,   ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC).
                                double* retVal        ///< [out] is the calculated goodness of fit value.
                                );


    /*! 
  * \brief   Examines the model's parameters for stability constraints (e.g. causality, invertability, stationary, etc.).
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The intercept or the regression constant term input argument is optional. If omitted, a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed zero.
  * \note 6. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed zero.
  * \note 7. The season length - s - is optional and can be omitted, in which case s is assumed zero (i.e. Plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_PARAM(), NDK_SARIMA_FORE(), NDK_SARIMA_FITTED()
  */
  int __stdcall NDK_SARIMAX_VALIDATE(double mean,         ///< [in] is the model mean (i.e. mu) for the differenced series.
                                    double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                                    WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                    double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                                    size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                    double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                                    size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                    WORD nSIntegral,      ///< [in] is the seasonal difference.
                                    WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                    double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                                    size_t sP,            ///< [in] is the order of the seasonal AR component.
                                    double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                                    size_t sQ             ///< [in] is the order of the seasonal MA component.
                                    );

    /*! 
  * \brief   Returns the in-sample model fitted values of the conditional mean, volatility or residuals.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The intercept or the regression constant term input argument is optional. If omitted, a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The long-run mean argument (mean) of the differenced regression residuals can take any value. If omitted, a zero value is assumed. 
  * \note 6. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed zero.
  * \note 7. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed zero.
  * \note 8. The season length - s - is optional and can be omitted, in which case s is assumed zero (i.e. Plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMAX_GOF(), NDK_SARIMAX_RESID(), NDK_SARIMAX_PARAM(), NDK_SARIMAX_FORE(), NDK_SARIMAX_VALIDATE()
  */
  int __stdcall NDK_SARIMAX_FITTED( double* pData,        ///< [inout] is the univariate time series data (a one dimensional array).
                                    double** pFactors,    ///< [in] is the exogneous factors time series data (each column is a separate factor, and each row is an observation).
                                    size_t nSize,         ///< [in] is the number of observations.
                                    size_t   nFactors,    ///< [in] is the number of exognous factors.
                                    double*  fBetas,      ///< [in] is the weights or loading of the exogneous factors.
                                    double   mean,        ///< [in] is the ARIMA/SARIMA model's long-run mean/trend (i.e. mu). If missing (i.e. NaN), then it is assumed zero.
                                    double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                                    WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                    double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                                    size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                    double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                                    size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                    WORD nSIntegral,      ///< [in] is the seasonal difference.
                                    WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                    double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                                    size_t sP,            ///< [in] is the order of the seasonal AR component.
                                    double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                                    size_t sQ,            ///< [in] is the order of the seasonal MA component.
                                    FIT_RETVAL_FUNC retType          ///< [in]  is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC).
                                    );


    /*! 
  * \brief  Returns the quick guess, optimal (calibrated) or std. errors of the values of model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The intercept or the regression constant term input argument is optional. If omitted, a zero value is assumed.
  * \note 4. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 5. The long-run mean argument (mean) of the differenced regression residuals can take any value. If omitted, a zero value is assumed.
  * \note 6. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed zero.
  * \note 7. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed zero.
  * \note 8. The season length - s - is optional and can be omitted, in which case s is assumed zero (i.e. Plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMAX_GOF(), NDK_SARIMAX_RESID(), NDK_SARIMAX_FORE(), NDK_SARIMAX_FITTED(), NDK_SARIMAX_VALIDATE()
  */
  int __stdcall NDK_SARIMAX_PARAM(  double* pData,        ///< [inout] is the univariate time series data (a one dimensional array).
                                    double** pFactors,    ///< [in] is the exogneous factors time series data (each column is a separate factor, and each row is an observation).
                                    size_t nSize,         ///< [in] is the number of observations.
                                    size_t   nFactors,    ///< [in] is the number of exognous factors.
                                    double*  fBetas,      ///< [inout] is the weights or loading of the exogneous factors.
                                    double* mean,         ///< [inout] is the mean of the differenced time series process.
                                    double* sigma,        ///< [inout] is the standard deviation of the model's residuals/innovations.
                                    WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                    double* phis,         ///< [inout] are the coefficients's values of the non-seasonal AR component.
                                    size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                    double* thetas,       ///< [inout] are the coefficients's values of the non-seasonal MA component.
                                    size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                    WORD nSIntegral,      ///< [in] is the seasonal difference.
                                    WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                    double* sPhis,        ///< [inout] are the coefficients's values of the seasonal AR component.
                                    size_t sP,            ///< [in] is the order of the seasonal AR component.
                                    double* sThetas,      ///< [inout] are the coefficients's values of the seasonal MA component.
                                    size_t sQ,            ///< [in] is the order of the seasonal MA component.
                                    MODEL_RETVAL_FUNC retType, ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC).
                                    size_t maxIter        ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed.
                                  );


    /*! 
  * \brief   Calculates the out-of-sample forecast statistics.
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 4. The exogneous factors input are expected to have at least n-more observations than the reponse variable.
  * \note 5. The intercept or the regression constant term input argument is optional. If omitted, a zero value is assumed.
  * \note 6. The long-run mean argument (mean) of the differenced regression residuals can take any value. If omitted, a zero value is assumed.
  * \note 7. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed zero.
  * \note 8. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed zero.
  * \note 9. The season length - s - is optional and can be omitted, in which case s is assumed zero (i.e. Plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_PARAM(), NDK_SARIMA_FITTED(), NDK_SARIMA_VALIDATE()
  */
  int __stdcall NDK_SARIMAX_FORE(double* pData,       ///< [in] is the univariate time series data (a one dimensional array).
                                double** pFactors,    ///< [in] is the exogneous factors time series data (each column is a separate factor, and each row is an observation).
                                size_t  nSize,        ///< [in] is the number of observations.
                                size_t  nFactors,     ///< [in] is the number of exognous factors.
                                double* fBetas,       ///< [inout] is the weights or loading of the exogneous factors.
                                double  mean,         ///< [inout] is the mean of the ARMA process.
                                double sigma,         ///< [in] is the standard deviation of the model's residuals/innovations.
                                WORD nIntegral,       ///< [in] is the non-seasonal difference order.
                                double* phis,         ///< [in] are the coefficients's values of the non-seasonal AR component.
                                size_t p,             ///< [in] is the order of the non-seasonal AR component.
                                double* thetas,       ///< [in] are the coefficients's values of the non-seasonal MA component.
                                size_t q,             ///< [in] is the order of the non-seasonal MA component.
                                WORD nSIntegral,      ///< [in] is the seasonal difference.
                                WORD nSPeriod,        ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                double* sPhis,        ///< [in] are the coefficients's values of the seasonal AR component.
                                size_t sP,            ///< [in] is the order of the seasonal AR component.
                                double* sThetas,      ///< [in] are the coefficients's values of the seasonal MA component.
                                size_t sQ,            ///< [in] is the order of the seasonal MA component.
                                size_t nStep,         ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series).
                                FORECAST_RETVAL_FUNC retType, ///< [in] is a switch to select the type of value returned (see \ref #FORECAST_RETVAL_FUNC).
                                double  alpha,        ///< [in] is the statistical significance level. If missing, a default of 5% is assumed.
                                double* retVal        ///< [out] is the calculated forecast value.
                                );


    /*! 
  * \brief  Calculates the out-of-sample simulated values. 
  * 
  * \note 1. The time series is homogeneous or equally spaced.
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The residuals/innovations standard deviation (i.e.\f$\sigma\f$) should be greater than zero.
  * \note 4. The intercept or the regression constant term input argument is optional. If omitted, a zero value is assumed.
  * \note 5. The exogenous factors input are expected to have at least n-more observations than the reponse variable.
  * \note 6. The long-run mean argument (mean) of the differenced regression residuals can take any value. If omitted, a zero value is assumed.
  * \note 7. The non-seasonal integration order - d - is optional and can be omitted, in which case d is assumed zero.
  * \note 8. The seasonal integration order - sD - is optional and can be omitted, in which case sD is assumed zero.
  * \note 9. The season length - s - is optional and can be omitted, in which case s is assumed zero (i.e. Plain ARIMA).
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_SARIMA_GOF(), NDK_SARIMA_RESID(), NDK_SARIMA_FORE(), NDK_SARIMA_FITTED(), NDK_SARIMA_VALIDATE()
  */
  int __stdcall NDK_SARIMAX_SIM(double* fBetas,     ///< [inout] is the weights or loading of the exogneous factors.
                                size_t  nFactors,   ///< [in] is the number of exognous factors.
                                double  mean,       ///< [inout] is the mean of the ARMA process.
                                double sigma,       ///< [in] is the standard deviation of the model's residuals/innovations.
                                WORD nIntegral,     ///< [in] is the non-seasonal difference order.
                                double* phis,       ///< [in] are the coefficients's values of the non-seasonal AR component.
                                size_t p,           ///< [in] is the order of the non-seasonal AR component.
                                double* thetas,     ///< [in] are the coefficients's values of the non-seasonal MA component.
                                size_t q,           ///< [in] is the order of the non-seasonal MA component.
                                WORD nSIntegral,    ///< [in] is the seasonal difference.
                                WORD nSPeriod,      ///< [in] is the number of observations per one period (e.g. 12=Annual, 4=Quarter).
                                double* sPhis,      ///< [in] are the coefficients's values of the seasonal AR component.
                                size_t sP,          ///< [in] is the order of the seasonal AR component.
                                double* sThetas,    ///< [in] are the coefficients's values of the seasonal MA component.
                                size_t sQ,          ///< [in] is the order of the seasonal MA component.
                                double* pData,      ///< [in] is the univariate time series data (a one dimensional array).
                                double** pFactors,  ///< [in] is the past exogneous factors time series data (each column is a separate factor, and each row is an observation).
                                size_t nSize,       ///< [in] is the number of observations in X. 
                                UINT nSeed,         ///< [in] is an unsigned integer for setting up the random number generators.
                                size_t nStep,       ///< [in] is the simulation time/horizon (expressed in terms of steps beyond end of the time series).
                                double* retVal      ///< [out] is the simulated value.
                                );


  ///@}


  /// \name GARCH
  ///GARCH Functions
  /// @{

  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit function of the GARCH model.   
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCH_GOF(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                              size_t nSize,         ///< [in] is the number of observations in X.    
                              double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                              const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                              size_t p,             ///< [in] is the number of elements in Alphas array
                              const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                              size_t q,             ///< [in] is the number of elements in Betas array
                              WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                    ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                    ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                    ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                              double  nu,           ///<  [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                              WORD retType,         ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC)
                              double* retVal        ///< [out] is the calculated goodness of fit value. 
                              );
  /*! 
  * \brief  Returns an array of cells for the standardized residuals of a given GARCH model    
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \deprecated this function is being replaced by NDK_GARCH_FITTED()
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCH_RESID(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.    
                                double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                      ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                      ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                      ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                WORD retType          ///< [in] is a switch to select a residuals-type:raw or standardized. see \ref #RESID_RETVAL_FUNC
                                );
  /*! 
  * \brief  Returns an array of cells for the initial (non-optimal), optimal or standard errors of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCH_PARAM(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.    
                                double* mu,           ///< [inout] is the GARCH model conditional mean (i.e. mu). 
                                double* Alphas,       ///< [inout] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                double* Betas,        ///< [inout] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                      ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                      ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                      ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                double* nu,           ///<  [inout] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                WORD retType,         ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC)
                                size_t maxIter        ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed. 
                                );
    /*! 
  * \brief  Returns a simulated data series the underlying GARCH process.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCH_SIM(double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                              const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                              size_t p,             ///< [in] is the number of elements in Alphas array
                              const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                              size_t q,             ///< [in] is the number of elements in Betas array
                              WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                              double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                              double* pData,        ///< [in] is the univariate time series of the latest observations (a one dimensional array).
                              size_t nSize,         ///< [in] is the number of observations in X.    
                              double* sigmas,       ///< [in] is the univariate time series of the latest observations (a one dimensional array of cells (e.g. rows or columns)) of the last q realized volatilities. 
                              size_t  nSigmaSize,   ///< [in] is the number of elements in sigmas. Only the latest q observations are used.
                              UINT nSeed,           ///< [in] is an unsigned integer for setting up the random number generators
                              double* retArray,     ///< [out] is the calculated simulation value
                              size_t nSteps         ///< [in] is the number of future steps to simulate for.  
                              );
  /*! 
  * \brief   Calculates the out-of-sample forecast statistics.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCH_FORE( double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.
                                double* sigmas,       ///< [in] is the univariate time series data (a one dimensional array of cells (e.g. rows or columns)) of the last q realized volatilities. 
                                size_t  nSigmaSize,   ///< [in] is the number of elements in sigmas. Only the latest q observations are used.
                                double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                      ///   - INNOVATION_GAUSSIAN Gaussian or Normal Distribution 
                                                      ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                      ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                size_t nStep ,        ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series). 
                                WORD retType,         ///< [in] is a switch to select the type of value returned
                                                      ///       1. Mean forecast 
                                                      ///       2. Forecast Error
                                                      ///       3. Volatility term structure
                                                      ///       4. Confidence interval lower limit
                                                      ///       5. Confidence interval upper limit 
                                                      ///       (see \ref #FORECAST_RETVAL_FUNC)
                                double  alpha,        ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                                double* retVal        ///< [out] is the calculated forecast value
                                );
  /*! 
  * \brief   Returns an array of cells for the fitted values (i.e. mean, volatility and residuals)
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCH_FITTED( double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,         ///< [in] is the number of observations in X.    
                                  double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  WORD retType          ///< [in] is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC)
                                  );

  /*! 
  * \brief   Calculates the long-run average volatility for the given GARCH model
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run variance is not affected by our choice of shock/innovation distribution
  * \note 4. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCH_LRVAR(  double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  double* retVal        ///< [out] is the calculated long run value
                                );
  /*! 
  * \brief   Examines the model's parameters for stability constraints (e.g. variance stationary, positive variance, etc.). 
  *  
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_TRUE Model is stable (i.e. variance process is stationary and yield positive values)
  *   \retval #NDK_FALSE Model is unstable.
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED()
  */
  int __stdcall NDK_GARCH_VALIDATE(double mu,           ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu            ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                   );
  ///@}

  /// \name EGARCH
  ///EGARCH Functions
  /// @{

  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit function of the GARCH model.   
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_EGARCH_RESID(), NDK_EGARCH_PARAM(), NDK_EGARCH_FORE(), NDK_EGARCH_FITTED(), NDK_EGARCH_VALIDATE()
  */
  int __stdcall NDK_EGARCH_GOF( double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.    
                                double mu,            ///< [in] is the EGARCH model conditional mean (i.e. mu). 
                                const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                const double* Gammas, ///< [in] are the leverage parameters (starting with the lowest lag).
                                size_t g,             ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                      ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                      ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                      ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                WORD retType,         ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC)
                                double* retVal        ///< [out] is the calculated goodness of fit value. 
                                );
  /*! 
  * \brief  Returns an array of cells for the standardized residuals of a given GARCH model    
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \deprecated this function is being replaced by NDK_EGARCH_FITTED()
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_EGARCH_RESID( double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,         ///< [in] is the number of observations in X.    
                                  double mu,            ///< [in] is the EGARCH model conditional mean (i.e. mu). 
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Gammas, ///< [in] are the leverage parameters (starting with the lowest lag).
                                  size_t g,             ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  WORD retType          ///< [in] is a switch to select a residuals-type:raw or standardized. see \ref #RESID_RETVAL_FUNC
                                  );
  /*! 
  * \brief  Returns an array of cells for the initial (non-optimal), optimal or standard errors of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_EGARCH_GOF(), NDK_EGARCH_RESID(), NDK_EGARCH_FORE(), NDK_EGARCH_FITTED(), NDK_EGARCH_VALIDATE()
  */
  int __stdcall NDK_EGARCH_PARAM( double* pData,       ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,        ///< [in] is the number of observations in X.    
                                  double* mu,          ///< [inout] is the EGARCH model conditional mean (i.e. mu). 
                                  double* Alphas,      ///< [inout] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,            ///< [in] is the number of elements in Alphas array
                                  double* Gammas,      ///< [inout] are the leverage parameters (starting with the lowest lag).
                                  size_t g,            ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                  double* Betas,       ///< [inout] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double*  nu,          ///< [inout] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  WORD retType,         ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC)
                                  size_t maxIter        ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed. 
                                  );
  /*! 
  * \brief  Returns a simulated data series the underlying EGARCH process.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_EGARCH_RESID(), NDK_EGARCH_PARAM(), NDK_EGARCH_FORE(), NDK_EGARCH_FITTED(), NDK_EGARCH_VALIDATE()
  */
  int __stdcall NDK_EGARCH_SIM( double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                const double* Gammas, ///< [in] are the leverage parameters (starting with the lowest lag).
                                size_t g,             ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.    
                                double* sigmas,       ///< [in] is the univariate time series data (a one dimensional array of cells (e.g. rows or columns)) of the last q realized volatilities. 
                                size_t  nSigmaSize,   ///< [in] is the number of elements in sigmas. Only the latest q observations are used.
                                UINT nSeed,           ///< [in] is an unsigned integer for setting up the random number generators
                                double* retArray,     ///< [out] is the calculated simulation value
                                size_t nSteps         ///< [in] is the number of future steps to simulate for.  
                                );
  /*! 
  * \brief   Calculates the out-of-sample forecast statistics.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_EGARCH_GOF(), NDK_EGARCH_RESID(), NDK_EGARCH_PARAM(), NDK_EGARCH_FITTED(), NDK_EGARCH_VALIDATE()
  */
  int __stdcall NDK_EGARCH_FORE(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.    
                                double* sigmas,       ///< [in] is the univariate time series data (a one dimensional array of cells (e.g. rows or columns)) of the last q realized volatilities. 
                                size_t  nSigmaSize,   ///< [in] is the number of elements in sigmas. Only the latest q observations are used.
                                double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                const double* Gammas, ///< [inout] are the leverage parameters (starting with the lowest lag).
                                size_t g,             ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                      ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                      ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                      ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                size_t nStep ,        ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series). 
                                WORD retType,         ///< [in] is a switch to select the type of value returned
                                                      ///       1. Mean forecast 
                                                      ///       2. Forecast Error
                                                      ///       3. Volatility term structure
                                                      ///       4. Confidence interval lower limit
                                                      ///       5. Confidence interval upper limit 
                                                      ///       (see \ref #FORECAST_RETVAL_FUNC)
                                double  alpha,        ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                                double* retVal        ///< [out] is the simulated value for the GARCH process.
                                );
  /*! 
  * \brief   Returns an array of cells for the fitted values (i.e. mean, volatility and residuals)
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_EGARCH_FITTED(  double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                    size_t nSize,         ///< [in] is the number of observations in X.    
                                    double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                    const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                    size_t p,             ///< [in] is the number of elements in Alphas array
                                    const double* Gammas, ///< [in] are the leverage parameters (starting with the lowest lag).
                                    size_t g,             ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                    const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                    size_t q,             ///< [in] is the number of elements in Betas array
                                    WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                          ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                          ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                          ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                    double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                    WORD retType          ///< [in] is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC)
                                      );


  /*! 
  * \brief   Calculates the long-run average volatility for a given E-GARCH model.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The long-run variance is not affected by our choice of shock/innovation distribution
  * \note 4. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 5. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 6. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_EGARCH_GOF(), NDK_EGARCH_RESID(), NDK_EGARCH_PARAM(), NDK_EGARCH_FORE(), NDK_EGARCH_VALIDATE()
  */
  int __stdcall NDK_EGARCH_LRVAR( double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Gammas, ///< [inout] are the leverage parameters (starting with the lowest lag).
                                  size_t g,             ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  double* retVal        ///< [out] is the calculated Long run volatility.
                                  );
  /*! 
  * \brief   Examines the model's parameters for stability constraints (e.g. stationary, positive variance, etc.). 
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model.
  * \note 4. The number of gamma-coefficients must match the number of alpha-coefficients minus one.
  * \note 5. The number of parameters in the input argument - beta - determines the order of the GARCH component model.
  *
  *   \return status code of the operation
  *   \retval #NDK_TRUE Model is stable (i.e. variance process is stationary and yield positive values)
  *   \retval #NDK_FALSE Model is unstable.
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_AIRLINE_GOF(), NDK_AIRLINE_RESID(), NDK_AIRLINE_PARAM(), NDK_AIRLINE_FORE(), NDK_AIRLINE_FITTED()
  */
  int __stdcall NDK_EGARCH_VALIDATE( double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                      const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                      size_t p,             ///< [in] is the number of elements in Alphas array
                                      const double* Gammas,       ///< [inout] are the leverage parameters (starting with the lowest lag).
                                      size_t g,             ///< [in] is the number of elements in Gammas. Must be equal to (p-1).
                                      const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                      size_t q,             ///< [in] is the number of elements in Betas array
                                      WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                            ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                            ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                            ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                      double  nu            ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                      );
  ///@}


  /// \name GARCH-M
  ///GARCH-M Functions
  /// @{

  /*! 
  * \brief Computes the log-likelihood ((LLF), Akaike Information Criterion (AIC) or other goodness of fit function of the GARCH model.   
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCHM_RESID(), NDK_GARCHM_PARAM(), NDK_GARCHM_FORE(), NDK_GARCHM_FITTED(), NDK_GARCHM_VALIDATE()
  */
  int __stdcall NDK_GARCHM_GOF(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                              size_t nSize,         ///< [in] is the number of observations in X.    
                              double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                              double flambda,       ///< [in] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                              const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                              size_t p,             ///< [in] is the number of elements in Alphas array
                              const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                              size_t q,             ///< [in] is the number of elements in Betas array
                              WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                    ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                    ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                    ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                              double  nu,           ///<  [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                              WORD retType,         ///< [in] is a switch to select a fitness measure ( see \ref #GOODNESS_OF_FIT_FUNC)
                              double* retVal        ///< [out] is the calculated goodness of fit value. 
                                );
  /*! 
  * \brief  Returns an array of cells for the standardized residuals of a given GARCH model    
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \deprecated this function is being replaced by NDK_GARCHM_FITTED()
  *   \sa NDK_GARCHM_GOF(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCHM_RESID( double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,         ///< [in] is the number of observations in X.    
                                  double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                  double flambda,       ///< [in] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  WORD retType          ///< [in] is a switch to select a residuals-type:raw or standardized. see \ref #RESID_RETVAL_FUNC
                                  );
  /*! 
  * \brief  Returns an array of cells for the initial (non-optimal), optimal or standard errors of the model's parameters.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCHM_PARAM( double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,         ///< [in] is the number of observations in X.    
                                  double* mu,           ///< [inout] is the GARCH model conditional mean (i.e. mu). 
                                  double* flambda,      ///< [inout] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                                  double* Alphas,       ///< [inout] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  double* Betas,        ///< [inout] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double*  nu,           ///<  [inout] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  WORD retType,         ///< [in] is a switch to select the type of value returned: 1= Quick Guess, 2=Calibrated, 3= Std. Errors ( see \ref #MODEL_RETVAL_FUNC)
                                  size_t maxIter        ///< [in] is the maximum number of iterations used to calibrate the model. If missing or less than 100, the default maximum of 100 is assumed. 
                                  );

  /*! 
  * \brief  Returns a simulated data series the underlying GARCH process.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCHM_SIM( double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                double  flambda,      ///< [in] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                                const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.    
                                double* sigmas,       ///< [in] is the univariate time series data (a one dimensional array of cells (e.g. rows or columns)) of the last q realized volatilities. 
                                size_t  nSigmaSize,   ///< [in] is the number of elements in sigmas. Only the latest q observations are used.
                                UINT nSeed,           ///< [in] is an unsigned integer for setting up the random number generators
                                double* retArray,     ///< [out] is the calculated simulation value
                                size_t nSteps         ///< [in] is the number of future steps to simulate for.  
                                );
  /*! 
  * \brief   Calculates the out-of-sample forecast statistics.
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FITTED(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCHM_FORE(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                size_t nSize,         ///< [in] is the number of observations in X.
                                double* sigmas,       ///< [in] is the univariate time series data (a one dimensional array of cells (e.g. rows or columns)) of the last q realized volatilities. 
                                size_t  nSigmaSize,   ///< [in] is the number of elements in sigmas. Only the latest q observations are used.
                                double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                double  flambda,      ///< [in] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                                const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                size_t p,             ///< [in] is the number of elements in Alphas array
                                const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                size_t q,             ///< [in] is the number of elements in Betas array
                                WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                      ///   - INNOVATION_GAUSSIAN Gaussian or Normal Distribution 
                                                      ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                      ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                size_t nStep ,        ///< [in] is the forecast time/horizon (expressed in terms of steps beyond end of the time series). 
                                WORD retType,         ///< [in] is a switch to select the type of value returned
                                                      ///       1. Mean forecast 
                                                      ///       2. Forecast Error
                                                      ///       3. Volatility term structure
                                                      ///       4. Confidence interval lower limit
                                                      ///       5. Confidence interval upper limit 
                                                      ///       (see \ref #FORECAST_RETVAL_FUNC)
                                double  alpha,        ///< [in] is the statistical significance level. If missing, a default of 5% is assumed. 
                                double* retVal        ///< [out] is the calculated forecast value
                                );
  /*! 
  * \brief   Returns an array of cells for the fitted values (i.e. mean, volatility and residuals)
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCHM_GOF(), NDK_GARCHM_RESID(), NDK_GARCHM_PARAM(), NDK_GARCHM_FORE(), NDK_GARCHM_VALIDATE()
  */
  int __stdcall NDK_GARCHM_FITTED(double* pData,        ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t nSize,         ///< [in] is the number of observations in X.    
                                  double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                  double  flambda,      ///< [in] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  WORD retType          ///< [in] is a switch to select a output type ( see \ref #FIT_RETVAL_FUNC) 
                                  );

  /*! 
  * \brief   Calculates the long-run average volatility for the given GARCH-M model
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCH_GOF(), NDK_GARCH_RESID(), NDK_GARCH_PARAM(), NDK_GARCH_FORE(), NDK_GARCH_VALIDATE()
  */
  int __stdcall NDK_GARCHM_LRVAR( double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                  double  flambda,      ///< [in] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                                  const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                  size_t p,             ///< [in] is the number of elements in Alphas array
                                  const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                  size_t q,             ///< [in] is the number of elements in Betas array
                                  WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                        ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                        ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                        ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                  double  nu,           ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                  double* retVal        ///< [out] is the calculated long run value
                                  );
  /*! 
  * \brief   Examines the model's parameters for stability constraints (e.g. stationary, etc.). 
  * 
  * \note 1. The time series is homogeneous or equally spaced
  * \note 2. The time series may include missing values (e.g. NaN) at either end.
  * \note 3. The number of parameters in the input argument - alpha - determines the order of the ARCH component model. 
  * \note 4. The number of parameters in the input argument - beta - determines the order of the GARCH component model
  *
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED operation is unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_GARCHM_GOF(), NDK_ARCHM_RESID(), NDK_ARCHM_PARAM(), NDK_ARCHM_FORE(), NDK_ARCHM_FITTED()
  */
  int __stdcall NDK_GARCHM_VALIDATE(double mu,            ///< [in] is the GARCH model conditional mean (i.e. mu). 
                                    double  flambda,      ///< [in] is the volatility coefficient for the mean. In finance, lambda is referenced as the risk premium.
                                    const double* Alphas, ///< [in] are the parameters of the ARCH(p) component model (starting with the lowest lag). 
                                    size_t p,             ///< [in] is the number of elements in Alphas array
                                    const double* Betas,  ///< [in] are the parameters of the GARCH(q) component model (starting with the lowest lag). 
                                    size_t q,             ///< [in] is the number of elements in Betas array
                                    WORD  nInnovationType,///< [in] is the probability distribution function of the innovations/residuals (see #INNOVATION_TYPE)
                                                          ///   - INNOVATION_GAUSSIAN Gaussian Distribution (default)
                                                          ///   - INNOVATION_TDIST    Student's T-Distribution, 
                                                          ///   - INNOVATION_GED      Generalized Error Distribution (GED)
                                    double  nu            ///< [in] is the shape factor (or degrees of freedom) of the innovations/residuals probability distribution function. 
                                    );
  ///@}


  /// \name Speactral Analysis
  /// @{
  /*! 
  *   \brief Returns an array of cells for the convolution operator of two time series 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, NDK_LAG(), NDK_DIFF
  */
  int   __stdcall NDK_CONVOLUTION(double *X,  ///< [in] is the univariate time series data (a one dimensional array).
                                  size_t N1,  ///< [in] is the number of observations in X. 
                                  double *Y,  ///< [in] is the second univariate time series data (a one dimensional array)
                                  size_t N2,  ///< [in] is the number of observations in Y.
                                  double* Z,  ///< [out] is the convolution time series output
                                  size_t* W   ///< [inout] is the maximum number of elements in Z.
                                  );

  /*! 
  *   \brief Calculates the inverse discrete fast Fourier transformation, recovering the time series.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, NDK_LAG(), NDK_DIFF
  */
  int   __stdcall NDK_IDFT( double *amp,        ///< [in]  is an array of the amplitudes of the fourier transformation components.
                            double *phase,      ///< [in]  is an array of the phase angle (radian) of the Fourier transformation components .
                            size_t nSize,       ///< [in] is the number of spectrum components (i.e. size of amp and phase). 
                            double* X,          ///< [out] is the filtered (recovered) time series output
                            size_t N            ///< [in]  is the original number of observations used to calculate the fourier transform. 
                            );

  /*! 
  *   \brief Calculates the discrete fast Fourier transformation for amplitude and phase.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, NDK_LAG(), NDK_DIFF
  */
  int   __stdcall NDK_DFT(double *X,        ///< [in] is the univariate time series data (a one dimensional array).
                          size_t N,         ///< [in] is the number of observations in X. 
                          double* retAmp,   ///< [out]  is an array of the amplitudes of the fourier transformation components
                          double* retPhase, ///< [out]  is an array of the phase angle (radian) of the Fourier transformation components .
                          size_t M          ///< [in] is the number of spectrum components (i.e. size of amp and phase)
                          );


  /*! 
  *   \brief computes cyclical component of given time series using the Hodrick–Prescott filter.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful (see \ref SFMacros.h) 
  *   \sa NDK_BaxterKingFilter(), NDK_DFT(), NDK_IDFT()
  */
  int   __stdcall NDK_HodrickPrescotFilter(double *X,       ///< [inout] is the univariate time series data (a one dimensional array).
                                           size_t N,        ///< [in] is the number of observations in X. 
                                           BOOL bAscending, ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)). 
                                           double lambda    ///< [in]  is the multiplier used to penalize the variation in the trend component. If missing, a default is used based on data frequency. 
                                           );


  /*! 
  *   \brief Computes trend and cyclical component of a macroeconomic time series using Baxter-King Fixed Length Symmetric Filter. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful (see \ref SFMacros.h) 
  *   \sa NDK_HodrickPrescotFilter(), NDK_DFT(), NDK_IDFT()
  */
  int   __stdcall NDK_BaxterKingFilter( double *X,        ///< [inout] is the univariate time series data (a one dimensional array).
                                        size_t N,         ///< [in] is the number of observations in X. 
                                        BOOL bAscending,  ///< [in] is the time order in the data series (i.e. the first data point's corresponding date (earliest date=1 (default), latest date=0)). 
                                        size_t freq_min,  ///< [in] is the number of periods for the high pass filter (e.g. 6 for quarterly data, 18 for monthly data). 
                                        size_t freq_max,  ///< [in] is the number of periods for the low passfilter (e.g. 32 for quarterly data, 96 for montly data). 
                                        size_t K,         ///< [in] is the number of points(aka terms) to use in the approximate optimal filter. If missing, a default value of 12 is assumed 
                                        BOOL drift,       ///< [in] is a logical value: FALSE if no drift in time series (default), TRUE if drift in time series. 
                                        BOOL unitroot,    ///< [in] is a logical value: FALSE if no unit-root is in time series (default), TRUE if unit-root is in time series. 
                                        WORD retTYpe      ///< [in] is the integer enumeration for the filter output: (1= trend component (default), 2=cyclical component, 3=noise component) 
                                        );


  ///@}


  /*!
  * \name Portfolio Analysis
  * \brief 
  * @{
  */
  /// \brief compute the portfolio equivalent returns
  /*! 
  *   \brief Calculates the portfolio equivalent return. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful (see \ref SFMacros.h) 
  *   \sa NDK_PORTFOLIO_VARIANCE(), NDK_PORTFOLIO_COVARIANCE()
  */
  int  __stdcall NDK_PORTFOLIO_RET(double* weights, size_t nAssets, double* returns, double* ret);

  /*! 
  *   \brief Calculates the overall portfolio variance (volatility squared). 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful (see \ref SFMacros.h) 
  *   \sa NDK_PORTFOLIO_RET(), NDK_PORTFOLIO_COVARIANCE()
  */
  int  __stdcall NDK_PORTFOLIO_VARIANCE(double* weights, size_t nAssets, double** covar, double* variance);

  /*! 
  *   \brief Calculates the covariance between two portfolios. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation is unsuccessful (see \ref SFMacros.h) 
  *   \sa NDK_PORTFOLIO_RET(), NDK_PORTFOLIO_VARIANCE()
  */
  int  __stdcall NDK_PORTFOLIO_COVARIANCE(double* weights1, double* weights2, size_t nAssets, double** covar, double* retVal);

  ///@}


  /*!
  * \name Utilities
  *  
  * @{
  */
  /*! 
  *   \brief estimate the value of the function represented by (x,y) data set at an intermediate x-value. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED   Operation unsuccessful (see \ref SFMacros.h)
  *   \sa NDK_WMA(), NDK_EWMA()
  */
  int __stdcall	NDK_INTERPOLATE(double* X,      ///< [in] is the x-component of the input data table (a one dimensional array)
                                size_t Nx,      ///< [in] is the number of elements in X
                                double* Y,      ///< [in] is the y-component of the input data table (a one dimensional array)
                                size_t Ny,      ///< [in] is the number of elements in Y  
                                double* XT,     ///< [in] is the desired x-value(s) to interpolate for (a single value or a one dimensional array).
                                size_t Nxt,     ///< [in] is the number of elements in XT
                                WORD  nMethod,  ///< [in] is the interpolation method (1=Forward Flat, 2=Backward Flat, 3=Linear, 4=Cubic Spline). 
                                                ///   1. Forward Flat
                                                ///   2. Backward Flat
                                                ///   3. Linear 
                                                ///   4. Cublic Spline
                                BOOL extrapolate, ///< [in]  sets whether or not to allow extrapolation (1=Yes, 0=No). If missing, the default is to not allow extrapolation
                                double* YVals,  ///< [out] is the output buffer to store the interpolated values
                                size_t Nyvals   ///< [in] is the number of elements in YVals (must equal to Nxt).
                                );

  /*! 
  *   \brief Query & retrieve NumXL SDK environment information 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, NDK_Init()
  */
  int   __stdcall NDK_INFO(int nRetType,    ///< [in] is a key/identifier to select the desired output
                                            ///   1. Version Number (default
                                            ///   2. Release
                                            ///   3. License Key
                                            ///   4. License Level
                                            ///   5. License Expiry Date
                                            ///   6. Installation Path
                                            ///   7. Data (e.g. Log-file) Path
                                            ///   8. Computer ID(unique identifier)
                           LPTSTR szMsg,    ///< [out]  The buffer that will receive the return value
                           int nSize        ///< [inout] maximum number of characters to copy to the buffer.
                           );
  /*! 
  *   \brief write a log message to the logging system 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLogger.h, SFLOG_LogMsg()
  */
  int   __stdcall NDK_MSG(  int nRetCode, ///< [in] is the log level (1=trace, 2=Debug, 3=Info, 4=Warn, 5=Error, 6=Fatal Error)
                            LPTSTR pMsg,  ///< [in] is the log message
                            size_t nSize  ///< [in] us the number of characters in pMsg
                            );


  /*!
  *   \brief set the seed value of the random number generator
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFSDK.h
  */
  int   __stdcall NDK_RNG_SEED(ULONG ulSeed    ///< [in] is the new seed value for the random number generator
                              );

  /*! 
  *   \brief Locate and return the full path of the default editor (e.g. notepad) in the system 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, NDK_Init()
  */
  int   __stdcall NDK_DEFAULT_EDITOR (LPTSTR szFullPath, ///< [out]  is the buffer that will receive the return value
                                      size_t* nSize      ///< [inout] is the maximum number of characters to copy to the buffer.
                                      );


  /*! 
  *   \brief Returns the n-th token/substring in a string after splitting it using a given delimiter 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa NDK_REGEX_REPLACE(), NDK_REGEX_MATCH()
  */
  int  __stdcall NDK_TOKENIZE (LPCTSTR szTxt,     ///< [in] is the input string to match for. 
                               LPCTSTR szDelim,   ///< [in] is the character to use for splitting the string. If missing, comma (,) is used. 
                               short nOrder,      ///< [in] is the order of the token to return, where first = 1, second = 2,..., and last = -1. If missing, the first token is returned
                               LPTSTR pRetVal,    ///< [out] is the n-th token/substring in a string
                               size_t nSize       ///< [in] is the number of characters in pRetVal buffer
                               );
  /*! 
  *   \brief Returns TRUE if the string matches the regular expression expressed 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa NDK_REGEX_REPLACE(), NDK_TOKENIZE()
  */
  int  __stdcall NDK_REGEX_MATCH( LPCTSTR szLine,     ///< [in] is the input string to match for.
                                  LPCTSTR szPattern,  ///< [in] is the regular expression (regex PERL-style) to match the input string with (e.g. ^Thi[sS].*$). 
                                  BOOL ignoreCase,    ///< [in] is a flag to instruct the function to ignore the letter-case in the string
                                  BOOL partialOK,     ///< [in] is a flag/switch to indicate whether a substring or a partial match (search) is permitted or to only consider full-string match.
                                  BOOL* bMatch        ///< [out] is the return value of the match.
                                  );

  /*! 
  *   \brief Returns the modified string after performing match/replace on the given string.  
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa NDK_REGEX_REPLACE(), NDK_TOKENIZE()
  */
  int  __stdcall NDK_REGEX_REPLACE(LPCTSTR szLine,  ///< [in] is the input string to process. 
                                  LPCTSTR szKey,    ///< [in] is the regular expression (PERL-style) (e.g. "^\d\w{1,2}.*$"). 
                                  LPCTSTR szValue,  ///< [in] is the value to replace the match with. If missing or omitted, an empty string is used
                                  BOOL ignoreCase,  ///< [in] is a flag to instruct the matching function whether to ignore letter-case. If missing, ignore_case is set to TRUE
                                  BOOL global,      ///< [in] is a flag to instruct the function whether to match and replace the first occurence (FALSE) or all the matches (TRUE). 
                                  LPTSTR pRetVal,   ///< [out] is the modified string after replacement
                                  size_t nSize      ///< [in] is the size of the output buffer (pRetVal)
                                  );
  /*! 
  *   \brief calculates the value of the regression function for an intermediate x-value.   
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa NDK_TREND(), NDK_DETREND()
  */
  int __stdcall	NDK_REGRESSION( double* X,          ///< [in] is the x-component of the input data table (a one dimensional array).
                                size_t nX,          ///< [in] is the number of elements in X.
                                double* Y,          ///< [in] is the y-component (i.e. function) of the input data table (a one dimensional array).
                                size_t nY,          ///< [in] is the number of elements in Y
                                WORD  nRegressType, ///< [in] is the model description flag for the trend function (1 = Linear (default), 2 = Polynomial, 3 = Exponential, 4 = Logarithmic, 5 = Power). 
                                WORD  POrder,       ///< [in] is the polynomial order. This is only relevant for a polynomial type of trend and is ignored for all others. If missing, POrder = 1.
                                double intercept,   ///< [in] is the constant or the intercept value to fix (e.g. zero). If missing (NaN), an intercept will not be fixed and is computed normally.
                                double target,      ///< [in] is the desired x-value to calculate regression value for (a single value). 
                                WORD nRetType,      ///< [in] is a switch to select the return output (1 = Forecast value (default), 2 = Upper limit, 3 = Lower Limit, 4 = R-Squared). 
                                double alpha,       ///< [in] is the statistical significance or confidence level (i.e. alpha). If missing or omitted, an alpha value of 5% is assumed
                                double* retVal      ///< [out] is the calculated value
                                );
  ///@}

}
/// @}