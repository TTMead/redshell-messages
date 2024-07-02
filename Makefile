HEADERS = include/redshell/command.h include/redshell/encoder.h include/redshell/imu.h include/redshell/power.h include/redshell/redshell_messages.h
CFLAGS = -Iinclude

default: test

test.o: test/test.c $(HEADERS)
	make clean
	mkdir build/
	gcc $(CFLAGS) -c test/test.c -o build/test.o

test: test.o
	gcc build/test.o -o build/test
	rm -f build/test.o
	./build/test

clean:
	-rm -rf build/