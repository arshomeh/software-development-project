#
# In order to execute this "Makefile" just type "make"
#

OBJS 	= main.o random.o HamMain.o  VecMain.o MatMain.o ./HamLSH/hashFun.o ./VecLSH/hashFunVec.o ./MatLSH/MatHash.o
SOURCE	= main.c random.c HamMain.c  VecMain.c MatMain.c ./HamLSH/hashFun.c ./VecLSH/hashFunVec.c ./MatLSH/MatHash.c 
HEADER  = headers.h lshmains.h random.h HamMain.h VecMain.h MatMain.h ./HamLSH/hashFun.h ./HamLSH/myRecords.h  ./VecLSH/hashFunVec.h ./VecLSH/VecRec.h ./MatLSH/MatHash.h ./MatLSH/MatRec.h  
OUT  	= test
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

random.o: random.c
	$(CC) $(FLAGS)  random.c $(LDFLAGS)
	
HamMain.o: HamMain.c
	$(CC) $(FLAGS)  HamMain.c $(LDFLAGS)

VecMain.o: VecMain.c
	$(CC) $(FLAGS)  VecMain.c $(LDFLAGS)

MatMain.o: MatMain.c
	$(CC) $(FLAGS)  MatMain.c $(LDFLAGS)

hashFun.o: ./Hamm/hashFun.c
	$(CC) $(FLAGS)  ./HamLSH/hashFun.c $(LDFLAGS)

hashFunVec.o: ./Vec/hashFunVec.c
	$(CC) $(FLAGS)  ./VecLSH/hashFunVec.c $(LDFLAGS)

MatHash.o: ./Mat/MatHash.c
	$(CC) $(FLAGS)  ./MatLSH/MatHash.c $(LDFLAGS)
 
# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
