HEADERS = include/redshell/command.h include/redshell/encoder.h include/redshell/imu.h include/redshell/power.h include/redshell/usb_protocol.h
CFLAGS = -Iinclude

default: test

test.o: src/test.c $(HEADERS)
	make clean
	mkdir build/
	gcc $(CFLAGS) -c src/test.c -o build/test.o

test: test.o
	gcc build/test.o -o build/test
	rm -f build/test.o
	./build/test

clean:
	-rm -rf build/