#include "gcl.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>

#define buff_max 64

#define filename "/sys/class/gpio/"

void delayMicroseconds(unsigned int microseconds)
{
        clock_t start = microseconds + clock();
        while(start > clock());
}

void delay(unsigned int milliseconds)
{
        clock_t start = (milliseconds * 1000) + clock();
        while(start > clock());
}

int gpio_export(unsigned int gpio)
{
        FILE *f;
        f = fopen(filename "export", "w");
        if(f == NULL)
        {
                perror("/gpio/export");
                return -1;
        }
        fprintf(f, "%d", gpio);
        fclose(f);
        return 0;
}

int gpio_unexport(unsigned int gpio)
{
        FILE *f;
        f = fopen(filename "unexport", "w");
        if(f == NULL)
        {
                perror("/gpio/unexport");
                return -1;
        }
        fprintf(f, "%d", gpio);
        fclose(f);
        return 0;
}

int gpio_direction(unsigned int gpio, char*  direction)
{
        FILE *f;
        char buff[buff_max] = {};
        snprintf(buff,sizeof(buff),filename "gpio%d/direction",gpio);
        f = fopen(buff,"w");
        if(direction == "out")
        {
                fprintf(f, "out");
        }
        else if(direction == "in")
        {
                fprintf(f, "in");
        }
        else
        {
                perror("unknown direction");
                return -1;
        }
        fclose(f);
        return 0;
}

//1 - HIGH
//0 - LOW
int digitalWrite(unsigned int gpio, int value)
{
        FILE *f;
        char buff[buff_max] = {};
        snprintf(buff,sizeof(buff),filename "gpio%d/value",gpio);
        f = fopen(buff,"w");
        if(f == NULL)
        {
                perror("/gpio/value");
                return -1;
        }
        switch(value)
        {
                case 0:
                        fprintf(f, "0");
                break;
                case 1:
                        fprintf(f, "1");
                break;
                default:
                        perror("unknown value");
                        return -1;
                break;
        }
        fclose(f);
        return 0;
}

int digitalRead(unsigned int gpio)
{
        FILE *f;
        char buff[buff_max] = {};
        char value[10] = {};
        snprintf(buff,sizeof(buff),filename "gpio%d/value",gpio);
        f = fopen(buff, "r");
        if(f == NULL)
        {
                perror("/gpio/value");
                return -1;
        }
        fscanf(f,"%s", value);
        fclose(f);
        return(atoi(value));
}

int gpio_set_edge(unsigned int gpio, char* edge)
{
        FILE *f;
        char buff[buff_max] = {};
        snprintf(buff,sizeof(buff),filename "gpio%d/edge",gpio);
        f = fopen(buff, "w");
        if(f == NULL)
        {
                perror("/gpio/edge");
                return -1;
        }
        if(edge == "none")
                fprintf(f, "none");
        else if(edge == "falling")
                fprintf(f, "falling");
        else if(edge == "rising")
                fprintf(f, "rising");
        else if(edge == "both")
                fprintf(f, "both");
        else
        {
                perror("unknown edge");
                return -1;
        }
        fclose(f);
        return 0;
}
