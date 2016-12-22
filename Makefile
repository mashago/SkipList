
default:	platform SkipList.o SkipListTest

CFLAG:= -Wall 

OS:=$(shell uname -s)

platform:
	@echo Platform: $(OS)

clean: 
	rm -rf SkipList.o
	rm -rf SkipListTest

SkipList.o:		SkipList.cpp
	g++ $(CFLAG) -c -o $@ $< 

SkipListTest:		SkipListTest.cpp SkipList.o
	g++ $(CFLAG) -o $@ $^ 
