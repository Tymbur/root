// @(#)root/eve:$Id$
// Author: Matevz Tadel 2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TEveArrowGL
#define ROOT_TEveArrowGL

#include "TGLObject.h"

class TGLViewer;
class TGLScene;
class TEveArrow;

class TEveArrowGL : public TGLObject
{
private:
   TEveArrowGL(const TEveArrowGL&);            // Not implemented
   TEveArrowGL& operator=(const TEveArrowGL&); // Not implemented

protected:
   mutable TEveArrow             *fM;  // Model object.

public:
   TEveArrowGL();
   ~TEveArrowGL() override {}

   Bool_t SetModel(TObject* obj, const Option_t *opt = nullptr) override;
   void   SetBBox() override;
   void   DirectDraw(TGLRnrCtx & rnrCtx) const override;

   ClassDefOverride(TEveArrowGL, 0); // GL renderer class for TEveArrow.
};

#endif
