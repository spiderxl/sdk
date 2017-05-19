// Smoothing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SFLogger.h"
#include "SFMacros.h"
#include "SFLUC.h"
#include "SFDBM.h"
#include "SFSDK.h"

// passengers data of the international airline problem (Box-Jenkins 1955)
double data[]={112,118,132,129,121,135,148,148,136,119,104,118,
              115,126,141,135,125,149,170,170,158,133,114,140,
              145,150,178,163,172,178,199,199,184,162,146,166,
              171,180,193,181,183,218,230,242,209,191,172,194,
              196,196,236,235,229,243,264,272,237,211,180,201,
              204,188,235,227,234,264,302,293,259,229,203,229,
              242,233,267,269,270,315,364,347,312,274,237,278,
              284,277,317,313,318,374,413,405,355,306,271,306,
              315,301,356,348,355,422,465,467,404,347,305,336,
              340,318,362,348,363,435,491,505,404,359,310,337,
              360,342,406,396,420,472,548,559,463,407,362,405,
              417,391,419,461,472,535,622,606,508,461,390,432,
              444,416,472,499,497,579,667,657,557,492,425,481};

using namespace std;

int test_wma(void);
int test_sesmth(void);
int test_desmth(void);
int test_lesmth(void);
int test_tesmth(void);


int _tmain(int argc, _TCHAR* argv[])
{
  // Let's get the library version number
  TCHAR szVersion[100];
  int nRet=-1;

  std::cout  << "(c) 2009-2016 Spider Financial Corp." << std::endl;
  std::cout  << "All rights reserved." << std::endl;
  std::cout  <<  std::endl;
  std::cout  <<  "Phone:    (312) 324-0366" << std::endl;
  std::cout  <<  "E-Mail:   support@numxl.com" << std::endl;
  std::cout  <<  "Website:  www.numxl.com" << std::endl;
  std::cout  <<  std::endl;
  std::cout << "*******************************************************" << std::endl;

  wmemset(szVersion, TCHAR(0x00), 100);

  // (1) Initialize the NumXL SDK environment
  std::wstring szAppName(L"TestApp");

  // log/data directory NULL == Use user's temp folder in his/her profile
  nRet = NDK_Init(szAppName.c_str(), NULL, NULL ,NULL /*Log Directory*/);
  if( nRet >= NDK_SUCCESS)
  {
    std::cout  <<  "<===== (1) Passed -- NDK_Init: Num SDK initialization =====>" << std::endl;
    // Print out the environment
    // (1) Version number
    nRet = NDK_INFO(1, szVersion, 100);
    if( nRet == NDK_SUCCESS)
    {
      std::wcout << TEXT("NumXL SDK version:") << szVersion << std::endl;

      // (2) Release Name
      wmemset(szVersion, TCHAR(0x00), 100);
      nRet = NDK_INFO(2, szVersion, 100);
      std::wcout << L"NumXL SDK Release:" << szVersion << std::endl;

      // (3) License key
      wmemset(szVersion, TCHAR(0x00), 100);
      nRet = NDK_INFO(3, szVersion, 100);
      std::wcout << L"NumXL SDK License Key:" << szVersion << std::endl;

      // (4) License key
      wmemset(szVersion, TCHAR(0x00), 100);
      nRet = NDK_INFO(4, szVersion, 100);
      std::wcout << L"NumXL SDK License Key Level:" << szVersion << std::endl;

      // (5) License key
      wmemset(szVersion, TCHAR(0x00), 100);
      nRet = NDK_INFO(5, szVersion, 100);
      std::wcout << L"NumXL SDK License key expiry date:" << szVersion << std::endl;

      // (6) Installation path
      wmemset(szVersion, TCHAR(0x00), 100);
      nRet = NDK_INFO(6, szVersion, 100);
      std::wcout << L"NumXL SDK is installed at:" << szVersion << std::endl;

      // (7) data/log path
      wmemset(szVersion, TCHAR(0x00), 100);
      nRet = NDK_INFO(7, szVersion, 100);
      std::wcout << L"NumXL SDK logs are found in:" << szVersion << std::endl;
    }
    std::cout  <<  std::endl;

    // test the wma functions
    test_wma();


    // test sesmth function
    test_sesmth();

    // test desmth function
    test_desmth();

    // test lesmth function
    test_lesmth();

    // test tesmth function
    test_tesmth();

    nRet = NDK_Shutdown();
    if(nRet == NDK_SUCCESS)
    {
      std::cout  <<  "<===== (*) Passed -- NDK_Shutdown: Num SDK shutdown  =====>" << std::endl;
    }
  }
  else
  {
    std::cout  <<  "<===== (1) Failed -- NDK_Init: NumXL SDK initialization =====>" << std::endl;
    switch(nRet)
    {
    case NDK_MISSING_CONF:          // FAILED: The configuration file is missing
      std::cout << "The configuration file is missing! (<myapp>.conf)" << std::endl;
      break;
    case NDK_CONF_DATAPATH_INVALID: // FAILED: Invalid datapath value in the configuration file
      std::cout << "Invalid [Globals][datapath] value in the configuration file (<myapp>.conf)" << std::endl;
      break;
    case NDK_CONF_PRODID_INVALID:   // FAILED: Invalid value for [GLOBALS][PRODUCTID] entry in the conf file
      std::cout << "Invalid value for [GLOBALS][PRODUCTID] entry in the conf file (<myapp>.conf)" << std::endl;
      break;
    case NDK_MISSING_LICENSE_KEY:   // FAILED: The product license ket is invalid
      std::cout << "The product license key is missing (NumXL.LIC)" << std::endl;
      break;
    case NDK_INVALID_LICENSE_KEY:   // FAILED: The product license ket is invalid
      std::cout << "The product license ket is invalid (NumXL.LIC)" << std::endl;
      break;
    case NDK_INACTIVE_LICENSE_KEY:  // FAILED: The license key has yet to be activated
      std::cout << "The license key has yet to be activated (NumXL.LIC)" << std::endl;
      break;
    case NDK_EXPIRED_LICENSE_KEY:   // FAILED: The license key has expired
      std::cout << "The license key has expired (NumXL.LIC)" << std::endl;
      break;
    case NDK_LOG_INIT_FAILED:       // FAILED: The logging system failed during initialization, check the configuration settings
      std::cout << "The logging system failed during initialization, check the configuration settings (<myapp>.conf)" << std::endl;
      break;
    default:
      std::cout << "Unknown Error, please contact your support personnel" << std::endl;
      break;
    }
  }// End else

  std::cout << "*******************************************************" << std::endl;
  nRet = NDK_INFO(8, szVersion, 100);
  std::wcout << L"Your computer Machine ID is: " << szVersion << std::endl;
  std::cout << "Please, present the license key and the Machine ID to your NumXL support personnel" << std::endl;

  return 0;
}

