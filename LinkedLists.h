#ifndef _LINKED_LISTS_H
#define _LINKED_LISTS_H

#ifndef _STDLIB_H
#include <stdlib.h>
#endif

enum types
{
    ULONG,
    LONG,
    UINT,
    INT,
    USHORT,
    SHORT,
    UCHAR,
    CHAR
}

#define __TYPES__ 8

typedef unsigned short datatype;

struct LinkedListElement
{
    void* value;
    void* next;
}, NULL_LIST_ELEMENT;

struct LinkedList
{
    datatype type;
    size_t size, elements;
    
    struct LinkedListElement* first;
}, NULL_LIST;

typedef struct LinkedList linkedlist;

#ifdef __cplusplus
extern "C" 
#endif
linkedlist* initList(linkedlist* list, const datatype type, const size_t size)
{
    if(size < 0 || type > __TYPES__) goto FAILED;
    
    list->type = type;
    list->size = size;
    list->elements = 0;
    
    list->first = (LinkedListElement*) malloc(sizeof(struct LinkedListElement));
    struct LinkedListElement* prev_element = list->first;
    
    for(int i = 0; i < size; i++) 
    {
        prev_element->next = (struct LinkedListElement*) malloc(sizeof(struct LinkedListElement));
        prev_element = prev_element->next;
    }
    
    return list;
    
    FAILED:
    free(list);
    return &NULL_LIST;
}

#define LinkedList<T>(S) initList((linkedlist*) malloc(sizeof(linkedlist)), T, S)

#ifdef __cplusplus
extern "C" 
#endif
void* get(const linkedlist list, const size_t element)
{
    if(element < 0 || element > list->size) return NULL;

    struct LinkedListElement* ret = list.first;
    for(size_t i = 0; i < element; i++) ret = ret->next;
    
    return (void*) &ret->value;
}

#ifdef __cplusplus
extern "C" 
#endif
void set(const linkedlist list, const size_t element, const void* value)
{
    if(element < 0 || element > list.size) return NULL;

    struct LinkedListElement* el = list.first;
    for(size_t i = 0; i < element; i++) el = el->next;
    
    el->value = value;
}

#ifdef __cplusplus
extern "C" 
#endif
void add(linkedlist* list, const void* value)
{
    size_t size = list->size;
    list = realloc(list, (sizeof(linkedlist) * list->size) + 1);
    
    set(*list, (size + 1), value);
}

#ifdef __cplusplus
extern "C" 
#endif
void remove(linkedlist* list, const size_t element)
{
    if(element < 0 || element > list->size) return NULL;

    struct LinkedListElement* el = list.first;
    size_t index;
    
    for(index = 0; index < element; index++) el = el->next;
    
    for(size_t i = index; index < (list->size - index) - 1; i++) set(list, i, get(list, (i + 1)));
    
    size_t size = list->size;
    realloc(list, (sizeof(linkedlist) * size) - 1);
}

#ifdef __cplusplus
extern "C" 
#endif
void destroy(linkedlist* list)
{
    struct LinkedListElement* el = list.first;
    size_t size = list->size;
    
    for(size_t i = 0; i < size; i++) 
    {
        linkedlist* listptr = el;
        el = el->next;
        
        free(el);
    }
    
    free(list);
}

#endif
