# vim: set noet:

CC=g++
CFLAGS=-I. -pthread -I../inc/gsl/include
OUTDIR=build
SOURCES=main.cpp
DEPS=colournames.h structures.h
EXE=$(OUTDIR)/cinema_seats
OBJ=$(patsubst %.cpp, $(OUTDIR)/%.o, $(SOURCES))

all: build $(EXE)

# $@ is a variable for whatever is on left of rule
# $^ is first thing on right of it, I guess $> is the rest?

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OUTDIR)/%.o : %.cpp #$(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< 

build:
	@mkdir -p build

clean:
	@rm -rf build
	
cleanlibs:
	@rm build/*.o
	
cleansolution:
	@rm -rf x64
	@rm -rf Debug
	@rm -rf Release
	@rm -rf .vs
