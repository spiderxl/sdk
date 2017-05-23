﻿/**
*  (c) 2007-2013 Spider Financial Corp.
*  All rights reserved.
*  
*  $Revision: 15258 $
*  $Date: 2016-05-03 11:38:24 -0500 (Tue, 03 May 2016) $
*/
using System;
using System.Runtime.InteropServices;


namespace NumXL
{
  enum SFSDK_RETCODE
  {
    // Error codes Map
    NDK_SUCCESS  = 0,     // SUCCESS

    // Warnings
    NDK_SKIP_INIT = 105,  // WARNING: The DLL is already initialize, skipping !
    NDK_RET_NAN = 100,    // WARNING: The function returns an invalid (i.e. missing) value

    // Error Codes 
    NDK_FAILED      =          -1,  // FAILED: Internal error occured
    NDK_SDK_UNINITIALIZED  =   -2,  // FAILED: The API NDK_INIT has not yet been called
    NDK_LOW_LICENSE_LEVEL  =   -3,  // FAILED: The required license level is not met by current license
    NDK_UNSUPPORTED     =      -4,  // FAILED: The required operation is not currently supported

    NDK_INVALID_ARG      =     -5,  // FAILED: an input argument with unexpected or invalid value.
    NDK_LENGTH_ERROR     =     -6,  // FAILED: The user's buffer is not big enough or Insufficient input data
    NDK_INVALID_VALUE    =     -7,  // FAILED: Invalid value of an argument
    NDK_MISSING_CONF     =     -8,  // FAILED: The configuration file is missing
    NDK_CONF_DATAPATH_INVALID  = -9,  // FAILED: Invalid datapath value in the configuration file
    NDK_CONF_PRODID_INVALID   = -10, // FAILED: Invalid value for [GLOBALS][PRODUCTID] entry in the conf file
    NDK_MISSING_LICENSE_KEY   = -11, // FAILED: The product license ket is invalid
    NDK_INVALID_LICENSE_KEY   = -12, // FAILED: The product license ket is invalid
    NDK_INACTIVE_LICENSE_KEY  = -13, // FAILED: The license key has yet to be activated
    NDK_INVALID_KEY_CODE      = -14, // FAILED: The license key and code are not valid
    NDK_EXPIRED_LICENSE_KEY   = -15, // FAILED: The license key has expired
    NDK_LOG_INIT_FAILED       = -16, // FAILED: The logging system failed during initialization, check the configuration settings
    NDK_EMPTY_TIME_SERIES     = -17, // FAILED: number of non-missing values is zero
    NDK_ZERO_INVALID_VARIANCE = -18, // FAILED: number of non-missing values is zero

    NDK_CALIBRATION_ERROR     = -19, // FAILED: The optimizer failed to converge to a unique solution.
    NDK_INVALID_MODEL         = -20 // FAILED: The model's parameters values did not pass the stability test.
  }

  class SFSDK
  {
    const string DLLName = "SFSDK.dll";

    // SFLogger APIs
    [DllImport(DLLName, EntryPoint = "#100")]
    public static extern int NDK_Init(string szAppName, string szKey, string szActCode, string szLogDir);

    [DllImport(DLLName, EntryPoint = "#105")]
    public static extern int NDK_Shutdown();
  }






}
