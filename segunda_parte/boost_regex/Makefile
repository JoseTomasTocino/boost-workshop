CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall
LDFLAGS   := -Wall
LIBS      := -lboost_regex

OUTPUT += programa

all: $(OUTPUT)

SRCS += main.cpp

OBJS += $(addsuffix .o,$(basename $(SRCS)))

$(OUTPUT): $(OBJS)
	$(CXX) $(LDFLAGS) $(LIBS) -o $@ $^

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf


