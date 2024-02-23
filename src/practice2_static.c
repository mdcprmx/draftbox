#include <stdio.h>
#include <string.h>
#include "malloc_with_check.c"

// in this practice, we are looking at difference between "static" and "normal" variables 
// difference being, that static is.. it remains the same between function calls
// ("HUH?!" WHAT DOES THAT MEAN U MIGHT SAY?) (in this case, just ask chatGPT)

int counter_up();

int main()
{
    counter_up();
    counter_up();
    counter_up();
    counter_up();
    counter_up();
    counter_up();
    counter_up();
    counter_up();
    counter_up();
    counter_up();
    counter_up();

    return EXIT_SUCCESS;
}

int counter_up()
{
    // int cunter = 1;
    static int cunter = 1;
    cunter++;
    printf("counter is %d\n", cunter);
    return cunter;
}