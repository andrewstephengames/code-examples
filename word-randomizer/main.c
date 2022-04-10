//TODO: custom input file
//TODO: Fix output in custom file with multiple switches
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WORD_COUNT 100
#define MAX_LEN 20
#define PI 3.1415926535897

void printUsage ()
{
     printf ("\nUsage:\n");
     printf ("-o: output file\n");
     printf ("-a: append mode (requires -o): Appends text to the output file on repeated execution\n");
     printf ("-r: number of words to output\n");
     printf ("-h: print usage and exit\n");
     printf ("\nDefaults: -r variable -o stdout\n\n");
     printf ("\nExamples:\n");
     printf ("./main: Prints a variable number of words from 1 to WORD_COUNT from words.txt\n");
     printf ("./main -r 5: Prints 5 random words from words.txt\n");
     printf ("./main -r 15 -o poem.txt: Adds 15 random words to poem.txt\n");
     printf ("On repeated execution, the file is cleared, thus only one sentence is included at one time\n");
     printf ("./main -o poem.txt -a: Appends a variable number of words to poem.txt\n");
     printf ("On repeated execution, the file will contain more sentences\n\n");
}

int main (int argc, char **argv)
{
     srand (clock());
     size_t randSize = 0, outputSignal = 0, appendSignal = 0;
     char outputFilename[255] = "";
     char words[WORD_COUNT][MAX_LEN];
     FILE *in = fopen ("words.txt", "r");
     FILE *out;
     while ((argc > 1) && (argv[1][0] == '-'))
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
                    appendSignal = 1;
                    break;
               case 'r':
                    randSize = atoi (argv[2]);
                    break;
               default:
                    printf ("\nInvalid argument!\n");
                    break;
          }
          ++argv;
          --argc;
     }
     for (size_t i = 0; i < WORD_COUNT; i++)
          fscanf (in, "%s", words[i]);
     if (strlen (outputFilename) == 0)
          strcpy (outputFilename, "stdout");
     if (outputSignal)
     {
          if (appendSignal)
               out = fopen (outputFilename, "a");
          else 
               out = fopen (outputFilename, "w");
     }
     if (randSize)
     {
          if (strcmp (outputFilename, "stdout") != 0)
          {
               for (size_t i = 0; i < randSize; i++)
                    if (words[rand()%WORD_COUNT][0] == '#')
                         fprintf (out, "%s ", words[rand()%WORD_COUNT]+1);
                    else 
                         fprintf (out, "%s ", words[rand()%WORD_COUNT]);
          }
          else 
          {
               for (size_t i = 0; i < randSize; i++)
                    if (words[rand()%WORD_COUNT][0] == '#')
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                    else 
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]);
          }
     }
     else
     {
          for (int i = 0; i < rand()%(WORD_COUNT); i++)
               if (strcmp (outputFilename, "stdout") == 0)
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                         continue;
 //                        fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                    else 
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]);
               }
               else 
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                         continue;
//                         fprintf (out, "%s ", words[rand()%WORD_COUNT]+1);
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
