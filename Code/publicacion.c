/**CFile***********************************************************************

  Fichero     publicacion.c

  Resumen     Incluye la estructura publicación y su método "mostrar".

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
#include "publicacion.h"

void mostrar_info(struct publicacion a_mostrar){
  printf("DOI %31s", a_mostrar.DOI);
  printf("Título %28s", a_mostrar.titulo);
  printf("ISSN %30s", a_mostrar.ISSN);
  printf("Fuente %28s", a_mostrar.nombre_fuente);
  printf("Autor(es) %25s", a_mostrar.autores); 
  printf("Año %30d\n", a_mostrar.anio);
  printf("Factor de impacto %16f\n", a_mostrar.factor_impacto);
  printf("Lugar / Volumen y nº\n"); 
  printf("de la revista: %20s\n", a_mostrar.variable_particular);
}
