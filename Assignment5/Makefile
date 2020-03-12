PRG=gnu.exe

GCC=g++
GCCFLAGS=-Wall -Wextra -std=c++11 -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor  -Weffc++ -pedantic
GCCOPTIMIZE=-O3
OBJECTS0= #bst-map.cpp
DRIVER0=driver.cpp
INCLUDE1=
MSCINCLUDE=
MSCDEFINE=
DEFINE=

VALGRIND_OPTIONS=-q --leak-check=full

OSTYPE := $(shell uname)
ifeq ($(OSTYPE),Linux)
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gcc0:
	$(GCC) -o $(PRG) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) $(GCCOPTIMIZE) $(INCLUDE1) $(DEFINE)
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46:
	@echo "should run in less than 1000 ms"
	./$(PRG) $@ >studentout$@
	@echo "lines after the next are mismatches with master output -- see out$@"
	diff out$@ studentout$@ $(DIFF_OPTIONS)
mem0 mem1 mem2 mem3 mem4 mem5 mem6 mem7 mem8 mem9 mem10 mem11 mem12 mem13 mem14 mem15 mem16 mem17 mem18 mem19 mem20 mem21 mem22 mem23 mem24 mem25 mem26:
	@echo "should run in less than 5000 ms"
	valgrind $(VALGRIND_OPTIONS) ./$(PRG) $(subst mem,,$@) 1>/dev/null 2>difference$@
	@echo "lines after this are memory errors"; cat difference$@
clean:
	rm -f *gcno *gcda *gcov *.exe *.o *.obj *.tds
