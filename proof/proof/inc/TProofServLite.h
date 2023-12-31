// @(#)root/proofx:$Id$
// Author: G. Ganis Oct 2005

/*************************************************************************
 * Copyright (C) 1995-2005, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TProofServLite
#define ROOT_TProofServLite

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TProofServLite                                                       //
//                                                                      //
// TProofServLite is the version of the PROOF worker server for local   //
// running. The client starts directly the desired number of these      //
// workers; the master and daemons are eliminated, optimizing the number//
// of messages exchanged and created / destroyed.                       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TProofServ.h"

class TProofServLiteInterruptHandler;

class TProofServLite : public TProofServ {

private:
   TProofServLiteInterruptHandler *fInterruptHandler;
   TString       fSockPath;   // unix socket path

   Bool_t        fTerminated; //true if Terminate() has been already called

   Int_t         Setup() override;
   Int_t         SetupOnFork(const char *ord);

public:
   TProofServLite(Int_t *argc, char **argv, FILE *flog = 0);
   ~TProofServLite() override;

   Int_t         CreateServer() override;

   void          HandleFork(TMessage *mess) override;

   //void          HandleUrgentData();
   void          HandleSigPipe() override;
   void          HandleTermination() override;

   void          Terminate(Int_t status) override;

   ClassDefOverride(TProofServLite,0)  //PROOF-Lite Server Application Interface
};

#endif
