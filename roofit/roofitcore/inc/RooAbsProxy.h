/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitCore                                                       *
 *    File: $Id: RooAbsProxy.h,v 1.15 2007/07/12 20:30:28 wouter Exp $
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_ABS_PROXY
#define ROO_ABS_PROXY

#ifdef _WIN32
// Turn off 'warning C4355: 'this' : used in base member initializer list'
//
// This message will pop up for any class that initializes member proxy objects
// Including the pragma here will automatically disable that warning message
// for all such cases
#pragma warning ( disable:4355 )
#endif

#include <TClass.h>

#include <string>
#include <unordered_map>

class RooAbsArg;
class RooAbsCollection;
class RooArgSet;

class RooAbsProxy {
public:

  // Constructors, assignment etc.
  RooAbsProxy() ;
  RooAbsProxy(const char* name, const RooAbsProxy& other) ;
  virtual ~RooAbsProxy() {
    // Destructor
  } ;

  virtual const char* name() const {
    // Return name of proxy
    return "dummy" ;
  } ;

  inline const RooArgSet* nset() const {
    // Return normalization set to be used for evaluation of contents
    return _nset ;
  }
  virtual void print(std::ostream& os, bool addContents=false) const ;

protected:

  RooArgSet* _nset = nullptr ; ///<! Normalization set to be used for evaluation of RooAbsPdf contents

  friend class RooAbsArg ;
  virtual bool changePointer(const RooAbsCollection& newServerSet, bool nameChange=false, bool factoryInitMode=false) = 0 ;
  virtual bool changePointer(std::unordered_map<RooAbsArg*, RooAbsArg*> const& replacements) = 0 ;

  friend class RooAbsPdf ;
  virtual void changeNormSet(const RooArgSet* newNormSet) ;

  ClassDef(RooAbsProxy,1) // Abstract proxy interface
} ;

#endif

