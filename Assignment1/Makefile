FLAGS_OPT=-O3

CFLAGS_DEBUG=-g

CXX=g++

CFLAGS=-std=c++11

CFLAGS+=-Wpedantic -Wall -Wextra -Werror -pedantic -Wconversion

CFLAGS := $(CFLAGS_OPT) $(CFLAGS)
LDFLAGS := -flto -fwhole-program
OBJDIR = obj

HDR := $(shell ls -t src/*.h)
SRC := $(shell ls -t src/*.cpp)
OBJ := $(SRC:src/%.cpp=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: src/%.cpp $(HDR)
	$(CXX) $(CFLAGS) -I. -c $< -o $@

TARGET_FILE = ObjectAllocator

$(TARGET_FILE): $(OBJDIR) $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

default: $(TARGET_FILE)

$(OBJDIR):
	mkdir $@

run:
	./$(TARGET_FILE) > debug.txt

clean:
	-rm -rf $(OBJDIR) $(TARGET_FILE)

diff:
	diff debug.txt output-sample-zeros-ec-LP64.txt --strip-trailing-cr
	
memchk:
	valgrind -q --leak-check=full --show-reachable=yes --tool=memcheck ./$(TARGET_FILE)
