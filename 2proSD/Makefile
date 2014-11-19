#
# In order to execute this "Makefile" just type "make"
#

OBJS 	= main.o mainfuns.o
SOURCE	= main.c mainfuns.c
HEADER  = headers.h define.h mainfuns.h
OUT  	= medoids
CC	= gcc
FLAGS   = -g -c 
LDFLAGS = -lm
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LDFLAGS)

# create/compile the individual files >>separately<< 
main.o: main.c
	$(CC) $(FLAGS)  main.c $(LDFLAGS)

mainfuns.o: mainfuns.c
	$(CC) $(FLAGS)  mainfuns.c $(LDFLAGS)

 
# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
