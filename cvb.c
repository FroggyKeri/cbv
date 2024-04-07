#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 2000
#define VER "1.2"

void printHelp()
{ // Print Help to CLI

    printf("--help              Hilfeinformation wird ausgeben; Programm terminiert\n");
    printf("-s n                Angabe der ersten auszugebenen (n-te) Zeile\n");
    printf("                    wenn keine Angabe, dann wird ab erster Zeile gelesen\n");
    printf("-e n                Angabe der letzten auszugebenen (m-te) Zeile\n");
    printf("                    wenn keine Angabe, dann wird bis zur letzten Zeile gelesen\n");
    printf("-n [format]         Ausgabe mit fuehrenden Zeilennummern\n");
    printf("                    optionale Formatparameter hierfuer:\n");
    printf("        uint                    Breite des Zeilennummernfelds (numerisch)\n");
    printf("          R                     rechtsbuendig (default)\n");
    printf("          0                     rechtsbuendig mit fuehrenden Nullen\n");
    printf("          L                     linksbuendig\n");
    printf("          N                     die Zeilennummer beginnt mit Null\n");
    printf("          Beispiel: 04 ... Ausgabe der Zeilennummer rechtsbuendig mit\n");
    printf("                         fuehrenden Nullen, z.B. 0017\n");
    printf("-v                  Programm gibt waehrend der Prozessierung etwaige zusaetzliche\n");
    printf("                    Status- und Dateiinformationen aus\n");
    printf("-q                  Programm gibt nur etwaige zusaetzliche Status- und\n");
    printf("                    Dateiinformationen aus, ohne jedoch den Inhalt der Datei\n");
    printf("                    auszugeben\n");
    printf("--version           Versionsinformation des Programms wird ausgegeben\n");
}

void printVersion()
{ // Print Version

    printf("cvb version %s\n", VER);
}

void printVerbose(char *filename, int start, int end)
{ // Print Verbose Information
    printVersion();
    if (filename != NULL)
    {
        printf("Reading From: %s\n", filename);
    }
    else
    {
        printf("Reading From: stdin\n");
    }
}

void printQuiet(char *filename, int start, int end)
{ // Print in quiet mode
    printVerbose(filename, start, end);
    printf("Quiet Mode, omitting output\n");
}



void error(char *err)
{ // Error Function to print to stderr
    fprintf(stderr, "%s\n", err);
}

void printLines(FILE *file, int start, int end) // Core function to print Lines from start to end
{
    if (file == NULL)
    {
        error("Error opening File");
    }
    char lineBuffer[MAX_LINE];                        // array to save the current line to
    int currentLine = 1;                              // iterator for line were currently at
    while (fgets(lineBuffer, MAX_LINE, file) != NULL) // read line by line
    {
        if (currentLine >= start && currentLine <= end) // check if we are in the range
        {
            printf("%s", lineBuffer); // print the line
        }
        else if (currentLine > end) // if we are past the end, break
        {
            break;
        }
        currentLine++; // increment the line counter
    }
}

int main(int argc, char *argv[]) // Main Function
{
    FILE *file; // main File Pointer
    int start = 1; // start line
    int end = -1; // end line
    char *filename = NULL; // filename, set to NULL

    if (argc < 2) // check if we have enough arguments, if not print help
    { 
        error("Not enough arguments, use --help for syntax");
        return 0;
    }

    for (int i = 1; i < argc; i++) // iterate over the arguments
    {
        if (strcmp(argv[i], "--help") == 0) // check if we have the help argument
        {
            printHelp();
            return 0;
        }
        else if (strcmp(argv[i], "--version") == 0) // check if we have the version argument
        {
            printVersion();
            return 0;
        }
        else if (strcmp(argv[i], "-s") == 0) // check if we have the start argument
        {
            if (i + 1 < argc)
            {
                start = strtol(argv[i + 1], NULL, 10); // convert the argument to a number
                i++; // increment the iterator to skip the number in the next iteration
            }
            else // print error if we dont have an argument
            {
                error("-s benötigt ein Argument"); 
            }
        }
        else if (strcmp(argv[i], "-e") == 0) // check if we have the end argument
        {
            if (i + 1 < argc) // check if we have an argument
            {
                end = strtol(argv[i + 1], NULL, 10); // convert the argument to a number
                i++; // increment the iterator to skip the number in the next iteration
            }
            else // print error if we dont have an argument
            {
                error("-e benötigt ein Argument"); 
            }
        }
        else if (strcmp(argv[i], "-v") == 0) // check if we have the verbose argument
        {
            printVerbose(filename, start, end); // print verbose information
        }
        else if (strcmp(argv[i], "-q") == 0) // check if we have the quiet argument
        {
            printQuiet(filename, start, end); // print quiet information
            return 0; // end the program so we omit the output
        }
        else // if none of the above, set the filename
        {
            filename = argv[i];
        }
    }

    if (filename == NULL || strcmp(filename, "-") == 0) // if we dont have a filename or the filename is "-", set the file to stdin
    {
        file = stdin; 
    }
    else // if we have a filename, open the file
    {
        file = fopen(filename, "r"); 
        if (file == NULL)
        {
            error("Fehler beim Öffnen der Datei.");
        }
    }

    printLines(file, start, end); // print the lines

    if (file != stdin) // close the file if its not stdin
    {
        fclose(file);
    }

    return 0; // end the program
}
