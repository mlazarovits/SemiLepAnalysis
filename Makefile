ROOTCFLAGS    = $(shell root-config --cflags)
ROOTGLIBS     = $(shell root-config --glibs)

CXX           = g++ -g

CXXFLAGS      = $(filter-out -stdlib=libc++ -pthread , $(ROOTCFLAGS))
CXXFLAGS      += $(filter-out -stdlib=libc++ -pthread , $(RFCFLAGS))

GLIBS         = $(filter-out -stdlib=libc++ -pthread , $(ROOTGLIBS))
GLIBS         += $(filter-out -stdlib=libc++ -pthread , $(RFGLIBS))

INCLUDEDIR       = ./include/
SRCDIR           = ./src/
CXX	         += -I$(INCLUDEDIR) -I.
OUTOBJ	         = ./obj/

CC_FILES := $(wildcard src/*.cc)
H_FILES := $(wildcard include/*.h)
OBJDIR 	:= $(OUTOBJ)
OBJ_FILES := $(addprefix $(OUTOBJ),$(notdir $(CC_FILES:.cc=.o)))

all: reducedTree.x makePlots.x makeEventCount.x

reducedTree.x: $(SRCDIR)reducedTree.C $(OBJ_FILES) $(H_FILES)
	$(CXX) $(CXXFLAGS) -o reducedTree.x $(OUTOBJ)*.o $(GLIBS) $ $<
	touch reducedTree.x

makePlots.x: $(SRCDIR)makePlots.C $(OBJ_FILES) $(H_FILES)
	$(CXX) $(CXXFLAGS) -o makePlots.x $(OUTOBJ)*.o $(GLIBS) $ $<
	touch makePlots.x

makeEventCount.x: $(SRCDIR)makeEventCount.C $(OBJ_FILES) $(H_FILES)
	$(CXX) $(CXXFLAGS) -o makeEventCount.x $(OUTOBJ)*.o $(GLIBS) $ $<
	touch makeEventCount.x


$(OUTOBJ)%.o: src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_FILES): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)


clean:
	rm -f $(OUTOBJ)*.o 
	rm -f *.x