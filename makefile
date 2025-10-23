main : biblioLC.o EntreeSortieLC.o main.o
	gcc -o $@ $^

biblioLC.o : biblioLC.c biblioLC.h
	gcc -c biblioLC.c

EntreeSortieLC.o :EntreeSortieLC.c EntreeSortieLC.h
	gcc -c EntreeSortieLC.c

main.o : main.c 
	gcc -c main.c 
clean :
	rm -f *.o 

