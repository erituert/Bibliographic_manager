#ifndef HASH_H
#define HASH_H
#include<stdio.h>

struct tabla_hash
 { 
  struct node **array;
  int size;
  int nodos;
};

struct tabla_hash* crear_tabla(int posiciones);

int funcion_hash(char *clave, int size);

void insertar_nodo_a_lista(struct tabla_hash *tabla, struct publicacion publi);

struct tabla_hash* redimensionar(struct tabla_hash *tabla);

void mostrar_informacion_publicacion (struct tabla_hash *tabla, char *id);

void mostrar_resumen (struct tabla_hash *tabla);

void borrar_publicacion (struct tabla_hash *tabla, char *id);

void modificar_publicacion(struct tabla_hash *tabla, char *id);

void mostrar_publicacion_fecha (struct tabla_hash *tabla, int year);

int detector_numeros(char *escrito, int size);

int detector_caracteres(char *escrito, int size);

char * leer_algo();

void leer_e_insertar(struct tabla_hash *tabla);


#endif
