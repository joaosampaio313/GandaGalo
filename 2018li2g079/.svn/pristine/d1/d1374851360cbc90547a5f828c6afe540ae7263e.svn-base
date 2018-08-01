CFLAGS=-std=c11 -Wall -Wextra -pedantic -g
FICHEIROS=cgi.h estado.c estado.h exemplo.c ajuda.c ancoras.c verificacao.c verificacao.h Makefile
EXECUTAVEL=GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install
	sudo chmod -R a+rwx /var/www/html/*

$(EXECUTAVEL): exemplo.o estado.o
	cc -o $(EXECUTAVEL) exemplo.o estado.o

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp ./Images/*.png /var/www/html/images

puzzles:
		sudo mkdir -p /var/www/html/puzzles		
		sudo cp ./Puzzles/*.txt /var/www/html/puzzles
users:
	sudo mkdir -p /var/www/html/users
	sudo cp ./Users/*.txt /var/www/html/users

GandaGalo.zip: $(FICHEIROS)
	zip -9 GandaGalo.zip $(FICHEIROS)

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install

estado.o: estado.c estado.h
exemplo.o: exemplo.c cgi.h estado.h
