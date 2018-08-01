CC         = gcc
CFLAGS     = -std=c11 -Wall -Wextra -pedantic -g
FICHEIROS  = exemplo.c cgi.h estado.c estado.h stack.c stack.h verificacao.c verificacao.h ajuda.c ajuda.h ficheiros.c ficheiros.h comparacoes.c comparacoes.h jogo.c jogo.h Makefile
OBJS       = estado.o stack.o verificacao.o ficheiros.o comparacoes.o ajuda.o jogo.o exemplo.o
EXECUTAVEL = GandaGalo

install: $(EXECUTAVEL)
	sudo cp $(EXECUTAVEL) /usr/lib/cgi-bin
	touch install
	sudo chmod -R a+rwx /var/www/html/*

$(EXECUTAVEL): $(OBJS)
	$(CC) -o $(EXECUTAVEL) $(OBJS)

imagens:
	sudo mkdir -p /var/www/html/images
	sudo cp ./Images/*.png /var/www/html/images

tabuleiros:
	sudo mkdir -p /var/www/html/tabuleiros
	sudo cp ./Tabuleiros/*.txt /var/www/html/tabuleiros

utilizadores:
	sudo mkdir -p /var/www/html/users
	sudo cp ./Users/*.txt /var/www/html/users

doc:
	doxygen -g
	doxygen

clean:
	rm -rf *.o $(EXECUTAVEL) Doxyfile latex html install