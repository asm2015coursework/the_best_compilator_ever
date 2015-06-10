makeall: clean test

test: test.o manager.a
	g++ -Wall -msse -g -o $@ $^ 
	#./test

test.o:
	g++ test.cpp -Wall -g -c -o $@

manager.a: manager.o
	ar rcs $@ $^

manager.o: 
	yasm -felf64 -gdwarf2 manager.asm -o $@

clean:
	rm -f test
	rm -f test.o
	rm -f manager.a
	rm -f manager.o

