// Author: Roel Aaij   30/08/2007

/*************************************************************************
 * Copyright (C) 1995-2007, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_TGTreeTable
#define ROOT_TGTreeTable

#include "TGTable.h"

class TTree;

class TGTreeTable : public TGTable {

private:
   TTree *fTree; // Pointer to the tree

protected:

public:
   TGTreeTable(TGWindow *p = nullptr, Int_t id = -1, TTree *tree = nullptr,
               const char *expression = nullptr, const char *selection = nullptr,
               const char *option = nullptr, UInt_t nrows = 50, UInt_t ncolumns = 10);
   ~TGTreeTable() override;

   ClassDefOverride(TGTreeTable, 0) // A TGTable that owns it's TTreeTableIngeface.
};

#endif
