// -*- C++ -*-
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**@file  startup.cpp
 * @brief System Intgrity 
 * 
 * Author: Robert M. McIsaac (aka Bob); 20573098.inc, Ontario, Canada
 */ 

#if defined( WIN32 )
#include "stdafx.h"
#else
#define HANDLE int ///< handle
#endif
#include <time.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "csci.h"

#define INI_FILE "_dt3_ini"

//---------------------------------------------------------------------
namespace {
   //   int running;
   int commNumber;
   int commBaud;

#include "LogMsg.hi"
   LogMsg *pLog;

#include "Console.hi"
   Console *pConsole;

#include "CommPort.hi"
   CommPort *pPort;
   
#include "Scripts.hi"
   Scripts *pScripts;

#include "BlackTerm.hi"
   BlackTerm *pTerm;

   
   //void error(char *msg){  perror(msg);  exit(0); }


};


//---------------------------------------------------------------------
/// @brief receive thread waits for serial port input
static void * thread_comm_input(void *){
   enum { LEN = 254 };
   static char line[LEN+2];
   int pos = 0;
   while( true ){
      Sleep(10);
      if( pPort->getOpen() ){
	 int ch;
	 while( ch = pPort->getRingChar(), ch != CommPort::NIL_DATA ){
	    if( (ch > 7 && ch < 0x0e) || ch >= 0x20 ){
	       pConsole->writeChar(ch);
	       if( ch >= 0x20 ){
		  line[pos++] = ch;
	       }
	       if( pos >= LEN || ch == 0x0a ){
		  line[pos++] = 0;
		  pLog->write_log(line);
		  pos = 0;
	       }
	    }
	 }
      }
   }
   //return NULL;
}

//---------------------------------------------------------------------------
typedef DWORD SRR_THREAD;

typedef struct {
   SRR_THREAD tid;
   void *(*routine)(void*);
   char name[30];
}SRR_THREAD_INFO_T;

static int srr_pthread_create(SRR_THREAD *pt, void *(*pFunc) (void *) ) {

   HANDLE h;
   int f = (int)pFunc;
   //DWORD ThreadID;
   h = CreateThread(
		    NULL,       // default security attributes
		    0,          // default stack size
		    (LPTHREAD_START_ROUTINE) f,
		    NULL,       // no thread function arguments
		    0,          // default creation flags
		    pt); // receive thread identifier

   if(h == NULL ) {
      printf("CreateThread error: %d\n", GetLastError());
      return -1;
   }
   return 0;
}


//---------------------------------------------------------------------------
/// command-line options
static void get_env_line_args( int argc, char *argv[] ) {

   int i,num=0;
   //commNumber = 1;
   //commBaud = 115200;

   if( argc < 2 ){
      //print_title();
      printf("RS232 defaults:- Port:%d Baud:%d\n",commNumber,commBaud);
      printf("Defaults may be changed with command line options\n"
	     " or .dt2_ini configuration file.\n");
      puts("COMM Port Selection:-");
      puts("-A\tCOMM Number (1-8)");
      puts("-B\tCOMM Baud Rate (9600-115200)");
      printf("Example: %s -A6 -B9600\n",PROGRAM);
      return;
   }
   
   for( i=0; i<argc; i++ ){
      char *p;
      p = argv[i];
      num = atoi(&p[2]);
      if( p[0] == '-' ){
	 switch( p[1] ){
	 case 'A':
	    commNumber = num;
	    break;
	 case 'B': 
	    commBaud = num;
	    break;
	 default: 
	    //commNumber = 1;
	    //commBaud = 115200;
	    break;
	 }
      }
      printf(" arg: %d\t %s\n", i, argv[i]);
   }

}


// ----------------------------------------------------------------
bool setCommPort( int commPortNum, int baudRate){
      
   bool b = false;
   if( pPort->getOpen() == true ){
      pPort->close();
   }
   b = pPort->open(commPortNum,  baudRate );
   if(b==false){
      std::cout << "Commport error\n" ;
   }
   else{
      std::cout << "CommPort " << commPortNum 
		<< " open at " << baudRate << std::endl;
   }
      
   //std::cout << "port" << commPortNum << std::endl;
   return b;
}

void goodbye( void ){
   puts("bye");
   delete pLog;
   //exit(0);
}

//---------------------------------------------------------------------
int main( int argc, char *argv[])
{
   volatile bool done = false;
   commNumber = -1;
   commBaud = 0;
   pConsole = new Console();
   
   printf("Dumb Terminal (%s) For Firmware\n\n",PROGRAM);

   pLog = new LogMsg();
   pLog->write_log("hello world");
   pLog->write_log("hello world");

   atexit(goodbye);

   get_env_line_args( argc, argv );

   pScripts = new Scripts();
   pScripts->fromFile();

   if( commNumber < 1 || commBaud < 1 ){
      puts("CommPort settings are invalid");
      Sleep(3000);
      exit(1);
   }

   pPort = new CommPort();
   pTerm = new BlackTerm();
   setCommPort(commNumber,commBaud);

   SRR_THREAD_INFO_T commThread[1] = {
      { 0, thread_comm_input,  "RS232" }
   };

   if(srr_pthread_create(&commThread[0].tid, 
			 commThread[0].routine )) {
      printf("\n ERROR creating thread %s\n",commThread[0].name);
      exit(1);
   }


   while( !done ){
      pTerm->monitorConsole();
   }

   return (done==true) ? 1 : 0;

}
// startup.cpp
