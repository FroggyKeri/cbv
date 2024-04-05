#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printHelp (){

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

void printVersion (){

    printf("cvb version 1.0\n");
}

void printVerboseMode() {


}

void printEndOfLine() {


}

void readFileQuiet() {


}

int main(int argc, char *argv[]){
FILE *file;


for (int i = 1; i < argc; i++){
    if (strcmp(argv[i], "--help") == 0){
        printHelp();
        return 0;
    } else if (strcmp(argv[i],"--version") == 0){
        printVersion();
        return 0;
    }
    
}


    return 0;
}