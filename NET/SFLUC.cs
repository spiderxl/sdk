/**
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
  enum SFLUC_RETCODE
  {
    SFLUC_SUCCESS = 0,   // SUCCESS
    SFLUC_MISSING_LICENSE_KEY =  11,   // WARNING: The product license ket is invalid
    SFLUC_INACTIVE_LICENSE_KEY=  13,   // WARNING: The license key has yet to be activated
    SFLUC_EXPIRED_LICENSE_KEY =  14,   // WARNING: The license key has expired
    SFLUC_SKIP_INIT           =  105,  // WARNING: The DLL is already initialize, skipping !
    SFLUC_EXPIRED_KEY         =  110,  // WARNING: License key is expired, running in Lite mode
    SFLUC_KEY_IN_GRACE_PEROD  =  1000,
    SFLUC_KEY_IN_TRIAL_PEROD  =  1005,
    SFLUC_KEY_NOT_IN_TRIAL_PEROD = 1010,
    SFLUC_PERP_KEY_ACTIVE     =  1015,
    SFLUC_PERP_KEY_INACTIVE   =  1020,
    SFLUC_SUB_KEY_ACTIVE      =  1025,
    SFLUC_SUB_KEY_INACTIVE    =  1030,

    
    // Error codes Map
    SFLUC_FAILED        =   -1,       // FAILED: Internal error occured
    SFLUC_UNINITIALIZED =   -2,       // FAILED: The API NDK_INIT has not yet been called
    SFLUC_MISSING_CONF  =   -3,       // FAILED: The configuration file is missing
    SFLUC_BAD_CONF      =   -4,       // FAILED: Access denied or corrupted file
    SFLUC_MISSING_KEY   =   -5,       // FAILED: Access denied or corrupted file
    SFLUC_INVALID_KEY   =   -6,       // FAILED: Access denied or corrupted file
    SFLUC_INVALID_CODE  =   -6,       // FAILED: Access denied or corrupted file
    SFLUC_INVALID_ARG   =   -7,       // FAILED: Passed argument is null or not big enough
    SFLUC_INVALID_LICENSE_KEY  = -12, // FAILED: The product license ket is invalid
  }

  class SFLUC
  {
    const string DLLName = "SFLUC.dll";

    // SFLogger APIs
    [DllImport("SFLog.dll", EntryPoint = "#100")]
    public static extern int SFLUC_Init(string szAppName, string szLogDir, Boolean bEnableGracePeriod);

    [DllImport("SFLog.dll", EntryPoint = "#105")]
    public static extern int SFLUC_Shutdown();

    [DllImport("SFLog.dll", EntryPoint = "#110")]
    public static extern int SFLOG_LogMsg(int nLevel, string szFilename, string szFuncName, string szFuncSig, int nLineNo, string szMsg);
  }
}
