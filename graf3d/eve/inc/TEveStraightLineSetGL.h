// @(#)root/eve:$Id$
// Authors: Matevz Tadel & Alja Mrak-Tadel: 2006, 2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TEveStraightLineSetGL
#define ROOT_TEveStraightLineSetGL

#include "TGLObject.h"

class TGLViewer;
class TGLScene;

class TEveStraightLineSet;

class TEveStraightLineSetGL : public TGLObject
{
private:
   TEveStraightLineSetGL(const TEveStraightLineSetGL&);            // Not implemented
   TEveStraightLineSetGL& operator=(const TEveStraightLineSetGL&); // Not implemented

protected:
   TEveStraightLineSet* fM; // fModel dynamic-casted to TEveStraightLineSetGL

public:
   TEveStraightLineSetGL();
   ~TEveStraightLineSetGL() override {}

   Bool_t SetModel(TObject* obj, const Option_t *opt = nullptr) override;
   void   SetBBox() override;
   void   Draw(TGLRnrCtx& rnrCtx) const override;
   void   DirectDraw(TGLRnrCtx& rnrCtx) const override;

   Bool_t IgnoreSizeForOfInterest() const override { return kTRUE; }

   Bool_t ShouldDLCache(const TGLRnrCtx& rnrCtx) const override;
   Bool_t SupportsSecondarySelect() const override { return kTRUE; }
   void ProcessSelection(TGLRnrCtx& rnrCtx, TGLSelectRecord& rec) override;

   ClassDefOverride(TEveStraightLineSetGL, 0); // GL-renderer for TEveStraightLineSet class.
};

#endif
