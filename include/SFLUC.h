/**
*  \addtogroup SFLUC 
*  @{
*  \file SFLUC.h
* 
*  \copyright © Spider Financial Corp - All rights reserved.
*       Unauthorized copying of this file, via any medium is strictly prohibited
*  	    Proprietary and confidential
*  \brief  header file for the public API of SFLUC library 
*  \details  License system support for NumXL SDK
*  \author Spider Financial Corp
*  \version 1.62
*  $Revision: 15834 $
*  $Date: 2016-08-25 13:54:04 -0500 (Thu, 25 Aug 2016) $
*/
#pragma once

// Functions API
extern "C"
{
  /// \name Initialzation APIs
  /// @{
  /*! 
  *   \brief initialize the SFLUC Library
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_Shutdown()
  */
  int   __stdcall SFLUC_Init( LPCTSTR szAppName,             ///<  [in] application name (user-defined), but must match the configuration base filename
                              LPCTSTR szLogDir,              ///<  [in, optional] absolute path of the log file directory. If NULL, LUC uses the default temp directory in the current user's profile
                              BOOL bEnableGracePeriod       ///<  [in] allow program to run for 7 days in the case the license key is missing
                              );                            

  /*! 
  *   \brief shutdown and release all resources used by SFLUC DLL
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_Init()
  */
  int   __stdcall SFLUC_Shutdown(void);                                                   
  /// \example luc_init.cpp

  /// @}


  /*! 
  *   \brief Examine the license key and activation code in the current system
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_Init()
  */
  int   __stdcall SFLUC_CHECK_LICENSE(void);


  /*! 
  *   \brief Query and retrieve the license level of the active license key
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_LICENSE_LEVEL()
  */
  int   __stdcall SFLUC_LICENSE_LEVEL(int* level /*! [out] license level (1=limited, 2=Pro) */);

  /*! 
  *   \brief Query and retrieve the unique identifier of the local machine
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_CHECK_LICENSE()
  */
  int   __stdcall SFLUC_MACHINEID(  LPTSTR szBuffer,   ///< [out]  Machine or Host Id
                                    size_t* nLen      ///< [inout] maximum number of characters to copy to the buffer. 
                                    );

  /*! 
  *   \brief Query and retrieve the current license key
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_LICENSE_KEY(),SFLUC_ACTIVATION_CODE()
  */
  int   __stdcall SFLUC_LICENSE_KEY(LPTSTR szBuffer,     ///< [out]  The buffer that will receive the License key
                                    size_t* nLen        ///< [inout] maximum number of characters to copy to the buffer.
                                    );

  /*! 
  *   \brief Query and retrieve the expiration date of the curent license key
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_ACTIVATION_CODE()
  */
  int   __stdcall SFLUC_LICENSE_KEY_EXPIRY(unsigned long* expiry /*! [out] expiration date expressed as number of days since January 1st, 1970 */);

  /*! 
  *   \brief Query and retrieve the activation code of the curent license key
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFLUC_Init()
  */
  int   __stdcall SFLUC_ACTIVATION_CODE(LPTSTR szCode,   ///< [out]  The buffer that will receive the activation code
                                        size_t* nLen    ///< [inout] maximum number of characters to copy to the buffer (minimum 32-character).
                                        );
  /*! 
  *   \brief Query and retrieve the activation status of curent license key
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Warning or Error code
  *   \sa SFMacros.h, SFLUC_LICENSE_STATUS(),SFLUC_LICENSE_KEY()
  */
  int   __stdcall SFLUC_LICENSE_STATUS(void);

  /*! 
  *   \brief Query and retrieve the expiration date of a given license key and activation code
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Warning or Error code
  *   \sa SFMacros.h, SFLUC_CHECK_KEYCODE()
  */
  int   __stdcall SFLUC_LICENSE_EXPIRY( LPCTSTR szKey,               ///< [in] License key
                                        LPCTSTR szActivationCode,    ///< [in] Activation code
                                        unsigned long* expiry       ///< [out] expiration date expressed as number of days since January 1st, 1970 
                                        );

  /*! 
  *   \brief Query and retrieve the expiration date and license level of a license key and activation code
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Warning or Error code
  *   \sa SFMacros.h, SFLUC_LICENSE_EXPIRY(), SFLUC_LICENSE_LEVEL()
  */
  int   __stdcall SFLUC_CHECK_KEYCODE(LPCTSTR PDKey,                 ///< [in] Product key (i.e. 31223-200-162)
                                      LPCTSTR szKey,                 ///< [in] License key
                                      LPCTSTR szActCode,             ///< [in] Activation code
                                      ULONG* ulExpiry,              ///< [out] expiration date expressed as number of days since January 1st, 1970
                                      int* nLevel                   ///< [out] Effective license level: 1=Limited, 2=Full/Pro
                                      );



  /*! 
  *   \brief Query and retrieve the latest version available
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Warning or Error code
  *   \sa SFMacros.h, SFLUC_SERVICEDATE()
  */
  int  __stdcall SFLUC_UPDATEVERSION(LPCTSTR szLicenseKey,           ///< [in] License key
                                      LPCTSTR szFileVersion,         ///< [in] is the long file version (1.XX.XXXX.X)
                                      LPTSTR updateVersion,          ///< [out] is the available most recent version available
                                      size_t* pVerSize,             ///< [inout] is the original size of the output buffer
                                      LPTSTR downloadURL,            ///< [out] is the download URL version
                                      size_t* pURLSize              ///< [inout] is the size of "downloadURL" buffer
                                      );

  /*! 
  *   \brief Query and retrieve the service date for a given license
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Warning or Error code
  *   \sa SFLUC_UPDATEVERSION(), SFLUC_LICENSE_LEVEL()
  */
  int  __stdcall SFLUC_SERVICEDATE(LPCTSTR szLicenseKey,             ///< [in] is the license key
                                   LPLONG serviceDate               ///< [out] is the serial date number of the service/support expiry date
                                   );


  /*!
  *   \brief Query and retrieve the recent activation code for a given license
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Warning or Error code
  *   \sa SFLUC_UPDATEVERSION(), SFLUC_LICENSE_LEVEL()
  */
  int  __stdcall SFLUC_ACTIVATE_LICENSE(LPCTSTR szLicenseKey,       ///< [in] License key
                                        LPCTSTR szEmail,            ///< [in] E-Mail address
                                        LPCTSTR szProdCode,         ///< [in] product code (e.g. 3223-200)
                                        LPTSTR szActivationCode,    ///< [out] Activation code
                                        size_t* puSize              ///< [in,out] Length of the Activation code buffer, and returns number of character used.
                                        );
}
/// @}