CXX:=g++
CURDIR:=$(PWD)
CXXFLAGS:=-Wall -std=c++11 -g -O0 -iquote=$(CURDIR)
LIB:=-lncursesw -lm
SRCDIR:=cpp
INCDIR:=include
BLDDIR:=build
CLSDIR:=class
EXENAME:=scgb
#to make all dependency automatically.REF:http://make.mad-scientist.net/papers/advanced-auto-dependency-generation/

DEPDIR:=dependency
$(shell mkdir -p $(BLDDIR))
$(shell mkdir -p $(DEPDIR))
DEPFLAGS=-MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td 
POSTCOMPILE=@mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

#apparently && is one of the shell scripts.
#@ means this command won't echo it's result.


SRC:=$(shell find $(SRCDIR) -type f -name *.cpp)
OBJ:=$(patsubst $(SRCDIR)/%,$(BLDDIR)/%,$(SRC:.cpp=.o))


#LINK
$(EXENAME) : $(OBJ)
	$(CXX) $(OBJ) $(CXXFLAGS) $(LIB) -o $(EXENAME)

#COMPILE
$(BLDDIR)/%.o : $(SRCDIR)/%.cpp $(DEPDIR)/%.d
	$(CXX) $< $(DEPFLAGS) $(CXXFLAGS) $(LIB) -c -o $@
	$(POSTCOMPILE)

#UTILITY
.PHONY: clean
.PHONY: git

clean :
	@rm $(BLDDIR) $(EXENAME) $(DEPDIR) $(SRCDIR)/#* $(INCDIR)/#* $(CLSDIR)/#* -rf

git :
	make clean && git add -A && git commit && git push origin master

#DEPENDENCY
$(DEPDIR)/%.d: ;

.PRECIOUS:$(DEPDIR)/%.d

include $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SRC:.cpp=.d))
