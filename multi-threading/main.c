#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
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

// Computed sum by background end
long long int sum = 0;

void* sumLong (void *arg)
{
     long long int *limit_ptr = (long long int*) arg;
     long long int limit = *limit_ptr;
     for (long long int i = 0; i < limit; i++)
     {
          /*
          printf (colors[rand()%16]);
          printf ("%lu ", i);
          */
          sum += i;
     }
     // Sum is a global variable so other threads can access it.
     pthread_exit(0);
}

int main (int argc, char **argv) 
{
/*
     red();
     printf("Hello ");
     yellow();
     printf("world\n");
     reset();
     //EXAMPLE
*/
     srand (clock());
     if (argc < 2)
     {
          printf ("Usage: %s <num>\n", argv[0]);
          exit(EXIT_FAILURE);
     }
     long long int limit = atoll (argv[1]);
     // set thread ID
     pthread_t tid;
     // Create attributes
     pthread_attr_t attr;
     // Initialize function
     pthread_attr_init(&attr);
     // Create thread
     pthread_create (&tid, &attr, sumLong, &limit);
     // Wait until thread has finished
     pthread_join (tid, NULL);
     printf ("Sum is %lld\n", sum);
     return 0;
}
