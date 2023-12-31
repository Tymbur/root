# Copyright (C) 1995-2019, Rene Brun and Fons Rademakers.
# All rights reserved.
#
# For the licensing terms see $ROOTSYS/LICENSE.
# For the list of contributors see $ROOTSYS/README/CREDITS.

############################################################################
# CMakeLists.txt file for building ROOT tmva package
# @author Pere Mato, CERN
############################################################################

set (EXTRA_DICT_OPTS)
if (runtime_cxxmodules AND WIN32)
  set (EXTRA_DICT_OPTS NO_CXXMODULE)
endif()

ROOT_STANDARD_LIBRARY_PACKAGE(TMVAGui
  HEADERS
    TMVA/BDT.h
    TMVA/BDTControlPlots.h
    TMVA/BDT_Reg.h
    TMVA/BoostControlPlots.h
    TMVA/CorrGui.h
    TMVA/CorrGuiMultiClass.h
    TMVA/MovieMaker.h
    TMVA/PlotFoams.h
    TMVA/TMVAGui.h
    TMVA/TMVAMultiClassGui.h
    TMVA/TMVARegGui.h
    TMVA/annconvergencetest.h
    TMVA/compareanapp.h
    TMVA/correlations.h
    TMVA/correlationsMultiClass.h
    TMVA/correlationscatters.h
    TMVA/correlationscattersMultiClass.h
    TMVA/deviations.h
    TMVA/efficiencies.h
    TMVA/efficienciesMulticlass.h
    TMVA/likelihoodrefs.h
    TMVA/mvaeffs.h
    TMVA/mvas.h
    TMVA/mvasMulticlass.h
    TMVA/mvaweights.h
    TMVA/network.h
    TMVA/paracoor.h
    TMVA/probas.h
    TMVA/regression_averagedevs.h
    TMVA/rulevis.h
    TMVA/rulevisCorr.h
    TMVA/rulevisHists.h
    TMVA/tmvaglob.h
    TMVA/training_history.h
    TMVA/variables.h
    TMVA/variablesMultiClass.h
  SOURCES
    src/BDTControlPlots.cxx
    src/BoostControlPlots.cxx
    src/CorrGui.cxx
    src/CorrGuiMultiClass.cxx
    src/MovieMaker.cxx
    src/PlotFoams.cxx
    src/TMVAGui.cxx
    src/TMVAMultiClassGui.cxx
    src/TMVARegGui.cxx
    src/annconvergencetest.cxx
    src/compareanapp.cxx
    src/correlations.cxx
    src/correlationsMultiClass.cxx
    src/correlationscatters.cxx
    src/correlationscattersMultiClass.cxx
    src/deviations.cxx
    src/efficiencies.cxx
    src/efficienciesMulticlass.cxx
    src/likelihoodrefs.cxx
    src/mvas.cxx
    src/mvasMulticlass.cxx
    src/mvaweights.cxx
    src/network.cxx
    src/paracoor.cxx
    src/regression_averagedevs.cxx
    src/rulevis.cxx
    src/rulevisCorr.cxx
    src/rulevisHists.cxx
    src/tmvaglob.cxx
    src/training_history.cxx
    src/variables.cxx
    src/variablesMultiClass.cxx
    src/BDT.cxx
    src/BDT_Reg.cxx
    src/probas.cxx
    src/mvaeffs.cxx
  DICTIONARY_OPTIONS
    -writeEmptyRootPCM
  DEPENDENCIES
    RIO
    Hist
    Tree
    TreeViewer
    MLP
    Minuit
    XMLIO
    TMVA
    Gui
    HistPainter
    Core
   ${EXTRA_DICT_OPTS}
)
