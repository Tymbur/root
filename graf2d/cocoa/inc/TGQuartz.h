// @(#)root/graf2d:$Id$
// Author: Olivier Couet and Timur Pocheptsov 23/01/2012

/*************************************************************************
 * Copyright (C) 1995-2011, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TGQuartz
#define ROOT_TGQuartz

#include <vector>

#include "TGCocoa.h"
#include "TPoint.h"
#include "TTF.h"

/** \class TGQuartz
\ingroup cocoa

This is non-GUI part of TVirtualX interface, implemented for
MacOS X, using CoreGraphics (Quartz).
*/

class TGQuartz : public TGCocoa {
private:
   enum EAlign {kNone, kTLeft, kTCenter, kTRight, kMLeft,
                kMCenter, kMRight, kBLeft, kBCenter, kBRight};

   FT_Vector   fAlign; // alignment vector
public:
   TGQuartz();
   TGQuartz(const char *name, const char *title);

   //Final-overriders for TVirtualX.
   void      DrawBox(Int_t x1, Int_t y1, Int_t x2, Int_t y2,
                             EBoxMode mode) override;
   void      DrawCellArray(Int_t x1, Int_t y1, Int_t x2, Int_t y2,
                                   Int_t nx, Int_t ny, Int_t *ic) override;
   void      DrawFillArea(Int_t n, TPoint *xy) override;

   using TGCocoa::DrawLine;//There is a GUI version of DrawLine.

   void      DrawLine(Int_t x1, Int_t y1, Int_t x2, Int_t y2) override;
   void      DrawPolyLine(Int_t n, TPoint *xy) override;
   void      DrawPolyMarker(Int_t n, TPoint *xy) override;
   void      DrawText(Int_t x, Int_t y, Float_t angle, Float_t mgn,
                              const char *text, ETextMode mode) override;
   void      DrawText(Int_t x, Int_t y, Float_t angle, Float_t mgn,
                              const wchar_t *text, ETextMode mode) override;

   //I have to override these setters, since they are alredy overriden
   //in TVirtualX (originally, they are declared in TAttXXX classes)
   //and do nothing in TVirtualX (though, they are implemented
   //correctly in TAttXXX classes).
   void      SetFillColor(Color_t cindex) override;
   void      SetFillStyle(Style_t style) override;
   void      SetLineColor(Color_t cindex) override;
   void      SetLineStyle(Style_t linestyle) override;
   void      SetLineWidth(Width_t width) override;
   void      SetMarkerColor(Color_t cindex) override;
   void      SetMarkerSize(Float_t markersize) override;
   void      SetMarkerStyle(Style_t markerstyle) override;
   void      SetOpacity(Int_t percent) override;
   void      SetTextAlign(Short_t talign=11) override;
   void      SetTextColor(Color_t cindex) override;
   void      SetTextFont(Font_t fontnumber) override;
   Int_t     SetTextFont(char *fontname, ETextSetMode mode) override;
   void      SetTextSize(Float_t textsize) override;

   void      GetTextExtent(UInt_t &w, UInt_t &h, char *text) override;
   Int_t     GetFontAscent() const override;
   Int_t     GetFontAscent(const char *text) const override;
   Int_t     GetFontDescent() const override;
   Int_t     GetFontDescent(const char *text) const override;
   Float_t   GetTextMagnitude() override;

private:

   //Unfortunately, I have to convert from
   //top-left to bottom-left corner system.
   std::vector<TPoint> fConvertedPoints;

   //Lines with AA can be quite different
   //from what we always had with X11.
   //Now this is a switch in our configuration file (system.rootrc),
   //so it can be disabled. This flag affects _only_ pad's graphics,
   //GUI graphics is special and different. AA for fill area has a special
   // switch because it is better to have it off by default.
   bool fUseAA;
   bool fUseFAAA;

   void AlignTTFString();
   Bool_t IsTTFStringVisible(Int_t x, Int_t y, UInt_t w, UInt_t h);
   void RenderTTFString(Int_t x, Int_t y, ETextMode mode);
   //I have to use void * instead of QuartzPixmap * because of CINT :(
   void DrawFTGlyphIntoPixmap(void *pixmap, FT_Bitmap *source, ULong_t fore, ULong_t back, Int_t bx, Int_t by);

   void SetAA();
   void *GetSelectedDrawableChecked(const char *calledFrom) const;

   TGQuartz(const TGQuartz &rhs);
   TGQuartz &operator = (const TGQuartz &rhs);

   ClassDefOverride(TGQuartz, 0);//2D non-GUI graphics for Mac OSX.
};

#endif
