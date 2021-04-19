train: train.o model.o
	g++ train.o model.o -o train -lpthread

train.o: src/train.cpp src/matrix.h src/layer.h src/utils.h
	g++ -c src/train.cpp -o train.o 

model.o: src/model.cpp src/model.h 
	g++ -c src/model.cpp -o model.o

clean: 
	rm *.o train