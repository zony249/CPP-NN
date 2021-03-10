train: train.o matrix.o
	g++ train.o matrix.o -o train

train.o: src/train.cpp src/matrix.h
	g++ -c src/train.cpp -o train.o 

matrix.o: src/matrix.cpp
	g++ -c src/matrix.cpp -o matrix.o 

clean: 
	rm *.o train