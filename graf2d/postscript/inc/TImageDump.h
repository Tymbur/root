// @(#)root/postscript:$Id$
// Author: Valeriy Onuchin   29/04/2005

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TImageDump
#define ROOT_TImageDump


#include "TVirtualPS.h"

class TImage;
class TColor;
class TPoint;

class TImageDump : public TVirtualPS {
protected:
   TImage           *fImage{nullptr};     ///< Image
   Int_t             fType{0};            ///< PostScript workstation type

   Int_t  XtoPixel(Double_t x);
   Int_t  YtoPixel(Double_t y);
   void   DrawDashPolyLine(Int_t npoints, TPoint *pt, UInt_t nDash,
                           const char* pDash, const char* col, UInt_t thick);

public:
   TImageDump();
   TImageDump(const char *filename, Int_t type = -111);
   ~TImageDump() override;

   void  CellArrayBegin(Int_t W, Int_t H, Double_t x1, Double_t x2, Double_t y1, Double_t y2) override;
   void  CellArrayFill(Int_t r, Int_t g, Int_t b) override;
   void  CellArrayEnd() override;
   void  Close(Option_t *opt = "") override;
   void  DrawBox(Double_t x1, Double_t y1,Double_t x2, Double_t  y2) override;
   void  DrawFrame(Double_t xl, Double_t yl, Double_t xt, Double_t  yt,
                   Int_t mode, Int_t border, Int_t dark, Int_t light) override;
   void  DrawPolyMarker(Int_t n, Float_t *x, Float_t *y) override;
   void  DrawPolyMarker(Int_t n, Double_t *x, Double_t *y) override;
   void  DrawPS(Int_t n, Float_t *xw, Float_t *yw) override;
   void  DrawPS(Int_t n, Double_t *xw, Double_t *yw) override;
   void  NewPage() override;
   void  Open(const char *filename, Int_t type = -111) override;
   void  Text(Double_t x, Double_t y, const char *string) override;
   void  Text(Double_t x, Double_t y, const wchar_t *string) override;
   void  SetColor(Float_t r, Float_t g, Float_t b) override;
   void *GetStream() const override { return (void*)fImage; }
   void  SetType(Int_t type = -111) override { fType = type; }
   Int_t GetType() const override { return fType; }
   TImage *GetImage() const { return fImage; }

   ClassDefOverride(TImageDump,0)  // create image in batch mode
};

#endif
