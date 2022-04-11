//TODO: Add custom input file
//TODO: Fix output in custom file with multiple switches
//TODO: Fix segmentation fault for any output
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//constants
#define WORD_COUNT 255
#define MAX_LEN 20
#define PI 3.1415926535897

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



void printUsage ()
{
     printf ("\nUsage:\n");
     printf ("-o: output file\n");
     printf ("-a: append mode (requires -o): Appends text to the output file on repeated execution\n");
     printf ("-r: number of words to output\n");
     printf ("-x: output non-colored plain text\nText color in this mode depends on your desktop.\n");
     printf ("Note: Only works if no output file is specified, or the output file specified is stdout.\n");
     printf ("Examples:\nGNOME uses a light terminal by default, so the text color is black.\n");
     printf ("KDE, most standalone window managers and the tty: uses a black background, so the text color is white.\n");
     printf ("Windows: cmd uses a black background and a white foreground, so the text is white.\n");
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
     size_t commentSignal = 0, colorSignal = 1;
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
               case 'x':
                    //exclude colors (default: include colors)
                    colorSignal = 0;
                    break;
               default:
                    printf ("Invalid argument!\n");
                    printf ("Type `%s -h` for help.\n", argv[0]);
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
          for (size_t i = 0; i < randSize; i++)
               if (strcmp (outputFilename, "stdout") != 0)
               {
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
                         if (words[rand()%WORD_COUNT][0] == '#')
                         {
                              if (commentSignal)
                              {
                                   if (colorSignal)
                                        printf (colors[rand()%16]);
                                   fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                              }
                              else continue;
                              //printf ("\n%s\n", outputFilename);
                         }
                         else 
                         {
                              if (colorSignal)
                                   printf (colors[rand()%16]);
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
                         {
                              if (colorSignal)
                                   printf (colors[rand()%16]);
                              fprintf (stdout, "%s ", words[rand()%WORD_COUNT]+1);
                         }
                         else continue;
                    }
                    else 
                    {
                         //printf ("\n%s\n", outputFilename);
                         if (colorSignal)
                              printf (colors[rand()%16]);
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
     fclose (in);
     fclose (out);
     return 0;
}
