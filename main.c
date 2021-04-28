#include "array.h"
#include <stdio.h>

int main(int argc, void *argv)
{
    array_handle_t array;
    array_create(&array, sizeof(int));
    int data[] = {1, 2, 3, 4, 5};
    for (int i = 0; i != 5; i++)
    {
        array_push(array, &data[i]);
    }
    int *number;
    array_forEach(array, number)
    {
        printf("%d,", *number);
    }
    printf("\n");
    array_pop(array,number);
    printf("%d\n",*number);
    array_shift(array,number);
    printf("%d\n",*number);
    array_forEach(array, number)
    {
        printf("%d,", *number);
    }
    printf("\n");

    return 0;
}