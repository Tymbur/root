// @(#)root/gl:$Id$
// Author:  Matevz Tadel, Jun 2007

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TGLScenePad
#define ROOT_TGLScenePad

#include "TGLScene.h"
#include "TVirtualViewer3D.h"
#include "CsgOps.h"
#include <vector>
#include <utility>

class TGLViewer;
class TGLFaceSet;
class TList;


class TGLScenePad : public TVirtualViewer3D,  public TGLScene {

private:
   TGLScenePad(const TGLScenePad&) = delete;
   TGLScenePad& operator=(const TGLScenePad&) = delete;

protected:
   TVirtualPad*       fPad;

   // For building via VV3D
   Bool_t             fInternalPIDs;          //! using internal physical IDs
   UInt_t             fNextInternalPID;       //! next internal physical ID (from 1 - 0 reserved)
   UInt_t             fLastPID;               //! last physical ID that was processed in AddObject()
   Int_t              fAcceptedPhysicals;

   Int_t              ValidateObjectBuffer(const TBuffer3D& buffer, Bool_t includeRaw) const;
   TGLLogicalShape*   CreateNewLogical(const TBuffer3D & buffer) const;
   TGLPhysicalShape*  CreateNewPhysical(UInt_t physicalID, const TBuffer3D& buffer,
                                        const TGLLogicalShape& logical) const;

   void               ComposePolymarker(const TList *padPrimitives);
   // Composite shape specific
   typedef std::pair<UInt_t, RootCsg::TBaseMesh*> CSPart_t;
   mutable TGLFaceSet     *fComposite; //! Paritally created composite
   UInt_t                  fCSLevel;
   std::vector<CSPart_t>   fCSTokens;
   RootCsg::TBaseMesh*     BuildComposite();

   TGLLogicalShape* AttemptDirectRenderer(TObject* id);

   Bool_t         fSmartRefresh;   //! cache logicals during scene rebuilds

public:
   TGLScenePad(TVirtualPad* pad);
   ~TGLScenePad() override {}

   TVirtualPad* GetPad() const { return fPad; }
   void SetPad(TVirtualPad* p) { fPad = p; }

   // Histo import and Sub-pad traversal
   void AddHistoPhysical(TGLLogicalShape* log, const Float_t *histColor = nullptr);
   void SubPadPaint(TVirtualPad* pad);

   // PadPaint wrapper for calls from TGLViewer:
   virtual void   PadPaintFromViewer(TGLViewer* viewer);

   Bool_t  GetSmartRefresh() const           { return fSmartRefresh; }
   void    SetSmartRefresh(Bool_t smart_ref) { fSmartRefresh = smart_ref; }


   // TVirtualViewer3D interface

   Bool_t CanLoopOnPrimitives() const override { return kTRUE; }
   void   PadPaint(TVirtualPad* pad) override;
   void   ObjectPaint(TObject* obj, Option_t* opt="") override;

   // For now handled by viewer
   Int_t  DistancetoPrimitive(Int_t /*px*/, Int_t /*py*/) override { return 9999; }
   void   ExecuteEvent(Int_t /*event*/, Int_t /*px*/, Int_t /*py*/) override {}

   Bool_t PreferLocalFrame() const override { return kTRUE; }

   void   BeginScene() override;
   Bool_t BuildingScene() const override { return CurrentLock() == kModifyLock; }
   void   EndScene() override;

   Int_t  AddObject(const TBuffer3D& buffer, Bool_t* addChildren = nullptr) override;
   Int_t  AddObject(UInt_t physicalID, const TBuffer3D& buffer, Bool_t* addChildren = nullptr) override;
   Bool_t OpenComposite(const TBuffer3D& buffer, Bool_t* addChildren = nullptr) override;
   void   CloseComposite() override;
   void   AddCompositeOp(UInt_t operation) override;

   ClassDefOverride(TGLScenePad, 0); // GL-scene filled via TPad-TVirtualViewer interface.
};

#endif
