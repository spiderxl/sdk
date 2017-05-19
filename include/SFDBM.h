/**
* \defgroup SFDBM SFDBM
*   Public APIs to process date, holiday and calendar calculations.
* * @{
*  \file SFDBM.h
*  \brief  header file for SFDBM public APIs 
*  \details  Internal database API calls; used for date, holiday and calendar calculations.
*  \copyright (c) 2007-2014 Spider Financial Corp.
*             All rights reserved.
*  \author Spider Financial Corp
*  \version 1.62
*  $Revision: 15882 $
*  $Date: 2016-09-08 21:19:51 -0500 (Thu, 08 Sep 2016) $
*/
#pragma once

// Functions API
extern "C"
{

  /// \name Initialzation APIs
  /// @{
  /*! 
  *   \brief initialize the SFDBM Library
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_Shutdown()
  */
  int  __stdcall SFDB_Init( LPCTSTR szAppName, ///<  [in] User-defined application name
                            LPCTSTR szKey,     ///<  [in] NumXL License key
                            LPCTSTR szActCode, ///<  [in] Activation code  
                            LPCTSTR szTmpPath, ///<  [in] Temporary files and Logging directory
                            LCID    zLocality  ///<  [in] Locale Id (Assigned by Microsoft) (e.g. en-US=1033, es-ES=1034, etc.)
                            );                


  /*! 
  *   \brief shutdown and release resources used by SFDBM Library
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_Init()
  */
  int  __stdcall SFDB_Shutdown(void); 
  /// \example dbm_rollover.cpp 
  

  ///@}

  /*! 
  *   \brief computed the date after a given a period (e.g. 1w, 1m, 3w, etc.)
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFLUC_Shutdown()
  */
  int __stdcall SFDB_EDATE( LONG argDate,     ///< [in] start date expressed as number of days since 1.1.1970
                            LPCTSTR szPeriod,  ///< [in] description of a period range (e.g. "5-days", "1 month", "1m", "3 w", "-1 year"). 
                            PLONG retVal      ///< [out] the calculated date that falls after the given period.
                            );

  /*! 
  *   \brief Returns the serial number of the n-th weekday in a month.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa FDB_WKDYOrder()
  */
  int __stdcall SFDB_NWKDAY(WORD weekdy,  ///< [in] the weekday (i.e. 1=Sunday, 2=Monday, 3=Tuesday, ..., 7=Saturday) 
                            short order,  ///< [in] the n-th occurence in the month (i.e. 1=First, 2=Second, 3=Third, 4=Fourth and -1=Last). 
                            WORD mnth,    ///< [in] the month in the year expressed as a number (i.e. 1=Jan, 2=Feb, ..., 12=Dec).
                            WORD year,    ///< [in] the target year (2 or 4 digits) (e.g. 99, 2007, 2008, 09, etc.). 
                            PLONG retVal  ///< [out] the calculated serial number of the n-th weekday in a month/year.
                            );

  /*! 
  *   \brief Returns the order of the weekday in the month for a given date. This is the inverse operator of SFDB_NWKDAY().
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_NWKDAY()
  */
  int __stdcall SFDB_WKDYOrder( LONG argDate, ///< [in] is the serial date number that represents the given date
                                short* retVal ///< [out] is the order of the weekday in the month for a given date
                                );

  /*! 
  *   \brief Returns the day of the week corresponding to a date. The day is given as an integer, ranging from 1 (Sunday) to 7 (Saturday), by default..
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_NWKDAY()
  */
  int __stdcall SFDB_WEEKDAY(LONG argDate,          ///< [in] is the serial date number that represents the given date.
                            WORD argReturnType,     ///< [in]  is a number that designates the weekdays coding (or ordering) scheme. If missing, convention=1 (Sun=1,..,Sat=7) is assumed. 
                            LPWORD retVal           ///< [out] is the day of the week corresponding to a date 
                            );

  /*! 
  *   \brief Examines whether the given date falls on a weekend or a holiday (i.e. non-working day), and returns the nearest working business day using a Business Day Convention (BDC).
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_DTADJUST(LONG argDate,         ///< [in] is a serial date number that represents a given date
                              WORD argNextPrev,     ///< [in] is the Business Day Convention (BDC): 1=Following, 2=Following Modified, 3=Preceding, 4=Preceding Modified, 5=Unadjusted (default
                              LPCTSTR holidays,      ///< [in] is a (:_:) separated list of holiday names, calendars, countries or currency
                              LPLONG zDates,        ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970)
                              size_t nSize,         ///< [in] is the number of holiday dates.
                              WORD   wkndNo,        ///< [in] is the weekend number (1-7,11-17). If missing, the western weekend (i.e. 1, "Saturday, Sunday") is used. 
                              LPLONG retVal         ///< [out] is the dates of the nearest business day.
                              );       


  /*! 
  *   \brief Examines a given date for weekends and holidays (non-working days), and returns FALSE if it falls on a non-working day; otherwise it returns TRUE
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_DTADJUST()
  */
  int __stdcall SFDB_ISWRKDY(LONG argDate,        ///< [in] is a serial date number that represents a given date
                             LPCTSTR holidays,     ///< [in] is a (:_:) separated list of holiday names, calendars, countries or currency
                             LPLONG zDates,       ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970)  
                             size_t nSize,        ///< [in] is the number of holiday dates in zDates.
                             WORD   wkndNo        ///< [in] is the weekend number (1-7,11-17). If missing, the western weekend (i.e. 1, "Saturday, Sunday") is used.
                             );

  /*! 
  *   \brief Returns the number of whole working days between two dates (inclusive). Working days exclude weekends and any date identified as a holiday.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_NETWRKDYS( LONG argStartDate,  ///< [in] is a serial date number that represents start date
                                LONG argEndDate,    ///< [in] is a serial date number that represents finish date
                                LPCTSTR holidays,    ///< [in] is a (:_:) separated list of holiday names, calendars, countries or currency
                                LPLONG zDates,      ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970)  
                                size_t nSize,       ///< [in] is the number of holiday dates in zDates.
                                WORD   wkndNo,      ///< [in] is the weekend number (1-7,11-17). If missing, the western weekend (i.e. 1, "Saturday, Sunday") is used.
                                int* retVal         ///< [out] is the returned number of work days in the given period.
                                );

  /*! 
  *   \brief Returns the serial date number that represents the date that falls after the start date by a given number of working days
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_WORKDAY( LONG argDate,       ///< [in] is a serial date number that represents a given date
                              short days,         ///< [in] is the number of workdays to advance
                              LPCTSTR holidays,    ///< [in] is a (:_:) separated list of holiday names, calendars, countries or currency
                              LPLONG zDates,      ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970)  
                              size_t nSize,       ///< [in] is the number of holiday dates in zDates.
                              WORD   wkndNo,      ///< [in] is the weekend number (1-7,11-17). If missing, the western weekend (i.e. 1, "Saturday, Sunday") is used.
                              LPLONG retVal       ///< [out] is the returned serial date number after a given number of working days.
                              );

  /// \name Holiday APIs
  /// @{
  /*! 
  *   \brief Examine the given code as a valid holiday code
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_FindHLDY()
  */
  int __stdcall SFDB_ISVALIDHLDYCODE(LPCTSTR argCode /*!< [in] is the given holiday code */);

  /*! 
  *   \brief Returns an array of the matching supported holiday codes.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_FindHLDY()
  */
  int __stdcall SFDB_HLDYS( LPCTSTR argHolidays,   ///< [in] is the holiday name/prefix to search for. If missing, the full list of holidays will be returned. 
                            LPTSTR retVal,         ///< [out] is a (:_:) separated list of holiday names.
                            size_t* nLen          ///< [inout] maximum number of characters to copy to the buffer. 
                            );
  
  
  /*! 
  *   \brief Returns the holiday code that falls on the given date
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_FindHLDY(LONG argDate,       ///< [in] is a serial date number that represents a given date
                              LPCTSTR argHolidays, ///< [in] is a (:_:) separated list of holiday codes
                              LPTSTR retVal,       ///< [out] is the holiday code that falls on the given date
                              size_t* nLen        ///< [inout] maximum number of characters to copy to the buffer. 
                              );


  /*! 
  *   \brief Returns the full name of the holiday that corresponds to the given short code
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_HLDYName(LPCTSTR code,      ///< [in] is the given holiday short code
                              LPTSTR retVal,     ///< [out] is the holiday code that falls on the given date
                              size_t* nLen      ///< [inout] maximum number of characters to copy to the buffer.
                              );

  /*! 
  *   \brief Returns the date serial number that represents the holiday in the given year. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_HLDYDate(LONG argDate,       ///< [in] is a serial date number that represents a given date
                              LPLONG zdates,      ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970) 
                              size_t nLen,        ///< [in] is the number of holiday dates.
                              LPCTSTR szHolidays,  ///< [in] is a (:_:) separated list of holiday codes
                              WORD retType,       ///< [in] is a switch to select the return output (1 = next holiday, 2= last holiday). 
                              LPLONG retVal       ///< [out] is the returned serial date number that represents the holiday.
                              );


  /*! 
  *   \brief Returns TRUE when the start date falls on a holiday.
  *   \return status code of the operation
  *   \retval NDK_TRUE  given date falls on holiday
  *   \retval NDK_FALSE given date does not fall on holiday
  *   \retval Else      Error code (see \ref SFMacros.h)
  *   \sa SFDB_HLDYDate()
  */
  int __stdcall SFDB_ISHLDY(LONG argDate,       ///< [in] is a serial date number that represents a given date
                            LPLONG zdates,      ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970)  
                            size_t nLen,        ///< [in] is the number of holiday dates.
                            LPCTSTR szHolidays  ///< [in] is a (:_:) separated list of holiday codes 
                            );                  


  /*! 
  *   \brief Returns an array of serial date numbers that represent observed holidays between the two given dates.
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_HLDYDates(LONG argStartDate, ///< [in] is a serial date number that represents start date 
                               LONG argEndDate,   ///< [in] is a serial date number that represents finish date
                               LPLONG zdates,     ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970)  
                               size_t nLen,       ///< [in] is the number of holiday dates.
                               LPCTSTR szHolidays, ///< [in] is a (:_:) separated list of holiday codes 
                               LPLONG retVal,     ///< [out] is an array for the holiday dates 
                               size_t* nSize      ///< [inout] is the maximum number of elements in the output array.
                               );
  /// @}


  int __stdcall SFDB_ONEHLDYDates(LONG argStartDate, ///< [in] is a serial date number that represents start date 
                                  LONG argEndDate,   ///< [in] is a serial date number that represents finish date
                                  LPCTSTR szHoliday, ///< [in] is a holiday code (e.g. USA-MLK, CHN-CNY, etc.) 
                                  LPLONG retVal,     ///< [out] is an array for the holiday dates 
                                  size_t* nSize      ///< [inout] is the maximum number of elements in the output array.
    );


  /// \name Weekend APIs
  /// @{
  // Weekend API

  /*! 
  *   \brief examines whether the given code corresponds to valid weekend convention. 
  *   \return status code of the operation
  *   \retval NDK_TRUE - weekend code is valid
  *   \retval NDK_FALSE  - weekend code is invalid
  *   \retval See \ref SFMacros.h for more details.
  *   \sa SFDB_WKNDNo()
  */
  int __stdcall SFDB_ISVALIDWKND(LPCTSTR szCode /*!< [in] is the given weekend code or number*/);


  /*! 
  *   \brief Returns the seven-character string code for a weekend-number (1-7, 11-17). 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_WKNDNo()
  */
  int __stdcall SFDB_WKNDCode(WORD argNumber,   ///< [in]  is the weekend number (1-7, 11-17). 
                              LPTSTR retVal,     ///< [out] is the buffer that will receive the string code
                              size_t* nLen      ///< [inout] is the maximum number of characters to copy to the buffer.
                              );

  /*! 
  *   \brief Returns the weekend-number (1-7 or 11-17) for a given country or a weekend code. 
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_WKNDNo(LPCTSTR argCode,    ///< [in] is the weekend 7-character string code.
                            LPWORD nNo          ///< [out] is the weekend number (1-7, 11-17).
                            );

  /*! 
  *   \brief Returns TRUE if the reference date falls on a (short/long) weekend. 
  *   \return status code of the operation
  *   \retval #NDK_TRUE date falls on a weekend
  *   \retval NDK_FALSE date does not fall on a weekend
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_ISWKND(LONG argDate,       ///< [in] is a serial date number that represents a given date
                            LPCTSTR holidays,   ///< [in] is a (:_:) separated list of holiday codes
                            LPLONG  zDates,     ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970) 
                            size_t nSize,       ///< [in] is the number of holiday dates in zDates
                            WORD  nWkndNo,      ///< [in] is the weekend number (1-7, 11-17). 
                            WORD  argOptions    ///< [in] is a switch to specify how to test for short or long weekends (1 = all (default), 2 = ignore holidays, 3 = only short weekends, 4 = only long weekends). 
                                                ///     1. All (default)
                                                ///     2. Ignore holidays (same as (1), but treats long weekend as short)
                                                ///     3. Only short weekends
                                                ///     4. Only long weekends  
                            );
  /*! 
  *   \brief Returns the duration (in calendar days) of the (long) weekend that a given day falls on.  
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_WKNDur(LONG argDate,       ///< [in] is a serial date number that represents a given date
                            LPCTSTR holidays,   ///< [in] is a (:_:) separated list of holiday codes
                            LPLONG  zDates,     ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970) 
                            size_t nSize,       ///< [in] is the number of holiday dates in zDates
                            WORD  nWkndNo,      ///< [in] is the weekend number (1-7, 11-17). 
                            LPWORD retVal       ///< [out] is the number of calendar days in the given weekend 
                            );

  /*! 
  *   \brief Returns the serial date number that corresponds to the first (last) day in the next (last) weekend  
  *   \return status code of the operation
  *   \retval #NDK_SUCCESS Operation successful
  *   \retval #NDK_FAILED Operation unsuccessful. See \ref SFMacros.h for more details.
  *   \sa SFDB_ISWRKDY()
  */
  int __stdcall SFDB_WKNDate(LONG argDate,      ///< [in] is a serial date number that represents a given date
                             LPCTSTR holidays,  ///< [in] is a (:_:) separated list of holiday codes
                             LPLONG  zDates,    ///< [in] is an array of holidays dates; each expressed as a serial number (i.e. number of days since 1.1.1970) 
                             size_t nSize ,     ///< [in] is the number of holiday dates in zDates
                             WORD  wkndNo,      ///< [in] is the weekend number (1-7, 11-17). 
                             WORD wkdOption,    ///< [in] is a switch to specify how to test for short or long weekends (1 = all (default), 2 = ignore holidays, 3 = only short weekends, 4 = only long weekends). 
                             WORD direction,    ///< [in]  is a switch to select the return output (1 = next weekend (default), 2 = last weekend). 
                             LPLONG retVal      ///< [out] is the serial date number of the next/previous weekend
                             );
  /// @}

  // Calendar API
  /// \name Calendar APIs
  /// @{

    /*! 
  *   \brief Examine the given code as a valid/supported calendar code
  *   \return status code of the operation
  *   \retval #NDK_TRUE the given code is a valid/supported calendar code
  *   \retval #NDK_FALSE  the given code is not a valid/supported calendar code  
  *   \retval #NDK_FAILED . For other codes, see \ref SFMacros.h
  *   \sa SFMacros.h, SFDB_FindHLDY()
  */
  int __stdcall SFDB_ISVALIDCALCODE(LPCTSTR argCode /*!< [in] is the given calendar code */);


  /*! 
  *   \brief Returns the calendar name and description, given the calendar's short code (e.g., "US" will return "US Government Holidays").
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_CALNAME(LPCTSTR argCode, ///< [in]   is the calendar short code.
                             LPTSTR retVal,   ///< [out] is the buffer that will receive the calendar name
                             size_t* nLen     ///< [inout] is the maximum number of characters to copy to the buffer.
                             );

  /*! 
  *   \brief Returns an array of names and codes for the supported calendars.
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_CALENDARS( LPCTSTR argName,  ///< [in]  is the name or prefix of the calendar name. If missing, all supported calendars will be returned.
                                LPTSTR retVal,    ///< [out] is the buffer that will receive the comma-separated calendar codes
                                size_t* nLen,     ///< [inout] is the maximum number of characters to copy to the buffer.
                                LPWORD nNumber    ///< [out] is the number of matching calendars
                                );

  /*! 
  *   \brief Returns an array of the holidays' names and codes as defined for the given calendar.
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_CALHLDYS(LPCTSTR argCalCode, ///< [in] is the calendar code (e.g. US, NYSE, CBT), name or alias. If missing, the US Government calendar is used.
                              LPTSTR retVal,      ///< [out] is the buffer that will receive the comma-separated holidays codes
                              size_t* nLen,       ///< [inout] is the maximum number of characters to copy to the buffer.
                              LPWORD nNumber      ///< [out] is the number of holidays returned.
                              );

  /*! 
  *   \brief Returns the weekend number associated with the given calendar
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_CALWKND(LPCTSTR argCalCode,  ///< [in] is the calendar code (e.g. US, NYSE, CBT), name or alias. If missing, the US Government calendar is used.
                             LPWORD nWKNDNo       ///< [out] is the weekend number (1-7, 11-17).
                             );

  ///@}

  // country support
  /// \name Country APIs
  /// @{
  /*! 
  *   \brief Return TRUE if the country code is a valid ISO country code (2 or 3 characters)
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_ISVALIDCNTRYCODE(LPCTSTR szCode /*! [in] is the ISO country code (e.g. US, GB, USA, GBR, etc.) */);   

  /*! 
  *   \brief Return the weekend code (i.e. 7 characters)  associated with the given country
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_GETWKNDFROMCNTRY(LPCTSTR szCode, ///< [in] is the ISO country code (e.g. US, GB, USA, GBR, etc.) */
                                      LPTSTR retVal,  ///< [out] is the buffer that will receive the weekend code
                                      size_t* nLen    ///< [inout] is the maximum number of characters to copy to the buffer.
                                      );   

  /*! 
  *   \brief Return the calendar code associated with the given country
  *   \return status code of the operation
  *   \retval NDK_SUCCESS Operation successful
  *   \retval Error code
  *   \sa SFMacros.h, SFDB_ISWRKDY()
  */
  int __stdcall SFDB_GETCALFROMCNTRY( LPCTSTR szCode, ///< [in] is the ISO country code (e.g. US, GB, USA, GBR, etc.) */
                                      LPTSTR retVal,  ///< [out] is the buffer that will receive the calendar code
                                      size_t* nLen    ///< [inout] is the maximum number of characters to copy to the buffer.
                                      );
  /// @}


  /// \name Currency APIs
  /// @{
  
  /*! \brief examine the validity of the currency iso code
  *   \param  szCCY [in] currency one ISO code (e.g. USD, JPY, tec.)
  *   \return NDK_SUCCESS for valid currency code,else NDK_FAILED
  *   \sa SFDB_GETWKNDFROMCCY(), SFDB_GETCALFROMCCY()
  */
  int __stdcall SFDB_ISVALIDCCYCODE(LPCTSTR szCCY); 
                                    
  /*! \brief return the weekend code (7 characters) associated with the given currency
  *   \return status code of the function: NDK_SUCCESS or NDK_FAILED
  *   \sa SFDB_ISVALIDCCYCODE(), SFDB_GETCALFROMCCY()
  */
  int __stdcall SFDB_GETWKNDFROMCCY(LPCTSTR CCY,       ///< [in] is the ISO code of the currency (e.g. USD, JPY, tec.)
                                    LPTSTR retVal,     ///< [out] is the buffer that will receive the weekend code
                                    size_t* nLen      ///< [inout] is the maximum number of characters to copy to the buffer.
                                    );

  /*! \brief return the calendar code associated with the given currency
  *   \return the status code of the function
  *   \retval NDK_SUCCESS 
  *   \retval Error code (see SFMacros.h)
  *   \sa SFMacros.h, SFDB_GETWKNDFROMCCY(), SFDB_ISVALIDCCYCODE()
  */
  int __stdcall SFDB_GETCALFROMCCY( LPCTSTR CCY,      ///<  [in] currency one ISO code (e.g. USD, JPY, tec.)
                                    LPTSTR retVal,    ///<  [out] is the buffer that will receive the calendar code
                                    size_t* nLen      ///<  [inout] is the maximum number of characters to copy to the buffer.
                                    );

  ///@}

  /// \name FX APIs
  /// @{
  /*! \brief return a currency pair ordered in FX mkt convention
  *   \retval NDK_SUCCESS 
  *   \retval Error code (see SFMacros.h)
  *   \sa SFDB_ISVALIDCCYCODE()
  */
  int __stdcall SFDB_GETVALIDCCYPAIR(LPCTSTR CCY1,   ///< [in] currency one ISO code (e.g. USD, JPY, tec.)
                                     LPCTSTR CCY2,   ///< [in] currency two ISO code (e.g. USD, JPY, tec.)
                                     LPTSTR szPair,  ///< [out] is the buffer that will receive the formatted currency pair
                                     size_t* nLen    ///< [inout] is the maximum number of characters to copy to the buffer.
                                     );
  ///@}
}
///  @}