/**CHeaderFile*****************************************************************

  Fichero     [importar.c]

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
#include "importar.h"
#include <string.h>


/**Función********************************************************************

  Resumen      [Opción para importar una tabla de un fichero.]

  Descripción  [Mediante esta función cargaremos toda la información almacenada en una tabla.]

  Parámetros   [char come_salto: Esta variable almacena los saltos ya que no nos interesa almacenarlos, es simple orden.]  
	       [nombre_archivo[]: Variable utilizada para designar el nombre del archivo de texto a usar. Además eliminamos el salto de 
               línea de la cadena.]
               [int tamanio_a_leer: almacena el tamaño de cada cadena a almacenar para luego pasarselo a la strctura publicacion]   
	       [int cerrando: si cerrando es igual a 0 es que el fichero se ha cerrado con éxito.]
               [int contador: contador cuya función, junto con el while, es la de hacer un for decreciente. Al principio es igual al numero de nodos almacenados]
              

  Efec. Colat. [Se crea una nueva tabla a partir de lo escrito en el archivo de texto]

******************************************************************************/


struct tabla_hash * importar(char *nombre_archivo, struct tabla_hash *tablah){
  FILE *fichero;
  char come_salto='\0';
  int tamanio_nombre_archivo=strlen(nombre_archivo);
  nombre_archivo[tamanio_nombre_archivo-1] = '\0';
  fichero=fopen(nombre_archivo, "rb");
  struct publicacion publi;
  int tamanio_a_leer=0;   
  int cerrando=0;
  int contador;
  char *cadenaaux=NULL;
  
  if(fichero==NULL){
   printf("Hubo un error a la hora de abrir el fichero\n");
  }else{
   printf("Procedemos a cargar los datos\n");
   
    fread(&contador, sizeof(int), 1, fichero);
    printf("Numero de nodos: %d\n", contador);
    fread(&come_salto, sizeof(char), 1, fichero);
    come_salto='\0';
    
   
   while(contador!=0){
    fread(&tamanio_a_leer, sizeof(int), 1, fichero);
    cadenaaux=(char *)malloc(tamanio_a_leer+1);
    fread(cadenaaux, sizeof(char), tamanio_a_leer, fichero);
    tamanio_a_leer=0;
    publi.DOI=cadenaaux;
    cadenaaux=NULL;
    printf("DOI: %s", publi.DOI);
    free(cadenaaux);
    
    fread(&tamanio_a_leer, sizeof(int), 1, fichero);
    cadenaaux=(char *)malloc(tamanio_a_leer+1);
    fread(cadenaaux, sizeof(char), tamanio_a_leer, fichero);
    tamanio_a_leer=0;
    publi.titulo=cadenaaux;
    cadenaaux=NULL;
    printf("Titulo: %s", publi.titulo);
    free(cadenaaux);
    
    fread(&tamanio_a_leer, sizeof(int), 1, fichero);
    cadenaaux=(char *)malloc(tamanio_a_leer+1);
    fread(cadenaaux, sizeof(char), tamanio_a_leer, fichero);
    tamanio_a_leer=0;
    publi.ISSN=cadenaaux;
    cadenaaux=NULL;
    printf("ISSN: %s", publi.ISSN);
    free(cadenaaux);
    
    fread(&tamanio_a_leer, sizeof(int), 1, fichero);
    cadenaaux=(char *)malloc(tamanio_a_leer+1);
    fread(cadenaaux, sizeof(char), tamanio_a_leer, fichero);
    tamanio_a_leer=0;
    publi.nombre_fuente=cadenaaux;
    cadenaaux=NULL;
    printf("Nombre de la fuente: %s", publi.nombre_fuente);
    free(cadenaaux);
    
    fread(&tamanio_a_leer, sizeof(int), 1, fichero);
    cadenaaux=(char *)malloc(tamanio_a_leer+1);
    fread(cadenaaux, sizeof(char), tamanio_a_leer, fichero);
    tamanio_a_leer=0;
    publi.autores=cadenaaux;
    cadenaaux=NULL;
    printf("Autores: %s", publi.autores);
    free(cadenaaux);
    
    fread(&publi.anio, sizeof(int), 1, fichero);
    fread(&come_salto, sizeof(char), 1, fichero);
    printf("Anio: %d\n", publi.anio);
    come_salto='\0';
    
    
    fread(&publi.factor_impacto, sizeof(double), 1, fichero);
    fread(&come_salto, sizeof(char), 1, fichero);
    printf("Factor de impacto: %f\n", publi.factor_impacto);
    come_salto='\0';
    
    
    fread(&tamanio_a_leer, sizeof(int), 1, fichero);
    cadenaaux=(char *)malloc(tamanio_a_leer+1);
    fread(cadenaaux, sizeof(char), tamanio_a_leer, fichero);
    tamanio_a_leer=0;
    publi.variable_particular=cadenaaux;
    cadenaaux=NULL;
    printf("Variable particular: %s", publi.variable_particular);
    free(cadenaaux);
    
    
    insertar_nodo_a_lista(tablah, publi);
   
     
    --contador;
    }
    
    tablah=redimensionar(tablah);
    
   }
   
   cerrando=fclose(fichero);
   if(cerrando==0){
     printf("Datos importados con éxito\n");
   }else{
      printf("Hubo un error al intentar cerrar el archivo\n");
   }
   return tablah;
   }
    
  

