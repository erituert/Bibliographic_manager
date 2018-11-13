#ifndef PUBLICACION_H
#define PUBLICACION_H
#include<stdio.h>

enum tipo_publicacion {conferencia, articulo};

struct publicacion{
  enum tipo_publicacion _publicacion;
  char *DOI;
  char *titulo;
  char *ISSN;
  char *nombre_fuente;
  char *autores;
  int anio;
  float factor_impacto;
  char *variable_particular;
};


void mostrar_info(struct publicacion a_mostrar);



#endif
