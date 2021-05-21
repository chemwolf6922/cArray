#include "array.h"
#include <stdio.h>
#include <stdbool.h>

bool match_int_value(void* data,void* arg)
{
    return *(int*)data == *(int*)arg;
}

int main(int argc, void *argv)
{
    array_handle_t array;
    array_create(&array, sizeof(int));
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8};
    for (int i = 0; i != sizeof(data) / sizeof(int); i++)
    {
        array_push(array, &data[i]);
    }
    int *number;
    array_forEach(array, number)
    {
        printf("%d,", *number);
    }
    printf("\n");
    array_pop(array, number);
    printf("%d\n", *number);
    array_shift(array, number);
    printf("%d\n", *number);
    array_forEach(array, number)
    {
        printf("%d,", *number);
    }
    printf("\n");
    array_delete_index(array, -1);
    int target = 5;
    number = array_find(array,match_int_value,&target);
    printf("value: %d\n",*number);
    int index = array_find_index(array,match_int_value,&target);
    printf("index: %d\n",index);
    array_forEach(array, number)
    {
        printf("%d,", *number);
    }
    printf("\n");
    array_clear(array);
    array_forEach(array, number)
    {
        printf("%d,", *number);
    }
    printf("\n");
    array_delete(array);
    return 0;
}