
#for test on another platform
CC=gcc
CFLAGS=-c -Wall -Werror
EXECUTABLE=gpio_devmem

all: $(EXECUTABLE)

main.o: main.c
			$(CC) $(CFLAGS) -o main.o main.c

gpio_devmem.o: gpio_devmem.c
			$(CC) $(CFLAGS) -o gpio_devmem.o gpio_devmem.c

$(EXECUTABLE): main.o gpio_devmem.o
			$(CC) -o $(EXECUTABLE) main.o gpio_devmem.o

clean:
			rm -rf $(EXECUTABLE) *.o