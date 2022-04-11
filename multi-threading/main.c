/* In case of compiler linker issues, add to compile arguments:
**   -pthread
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>

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
