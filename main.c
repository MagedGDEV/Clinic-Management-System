#include <stdio.h>
#include "clinic_system/clinic_system.h"

int main (void){
    int isDone = true; extern bool isStarting;
    do {
        isDone = home();
        isStarting = false;
        printf(DIVIDOR_0);
    } while (!isDone);
    return 0;
}