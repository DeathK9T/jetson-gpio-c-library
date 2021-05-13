#ifndef GCL_H_INCLUDED
#define GCL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#define buff_max 64
#define filename "/sys/class/gpio/"

void delayMicroseconds(unsigned int microseconds);
void delay(unsigned int milliseconds);
int gpio_export(unsigned int gpio);
int gpio_unexport(unsigned int gpio);
int gpio_direction(unsigned int gpio, char* direction);
int digitalWrite(unsigned int gpio, int value);
int digitalRead(unsigned int gpio);
int gpio_set_edge(unsigned int gpio, char* edge);


#endif
