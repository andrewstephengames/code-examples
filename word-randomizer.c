#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WORD_COUNT 50
#define MAX_LEN 20

void aboutInfo ()
{
     printf ("Word Randomizer\n");
     printf ("\n");
     printf ("Author: Andrew Stephen\n");
     printf ("\n");
     printf ("This program was made to challenge my coding.\n");
}

void printUsage ()
{
     printf ("Usage:\n");
     printf ("-o: output file\n");
     printf ("-a: print about information\n");
     printf ("-r: number of words to output\n");
     printf ("-h: print usage\n");
}

int main (int argc, char **argv)
{
     srand (time(0));
     size_t randSize = 0;
     char *outputFilename;
     FILE *in = fopen ("words.txt", "r");
     FILE *out = fopen (outputFilename, "w");
     if ((argc > 1) && (argv[1][0] == '-'))
     {
          switch (argv[1][1])
          {
               case 'o':
                    strcpy (outputFilename, argv[2]);
                    break;
               case 'h':
                    printUsage ();
                    break;
               case 'a':
                    aboutInfo ();
                    break;
               case 'r':
                    randSize = atoi (argv[2]);
                    break;
               default:
                    printf ("Invalid argument!\n");
                    break;
          }
     }
     char words[WORD_COUNT][MAX_LEN];
     for (size_t i = 0; i < WORD_COUNT; i++)
          fscanf (in, "%s", words[i]);
     if (strcmp (outputFilename, NULL) == 0)
          strcpy (outputFilename, "stdout");
     for (size_t i = 0; i < randSize; i++)
          fprintf (out, "%s ", words[rand()%WORD_COUNT]);
     fprintf (out, "\n");
     return 0;
}
