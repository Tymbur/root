// @(#)root/eve:$Id$
// Author: Matevz Tadel, 2010

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TEveBoxGL
#define ROOT_TEveBoxGL

#include "TGLObject.h"

class TGLViewer;
class TGLScene;

class TEveBox;
class TEveBoxProjected;

//------------------------------------------------------------------------------
// TEveBoxGL
//------------------------------------------------------------------------------

class TEveBoxGL : public TGLObject
{
private:
   TEveBoxGL(const TEveBoxGL&);            // Not implemented
   TEveBoxGL& operator=(const TEveBoxGL&); // Not implemented

protected:
   TEveBox             *fM;  // Model object.

   void RenderOutline    (const Float_t p[8][3]) const;
   void RenderBoxStdNorm (const Float_t p[8][3]) const;
   void RenderBoxAutoNorm(const Float_t p[8][3]) const;

public:
   TEveBoxGL();
   ~TEveBoxGL() override {}

   Bool_t SetModel(TObject* obj, const Option_t *opt = nullptr) override;
   void   SetBBox() override;

   void Draw(TGLRnrCtx& rnrCtx) const override;
   void DirectDraw(TGLRnrCtx& rnrCtx) const override;

   Bool_t IgnoreSizeForOfInterest() const override { return kTRUE; }

   // To support two-level selection
   // virtual Bool_t SupportsSecondarySelect() const { return kTRUE; }
   // virtual void ProcessSelection(TGLRnrCtx & rnrCtx, TGLSelectRecord & rec);

   ClassDefOverride(TEveBoxGL, 0); // GL renderer class for TEveBox.
};


//------------------------------------------------------------------------------
// TEveBoxProjectedGL
//------------------------------------------------------------------------------

class TEveBoxProjectedGL : public TGLObject
{
private:
   TEveBoxProjectedGL(const TEveBoxProjectedGL&);            // Not implemented
   TEveBoxProjectedGL& operator=(const TEveBoxProjectedGL&); // Not implemented

protected:
   TEveBoxProjected             *fM;  // Model object.

   void RenderPoints(Int_t mode) const;

public:
   TEveBoxProjectedGL();
   ~TEveBoxProjectedGL() override {}

   Bool_t SetModel(TObject* obj, const Option_t *opt = nullptr) override;
   void   SetBBox() override;

   void Draw(TGLRnrCtx& rnrCtx) const override;
   void DirectDraw(TGLRnrCtx& rnrCtx) const override;

   Bool_t IgnoreSizeForOfInterest() const override { return kTRUE; }

   // To support two-level selection
   // virtual Bool_t SupportsSecondarySelect() const { return kTRUE; }
   // virtual void ProcessSelection(TGLRnrCtx & rnrCtx, TGLSelectRecord & rec);

   ClassDefOverride(TEveBoxProjectedGL, 0); // GL renderer class for TEveBoxProjected.
};

#endif
