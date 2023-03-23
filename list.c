#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *L = (List *)malloc(sizeof(List));
  L->head = NULL;
  L->current = NULL;
  L->tail = NULL;

  return L;
}

void *firstList(List *list) {
  if (list->head != NULL) {
    list->current = list->head;
    return list->head->data;
  } else
    return NULL;
}

void *nextList(List *list) {

  if (list->current == NULL || list->current->next == NULL)
    return NULL;

  list->current = list->current->next;

  return list->current->data;
}

void *lastList(List *list) {

  if (list->tail == NULL)
    return NULL;

  list->current = list->tail;
  return list->current->data;

      
}

void *prevList(List *list) { 
  
  if(list->current == NULL || list->current->prev == NULL)
    return NULL;

  list->current = list->current->prev;

  return list->current->data;

}

void pushFront(List *list, void *data) {
  Node *nuevoNodo = createNode(data);

  if(list->head == NULL)
  {
    list->head = nuevoNodo;
    list->tail = list->head;
  }
  else
  {
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }

  
}

void pushBack(List *list, void *data) {
  list->current = list->tail;

  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {

  if(list->current == NULL) return;
  
  Node *nuevoNodo = createNode(data);

  
  nuevoNodo->next = list->current->next;
  nuevoNodo->prev = list->current;

  if(list->current->next == NULL)
  {
    list->tail = nuevoNodo;
  }
  else
  {
    list->current->next->prev = nuevoNodo;
  }
  list->current->next = nuevoNodo;
  
  
  
  
  
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) { 
  
  if(list->current == NULL) return NULL;
  
  void* datoEliminado = list->current->data;
  
  
  if(list->current == list->head)
  {
    
    list->head = list->head->next;

    if(list->head->prev != NULL)
    {
      list->head->prev = NULL;
    }
    
  }
  else
  {
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
  }
  
  if(list->current == list->tail)
  {
    
    list->tail = list->current->prev;
    list->tail->next = NULL;
  }
  
  
  Node *nodoAux = list->current->next;
  
  free(list->current);

  list->current = nodoAux;

  return datoEliminado;
}  

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}