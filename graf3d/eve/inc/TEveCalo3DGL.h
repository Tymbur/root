// @(#)root/eve:$Id$
// Author: Matevz Tadel 2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TEveCalo3DGL
#define ROOT_TEveCalo3DGL

#include "TGLObject.h"
#include "TEveCaloData.h"
#include <vector>

class TEveCalo3D;

class TEveCalo3DGL : public TGLObject
{
private:
   TEveCalo3DGL(const TEveCalo3DGL&) = delete;
   TEveCalo3DGL& operator=(const TEveCalo3DGL&) = delete;

   void    CrossProduct(const Float_t a[3], const Float_t b[3], const Float_t c[3], Float_t out[3]) const;

   void    RenderBox(const Float_t pnts[8]) const;
   void    RenderGridEndCap() const;
   void    RenderGridBarrel() const;
   void    RenderGrid(TGLRnrCtx & rnrCtx) const;
   void    RenderBarrelCell(const TEveCaloData::CellGeom_t &cell, Float_t towerH, Float_t& offset) const;
   void    RenderEndCapCell(const TEveCaloData::CellGeom_t &cell, Float_t towerH, Float_t& offset) const;

   void    DrawSelectedCells(TEveCaloData::vCellId_t cells) const;

protected:
   TEveCalo3D     *fM;  // Model object.

   mutable std::vector<Float_t>     fOffset;

public:
   TEveCalo3DGL();
   ~TEveCalo3DGL() override {}

   Bool_t SetModel(TObject* obj, const Option_t *opt = nullptr) override;
   void   SetBBox() override;

   void   DirectDraw(TGLRnrCtx & rnrCtx) const override;
   void   DrawHighlight(TGLRnrCtx & rnrCtx, const TGLPhysicalShape* ps, Int_t lvl=-1) const override;

   Bool_t ShouldDLCache(const TGLRnrCtx& rnrCtx) const override;
   Bool_t SupportsSecondarySelect() const override { return kTRUE; }
   Bool_t AlwaysSecondarySelect()   const override { return kTRUE; }
   void   ProcessSelection(TGLRnrCtx & rnrCtx, TGLSelectRecord & rec) override;

   ClassDefOverride(TEveCalo3DGL, 0); // GL renderer class for TEveCalo.
};

#endif
