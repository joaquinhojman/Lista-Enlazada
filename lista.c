#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct nodo {
    void* dato;
    struct nodo* prox;
}nodo_t; 

struct lista {
    nodo_t* prim;
    nodo_t* ult;
    size_t largo;
};

struct lista_iter {
	lista_t* lista;	
    nodo_t* act;
    nodo_t* ant;
};

/*FUNCIONES*/

nodo_t* crear_nodo(void* valor) {
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo){
		return NULL;
	}
	nodo->dato = valor;
	nodo->prox = NULL;
	return nodo;
}
lista_t* lista_crear(void) {
	lista_t* lista = malloc(sizeof(lista_t));
	if (lista == NULL) 
		return NULL;
	lista->prim=NULL;
	lista->ult=NULL;
	lista->largo=0;
    return lista;
}

bool lista_esta_vacia(const lista_t* lista){
	if (lista->largo==0) return true;
	return false;
}

bool lista_insertar_primero(lista_t* lista, void* dato){
	nodo_t* primero=crear_nodo(dato);
	if(primero==NULL) return false;
	lista->largo+=1;
	if (lista->prim==NULL){
		lista->prim=primero;
		lista->ult=lista->prim;
	}else{
		primero->prox=lista->prim;
		lista->prim=primero;
	}	
	return true;
}

bool lista_insertar_ultimo(lista_t* lista, void* dato){
	nodo_t* ultimo=crear_nodo(dato);
	if(ultimo==NULL) return false;
	if (lista_esta_vacia(lista)){
		lista->prim=ultimo;
		lista->ult=lista->prim;
	}else{
		lista->ult->prox=ultimo;
		lista->ult=lista->ult->prox;
	}
	lista->largo+=1;
	return true;
}

void *lista_borrar_primero(lista_t* lista){
	if(lista->largo==0) return NULL;
	void* primero=lista->prim->dato;
	void* prox=lista->prim->prox;
	free(lista->prim);
	if (lista->largo==1){
		lista->ult=NULL;
		lista->prim=NULL;
	}else{
		lista->prim=prox;	
	}
	lista->largo-=1;
	return primero;
}

void *lista_ver_primero(const lista_t* lista){
	if(!lista->prim) return NULL;
	return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if(!lista->ult) return NULL;
	return lista->ult->dato;
}

size_t lista_largo(const lista_t* lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void*)) {
	while(!lista_esta_vacia(lista)){
		if(destruir_dato)
			destruir_dato(lista->prim->dato);
		lista_borrar_primero(lista);
	}
	free(lista);
}

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra){
	nodo_t* actual=lista->prim;
	while(actual){
		if(visitar){
			bool aux=visitar(actual->dato,extra);
			if(!aux) break;
		}
		actual=actual->prox;
	}
}

lista_iter_t* lista_iter_crear(lista_t* lista){
	lista_iter_t* lista_iter = malloc(sizeof(lista_iter_t));
	if (lista_iter == NULL) 
		return NULL;
	lista_iter->lista=lista;
	lista_iter->act=lista_iter->lista->prim;
	lista_iter->ant=NULL;
    return lista_iter;
}

bool lista_iter_avanzar(lista_iter_t* iter){
	iter->ant=iter->act;
	if(!iter->act) return false;
	iter->act=iter->act->prox;
	return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
	if(!iter->act) return NULL;
	return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t* iter){
	if (!iter->act) return true;
	return false;
}

void lista_iter_destruir(lista_iter_t* iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato){
	nodo_t* nodo=crear_nodo(dato);
	if(nodo==NULL) return false;
	if(!iter->ant) iter->lista->prim=nodo;
	else iter->ant->prox=nodo;
	if(lista_iter_al_final(iter)) iter->lista->ult=nodo;
	nodo->prox=iter->act;
	iter->act=nodo;
	iter->lista->largo+=1;	
	return true;	
}

void* lista_iter_borrar(lista_iter_t* iter){
	if(lista_esta_vacia(iter->lista)||!iter->act) 
		return NULL;
	nodo_t* borrar=iter->act;
	void* elem=borrar->dato;
	if(lista_iter_al_final(iter))
		return NULL;
	if(!iter->ant) 
		iter->lista->prim=iter->act->prox;
	else
		iter->ant->prox=iter->act->prox;
	if(!iter->act->prox) 
		iter->lista->ult=iter->ant;
	iter->act=iter->act->prox;
	free(borrar);
	iter->lista->largo-=1;
	return elem;
}
