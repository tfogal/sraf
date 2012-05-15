CFLAGS=-Wall -Wextra
OBJ=s-image.o s-mesh.o sraf.o

all: $(OBJ)

clean:
	rm -f *.o
