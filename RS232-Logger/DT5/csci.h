/// -*- C++ -*-
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ 
/**@file  csci.h 
 * @brief identifiers common to CSCIs
 *
 * identifiers common to Computer Software Configuration Items 

 * Author: Robert M. McIsaac (aka Bob); 20573098.inc, Ontario, Canada
 */ 


#if !defined CSCI_H
#define CSCI_H

#ifdef __cplusplus
// only need to export C interface if
// used by C++ source code
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

   //#include <lib_srr.h>

   //--------------------------------------------------------------------

   typedef unsigned short int	u16_t; ///< x
   typedef unsigned       int	u32_t; ///< x
   typedef unsigned char	uc8_t; ///< x


   //-------------------------------------------------------------------------
   /// typically indicates the state or status of some device so
   /// representation on different interfaces is consistent.
   /// see getDeviceStateString. It should be modified if this
   /// enumeration is modified.
   /// 
   /// @brief device attribute tokens for descriptor or message fields
   /// 
   typedef enum {
      eAoiDeviceError,		///< 0..ERR; broken or unknown
      eAoiDevNotUsed, 		///< 1..NA; in this configuration
      eAoiFlagTrue,		///< 2..T
      eAoiFlagFalse,		///< 3..F
      eAoiDevOff,		///< 4..OFF; or inactive
      eAoiDevOn,		///< 5..ON; or active
      eAoiDevOpen,		///< 6..OPEN; not closed
      eAoiDevClosed,		///< 7..CLOSED; not open
      eAoiDevBeamWD,		///< 8..WD; wide divergence
      eAoiDevBeamND,		///< 9..ND; narrow divergence
      eAoiDevStandby,		///< 10..STBY;
      eAoiDevSimulation,	///< 11..SIM;
      eAoiDevNav,		///< 12..NAV; navigation state
      eAoiDevFine,		///< 13..FINE; align state
      eAoiDevBusy,		///< 14..allow mechanical things to move
      eAoiDevInit,		///< 15..getting ready
      eAoiDevReady,		///< 16..idle
      eAoiDevAided,		///< 17..Aided eyesafety
      eAoiDevUnaided,		///< 18..Unaided eyesafety
      eAoiDeviceCodeLimit
   }AOI_DEVS_E;

   //--------------------------------------------------------------------
   /// \brief ok
   typedef union {
      short v16;		///< ok
      u16_t u16;		///< x
      uc8_t v8[2];		///< x
   }INT16_U;

   //--------------------------------------------------------------------
   /// \brief ok
   typedef union {
      u32_t u32;		///< x
      u16_t u16[2];		///< x
      uc8_t u8[4];		///< x
   }INT32_U;


   //--------------------------------------------------------------------
   /// \brief ok
   typedef union   {
      float   fv;		///< x
      u32_t   u32;		///< x
      short   v16[2];		///< x
      u16_t   u16[2];		///< x
      char    v8[4];		///< x
      uc8_t   u8[4];		///< x
   }DATA32_U;


   //--------------------------------------------------------------------
   /// \brief ok
   typedef union   {
      double  *dp;		///< x
      float   *fp;		///< x
      int     *sip;		///< x
      int     iv;		///< x
      char    *scp;		///< x
      u32_t   *uip;		///< x
      u16_t   *usp;		///< x
      uc8_t   *ucp;		///< x
   }PTR_U;


   //--------------------------------------------------------------------
   /// \brief ok
   typedef struct   {
      int msgid;		///< x
      int data1;		///< x
      int data2;		///< x
   }INT_MSG_T;			///< x


   //--------------------------------------------------------------------
   /// legacy codes prefixed with Oi5
   enum {
      eOi5Ok,                           ///< ok
      eOi5Init,                 ///< ok
      eOi5Process,                      ///< ok
      eOi5Write,                        ///< ok
      eOi5Receive,                      ///< ok
      eOi5Done,                 ///< ok
      eOi5Accept,                       ///< ok
      eOi5Deny,                 ///< ok
      eOi5_,                    ///< ok
      eOi5NotOk = -1            ///< ok
   };

   // ok   void pr_float( char *pn,int id, int index, float fv );
   // ok   void pr_int( char *pn, int id, int index, int iv );
   /// ok  //void pr_string( char *pn, int id, char *pMsg );
   enum { eMaxAlertMsgs=50, eMaxAlertLen=80 };

   enum { 
      OI_BIN_PORT = 4558,
      OI_TXT_PORT = 4567,
      OI_CTRL_PORT = OI_BIN_PORT
   };


   //--------------------------------------------------------------------
   /// state machine for producer-consumer shared memory
   typedef enum {
      eSyncInit,		///< ok
      eSyncRequest,		///< consumer request
      eSyncReady,		///< production ready
      eSyncClear		///< consumer clear
   }SYNC_STEPS_E;



#ifdef __cplusplus
}
#endif



#endif  /* csci.h */

