// @(#)root/eve:$Id$
// Authors: Matevz Tadel & Alja Mrak-Tadel: 2006, 2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TEveTreeTools
#define ROOT_TEveTreeTools

#include "TSelectorDraw.h"
#include "TEventList.h"

/******************************************************************************/
// TEveSelectorToEventList
/******************************************************************************/

class TEveSelectorToEventList : public TSelectorDraw
{
   TEveSelectorToEventList(const TEveSelectorToEventList&) = delete;
   TEveSelectorToEventList& operator=(const TEveSelectorToEventList&) = delete;

protected:
   TEventList* fEvList;
   TList       fInputList;
public:
   TEveSelectorToEventList(TEventList* evl, const char* sel);

   Int_t  Version() const override { return 1; }
   Bool_t Process(Long64_t entry) override;

   ClassDefOverride(TEveSelectorToEventList, 2); // TSelector that stores entry numbers of matching TTree entries into an event-list.
};

/******************************************************************************/
// TEvePointSelectorConsumer, TEvePointSelector
/******************************************************************************/

class TEvePointSelector;

class TEvePointSelectorConsumer
{
public:
   enum ETreeVarType_e { kTVT_XYZ, kTVT_RPhiZ };

protected:
   ETreeVarType_e fSourceCS; // Coordinate-System of the source tree variables

public:
   TEvePointSelectorConsumer(ETreeVarType_e cs=kTVT_XYZ) :fSourceCS(cs) {}
   virtual ~TEvePointSelectorConsumer() {}

   virtual void InitFill(Int_t /*subIdNum*/) {}
   virtual void TakeAction(TEvePointSelector*) = 0;

   ETreeVarType_e GetSourceCS() const  { return fSourceCS; }
   void SetSourceCS(ETreeVarType_e cs) { fSourceCS = cs; }

   ClassDef(TEvePointSelectorConsumer, 1); // Virtual base for classes that can be filled from TTree data via the TEvePointSelector class.
};

class TEvePointSelector : public TSelectorDraw
{
   TEvePointSelector(const TEvePointSelector&) = delete;
   TEvePointSelector& operator=(const TEvePointSelector&) = delete;

protected:
   TTree                  *fSelectTree;
   TEvePointSelectorConsumer *fConsumer;

   TString                 fVarexp;
   TString                 fSelection;

   TString                 fSubIdExp;
   Int_t                   fSubIdNum;

   TList                   fInputList;

public:
   TEvePointSelector(TTree* t=nullptr, TEvePointSelectorConsumer* c=nullptr,
                     const char* vexp="", const char* sel="");
   ~TEvePointSelector() override {}

   virtual Long64_t Select(const char* selection=nullptr);
   virtual Long64_t Select(TTree* t, const char* selection=nullptr);
   void  TakeAction() override;


   TTree* GetTree() const   { return fSelectTree; }
   void   SetTree(TTree* t) { fSelectTree = t; }

   TEvePointSelectorConsumer* GetConsumer() const { return fConsumer; }
   void SetConsumer(TEvePointSelectorConsumer* c) { fConsumer = c; }

   const char* GetVarexp() const { return fVarexp; }
   void SetVarexp(const char* v) { fVarexp = v; }

   const char* GetSelection() const { return fSelection; }
   void SetSelection(const char* s) { fSelection = s; }

   const char* GetSubIdExp() const { return fSubIdExp; }
   void SetSubIdExp(const char* s) { fSubIdExp = s; }

   Int_t GetSubIdNum() const { return fSubIdNum; }

   ClassDefOverride(TEvePointSelector, 2); // TSelector for direct extraction of point-like data from a Tree.
};

#endif
