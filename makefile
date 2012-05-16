CFLAGS=-Wall -Wextra -std=c99 -g
OBJ=s-image.o s-mesh.o sraf.o driver.o

all: $(OBJ) writeit

writeit: $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

clean:
	rm -f *.o
