#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char dato;
	struct Nodo* ptrNext;
}Nodo;

Nodo* header = NULL;
Nodo* footer = NULL;

Nodo* new(){
	Nodo* nuevo = (Nodo*) malloc(sizeof(Nodo));
	nuevo -> ptrNext = NULL;
	return(nuevo); 
}

void insertar(Nodo* nodo){
	if(header == NULL){
		header = nodo;
		footer = nodo;
	}
	else
	{
		footer -> ptrNext = nodo; //nodo
		footer = nodo;
	}
}

void walkList(){
	Nodo* i = header;	
	if(i == NULL){
		printf("Lista vacia\r\n");
		return;
	}
	while(i != NULL){
		printf("%d -> ", i->dato);
		i = i -> ptrNext;		
	}
	printf("\n\r");
}

void append(char dato){
	Nodo* nodo = new();	//Se crea el nodo
	nodo -> dato = dato; //Se le asigna valor al nodo
	insertar(nodo); //se inserta a la lista
}

int main(){
	append(4);
}
