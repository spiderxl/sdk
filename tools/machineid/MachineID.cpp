// MachineID.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "SFLogger.h"
#include "SFMacros.h"
#include "SFLUC.h"
#include "SFDBM.h"
#include "SFSDK.h"



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

  std::wstring szAppName(TEXT("TestApp"));

 // (1) Retrieve the machine ID
  size_t nLen = 100;
  wmemset(szVersion, TCHAR(0x00), nLen);

  nRet = SFLUC_MACHINEID( szVersion, &nLen);
  if( nRet >= NDK_SUCCESS)
  {
    std::wcout << TEXT("Machine Id:") << szVersion << std::endl;
  }
  else
  {
    std::wcout << TEXT("Error in retrieving the machine Id: <Error>") << std::endl;
  }

	return 0;

  std::cout<<"Hello World" << std::endl;
}

