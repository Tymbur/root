// @(#)root/proofx:$Id$
// Author: G. Ganis Oct 2005

/*************************************************************************
 * Copyright (C) 1995-2005, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TXSlave
#define ROOT_TXSlave


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TXSlave                                                              //
//                                                                      //
// This is the version of TSlave for slave servers based on XRD.        //
// See TSlave for details.                                              //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TSlave.h"
#include "TXHandler.h"

class TObjString;
class TSocket;
class TSignalHandler;

class TXSlave : public TSlave, public TXHandler {

friend class TProof;
friend class TXProofMgr;

private:
   Bool_t   fValid;
   Int_t    fNWrks;     // Number of workers when submaster in remote plite
   TSignalHandler *fIntHandler;     //interrupt signal handler (ctrl-c)

   void  Init(const char *host, Int_t stype);
   void  ParseBuffer();

   // Static methods
   static Int_t GetProofdProtocol(TSocket *s);

protected:
   void     FlushSocket() override;
   void     Interrupt(Int_t type) override;
   Int_t    Ping() override;
   TObjString *SendCoordinator(Int_t kind, const char *msg = 0, Int_t int2 = 0) override;
   Int_t    SendGroupPriority(const char *grp, Int_t priority) override;
   void     SetAlias(const char *alias) override;
   void     StopProcess(Bool_t abort, Int_t timeout) override;

public:
   TXSlave(const char *url, const char *ord, Int_t perf,
           const char *image, TProof *proof, Int_t stype,
           const char *workdir, const char *msd, Int_t nwk = 1);
   ~TXSlave() override;

   void   Close(Option_t *opt = "") override;
   void   DoError(int level, const char *location, const char *fmt,
                  va_list va) const override;

   Bool_t HandleError(const void *in = 0) override; // Error Handler
   Bool_t HandleInput(const void *in = 0) override; // Input handler

   void   SetInterruptHandler(Bool_t on = kTRUE) override;

   Int_t  SetupServ(Int_t stype, const char *conffile) override;

   void   Touch() override;

   ClassDefOverride(TXSlave,0)  //Xrd PROOF slave server
};

#endif
