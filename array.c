#include "array.h"
#include <stddef.h>
#include <string.h>
#include <malloc.h>



int array_create(array_handle_t *p_handle, int item_size)
{
    array_t *array = (array_t *)malloc(sizeof(array_t));
    if (array == NULL)
    {
        return -1;
    }
    array->entry = NULL;
    array->tail = NULL;
    array->item_size = item_size;
    *p_handle = array;
    return 0;
}

int array_push(array_handle_t handle, void *data)
{
    array_t *array = (array_t *)handle;
    array_node_t *node = array->tail;
    if (node == NULL)
    {
        node = (array_node_t *)malloc(sizeof(array_node_t) + array->item_size);
        if (node == NULL)
        {
            return -1;
        }
        node->prev = NULL;
        node->next = NULL;
        node->data = (void*)(node + 1);
        memcpy(node->data,data,array->item_size);
        array->entry = node;
        array->tail = node;
    }
    else
    {
        array_node_t* new_node = (array_node_t*)malloc(sizeof(array_node_t) + array->item_size);
        if(new_node == NULL)
        {
            return -1;
        }
        new_node->prev = node;
        new_node->next = NULL;
        new_node->data = (void*)(new_node + 1);
        memcpy(new_node->data,data,array->item_size);
        node->next = new_node;
        array->tail = new_node;
    }
    return 0;
}

int array_pop(array_handle_t handle,void* dst)
{
    array_t* array = (array_t*)handle;
    array_node_t* node = array->tail;
    if(node == NULL)
    {
        return -1;
    }
    array->tail = node->prev;
    if(node->prev!=NULL)
    {
        node->prev->next = NULL;
    }
    else
    {
        array->entry = NULL;
    }
    memcpy(dst,node->data,array->item_size);
    free(node);
    return 0;
}

int array_shift(array_handle_t handle,void* dst)
{
    array_t* array = (array_t*)handle;
    array_node_t* node = array->entry;
    if(node == NULL)
    {
        return -1;
    }
    array->entry = node->next;
    if(node->next!=NULL)
    {
        node->next->prev = NULL;
    }
    else
    {
        array->tail = NULL;
    }
    memcpy(dst,node->data,array->item_size);
    free(node);
    return 0;
}

void *array_get(array_handle_t handle, int index)
{
    array_t* array = (array_t*)handle;
    int i = 0;
    array_node_t* node = array->entry;
    while(i!=index && node != NULL)
    {
        i++;
        node = node->next;
    }
    if(i==index)
    {
        return node->data;
    }
    return NULL;
}

void *array_find(array_handle_t handle, array_match_t match)
{
    return NULL;
}

int array_find_index(array_handle_t handle,array_match_t match)
{
    return -1;
}

array_handle_t array_concat(array_handle_t A, array_handle_t B)
{
    return NULL;
}

int array_delete_index(array_handle_t handle,int i)
{
    return 0;
}

int array_delete(array_handle_t handle)
{
    array_t* array = (array_t*)handle;
    
    return 0;
}