# makefile
#./main>output.txt

program: main.o
	g++ -g -std=c++11 main.o -o main
	./main
main.o: main.cpp matrix.cpp matrix.h
	g++ -g -std=c++11 -c main.cpp

clean:
	rm -f *.o
	rm -f main

com:
	git push origin master

all:
	git add -u
	git commit -m "same"
	git push origin main
	
stab:
	git add -u
	git commit -m "Stable copy"
	git push origin main

pull:
	git pull
	make
	./main

val:
	make
	valgrind ./main

check:
	make
	valgrind --leak-check=full ./main


