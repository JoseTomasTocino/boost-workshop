CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall
LDFLAGS   := -Wall
LIBS      :=

OUTPUT += ej_scoped ej_shared ej_shared_aux

all: $(OUTPUT)

SRCS += scoped.cpp shared.cpp shared_aux.cpp

OBJS += $(addsuffix .o,$(basename $(SRCS)))

ej_scoped: scoped.o
	$(CXX) $(LDFLAGS) $(LIBS) -o $@ $^

ej_shared: shared.o
	$(CXX) $(LDFLAGS) $(LIBS) -o $@ $^

ej_shared_aux: shared_aux.o
	$(CXX) $(LDFLAGS) $(LIBS) -o $@ $^

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf


