ROOTCFLAGS    = $(shell root-config --cflags)
ROOTGLIBS     = $(shell root-config --glibs)

CXX           = g++

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

all: reducedTree.x makePlotsTEST.x 

reducedTree.x: $(SRCDIR)reducedTree.C $(OBJ_FILES) $(H_FILES)
	$(CXX) $(CXXFLAGS) -o reducedTree.x $(OUTOBJ)*.o $(GLIBS) $ $<
	touch reducedTree.x

makePlotsTEST.x: $(SRCDIR)makePlotsTEST.C $(OBJ_FILES) $(H_FILES)
	$(CXX) $(CXXFLAGS) -o makePlotsTEST.x $(OUTOBJ)*.o $(GLIBS) $ $<
	touch makePlotsTEST.x


$(OUTOBJ)%.o: src/%.cc include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_FILES): | $(OBJDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)


clean:
	rm -f $(OUTOBJ)*.o 
	rm -f *.x