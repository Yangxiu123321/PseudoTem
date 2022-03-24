objs := main.o PseudoTem.o

.PHONY : clean

all:$(objs)
	g++ $^ -o test -std=gnu++11 -lpthread

%.o : %.cpp
	g++ -c $< -I.

clean :
	rm *.o test
