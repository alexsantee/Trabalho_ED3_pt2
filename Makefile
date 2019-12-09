all:	programa.out

run:	programa.out
	./programa.out

clear:
	rm funcionalidades.o helper.o grafo.o leitor.o dijkstra.o prim.o main.o

programa.out:	funcionalidades.o helper.o grafo.o leitor.o dijkstra.o prim.o main.o
	g++ funcionalidades.o helper.o grafo.o leitor.o dijkstra.o prim.o main.o -o programa.out

funcionalidades.o:
	g++ -std=c++11 -c funcionalidades.cpp -o funcionalidades.o

helper.o:
	g++ -std=c++11 -c helper.cpp -o helper.o

grafo.o:
	g++ -std=c++11 -c grafo.cpp -o grafo.o

leitor.o:
	g++ -std=c++11 -c leitor.cpp -o leitor.o

dijkstra.o:
	g++ -std=c++11 -c dijkstra.cpp -o dijkstra.o

prim.o:
	g++ -std=c++11 -c prim.cpp -o prim.o

main.o:
	g++ -std=c++11 -c main.cpp -o main.o
