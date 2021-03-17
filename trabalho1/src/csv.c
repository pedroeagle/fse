#include "csv.h"
struct stat st = {0};
char filename[100];
void CSV(){
    if (stat("log", &st) == -1) {
        mkdir("log", 0700);
    }
    
    FILE *fp;
    
    int i,j;
    time_t now;
    time(&now);
    sprintf(filename, "log/%s", ctime(&now));
    filename[strlen(filename)-1] = 0;
    strcpy(filename, strcat(filename, ".csv"));

    fp=fopen(filename,"w+");
    
    fprintf(fp,"Temperatura Interna, Temperatura Externa, Temperatura do Potenciômetro, Temperatura do Terminal, Temperatura de Referência");
    fclose(fp);
 
}
void insert_line(float values[], int size){
    FILE *fp;
    fp=fopen(filename, "a");
    char line[1000];
    sprintf(line, "\n%f", values[0]);
    for(int i = 1; i < size; i++){
        char value[100];
        sprintf(value, ", %f",values[i]);
        strcpy(line, strcat(line, value));
    }
    fprintf(fp, line);
    fclose(fp);
}
