/**CFile***********************************************************************

  Fichero     hash.c

  Resumen     Este fichero incluye todas las funciones que implican la modificación de la estructura "tabla hash"

  Descripción Funciones a las que se pasa como parámetro la estructura principal del programa, "tabla hash", se encarga de crear, modificar y redimensionar.

  Autor       Diego Rodríguez Soria, Daniel Ruiz García, Álvaro Pérez Benayas, Esther Rituerto González

  Copyright   [Copyright (c) 2012 Universidad Carlos III de Madrid

  Se concede, sin necesidad de acuerdo por escrito y sin ningún tipo de derechos
  de autor, permiso para utilizar, copiar, modificar y distribuir este programa
  y su documentación para cualquier propósito siempre y cuando esta advertencia
  y los siguientes dos párrafos aparezcan en las copias.

  EN NINGÚN CASO SE RECONOCERÁ A LA UNIVERSIDAD CARLOS III DE MADRID RESPONSABLE
  DIRECTA, INDIRECTA, ESPECIAL, O SUBSIDIARIA DE LOS POSIBLES DAÑOS Y PERJUICIOS
  QUE PUEDAN DERIVARSE DEL USO DE ESTE PROGRAMA Y DE SU DOCUMENTACIÓN, INCLUSO
  EN EL CASO DE QUE LA UNIVERSIDAD CARLOS III DE MADRID HAYA SIDO ADVERTIDA DE
  TALES DAÑOS Y PERJUICIOS.

  LA UNIVERSIDAD CARLOS III DE MADRID ESPECÍFICAMENTE SE DESENTIENDE DE TODO
  TIPO DE GARANTÍAS INCLUYENDO, PERO NO LIMITANDOLAS A, LAS GARANTIAS IMPLÍCITAS
  DE LA COMERCIALIZACIÓN Y ADECUACIÓN PARA CUALQUIER PROPÓSITO EN PARTICULAR. EL
  PROGRAMA SE PROVEE TAL CUAL Y LA UNIVERSIDAD CARLOS III DE MADRID NO TIENE
  OBLIGACIÓN ALGUNA DE OFRECER MANTENIMIENTO, SOPORTE, ACTUALIZACIONES, MEJORAS
  O MODIFICACIONES.]

******************************************************************************/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>
#include <ctype.h>
#include "hash.h"

/**Función*crear*tabla********************************************************************

  Resumen      Crea una tabla hash 

  Parámetros   Posiciones  

  Efec. Colat. Inicializa las posiciones del array de la tabla a NULL y sus parámetros a cero.

******************************************************************************/
struct tabla_hash* crear_tabla(int posiciones)
{
  int i;
  struct tabla_hash *tabla = (struct tabla_hash*)malloc(sizeof(struct tabla_hash));
  (*tabla).size = posiciones;
  (*tabla).array=(struct node **)malloc((*tabla).size*sizeof(struct node*));
  for(i = 0; i<(*tabla).size;i++)
  {
    (*tabla).array[i] = NULL;
  }
  (*tabla).nodos = 0;
  return tabla;
}
/**Función*hash********************************************************************

  Resumen      Calcula la posición del array de la tabla hash en la que se introducirá el nodo

  Parámetros   Char *clave (DOI) e int size(tamaño array tabla hash) 

******************************************************************************/
int funcion_hash(char *clave, int size)
{
  int i;
  int valor = 0;
  for(i = 0; i < strlen(clave); i++)
  {
    valor = valor + clave[i];
  }
  while(valor>size)
  {
    valor = valor/(size+1);
  }  
  if(valor<=0)
  {
    return 0;
  }else{
    return valor-1;
  }
}
  
/**Función*insertar*nodo*a*lista*******************************************************************

  Resumen      Inserta un nodo a la tabla hash

  Parámetros   Struct tabla_hash *tabla, struct publicacion publi 


******************************************************************************/
void insertar_nodo_a_lista (struct tabla_hash *tabla, struct publicacion publi)
{
  int posicion = funcion_hash(publi.DOI, (*tabla).size);
  struct node *nodo = crear_nodo(publi);
  struct node *aux = (*tabla).array[posicion];
  if(aux == NULL)
  {
    (*tabla).array[posicion] = nodo;
  }else{
    while((*aux).next !=NULL)
    {  
      aux = (*aux).next;
    }
    (*aux).next = nodo;
  }
  (*tabla).nodos++;
}

