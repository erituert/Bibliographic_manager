#ifndef NODE_H
#define NODE_H
#include<stdio.h>

struct node 
{
  struct publicacion info;
  struct node *next;
};

struct node* crear_nodo(struct publicacion publi);

#endif
