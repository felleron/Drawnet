CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lSDL2
INCLUDES = -I/usr/include/SDL2/
SRCS = drawnet.c
OBJS = $(SRCS:.c=.o)
MAIN = drawnet

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIBS)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) *.o *~ $(MAIN)