/**Función*redimensionar*******************************************************************

  Resumen      Redimensiona la tabla hash, la tabla hash óptima sería una cuadrada, que tuviese el mismo número de nodos que
  de posiciones en el array, por lo que halla la raíz del numero de nodos que tiene la antigua tabla y crea una nueva que tiene 
  como posiciones del array esa raíz.

  Parámetros   Struct tabla_hash *tabla  
  
******************************************************************************/
struct tabla_hash* redimensionar(struct tabla_hash *tabla)
{   
  struct tabla_hash *nueva = (struct tabla_hash*)malloc(sizeof(struct tabla_hash));
  int i;
  struct node *aux;
  struct node *a_liberar;
  double raiz = sqrt((*tabla).nodos);
  double densidad = round(raiz);
  int dens = (int)densidad;  
  if(dens>(*tabla).size-1 && dens<(*tabla).size+1)
  {
    free(nueva);
    return tabla;
  }else{
     nueva = crear_tabla(dens);
    for(i = 0; i<(*tabla).size; i++)
      {
      aux = (*tabla).array[i];
      while(aux != NULL)
      {
	insertar_nodo_a_lista(nueva, (*aux).info);
	a_liberar = aux;
	aux = (*aux).next;
	free(a_liberar);
      }
    }
    
  free((*tabla).array);
  free(tabla);
  tabla = NULL;
  return nueva;
  }   
}

/**Función*mostrar*informacion*publicacion*****************************************************************

  Resumen      Muestra todos los datos de una publicación previamente pidiendo su DOI

  Parámetros   struct tabla_hash *tabla, char *id  

******************************************************************************/
void mostrar_informacion_publicacion (struct tabla_hash *tabla, char *id)
{
 int posicion;
 int comprobar;
 struct node *aux;
 posicion = funcion_hash(id, (*tabla).size);
 aux = (*tabla).array[posicion];
 comprobar=strcmp(id, (*aux).info.DOI);
 while(aux != NULL && comprobar!=0)
 {
   aux = (*aux).next;
   comprobar=strcmp(id, (*aux).info.DOI);
 }
 if(aux == NULL)
 {
   printf("No existe ninguna publicación con el DOI introducido"); 
 }else{
   printf("Ésta es la información de su publicación:\n"); 
   mostrar_info((*aux).info);
 }
}

/**Función*mostrar*resumen******************************************************************

  Resumen      Hace lo requerido en el punto 3 del trabajo, muestra algunos campos de las publicaciones de la tabla

  Parámetros   Struct tabla_hash *tabla  

******************************************************************************/
void mostrar_resumen (struct tabla_hash *tabla)
{
  struct node *aux;
  int i;
  if(tabla == NULL){
    printf("No se ha podido mostrar un resumen, la tabla está vacía.\n");
  }else{
    for(i=0; i<(*tabla).size; i++)
    {
      aux=(*tabla).array[i];
      while(aux != NULL)
      {  
	printf("DOI: %30s", (*aux).info.DOI);
	printf("Título: %27s", (*aux).info.titulo); 
	printf("Año: %29i\n\n", (*aux).info.anio);
	aux = (*aux).next;
      }
    }
  }
}

/**Función*borrar*publicacion******************************************************************

  Resumen      Elimina una publicación previamente seleccionando su DOI

  Parámetros   struct tabla_hash *tabla, char *id  

******************************************************************************/
void borrar_publicacion (struct tabla_hash *tabla, char *id)
{
 int posicion;
 int comprobar;
 struct node *aux;
 struct node *aux2;
 posicion = funcion_hash(id, (*tabla).size);
 aux = (*tabla).array[posicion];
 
 if(aux == NULL)
 { 
   printf("No hay ninguna publicación con ese DOI.\n");
 }else if(aux != NULL && (*aux).next == NULL)
 { 
    comprobar=strcmp(id, (*aux).info.DOI);
    if(comprobar == 0)
    {
      free((*tabla).array[posicion]);
      (*tabla).array[posicion]=NULL;
      printf("Se ha borrado la publicación.\n");
      (*tabla).nodos--;
    }else{
      printf("No hay ninguna publicación con ese DOI.\n"); 
    }
 }else{ 
  comprobar=strcmp(id, (*aux).info.DOI);
  aux2=(*aux).next;
  while(aux2!=NULL && comprobar!=0)
  {
    comprobar=strcmp(id, (*aux2).info.DOI);
    if(comprobar!=0)
    {
      aux = (*aux).next;
      aux2 = (*aux2).next;
    }
  }
  if(comprobar==0)
  {
    struct node *liberado=(*aux).next;
    (*aux).next=(*aux2).next;
    free(liberado);
    printf("Se ha borrado la publicación.\n");
    (*tabla).nodos--;
  }else{
    printf("No hay ninguna publicación con ese DOI.\n"); 
  }
 }
}

/**Función*modificar*publicacion******************************************************************

  Resumen      Da la opcion al usuario de modificar todos los campos de la publicacion

  Parámetros   struct tabla_hash *tabla, char *id  

******************************************************************************/
void modificar_publicacion(struct tabla_hash *tabla, char *id)
{
  borrar_publicacion(tabla, id);
  printf("Ahora se le da la opción de modificar los campos de su publicación\n");
  leer_e_insertar(tabla);
}


/**Función*mostrar*publicacion*por*fechas******************************************************************

  Resumen      Recorre los nodos de la tabla hash y los guarda en un array, para después imprimir los 10 primeros dependiendo de la fecha
  introducida

  Parámetros   struct tabla_hash *tabla, int year 

******************************************************************************/
void mostrar_publicacion_fecha (struct tabla_hash *tabla, int year) 
{
  int i=0;
  int j;
  int k;
  int l=0;
  int m=0;
  int empezar=-1;
  struct node *aux;
  struct publicacion fechas[(*tabla).nodos];
  struct publicacion inter;
  for(j=0;j<(*tabla).size; j++){
     aux = (*tabla).array[j];
     while(aux != NULL){
        fechas[i] = (*aux).info;
	i++;
	aux = (*aux).next;
    }
  }
  if((*tabla).nodos > 1)
  {
    for(k=0; k<(*tabla).nodos; k++)
    {
      if((fechas[k]).anio<(fechas[k+1]).anio){
      inter = fechas[k];
      fechas[k] = fechas[k+1];
      fechas[k+1] = inter;
      k=-1;
      }
    }
  }
  while(l<(*tabla).nodos)
  {
    if(fechas[l].anio <= year){
      empezar = l;
      l = (*tabla).nodos;
    }
    l++;
  }
  if(empezar == -1)
  {
     printf("No se ha encontrado ninguna publicación con ese año");
  }else{
    while(m<10)
    {
      if(empezar+m < (*tabla).nodos)
      {
	mostrar_info(fechas[empezar+m]);
	m++;
      }else{
	m=10;
      }
    }
  }
}


/**Función*detecta*numeros******************************************************************

  Resumen     Detecta si hay un numero en la cadena

  Parámetros   char *escrito, int size  

******************************************************************************/

int detector_numeros(char *escrito, int size)
{
 int resultado=0; 
 int i;
 for(i=0; i<size; i++)
 {
    resultado=isdigit(escrito[i]);
    if(resultado!=0)
    {
     printf("Se ha detectado un caracter invalido\n"); 
     i=size;
    }
  }
return resultado;
}

/**Función*detector*caracteres******************************************************************

  Resumen      Detecta si hay una letra en la cadena

  Descripción  Se encarga de detectar caracteres en las cadenas

******************************************************************************/
int detector_caracteres(char *escrito, int size)
{
 int comprobador=1; 
 int i;
 for(i=0; i<size; i++)
 {
    comprobador=isalpha(escrito[i]);
    if(comprobador!=0)
    {
     printf("Se ha detectado un caracter invalido\n"); 
     i=size;
    }
 }
  return comprobador;
}

/**Función********************************************************************

  Resumen      Función como "data_read()", devuelve una cadena leida

******************************************************************************/
char *leer_algo()
{
 unsigned int n=0;
 char *c;
 unsigned int size_leido = size_leido=getline(&c, &n, stdin);
 return c;
}
   
/**Función********************************************************************

  Resumen      Lee por teclado una publicación y la inserta a la tabla hash actual

  Parámetros   Struct tabla_hash *tabla

******************************************************************************/
void leer_e_insertar(struct tabla_hash *tabla)
{
  unsigned int n=0;
  int size_leido;
  char *cadena;
  char *fincadena;
  //int comprobador 1 y 2 se encargaran de crear un bucle para introducir palabras o fechas correctamente
  int comprobador=1;
  int comprobador2=1;
  int numero;
  float fac_imp;
  struct publicacion nueva_publicacion;
    
  //INTRODUCIMOS EL DOI
  printf("Introduzca el DOI\n");
  size_leido=getline(&cadena, &n, stdin);
  if(feof(stdin))
  {
   printf("Usted ha pulsado Ctrl+D\n");
   printf("Finalizando programa\n");
   exit(0);
  }
  nueva_publicacion.DOI=cadena;
  cadena = NULL;
//-------------------------------------------------------
  //INTRODUCIMOS EL TITULO
  while(comprobador!=0)
  {
    printf("Introduzca el titulo de la publicación: \n");
    size_leido=getline(&cadena, &n, stdin);
    if(feof(stdin)){
    printf("Usted ha pulsado Ctrl+D\n");
    printf("Finalizando programa\n");
    exit(0);
    }
    comprobador=detector_numeros(cadena, size_leido);
  }
  nueva_publicacion.titulo=cadena;
  comprobador=1;
  cadena=NULL;
//-------------------------------------------------------
  //INTRODUCIMOS EL ISSN
  printf("Introduzca el ISSN: \n");
  size_leido=getline(&cadena, &n, stdin);
  if(feof(stdin)){
   printf("Usted ha pulsado Ctrl+D\n");
   printf("Finalizando programa\n");
   exit(0);
  }
  nueva_publicacion.ISSN=cadena;
  cadena = NULL;
//-------------------------------------------------------
  //INTRODUCIMOS EL NOMBRE DE LA FUENTE
  while(comprobador!=0)
  {
  printf("Introduzca el nombre de la fuente: \n");
  size_leido=getline(&cadena, &n, stdin);
   if(feof(stdin)){
    printf("Usted ha pulsado Ctrl+D\n");
    printf("Finalizando programa\n");
    exit(0);
   }
  comprobador=detector_numeros(cadena, size_leido);
  }
  nueva_publicacion.nombre_fuente=cadena;
  comprobador=1;
  cadena = NULL;
//--------------------------------------------------------
  //INTRODUCIMOS EL NOMBRE DE LOS AUTORES DE LA FUENTE
  while(comprobador!=0)
  {
    printf("Introduzca el nombre de los autores de la publicación: \n");
    size_leido=getline(&cadena, &n, stdin);
    if(feof(stdin)){
    printf("Usted ha pulsado Ctrl+D\n");
    printf("Finalizando programa\n");
    exit(0);
    }
    comprobador=detector_numeros(cadena, size_leido);
  }
  nueva_publicacion.autores=cadena;
  comprobador=1;
  cadena = NULL;
//--------------------------------------------------------
  //INTRODUCIMOS EL AÑO DE PUBLICACION
  while(comprobador2!=0)
  {
    printf("Introduzca el año de publicación: \n");
    size_leido=getline(&cadena, &n, stdin);
    if(feof(stdin)){
      printf("Usted ha pulsado Ctrl+D\n");
      printf("Finalizando programa\n");
      exit(0);
    }
    comprobador2=detector_caracteres(cadena, size_leido);
  }
  numero=strtol(cadena, &fincadena, 10);
  nueva_publicacion.anio=numero;
  comprobador2=1;
  cadena = NULL;
//--------------------------------------------------------
  //INTRODUCIMOS EL FACTOR DE IMPACTO
  while(comprobador2!=0){
    printf("Introduzca el factor de impacto: \n");
    size_leido=getline(&cadena, &n, stdin);
    if(feof(stdin)){
      printf("Usted ha pulsado Ctrl+D\n");
      printf("Finalizando programa\n");
      exit(0);
    }
    comprobador2=detector_caracteres(cadena, size_leido);
  }
  fac_imp=atof(cadena);
  nueva_publicacion.factor_impacto=fac_imp;
  cadena = NULL;
//--------------------------------------------------------
    //INTRODUCIMOS LA VARIABLE PARTICULAR	
   while(comprobador!=0){
  printf("Introduzca el nombre de la variable particular: \n");
  size_leido=getline(&cadena, &n, stdin);
  if(feof(stdin)){
   printf("Usted ha pulsado Ctrl+D\n");
   printf("Finalizando programa\n");
   exit(0);
 }
  comprobador=detector_numeros(cadena, size_leido);
  }
  nueva_publicacion.variable_particular=cadena;
  cadena = NULL;
//----------------------------------------------------------
  
  insertar_nodo_a_lista(tabla, nueva_publicacion);
}
