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
    
    fprintf(fp,"comando, porta, horario");
    fclose(fp);
 
}
void insert_line(char * comando, int porta){
    FILE *fp;
    fp=fopen(filename, "a");
    char line[1000];
    char time_string[100];
    time_t now;
    time(&now);
    sprintf(time_string, "%s", ctime(&now));
    sprintf(line, "\n%s, %d, %s", comando, porta, time_string);
    fprintf(fp, line);
    fclose(fp);
}