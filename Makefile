CC=gcc

CFLAGS= -Wall -Wextra

automaton : main.o utile.o automate.o create_automate.o
	$(CC) -o $@ $^ 

main.o : main.c automate.h create_automate.h utile.h
	$(CC) $(CFLAGS) -o $@ -c $<

automate.o : automate.c automate.h create_automate.h utile.h
	$(CC) $(CFLAGS) -o $@ -c $<

create_automate.o : create_automate.c create_automate.h
	$(CC) $(CFLAGS) -o $@ -c $<

utile.o : utile.c utile.h 
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f *.o 
	rm -f automaton
	rm -f *.out