int test_wma(void)
{
  double weights[]={5};
  double retVal= -1;
  int nRet=-1;
    

  nRet = NDK_WMA(data,144, true, weights, 1, 0, &retVal); 

  if(nRet == NDK_SUCCESS)
  {
    std::cout  <<  "<===== (2) Passed -- NDK_WMA Testing =====>" << std::endl;
  }
  else
  {
    std::cout  <<  "<===== (2) Failed -- NDK_WMA Testing =====>" << std::endl;
  }

  return nRet;
}


int test_sesmth(void)
{
  double retVal= -1;
  int nRet=-1;

  double alpha=0.50f;

  nRet = NDK_SESMTH(data,144, true,&alpha, 0, true /*optimze*/, &retVal);
  if(nRet == NDK_SUCCESS)
  {
    std::cout  <<  "<===== (3) Passed -- NDK_SESMTH Testing =====>" << std::endl;
  }
  else
  {
    std::cout  <<  "<===== (3) Faield -- NDK_SESMTH Testing =====>" << std::endl;
  }

  return nRet;
}


int test_desmth(void)
{
  double retVal= -1;
  int nRet=-1;

  double alpha=0.333f;
  double beta=0.333f;

  nRet = NDK_DESMTH(data,144, true,&alpha, &beta, 0, true /*optimze*/, &retVal);
  if(nRet == NDK_SUCCESS)
  {
    std::cout  <<  "<===== (4) Passed -- NDK_DESMTH Testing =====>" << std::endl;
  }
  else
  {
    std::cout  <<  "<===== (4) Failed -- NDK_DESMTH Testing =====>" << std::endl;
  }

  return nRet;
}


int test_lesmth(void)
{
  double retVal= -1;
  int nRet=-1;

  double alpha=0.333f;

  nRet = NDK_LESMTH(data,144, true,&alpha, 0, true /*optimze*/, &retVal);
  if(nRet == NDK_SUCCESS)
  {
    std::cout  <<  "<===== (5) Passed -- NDK_LESMTH Testing =====>" << std::endl;
  }
  else
  {
    std::cout  <<  "<===== (5) Failed -- NDK_LESMTH Testing =====>" << std::endl;
  }

  return nRet;
}


int test_tesmth(void)
{
  double retVal= -1;
  int nRet=-1;

  double alpha=0.333f;
  double beta=0.333f;
  double gamma=0.333f;
  int seasonLen=12;
  

  nRet = NDK_TESMTH(data,144, true,&alpha,&beta,&gamma, seasonLen, 0, true /*optimze*/, &retVal);
  if(nRet == NDK_SUCCESS)
  {
    std::cout  <<  "<===== (6) Passed -- NDK_TESMTH Testing =====>" << std::endl;
  }
  else
  {
    std::cout  <<  "<===== (6) Faield -- NDK_TESMTH Testing =====>" << std::endl;
  }

  return nRet;
}


