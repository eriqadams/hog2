#-----------------------------------------------------------------------------
# Main Makefile for project_hog.
# The sub-makefiles are invoked sequentially
# (see: Peter Miller: Recursive Make Considered Harmful
# http://aegis.sourceforge.net/auug97.pdf)
#
# $Source: /usr/cvsroot/project_hog/build/gmake/Makefile,v $
# $Id: Makefile,v 1.5 2006/11/01 23:34:14 nathanst Exp $
#-----------------------------------------------------------------------------

# All projects to build in this order.
PROJECTS = \
  util \
  abstraction \
  shared \
  simulation \
  driver \
  apps/sample \
  apps/299 \
  apps/aVsPra \
  apps/cluster \
  apps/RTS \
  apps/bidding \
  apps/FLS \
  apps/HPAStar \
  apps/MTS \
  apps/pathfinding

# Include projects with broken compilation
PROJECTS_ALL = \
  util \
  abstraction \
  shared \
  simulation \
  driver \
  apps/sample \
  apps/299 \
  apps/aStarMM \
  apps/multipleAStarMM \
  apps/aVsPra \
  apps/cluster \
  apps/RTS \
  apps/sarsa \
  apps/FLS \
  apps/HPAStar \
  apps/MTS \
  apps/pathfinding \
  apps/sokoban

# sequentially to avoid same sub-target in sub-make invoked twice
default:
	$(MAKE) debug
	$(MAKE) release

debug:
	@for dir in $(PROJECTS); do \
           if test -f $$dir/Makefile; then \
             echo -e "\n--------------- $$dir (dbg)"; \
             $(MAKE) -C $$dir debug || exit -1; \
           fi; \
        done
	@echo ""

release:
	@for dir in $(PROJECTS); do \
           if test -f $$dir/Makefile; then \
             echo -e "\n--------------- $$dir (rel)"; \
             $(MAKE) -C $$dir release || exit -1; \
           fi; \
        done
	@echo ""

clean:
	@for dir in $(PROJECTS); do \
           if test -f $$dir/Makefile; then \
             echo -e "\n--------------- Removing temporary files for $$dir"; \
             $(MAKE) -C $$dir clean || exit -1; \
           fi; \
         done
	@echo ""

# sequentially to avoid same sub-target in sub-make invoked twice
all: override PROJECTS = $(PROJECTS_ALL)
all:
	$(MAKE) all-debug
	$(MAKE) all-release

all-debug: override PROJECTS = $(PROJECTS_ALL)
all-debug: debug

all-release: override PROJECTS = $(PROJECTS_ALL)
all-release: release

tags:
	@echo -e "Generating tags for Emacs"
	@(ctags -e `find ../.. -name "*.h" -o -name "*.cpp"`)

.PHONY: clean debug default release tags