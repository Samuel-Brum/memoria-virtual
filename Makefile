CC = gcc
CFLAGS = -Wall -g

SRCS = tp2virtual.c algsRepo.c trocaPag.c lista.c
OBJS = $(SRCS:.c=.o)
DEPS = memoria.h lista.h algsRepo.h trocaPag.h

TARGET = tp2virtual

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)