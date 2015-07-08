all: bin/mfft

clean: 
	rm *o main


bin/mfft: dist/main.o dist/fft.o dist/complex.o
	g++ -lm dist/main.o dist/fft.o dist/complex.o -o bin/mfft

dist/main.o: src/main.cpp
	g++ -I./include -c src/main.cpp -o dist/main.o

dist/fft.o: include/fft.cpp
	g++ -I./include -c include/fft.cpp -o dist/fft.o

dist/complex.o: include/complex.cpp
	g++ -I./include -c include/complex.cpp -o dist/complex.o
