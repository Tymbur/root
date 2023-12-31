// @(#)root/proofx:$Id$
// Author: G. Ganis, Nov 2005

/*************************************************************************
 * Copyright (C) 1995-2005, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TXProofMgr
#define ROOT_TXProofMgr


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TXProofMgr                                                           //
//                                                                      //
// The PROOF manager interacts with the PROOF server coordinator to     //
// create or destroy a PROOF session, attach to or detach from          //
// existing one, and to monitor any client activity on the cluster.     //
// At most one manager instance per server is allowed.                  //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TProofMgr.h"
#include "TUrl.h"
#include "TXHandler.h"

//
// XPROOF client version: increase whenever a non backward compatible
// change occur
//  ->1      first version being tested by ALICE
const Int_t kXPROOF_Protocol = 1;

class TStopwatch;
class TXSocket;

class TXProofMgr : public TProofMgr, public TXHandler {

private:

   TXSocket   *fSocket; // Connection to XRD

   Int_t Init(Int_t loglevel = -1);

   void CpProgress(const char *pfx, Long64_t bytes,
                   Long64_t size, TStopwatch *watch, Bool_t cr = kFALSE);
   TObjString *Exec(Int_t action,
                    const char *what, const char *how, const char *where);

public:
   TXProofMgr(const char *url, Int_t loglevel = -1, const char *alias = "");
   ~TXProofMgr() override;

   Bool_t      HandleInput(const void *) override;
   Bool_t      HandleError(const void *in = 0) override;

   Bool_t      IsValid() const override { return fSocket; }
   void        SetInvalid() override;

   TProof     *AttachSession(Int_t id, Bool_t gui = kFALSE) override
                      { return TProofMgr::AttachSession(id, gui); }
   TProof     *AttachSession(TProofDesc *d, Bool_t gui = kFALSE) override;
   void        DetachSession(Int_t, Option_t * = "") override;
   void        DetachSession(TProof *, Option_t * = "") override;
   const char *GetMssUrl(Bool_t = kFALSE) override;
   TProofLog  *GetSessionLogs(Int_t ridx = 0, const char *stag = 0,
                              const char *pattern = "-v \"| SvcMsg\"",
                              Bool_t rescan = kFALSE) override;
   Bool_t      MatchUrl(const char *url) override;
   void        ShowROOTVersions() override;
   TList      *QuerySessions(Option_t *opt = "S") override;
   TObjString *ReadBuffer(const char *file, Long64_t ofs, Int_t len) override;
   TObjString *ReadBuffer(const char *file, const char *pattern) override;
   Int_t       Reset(Bool_t hard = kFALSE, const char *usr = 0) override;
   Int_t       SendMsgToUsers(const char *msg, const char *usr = 0) override;
   Int_t       SetROOTVersion(const char *tag) override;
   void        ShowWorkers() override;

   // Remote file system actions
   Int_t       Cp(const char *src, const char *dst = 0, const char *opts = 0) override;
   void        Find(const char *what = "~/", const char *how = "-type f", const char *where = 0) override;
   void        Grep(const char *what, const char *how = 0, const char *where = 0) override;
   void        Ls(const char *what = "~/", const char *how = 0, const char *where = 0) override;
   void        More(const char *what, const char *how = 0, const char *where = 0) override;
   Int_t       Rm(const char *what, const char *how = 0, const char *where = 0) override;
   void        Tail(const char *what, const char *how = 0, const char *where = 0) override;
   Int_t       Md5sum(const char *what, TString &sum, const char *where = 0) override;
   Int_t       Stat(const char *what, FileStat_t &st, const char *where = 0) override;

   Int_t       GetFile(const char *remote, const char *local, const char *opt = 0) override;
   Int_t       PutFile(const char *local, const char *remote, const char *opt = 0) override;

   ClassDefOverride(TXProofMgr,0)  // XrdProofd PROOF manager interface
};

#endif
