mainH : biblioH.o EntreeSortieH.o mainH.o
	gcc -o $@ $^

biblioH.o : biblioH.c biblioH.h
	gcc -c biblioH.c

EntreeSortieH.o :EntreeSortieH.c EntreeSortieH.h
	gcc -c EntreeSortieH.c

mainH.o : mainH.c 
	gcc -c mainH.c 
clean :
	rm -f *.o 

#ajouter -lm pour l'ajout de la bibliotheque math.h
