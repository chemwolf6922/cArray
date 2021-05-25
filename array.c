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
    array->len = 0;
    *p_handle = array;
    return 0;
}

void* array_push(array_handle_t handle, void *data)
{
    array_t *array = (array_t *)handle;
    array_node_t *node = array->tail;
    if (node == NULL)
    {
        node = (array_node_t *)malloc(sizeof(array_node_t) + array->item_size);
        if (node == NULL)
        {
            return NULL;
        }
        node->prev = NULL;
        node->next = NULL;
        node->data = (void*)(node + 1);
        if(data != NULL)
        {
            memcpy(node->data,data,array->item_size);
        }
        else
        {
            memset(node->data,0,array->item_size);
        }
        array->entry = node;
        array->tail = node;
        array->len ++;
    }
    else
    {
        array_node_t* new_node = (array_node_t*)malloc(sizeof(array_node_t) + array->item_size);
        if(new_node == NULL)
        {
            return NULL;
        }
        new_node->prev = node;
        new_node->next = NULL;
        new_node->data = (void*)(new_node + 1);
        if(data != NULL)
        {
            memcpy(new_node->data,data,array->item_size);
        }
        else
        {
            memset(new_node->data,0,array->item_size);
        }
        node->next = new_node;
        array->tail = new_node;
        array->len ++;
    }
    return array->tail->data;
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
    array->len --;
    if(dst != NULL)
    {
        memcpy(dst,node->data,array->item_size);
    }
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
    array->len --;
    if(dst != NULL)
    {
        memcpy(dst,node->data,array->item_size);
    }
    free(node);
    return 0;
}

void *array_get(array_handle_t handle, int index)
{
    array_t* array = (array_t*)handle;
    if(index >= 0)
    {
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
    else
    {
        int i = -1;
        array_node_t* node = array->tail;
        while(i!=index && node != NULL)
        {
            i--;
            node = node->prev;
        }
        if(i==index)
        {
            return node->data;
        }
        return NULL;
    }
}

void *array_find(array_handle_t handle, array_match_t match,void* arg)
{
    void* data;
    array_forEach(handle,data)
    {
        if(match(data,arg))
        {
            return data;
        }
    }
    return NULL;
}

int array_find_index(array_handle_t handle,array_match_t match,void* arg)
{
    void* data;
    int i = 0;
    array_forEach(handle,data)
    {
        if(match(data,arg))
        {
            return i;
        }
        i++;
    }
    return -1;
}

int array_length(array_handle_t handle)
{
    array_t* array = (array_t*)handle;
    return array->len;
}

array_handle_t array_concat(array_handle_t A, array_handle_t B)
{
    array_t* arrayA = (array_t*)A;
    array_t* arrayB = (array_t*)B;
    if(arrayA->item_size != arrayB->item_size)
    {
        return NULL;
    }
    array_handle_t C = NULL;
    array_create(&C,arrayA->item_size);
    void* item;
    array_forEach(A,item)
    {
        if(array_push(C,item)==NULL)
        {
            array_delete(C);
            return NULL;
        }
    }
    array_forEach(B,item)
    {
        if(array_push(C,item)==NULL)
        {
            array_delete(C);
            return NULL;
        }
    }
    return C;
}

int array_delete_index(array_handle_t handle,int i)
{
    array_t* array = (array_t*)handle;
    array_node_t* node = NULL;
    // find node
    if(i >= 0)
    {
        if(array->len <= i)
        {
            return -1;
        }
        node = array->entry;
        for(int j=0;j!=i;j++)
        {
            node = node->next;
        }
    }
    else
    {
        if(array->len <= (0-i))
        {
            return -1;
        }
        node = array->tail;
        for(int j=-1;j!=i;j--)
        {
            node = node->prev;
        }
    }
    // delete node
    if(node->prev!=NULL)
    {
        node->prev->next = node->next;
    }
    else
    {
        array->entry = node->next;
    }
    if(node->next!=NULL)
    {
        node->next->prev = node->prev;
    }
    else
    {
        array->tail = node->prev;
    }
    free(node);
    array->len --;
    return 0;
}

int array_delete_match(array_handle_t handle,array_match_t match,void* arg)
{
    array_t* array = (array_t*)handle;
    array_node_t* node = array->entry;
    while(node != NULL)
    {
        if(match(node->data,arg))
        {
            if(node->prev != NULL)
            {
                node->prev->next = node->next;
            }
            else
            {
                array->entry = node->next;
            }
            if(node->next != NULL)
            {
                node->next->prev = node->prev;
            }
            else
            {
                array->tail = node->prev;
            }
            free(node);
            array->len --;
            return 0;
        }
        node = node->next;
    }
    return -1;
}

int array_clear(array_handle_t handle)
{
    array_t* array = (array_t*)handle;
    array_node_t* node = array->entry;
    while(node != NULL)
    {
        array_node_t* next = node->next;
        free(node);
        node = next;
    }
    array->entry = NULL;
    array->tail = NULL;
    array->len = 0;
    return 0;
}

int array_delete(array_handle_t handle)
{
    if(array_clear(handle)!=0)
    {
        return -1;
    }
    array_t* array = (array_t*)handle;
    free(array);
    return 0;
}