CFLAGS=-std=c11 -O2 -Wall -Wextra -pedantic -g
FICHEIROS= gerar.c gerar.o Makefile 
EXECUTAVEL=Gerar

$(EXECUTAVEL): $(FICHEIROS) gerar.c
	cc -o $(EXECUTAVEL) $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install

gerar.o : gerar.c
