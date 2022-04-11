#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

//colors
#define BLACK "\033[0;30m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BROWN_ORANGE "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define CYAN "\033[0;36m"
#define LIGHT_GRAY "\033[0;37m"
#define DARK_GRAY "\033[1;30m"
#define LIGHT_RED "\033[1;31m"
#define LIGHT_GREEN "\32m"
#define YELLOW "\033[1;33m"
#define LIGHT_BLUE "\033[1;34m"
#define LIGHT_PURPLE "\033[1;35m"
#define LIGHT_CYAN "\033[1;36m"
#define WHITE "\033[1;37m"
#define RESET "\033[0m"

//color array
char colors[16][10] = {
     BLACK,
     RED,
     GREEN,
     BROWN_ORANGE,
     BLUE,
     PURPLE,
     CYAN,
     LIGHT_GRAY,
     DARK_GRAY,
     LIGHT_RED,
     LIGHT_GREEN,
     YELLOW,
     LIGHT_BLUE,
     LIGHT_PURPLE,
     LIGHT_CYAN,
     WHITE,
     RESET
};


int main (int argc, char **argv)
{
     srand (clock());
     if (argc < 2)
     {
          printf ("Invalid Argument!\n");
          printf ("Usage: ./main <num>\n");
          printf ("Upper limit for <num>: %lld\n", LLONG_MAX);
          exit (EXIT_FAILURE);
     }
     long long int num = atoll (argv[1]);
     for (long long int i = 0; i < num; i++)
     {
          printf (colors[rand()%16]);
          printf ("%lld ", i);
     }
     printf ("\n");
     return 0;
}

