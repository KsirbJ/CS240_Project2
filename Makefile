
FLAGS = -Wall -std=c++11

all:	p2

p2:	driver.o
	g++ $(FLAGS) driver.o -o p2

driver.o:	driver.cpp TTST.h TTST.cpp
	g++ $(FLAGS) -c driver.cpp -o driver.o

clean:
	rm -f *.o lab6