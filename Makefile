all: tst

tst: main.o BinaryTreeAVL.o Node.o Users.o
	g++ -o tst main.o BinaryTreeAVL.o Node.o Users.o

main.o: main.cpp
	g++ -c main.cpp

BinaryTreeAVL.o: BinaryTreeAVL.cpp BinaryTreeAVL.h
	g++ -c BinaryTreeAVL.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

Users.o: Users.cpp Users.h
	g++ -c Users.cpp

clean:
	rm *.o tst