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
  class SFDBM
  {
    const string DLLName="SFDBM.dll";

    // SFLogger APIs
    [DllImport(DLLName, EntryPoint = "#100")]
    public static extern int SFDB_Init(string szAppName, string szKey, string szActCode, string szLogDir);

    [DllImport(DLLName, EntryPoint = "#105")]
    public static extern int SFDB_Shutdown();




  }// End of class SFDBM
}
