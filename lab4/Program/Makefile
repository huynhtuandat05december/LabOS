all:
	gcc pi_serial.c -o pi_serial
	gcc pi_multi-thread.c -lpthread -o pi_multi-thread
	gcc code.c -lpthread -o code
clean:
	rm -f *o pi_serial pi_multi-thread code
