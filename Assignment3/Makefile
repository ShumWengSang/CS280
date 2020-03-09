GCC=g++
GCCFLAGS=-Wall -Werror -Wextra -std=c++11 -pedantic -Wconversion -O2 -Wno-unused-result

PRG = rummikup.exe

OBJECTS0=
DRIVER0=driver.cpp

VALGRIND_OPTIONS=-q --leak-check=full
DIFF_OPTIONS=-y --strip-trailing-cr --suppress-common-lines -b

OSTYPE := $(shell uname)
ifeq ($(OSTYPE),Linux)
CYGWIN=
else
CYGWIN=-Wl,--enable-auto-import
endif

gcc0:
	$(GCC) -o $(PRG) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS)
	#$(GCC) -o $(PRG2) $(CYGWIN) $(DRIVER0) $(OBJECTS0) $(GCCFLAGS) -m32
0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46:
	#echo "running test$@"
	#@echo "should run in less than 200 ms"
	@echo "should run in less than 200 ms"
	./$(PRG) $@ >studentout$@
	diff out$@ studentout$@ $(DIFF_OPTIONS) > difference$@
	
stress:
	time for((i=0;i<100;++i)); do echo $i; ./rummikup.exe 3 &> /dev/null; done
clean : 
	rm *.exe student* difference*
