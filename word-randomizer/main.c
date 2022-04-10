//TODO: custom input file
//TODO: Fix output in custom file with multiple switches
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WORD_COUNT 500
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
     size_t commentSignal = 0;
     char outputFilename[255] = "";
     char words[WORD_COUNT][MAX_LEN];
     FILE *in = fopen ("words.txt", "r"), *out;
     while ((argc > 1) && (argv[1][0] == '-'))
     {
          switch (argv[1][1])
          {
               case 'o':
                    //output in a user defined file
                    outputSignal = 1;
                    strcpy (outputFilename, argv[2]);
                    break;
               case 'h':
                    //print helpful information and usage
                    printUsage ();
                    exit (EXIT_SUCCESS);
                    break;
               case 'a':
                    //append to existing file on multiple executions
                    appendSignal = 1;
                    break;
               case 'r':
                    //sentence size
                    randSize = atoi (argv[2]);
                    break;
               case 'u':
                    //use words that start with '#' from the input file
                    commentSignal = 1;
                    break;
               default:
                    printf ("Invalid argument!\n");
                    exit (EXIT_FAILURE);
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
                    {
                         if (commentSignal)
                              fprintf (out, "%s ", words[rand()%WORD_COUNT]+1);
                         else continue;
                         //printf ("\n%s\n", outputFilename);
                    }
                    else 
                    {
                         fprintf (out, "%s ", words[rand()%WORD_COUNT]);
                         //printf ("\n%s\n", outputFilename);
                    }
          }
          else 
          {
               for (size_t i = 0; i < randSize; i++)
                    if (words[rand()%WORD_COUNT][0] == '#')
                    {
                         if (commentSignal)
                              fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                         else continue;
                         //printf ("\n%s\n", outputFilename);
                    }
                    else 
                    {
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]);
                         //printf ("\n%s\n", outputFilename);
                    }
          }
     }
     else
     {
          for (int i = 0; i < rand()%(WORD_COUNT); i++)
               if (strcmp (outputFilename, "stdout") == 0)
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                    {
                         if (commentSignal)
                              fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                         else continue;
                    }
                    else 
                    {
                         //printf ("\n%s\n", outputFilename);
                         fprintf (stdout, "%s ", words[rand()%WORD_COUNT]);
                    }
               }
               else 
               {
                    if (words[rand()%WORD_COUNT][0] == '#')
                         if (commentSignal)
                              fprintf (out, "%s ", words[rand()%WORD_COUNT]+1);
                         else continue;
                    else 
                    {
                         //printf ("\n%s\n", outputFilename);
                         fprintf (out, "%s ", words[rand()%WORD_COUNT]);
                    }
               }
     }
     if (strcmp (outputFilename, "stdout") == 0)
          fprintf (stdout, "\n");
     else 
          fprintf (out, "\n");
     return 0;
}
