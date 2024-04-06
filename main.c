#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 2000

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

    printf("cvb version 1.0\n");
}

void error(char *err)
{ // Error Function to print to stderr
    fprintf(stderr, "%s\n", err);
}

void printLines(FILE *file, int start, int end)// Core function to print Lines from start to end
{ 
    if(file == NULL){
        printf("AAAAAAAAAAAAAAAAAAAAAAAA");
    }
    char lineBuffer[MAX_LINE]; //array to save the current line to
    int currentLine = start; //iterator for line were currently at
    while (fgets(lineBuffer, MAX_LINE, file) != NULL) //ersetze mit fseek damit wir nicht durchs ganze file müssen?
    {
        if (currentLine <= end)
        {
            printf("%s", lineBuffer);
        }
        else
        {
            break;
        }
        currentLine++;
        printf("%d", currentLine);
    }
}

void readFileQuiet()
{
}

int main(int argc, char *argv[])
{
    FILE *file;
    int start = 1;
    int end = -1;
    char *filename = NULL;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--help") == 0)
        {
            printHelp();
            return 0;
        }
        else if (strcmp(argv[i], "--version") == 0)
        {
            printVersion();
            return 0;
        }
        else if (strcmp(argv[i], "-s") == 0)
        {
            if (i + 1 < argc)
            {
                start = strtol(argv[i + 1], NULL, 10);
            }
            else
            {
                error("-s benötigt ein Argument");
            }
        }
        else if (strcmp(argv[i], "-e") == 0)
        {
            if (i + 1 < argc)
            {
                end = strtol(argv[i + 1], NULL, 10);
            }
            else
            {
                error("-e benötigt ein Argument");
            }
        }
        else
        {
            filename = argv[argc];
        }
    }

    if (filename == NULL || strcmp(filename, "-") == 0)
    {
        file = stdin;
    }
    else
    {
        file = fopen(filename, "r");
        if (file == NULL)
        {
            error("Fehler beim Öffnen der Datei.");
        }
    }

    printLines(file, start, end);

    if (file != stdin)
    {
        fclose(file);
    }

    return 0;
}
