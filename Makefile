exec    = a.out
cc      = g++
opt     = -g
cflags  = -std=c++11 $(opt)
testdir = Testing
pwd     = $(shell pwd)

main    = main.cpp
objects = $(patsubst %.cpp,%.o,$(filter-out $(main), $(wildcard *.cpp)))

.PHONY : all test clean

all :	$(objects) $(exec) test

test :
	@ cd $(testdir) && $(MAKE)

%.o : %.cpp
	$(cc) $(cflags) -c $<

$(exec) : $(main)
	@rm -f $(exec)
	$(cc) $(cflags) $(objects) $< -o $@

clean :
	rm -f $(objects) $(exec)
	@ cd $(testdir) && $(MAKE) clean
