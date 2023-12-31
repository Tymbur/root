// @(#)root/postscript:$Id$
// Author: Olivier Couet

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TTeXDump
#define ROOT_TTeXDump


#include "TVirtualPS.h"

class TPoints;

class TTeXDump : public TVirtualPS {

protected:
   Float_t      fXsize;           ///< Page size along X
   Float_t      fYsize;           ///< Page size along Y
   Int_t        fType;            ///< Workstation type used to know if the Tex is open
   Bool_t       fBoundingBox;     ///< True when the TeX header is printed
   Bool_t       fRange;           ///< True when a range has been defined
   Bool_t       fStandalone;      ///< True when a TeX file should be standalone
   Float_t      fCurrentRed;      ///< Current Red component
   Float_t      fCurrentGreen;    ///< Current Green component
   Float_t      fCurrentBlue;     ///< Current Blue component
   Float_t      fCurrentAlpha;    ///< Current Alpha value
   Float_t      fLineScale;       ///< Line width scale factor


public:
   TTeXDump();
   TTeXDump(const char *filename, Int_t type=-113);
   ~TTeXDump() override;

   void    CellArrayBegin(Int_t W, Int_t H, Double_t x1, Double_t x2, Double_t y1, Double_t y2) override;
   void    CellArrayFill(Int_t r, Int_t g, Int_t b) override;
   void    CellArrayEnd() override;
   void    Close(Option_t *opt="") override;
   Int_t   CMtoTeX(Double_t u) { return Int_t(0.5 + 72*u/2.54); }
   void    DefineMarkers();
   void    DrawBox(Double_t x1, Double_t y1,Double_t x2, Double_t  y2) override;
   void    DrawFrame(Double_t xl, Double_t yl, Double_t xt, Double_t  yt,
                     Int_t mode, Int_t border, Int_t dark, Int_t light) override;
   void    DrawPolyLine(Int_t n, TPoints *xy);
   void    DrawPolyLineNDC(Int_t n, TPoints *uv);
   void    DrawPolyMarker(Int_t n, Float_t *x, Float_t *y) override;
   void    DrawPolyMarker(Int_t n, Double_t *x, Double_t *y) override;
   void    DrawPS(Int_t n, Float_t *xw, Float_t *yw) override;
   void    DrawPS(Int_t n, Double_t *xw, Double_t *yw) override;
   void    NewPage() override;
   void    Off();
   void    On();
   void    Open(const char *filename, Int_t type=-111) override;
   void    Range(Float_t xrange, Float_t yrange);
   void    SetColor(Int_t color = 1);
   void    SetColor(Float_t r, Float_t g, Float_t b) override;
   void    SetFillColor(Color_t cindex=1) override;
   void    SetLineColor(Color_t cindex=1) override;
   void    SetLineStyle(Style_t linestyle = 1) override;
   void    SetLineWidth(Width_t linewidth = 1) override;
   void    SetLineScale(Float_t scale=1) { fLineScale = scale; }
   void    SetMarkerSize(Size_t msize=1) override;
   void    SetMarkerColor(Color_t cindex=1) override;
   void    SetTextColor(Color_t cindex=1) override;
   void    Text(Double_t x, Double_t y, const char *string) override;
   void    Text(Double_t, Double_t, const wchar_t *) override {}
   void    TextNDC(Double_t u, Double_t v, const char *string);
   void    TextNDC(Double_t, Double_t, const wchar_t *) {}
   Float_t UtoTeX(Double_t u);
   Float_t VtoTeX(Double_t v);
   Float_t XtoTeX(Double_t x);
   Float_t YtoTeX(Double_t y);

   ClassDefOverride(TTeXDump, 0);  //Tex driver
};

#endif
