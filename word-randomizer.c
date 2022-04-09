//TODO: File named stdout gets created by default
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WORD_COUNT 100
#define MAX_LEN 20
#define PI 3.1415926535897

void aboutInfo ()
{
     printf ("\nWord Randomizer\n");
     printf ("\n");
     printf ("Author: Andrew Stephen\n");
     printf ("\n");
     printf ("This program was made to challenge my coding.\n");
}

void printUsage ()
{
     printf ("\nUsage:\n");
     printf ("-o: output file\n");
     printf ("-a: print about info and exit\n");
     printf ("-r: number of words to output\n");
     printf ("-h: print usage and exit\n");
     printf ("\nDefaults: -r variable -o stdout\n\n");
}

int main (int argc, char **argv)
{
     srand (clock());
     size_t randSize = 0, outputSignal = 0;
     char outputFilename[255] = "";
     FILE *in = fopen ("words.txt", "r");
     if ((argc > 1) && (argv[1][0] == '-'))
     {
          switch (argv[1][1])
          {
               case 'o':
                    outputSignal = 1;
                    strcpy (outputFilename, argv[2]);
                    break;
               case 'h':
                    printUsage ();
                    exit (EXIT_SUCCESS);
                    break;
               case 'a':
                    aboutInfo ();
                    exit (EXIT_SUCCESS);
                    break;
               case 'r':
                    randSize = atoi (argv[2]);
                    break;
               default:
                    printf ("\nInvalid argument!\n");
                    break;
          }
     }
     char words[WORD_COUNT][MAX_LEN];
     for (size_t i = 0; i < WORD_COUNT; i++)
          fscanf (in, "%s", words[i]);
     if (strlen (outputFilename) == 0)
          strcpy (outputFilename, "stdout");
     //TODO
     //if (outputSignal)
          FILE *out = fopen (outputFilename, "w");
     if (randSize)
     {
          for (size_t i = 0; i < randSize; i++)
               if (strcmp (outputFilename, "stdout") == 0)
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                    else 
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]);
               }
               else 
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                         fprintf (out, "%s ", words[rand()%WORD_COUNT]+1);
               }
     }
     else
     {
          for (int i = 0; i < rand()%(WORD_COUNT-1); i++)
               if (strcmp (outputFilename, "stdout") == 0)
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                    else 
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]);
               }
               else 
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                         fprintf (out, "%s ", words[rand()%WORD_COUNT]+1);
                    else 
                         fprintf (out, "%s ", words[rand()%WORD_COUNT]);
               }
     }
     if (strcmp (outputFilename, "stdout") == 0)
          fprintf (stdout, "\n");
     else 
          fprintf (out, "\n");
     return 0;
}
