/**
*  \addtogroup SFMSG 
*  @{
*  \file SFMSG.h
* 
*  \copyright © Spider Financial Corp - All rights reserved.
*  Unauthorized copying of this file, via any medium is strictly prohibited
*  	Proprietary and confidential

*  \brief  header file for the public API of SFLUC library 
*  \details  License system support for NumXL SDK
*  \copyright (c) 2007-2014 Spider Financial Corp.
*             All rights reserved.
*  \author Spider Financial Corp
*  \version 1.62
*  $Revision: 15310 $
*  $Date: 2016-05-05 16:48:43 -0500 (Thu, 05 May 2016) $
*/

#pragma once

extern "C"
{
  /*! 
  *   \brief initialize the SFMSG Library
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Shutdown(), SFMSG_MSG()
  */
  int   __stdcall SFMSG_Init( LPCTSTR szAppName,    ///<  [in] the application name (e.g. NumXL)
                              DWORD lcid            ///<  [in] MS Locality ID 
                            );                            


  /*! 
  *   \brief Cleanup the SFMSG Library
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Shutdown()
  */
  int   __stdcall SFMSG_Shutdown(void);                            


  /*!
  *   \brief query the current LCID
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Reset()
  */
  int __stdcall SFMSG_LCID(LPDWORD plcid);

  /*!
  *   \brief examine whether the given LCID is installed
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Reset()
  */
  int __stdcall SFMSG_LCID_SUPPORTED(DWORD lcid, LPBOOL pbExist);


  /*!
  *   \brief convert the given LCID to neutral LCID (no sub-language or sort order)
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Reset()
  */
  int __stdcall SFMSG_NEUTRAL_LCID(LPDWORD pSupportedLCID);



  /*!
  *   \brief Return the full path of the locale resources folder on user's filesystem
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Reset()
  */
  int   __stdcall SFMSG_LCID_PATH(DWORD lcid, LPTSTR  szPath, size_t* pSize);

  /*! 
  *   \brief Switch the language library to a different one
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Shutdown()
  */
  int   __stdcall SFMSG_Reset(DWORD lcid);


  /*! 
  *   \brief initialize the SFMSG Library
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFMSG_Shutdown()
  */
  int   __stdcall SFMSG_MSG( DWORD resId,      ///<  [in] Resource ID
                             LPTSTR szLogDir,  ///<  [out] output buffer to return the designated string
                             size_t* pSize     ///<  [inout] the size of the buffer, and upon return, the number of bytes copied
                            );                            


}
/// @}