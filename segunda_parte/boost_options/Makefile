CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall
LDFLAGS   := -Wall
LIBS      := -lboost_program_options

OUTPUT += ej1 ejreg

all: $(OUTPUT)

SRCS += ejemplo_1.cpp ejemplo_regex.cpp

OBJS += $(addsuffix .o,$(basename $(SRCS)))

ej1: ejemplo_1.o
	$(CXX) $(LDFLAGS) $(LIBS) -o $@ $^

ejreg: ejemplo_regex.o
	$(CXX) $(LDFLAGS) $(LIBS) -lboost_regex -o $@ $^

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf


