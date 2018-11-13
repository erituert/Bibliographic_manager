/**CHeaderFile*****************************************************************

  Fichero     [exportar.c]

  Resumen     [Opción para exportar información a un fichero]

  Descripción [En este fichero vamos a guardar toda la información almacenada en las publicaciones de una tabla]

  Autor       [Diego Rodríguez Soria, Daniel Ruiz García, Álvaro Pérez Benayas, Esther Rituerto González]

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

#include <stdio.h>
#include <string.h>
#include "exportar.h"


/**Función********************************************************************

  Resumen      [Función que escribe en un archivo de texto]

  Descripción  [En esta función iremos recorriendo la tabla así como las listas enlazadas de cada posición para ir guardando cada nodo en el archivo]

  Parámetros   [char *nombre_archivo: Nombre con el que designaremos al archivo]  
	       [struct tabla_hash *tabla: Estructura a guardar en el archivo]

  Efec. Colat. [Escribe en un archivo de texto cada una de las variables de una publicacion]

******************************************************************************/

void exportar(char *nombre_archivo, struct tabla_hash *tablah){
  
  /**Variables********************************************************************

  Resumen     [Declaración de variables]

  Descripción [char *salto2: Variable encargada de separar las variables int en el archivo de texto.]
              [nombre_archivo[]: Variable utilizada para designar el nombre del archivo de texto a usar. Además eliminamos el salto de 
              línea de la cadena.]
              

******************************************************************************/
  FILE *fichero;
  struct node *aux;
  int corredor_tabla, tamanio, cerrado; 
  int tamanio_nombre_archivo=strlen(nombre_archivo);
  nombre_archivo[tamanio_nombre_archivo-1] = '\0';
  char *salto2="\n";
  
  fichero=fopen(nombre_archivo, "wb");
  if(fichero==NULL){
   printf("Hubo un error a la hora de abrir el fichero\n");
  }else{
   printf("Procedemos a guardar los datos\n");
   
	fwrite(&tablah->nodos, sizeof(int), 1, fichero);
	fwrite(salto2, sizeof(char), 1, fichero);

   for(corredor_tabla=0; corredor_tabla<tablah->size; corredor_tabla++){
    aux=tablah->array[corredor_tabla];
    if(aux!=NULL){

      while(aux!=NULL){
      
	tamanio=strlen(aux->info.DOI);
	fwrite(&tamanio, sizeof(int), 1, fichero);
	fwrite(aux->info.DOI, sizeof(char), tamanio, fichero);
	tamanio=0;

	tamanio=strlen(aux->info.titulo);
	fwrite(&tamanio, sizeof(int), 1, fichero);
	fwrite(aux->info.titulo, sizeof(char), tamanio, fichero);
	tamanio=0;
	
	tamanio=strlen(aux->info.ISSN);
	fwrite(&tamanio, sizeof(int), 1, fichero);
	fwrite(aux->info.ISSN, sizeof(char), tamanio, fichero);
	tamanio=0;
	
	tamanio=strlen(aux->info.nombre_fuente);
	fwrite(&tamanio, sizeof(int), 1, fichero);
	fwrite(aux->info.nombre_fuente, sizeof(char), tamanio, fichero);
	tamanio=0;
	
	tamanio=strlen(aux->info.autores);
	fwrite(&tamanio, sizeof(int), 1, fichero);
	fwrite(aux->info.autores, sizeof(char), tamanio, fichero);
	tamanio=0;
	
	fwrite(&aux->info.anio, sizeof(int), 1, fichero);
	fwrite(salto2, sizeof(char), 1, fichero);
	fwrite(&aux->info.factor_impacto, sizeof(double), 1, fichero);
	fwrite(salto2, sizeof(char), 1, fichero);
	
	tamanio=strlen(aux->info.variable_particular);
	fwrite(&tamanio, sizeof(int), 1, fichero);
	fwrite(aux->info.variable_particular, sizeof(char), tamanio, fichero);
	tamanio=0;
	
	aux=aux->next;
      }
    }
   }
  }
    cerrado=fclose(fichero);
    if(cerrado==0){
    printf("Datos guardados\n");
    }else{
     printf("Hubo un error al cerrar el fichero\n"); 
    }
}
