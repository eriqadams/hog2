#-----------------------------------------------------------------------------
# GNU Makefile for static libraries: project dependent part
#
# $Id: Makefile.prj.inc,v 1.2 2006/10/20 20:20:15 emarkus Exp $
# $Source: /usr/cvsroot/project_hog/build/gmake/apps/sample/Makefile.prj.inc,v $
#-----------------------------------------------------------------------------

NAME = dynsearch
DBG_NAME = $(NAME)
REL_NAME = $(NAME)

ROOT = ../../../..
VPATH = $(ROOT)

DBG_OBJDIR = $(ROOT)/objs/$(NAME)/debug
REL_OBJDIR = $(ROOT)/objs/$(NAME)/release
DBG_BINDIR = $(ROOT)/bin/debug
REL_BINDIR = $(ROOT)/bin/release

PROJ_CXXFLAGS = -I$(ROOT)/absmapalgorithms -I$(ROOT)/graphalgorithms -I$(ROOT)/shared -I$(ROOT)/abstraction -I$(ROOT)/gui -I$(ROOT)/simulation -I$(ROOT)/abstractionalgorithms -I$(ROOT)/environments -I$(ROOT)/mapalgorithms -I$(ROOT)/algorithms -I$(ROOT)/generic -I$(ROOT)/utils -I$(ROOT)/graph

PROJ_DBG_CXXFLAGS = $(PROJ_CXXFLAGS)
PROJ_REL_CXXFLAGS = $(PROJ_CXXFLAGS)

PROJ_DBG_LNFLAGS = -L$(DBG_BINDIR)
PROJ_REL_LNFLAGS = -L$(REL_BINDIR)

PROJ_DBG_LIB = -lshared -labstraction -labstractionalgorithms -lenvironments -lmapalgorithms -lalgorithms -labsmapalgorithms -lgraphalgorithms -lgui -lgraph -lutils
PROJ_REL_LIB = -lshared -labstraction -labstractionalgorithms -lenvironments -lmapalgorithms -lalgorithms -labsmapalgorithms -lgraphalgorithms -lgui -lgraph -lutils


PROJ_DBG_DEP = \
  $(DBG_BINDIR)/libutils.a \
  $(DBG_BINDIR)/libgraph.a \
  $(DBG_BINDIR)/libabstraction.a \
  $(DBG_BINDIR)/libgui.a \
  $(DBG_BINDIR)/libabstractionalgorithms.a \
  $(DBG_BINDIR)/libenvironments.a \
  $(DBG_BINDIR)/libmapalgorithms.a \
  $(DBG_BINDIR)/libabsmapalgorithms.a \
  $(DBG_BINDIR)/libgraphalgorithms.a \
  $(DBG_BINDIR)/libalgorithms.a \
  $(DBG_BINDIR)/libshared.a


PROJ_REL_DEP = \
  $(REL_BINDIR)/libutils.a \
  $(REL_BINDIR)/libgraph.a \
  $(REL_BINDIR)/libabstraction.a \
  $(REL_BINDIR)/libgui.a \
  $(REL_BINDIR)/libabstractionalgorithms.a \
  $(REL_BINDIR)/libenvironments.a \
  $(REL_BINDIR)/libmapalgorithms.a \
  $(REL_BINDIR)/libabsmapalgorithms.a \
  $(REL_BINDIR)/libgraphalgorithms.a \
  $(REL_BINDIR)/libalgorithms.a \
  $(REL_BINDIR)/libshared.a

default : all

SRC_CPP = \
	apps/dynamicsearch/dynsearch.cpp \
	apps/dynamicsearch/GeneralIDA.cpp \
	apps/dynamicsearch/experiment_basics.cpp \
	apps/dynamicsearch/GeneralRBFS.cpp \
	apps/dynamicsearch/GeneralBeamSearch.cpp \
	apps/dynamicsearch/GeneralBulb.cpp \
	apps/dynamicsearch/TurnTakingSimulation.cpp \
	apps/dynamicsearch/SortingIDA.cpp \
	apps/dynamicsearch/RandomSortingIDA.cpp \
	#apps/dynamicsearch/GeneralProbBulb.cpp \
	#apps/dynamicsearch/GenericTemplateAStar.cpp \
	#apps/dynamicsearch/TurnTakingUCT.cpp