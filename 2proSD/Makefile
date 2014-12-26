#
# In order to execute this "Makefile" just type "make"
#

OBJS 	= main.o generalfuns.o aHamMain.o aEucMain.o aMatMain.o cluster.o algorithms.o ./Ham/hamfuns.o ./Euc/eucfuns.o ./Mat/matfuns.o 
SOURCE	= main.c generalfuns.c aHamMain.c aEucMain.c aMatMain.c cluster.c algorithms.c ./Ham/hamfuns.c ./Euc/eucfuns.c ./Mat/matfuns.c
HEADER  = headers.h defines.h mainfuns.h generalfuns.h cluster.h algorithms.h ./Ham/hamfuns.h ./Euc/eucfuns.h ./Mat/matfuns.h
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

generalfuns.o: generalfuns.c
	$(CC) $(FLAGS)  generalfuns.c $(LDFLAGS)

aHamMain.o: aHamMain.c
	$(CC) $(FLAGS)  aHamMain.c $(LDFLAGS)

aEucMain.o: aEucMain.c
	$(CC) $(FLAGS)  aEucMain.c $(LDFLAGS)

aMatMain.o: aMatMain.c
	$(CC) $(FLAGS)  aMatMain.c $(LDFLAGS)

cluster.o: cluster.c
	$(CC) $(FLAGS)  cluster.c $(LDFLAGS)

algorithms.o: algorithms.c
	$(CC) $(FLAGS)  algorithms.c $(LDFLAGS)

hamfuns.o: /Ham/hamfuns.c
	$(CC) $(FLAGS)  /Ham/hamfuns.c $(LDFLAGS)

eucfuns.o: /Euc/eucfuns.c
	$(CC) $(FLAGS)  /Euc/eucfuns.c $(LDFLAGS)

matfuns.o: /Mat/matfuns.c
	$(CC) $(FLAGS)  /Mat/matfuns.c $(LDFLAGS)

# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
