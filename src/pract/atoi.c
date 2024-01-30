#include <stdio.h>
#include <stdlib.h>

int main (int arg_counter, char* arg_values[])
{
    int firstn = atoi(arg_values[1]);    // atoi - ASCII to Integer
    int secondn = atoi(arg_values[2]);   // in this case, it converts value inside [1] and [2] argument to integer
                                         // basically converts arguments to programm readable numbers.
                                         // and then counts from first number to second.
                                         
    for (int a = firstn; a <= secondn; a++)
    {
        printf("%d\n", a);
    }
   
    return 0;
}






