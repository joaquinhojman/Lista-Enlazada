#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stdlib.h>

struct lista;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

// Crea una lista.
// Post: devuelve una lista vacía.
lista_t* lista_crear(void);

// Devuelve verdadero si la lista tiene al menos un elemento, false si no.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t* lista);

// Agrega un elemento al principio de la lista. Devuelve false en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un elemento al principio de la lista.
bool lista_insertar_primero(lista_t* lista, void* dato);

// Agrega un elemento al final de la lista. Devuelve false en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un elemento al final de la lista.
bool lista_insertar_ultimo(lista_t* lista, void* dato);

// Elimina el primer elemento de la lista y lo devuelve.
// Pre: la lista fue creada.
// Post: se eliminó primer elemento de la lista y lo devolvio.
void *lista_borrar_primero(lista_t* lista);

// Obtiene el valor del primer elemento de la lista y se devuelve su valor. Si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t* lista);

// Obtiene el valor del último elemento de la lista y devuelve su valor. Si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el último elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

//Devuelve el largo de la lista.
//Pre: La lista fue creada.
//Post: se devuelve el largo de la lista.
size_t lista_largo(const lista_t* lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t* lista, void destruir_dato(void*));

//Recorre la lista. 
//Pre: la lista fue creada.
void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra);

// Crea un iterador de lista.
//Pre: la lista fue creada.
// Post: devuelve un iterador de lista.
lista_iter_t* lista_iter_crear(lista_t* lista);

//Avanza al siguiento nodo de la lista.
//Pre: el iterador fue creado.
//Post: devuelve true si avanzó al siguiente nodo, o false en caso de error.
bool lista_iter_avanzar(lista_iter_t* iter);

//Devuelve el dato del nodo en el que está posicionado.
//Pre: el iterador fue creado.
//Post: devolvió el dato del nodo actual.
void* lista_iter_ver_actual(const lista_iter_t* iter);

//Devuelve true si el iterador esta al final de la lista, false si no
//Pre: el iterador fue creado.
//Post: Devolvio si esta al final o no.
bool lista_iter_al_final(const lista_iter_t* iter);

//Elimina el iterador.
//Pre: el iterador fue creado.
//Post: se eliminó el iterador.
void lista_iter_destruir(lista_iter_t* iter);

//Inserta un nodo en el lugar del actual.
//Pre: el iterador fue creado.
//Post: se agregó un elemento en el lugar del actual.
bool lista_iter_insertar(lista_iter_t* iter, void* dato);

//Elimina el nodo actual.
//Pre: el iterador fue creado.
//Post: eliminó el nodo actual y devolvió su valor.
void* lista_iter_borrar(lista_iter_t* iter);

#endif // LISTA_H
