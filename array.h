#ifndef __ARRAY_H
#define __ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct array_node_s
{
    struct array_node_s *prev;
    struct array_node_s *next;
    void *data;
} array_node_t;

typedef struct array_s
{
    array_node_t *entry;
    array_node_t *tail;
    int item_size;
} array_t;

typedef void* array_handle_t;
typedef bool (*array_match_t)(void* data);

int array_create(array_handle_t* p_handle,int item_size);
int array_push(array_handle_t handle,void* data);
int array_pop(array_handle_t handle,void* dst);
int array_shift(array_handle_t handle,void* dst);
void* array_get(array_handle_t handle,int index);
void* array_find(array_handle_t handle,array_match_t match);
int array_find_index(array_handle_t handle,array_match_t match);
int array_length(array_handle_t handle);
array_handle_t array_concat(array_handle_t A,array_handle_t B);
int array_delete_index(array_handle_t handle,int i);
int array_delete(array_handle_t handle);

#define array_forEach(handle,item) for(array_node_t* node_fca0be72=((array_t*)(handle))->entry;\
                                        node_fca0be72!=NULL?(item=node_fca0be72->data):0;\
                                        node_fca0be72 = node_fca0be72->next)


#endif