/**
*  \addtogroup SFLOG 
*  @{
*  \file SFLogger.h
* 
*  \copyright (c) 2007-2016 Spider Financial Corp.
*  All rights reserved.
*  \brief  header file for the public API of SFLOG library 
*  \details  logging system support for NumXL SDK
*  \copyright (c) 2007-2014 Spider Financial Corp.
*             All rights reserved.
*  \author Spider Financial Corp
*  \version 1.62
*  $Revision: 15278 $
*  $Date: 2016-05-03 18:08:24 -0500 (Tue, 03 May 2016) $
*/
#pragma once


#define SFLOG_ALL   0   ///< Enable all logging messages (info, debug, trace, warning and error)
#define SFLOG_TRACE 1   ///< Enable trace level logging: trace, debug, info, warning, error and fatal error messages
#define SFLOG_DEBUG 2   ///< Enable debug level logging: debug, info, warning, error and fatal error messages
#define SFLOG_INFO  3   ///< Enable information level logging: info, warning, error, and fatal error messages
#define SFLOG_WARN  4   ///< Enable warning level logging: warning, error and fatal error messages
#define SFLOG_ERROR 5   ///< Enable error level logging: error and fatal error messages
#define SFLOG_FATAL 6   ///< Enable fatal or critical level logging.
#define SFLOG_OFF   7   ///< Disable all logging messages



// Functions API
extern "C"
{
  /// \name Initialization APIs
  /// @{
  /*! 
  *   \brief Initialize the logging system for NumXL SDK 
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLOG_Shutdown()
  */
  int   __stdcall SFLOG_Init( LPCTSTR szAppName,   ///<  [in] is the application name (user-defined), but must match the configuration base filename
                              LPCTSTR szLogDir     ///<  [in, optional] is the full (absolute) path of the log file directory. If missing (i.e. NULL), SFLOG_Init uses the default temp directory in the current user's profile
                              );                  

  /*! 
  *   \brief Shutdown and release resources allocated by \b logging system
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLOG_Init()
  */
  int   __stdcall SFLOG_Shutdown(void);           

  /// \example log_init.cpp

  /// @}

  /*! 
  *   \brief query the current logging level in the SDK
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLOG_Init()
  */
  int   __stdcall SFLOG_LogMsg( int nLevel,         ///< logging level (i.e. debug, info, trace, error, etc.)
                                LPCSTR szFilename,  ///< the source filename that triggers this logging message
                                LPCSTR szFuncName,  ///< the function name from which this log is triggered from
                                LPCSTR szFuncSig,   ///< the function sugnature (i.e. mangled name)
                                int nLineNo,        ///< Line number in the source file
                                LPCTSTR szMsg       ///< Error message
                                );
  /*! 
  *   \brief log a message into the logging system
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLOG_SETLEVEL()
  */
  int   __stdcall SFLOG_GETLEVEL(int* nLevel /*!< [out] current logging level */);
  /*! 
  *   \brief set the new logging level in the SDK
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLOG_GETLEVEL()
  */
  int   __stdcall SFLOG_SETLEVEL(int nLevel /*!< [in] new logging level*/);
}

/// @}