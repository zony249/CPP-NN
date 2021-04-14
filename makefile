<<<<<<< HEAD
train: train.o matrix.o layer.o model.o
	g++ train.o matrix.o layer.o model.o -o train

train.o: src/train.cpp 
	g++ -c src/train.cpp -o train.o 

matrix.o: src/matrix.cpp src/matrix.h src/matrix_implementer.h
	g++ -c src/matrix.cpp -o matrix.o 

layer.o: src/layer.cpp src/layer.h src/layer_implementer.h
	g++ -c src/layer.cpp -o layer.o

=======
train: train.o model.o
	g++ train.o model.o -o train -lpthread

train.o: src/train.cpp src/matrix.h src/layer.h
	g++ -c src/train.cpp -o train.o 

>>>>>>> fce2300 (Nuked repo. retransferring files)
model.o: src/model.cpp src/model.h 
	g++ -c src/model.cpp -o model.o

clean: 
	rm *.o train