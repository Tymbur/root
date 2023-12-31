// @(#)root/gl:$Id$
// Author: Timur Pocheptsov 09/08/2004

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TX11GL
#define ROOT_TX11GL


//////////////////////////////////////////////////////////////////////////
//                                                                      //
// TX11GL                                                               //
//                                                                      //
// The TX11GL is X11 implementation of TVirtualGLImp class.             //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "TVirtualGL.h"

#if !defined(__CLING__)
#include <GL/glx.h>
#else
typedef struct _XDisplay Display;
struct XVisualInfo;
#endif


class TX11GLManager : public TGLManager {
private:
   class TX11GLImpl;
   TX11GLImpl *fPimpl;

public:
   TX11GLManager();
   ~TX11GLManager() override;

   //All public functions are TGLManager's final-overriders

   //index returned can be used as a result of gVirtualX->InitWindow
   Int_t    InitGLWindow(Window_t winID) override;
   //winInd is the index, returned by InitGLWindow
   Int_t    CreateGLContext(Int_t winInd) override;

   //[            Off-screen rendering part
   //create pixmap to read GL buffer into it,
   //ctxInd is the index, returned by CreateGLContext
   Bool_t   AttachOffScreenDevice(Int_t ctxInd, Int_t x, Int_t y, UInt_t w, UInt_t h) override;
   Bool_t   ResizeOffScreenDevice(Int_t devInd, Int_t x, Int_t y, UInt_t w, UInt_t h) override;
   //analog of gVirtualX->SelectWindow(fPixmapID) => gVirtualGL->SelectOffScreenDevice(fPixmapID)
   void     SelectOffScreenDevice(Int_t devInd) override;
   //Index of pixmap, valid for gVirtualX
   Int_t    GetVirtualXInd(Int_t devInd) override;
   //copy pixmap into window directly/by pad
   void     MarkForDirectCopy(Int_t devInd, Bool_t) override;
   //Off-screen device holds sizes for glViewport
   void     ExtractViewport(Int_t devInd, Int_t *vp) override;
   //Read GL buffer into pixmap
   void     ReadGLBuffer(Int_t devInd) override;
   //]

   //Make the gl context current
   Bool_t   MakeCurrent(Int_t devInd) override;
   //Sswap buffers or copies pixmap (XCopyArea)
   void     Flush(Int_t ctxInd) override;
   //Generic function for gl context and off-screen device deletion
   void     DeleteGLContext(Int_t devInd) override;

   //used by viewer
   Bool_t   SelectManip(TVirtualGLManip *manip, const TGLCamera *camera, const TGLRect *rect, const TGLBoundingBox *sceneBox) override;
   //
   Bool_t   PlotSelected(TVirtualGLPainter *plot, Int_t px, Int_t py) override;
   char    *GetPlotInfo(TVirtualGLPainter *plot, Int_t px, Int_t py) override;
   //
   void     PaintSingleObject(TVirtualGLPainter *) override;
   void     PanObject(TVirtualGLPainter *o, Int_t x, Int_t y) override;
   void     PrintViewer(TVirtualViewer3D *vv) override;

   Bool_t   HighColorFormat(Int_t /*ctxInd*/) override{return kFALSE;}

   struct TGLContext_t;

private:
   Bool_t CreateGLPixmap(TGLContext_t &);

   //implicit copy-ctor/assignment generation
   // was already disabled by base class, but to be explicit ...
   TX11GLManager(const TX11GLManager &);
   TX11GLManager &operator = (const TX11GLManager &);

   ClassDefOverride(TX11GLManager, 0) //X11-specific version of TGLManager
};



#endif
