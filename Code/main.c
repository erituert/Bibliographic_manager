/**CFile***********************************************************************

  Fichero     main.c

  Resumen     Utilizamos una variable tabla_hash para todo el programa. Aquí está el menú principal

  Autor       Diego Rodríguez Soria, Daniel Ruiz García, Álvaro Pérez Benayas, Esther Rituerto González

  Copyright   [Copyright (c) 2011 Universidad Carlos III de Madrid
  
  Referencias "C con clase", "Wikipedia", "Programación en C" y "Cpluplus.com"

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
#include <math.h>
#include <stdlib.h>
#include "publicacion.c"
#include "node.c"
#include "hash.c"
#include "importar.c"
#include "exportar.c"


 int main(){  
  printf("\n=HASH-BIBMANAGER (Eficient Edd.)=\n\n");
  printf("[1]     Salir \n");
  printf("[2]     Insertar\n");
  printf("[3]     Mostrar resumen\n");
  printf("[4]     Mostrar una publicación\n");
  printf("[5]     Modificar una publicación\n");
  printf("[6]     Borrar una publicación\n");
  printf("[7]     Exportar a un archivo\n");
  printf("[8]     Importar de un archivo\n");
  printf("[9]     Mostrar publicaciones cronológicamente\n\n");
  
  
  struct tabla_hash *tabla=crear_tabla(10);
  
  char *leido=NULL;
  int continuar=1;
  int numero;
  int opcion;
  char *cadena;
  unsigned int n = 0;
  int size_leido;
  
  while(continuar == 1){
    printf("      Introduzca una opción:\n");
    size_leido = getline(&cadena, &n, stdin);
    opcion = atoi(cadena);
    if(opcion == 1){
	    printf("	Ha salido del programa\n");
	    continuar = 0;
    }else if(opcion == 2){
    	    printf("\n	Insertar publicación:\n");
	    leer_e_insertar(tabla);
	    tabla = redimensionar(tabla);
    }else if(opcion == 3){
	    printf("\n	A continuación se mostrará un resumen:\n");
	    mostrar_resumen(tabla);
    }else if(opcion == 4){
    	    printf("\n	Inserte el DOI de la publicación a buscar:\n");
	    leido=leer_algo();
	    mostrar_informacion_publicacion(tabla, leido);
	    leido=NULL;
    }else if(opcion == 5){
    	    printf("\n	Inserte el DOI de la publicación a modificar:\n");
            leido=leer_algo();
	    modificar_publicacion(tabla, leido);
	    leido=NULL;
    }else if(opcion == 6){
	    printf("\n	Inserte el DOI de la publicación a borrar:\n");
	    leido=leer_algo();
            borrar_publicacion(tabla, leido);
	    leido = NULL;
    }else if(opcion == 7){
	    printf("\n	Inserte el nombre del archivo al que desee exportar:\n");
	    leido=leer_algo();
            exportar(leido, tabla);
	    leido=NULL;
    }else if(opcion == 8){
	    printf("\n	Inserte el nombre del archivo del que desee importar:\n");
	    leido=leer_algo();
            tabla=importar(leido, tabla);
	    leido=NULL;
    }else if(opcion == 9){
	    printf("\n	A continuación se mostrará las publicaciones cronológcamente:\n");
	    leido = NULL;
	    printf("Introduzca el año a partir del cual quiera buscar: \n");
	    leido=leer_algo();
	    numero=atoi(leido);
	    mostrar_publicacion_fecha(tabla, numero);
    }else if(feof(stdin)){
	    printf("Usted ha pulsado Ctrl+D\n");
	    printf("Finalizando programa\n");
	    exit(0);
	  }
  }
  size_leido=0;
  return 0;
}
