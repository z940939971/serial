CC = arm-none-linux-gnueabi-gcc

MAIN = main_serial


$(MAIN):*.c
	$(CC) $^ -o $@ -lpthread

clean:
	$(RM) serial
