// @(#)root/proofplayer:$Id$
// Author: G. Ganis Mar 2008

/*************************************************************************
 * Copyright (C) 1995-2001, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TProofPlayerLite
#define ROOT_TProofPlayerLite


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TProofPlayerLite                                                     //
//                                                                      //
// This version of TProofPlayerRemote merges the functionality needed   //
// by clients and masters. It is used in optmized local sessions.       //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TProofPlayer.h"


class TProofPlayerLite : public TProofPlayerRemote {

protected:
   Bool_t  HandleTimer(TTimer *timer) override;

   Int_t   MakeSelector(const char *selfile);
   void    SetupFeedback() override;

public:
   TProofPlayerLite(TProof *proof = 0) : TProofPlayerRemote(proof) { }

   ~TProofPlayerLite() override { }   // Owns the fOutput list

   Long64_t       Process(TDSet *set, const char *selector,
                          Option_t *option = "", Long64_t nentries = -1,
                          Long64_t firstentry = 0) override;
   Long64_t       Process(TDSet *set, TSelector *selector,
                          Option_t *option = "", Long64_t nentries = -1,
                          Long64_t firstentry = 0) override;
   Long64_t       Finalize(Bool_t force = kFALSE, Bool_t sync = kFALSE) override;
   Long64_t       Finalize(TQueryResult *qr) override
                            { return TProofPlayerRemote::Finalize(qr); }

   void           StoreFeedback(TObject *slave, TList *out) override; // Adopts the list

   ClassDefOverride(TProofPlayerLite,0)  // PROOF player running in PROOF-Lite
};

#endif
