// https://github.com/Jacob-Tr/LinkedLists

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
};

size_t type_size[] =
{
    sizeof(unsigned long),
    sizeof(long),
    sizeof(unsigned int),
    sizeof(int),
    sizeof(unsigned short),
    sizeof(short),
    sizeof(unsigned char),
    sizeof(char)
};

#define __TYPES__ 8

typedef unsigned short datatype;

struct LinkedListElement
{
    struct LinkedListElement* prev;
    void* value;
    unsigned short element_id;
    struct LinkedListElement* next;
} NULL_LIST_ELEMENT;

struct LinkedList
{
    datatype type;
    size_t size;
    
    struct LinkedListElement* first;
    struct LinkedListElement* last;
} NULL_LIST;

typedef struct LinkedList linkedlist;

#define LinkedList(T, S) initList((linkedlist*) malloc(sizeof(linkedlist)), (T), (S))

#ifdef __cplusplus
extern "C" 
{
#endif

linkedlist initList(linkedlist* list, const datatype type, const size_t size)
{
    if(size < 0 || type > __TYPES__) goto FAILED;
    
    list->type = type;
    list->size = size;
    
    struct LinkedListElement* element;
    struct LinkedListElement* prev_element = &NULL_LIST_ELEMENT;
    
    for(unsigned short i = 0; i < size; i++) 
    {
        element = (struct LinkedListElement*) malloc(sizeof(struct LinkedListElement));
        
        if(!i) list->first = element;
        
        element->element_id = i;
        element->value = malloc(type_size[type]);
        
        element->prev = prev_element;
        prev_element->next = element;
        prev_element = element;
        prev_element->value = NULL;
        
        element = element->next;
    }
    
    element = &NULL_LIST_ELEMENT;
    
    list->last = prev_element;
    (list->last)->next = element;
    
    return *list;
    
    FAILED:
    free(list);
    return NULL_LIST;
}

struct LinkedListElement* getElement(const linkedlist list, const size_t element)
{
    if(element < 0 || element > list.size) return &NULL_LIST_ELEMENT;
    
    struct LinkedListElement* ret = list.first;
    
    if(element < (list.size / 2))
    {
        ret = list.first;
        for(size_t i = 0; i < element; i++) ret = ret->next;
    }
    else
    {
        ret = list.last;
        for(size_t i = (list.size - 1); i > 0; i--) ret = ret->prev;
    }
    
    return ret;
}

void* get(const linkedlist list, const size_t element)    
{
    struct LinkedListElement* ret = getElement(list, element);
    
    if(ret == &NULL_LIST_ELEMENT) return ret;
    
    void* value = ret->value;
    
    return value;
}

void set(linkedlist list, const size_t element, void* value)
{
    struct LinkedListElement* el = getElement(list, element);
    
    if(el == NULL) return;
    
    switch(list.type)
    {
        case UINT:
        {
            el->value = ((unsigned int*) value);
            break;
        }
    }
}

void add(linkedlist* list, void* value)
{
    list = realloc(list, (sizeof(linkedlist) * ++list->size));
    
    struct LinkedListElement* el = getElement(*list, list->size);
    struct LinkedListElement* prev_el = getElement(*list, (list->size - 1));
    
    prev_el->next = el;
    el->prev = prev_el;
    
    set(*list, list->size, value);
}

void removeElement(linkedlist* list, const size_t element)
{
    struct LinkedListElement* el = getElement(*list, element);
    
    if(el == NULL || el == &NULL_LIST_ELEMENT) return;
    
    if(el->value) free(el->value);
    
    if(el != list->last) 
    {
        if(el == list->first) (el->next)->prev = &NULL_LIST_ELEMENT;
        else (el->next)->prev = el->prev;
    }
    if(el != list->first) (el->prev)->next = el->next;
    
    for(size_t i = element; element < (list->size - element); i++) el = el->next;
    
    free(el);
    
    --list->size;
}

void destroy(linkedlist* list)
{
    struct LinkedListElement* el = list->first;
    
    for(size_t i = 0; i < list->size; i++) 
    {
        struct LinkedListElement* listptr = el;
        el = el->next;
        
        free(listptr);
    }
    
    free(list);
}

#ifdef __cplusplus 
}
#endif

#endif
