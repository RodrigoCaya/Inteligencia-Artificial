#include <stdio.h>
#include <stdlib.h>

int largo_archivo(char* path){
    FILE *fp;
    fp = fopen(path, "r");
    int lines = 1;
    char ch;
    while(!feof(fp)){
        ch = fgetc(fp);
        if(ch == '\n'){
            lines++;
        }
    }
    fclose(fp);
    return lines;
}

int** leer_exm(char* path, int *lines_exm){
    FILE *fp;
    int i = 0;
    int id_examen, cant_alumnos;
    *lines_exm = largo_archivo(path);
    int **matriz_exm = (int **)malloc(*lines_exm * sizeof(int*));
    fp = fopen(path, "r");
    while(!feof(fp)){
        int *arreglo_exm = (int *)malloc(2 * sizeof(int));
        fscanf(fp, "%d", &id_examen);
        fscanf(fp, "%d", &cant_alumnos);
        arreglo_exm[0] = id_examen;
        arreglo_exm[1] = cant_alumnos;
        matriz_exm[i] = arreglo_exm;
        i++;
    }
    fclose(fp);
    return matriz_exm;
}

char*** leer_stu(char* path, int *lines_stu){
    FILE *fp;
    int i = 0;
    *lines_stu = largo_archivo(path);
    char ***matriz_stu = (char ***)malloc(*lines_stu * sizeof(char**));
    fp = fopen(path, "r");
    while(!feof(fp)){
        char *id_estudiante = (char *)malloc(255 * sizeof(char));
        char *id_examen = (char *)malloc(255 * sizeof(char));
        char **arreglo_stu = (char **)malloc(2 * sizeof(char*));
        fscanf(fp, "%s", id_estudiante);
        fscanf(fp, "%s", id_examen);
        arreglo_stu[0] = id_estudiante;
        arreglo_stu[1] = id_examen;
        matriz_stu[i] = arreglo_stu;
        i++;
    }
    fclose(fp);
    return matriz_stu;
}

void liberar_memoria(int lines_exm, int lines_stu, int** matriz_exm, char*** matriz_stu){
    int i;
    for(i = 0 ; i<lines_exm ; i++){
        free(matriz_exm[i]);
    }
    free(matriz_exm);
    for(i = 0 ; i<lines_stu ; i++){
        free(matriz_stu[i][0]);
        free(matriz_stu[i][1]);
        free(matriz_stu[i]);
    }
    free(matriz_stu);
    printf("Memoria liberada.\n");
}

int main() {
    char exm[] = "ejemplo.exm";
    char stu[] = "ejemplo.stu";
    int lines_exm, lines_stu;
    int **matriz_exm;
    char ***matriz_stu;

    matriz_exm = leer_exm(exm, &lines_exm);
    matriz_stu = leer_stu(stu, &lines_stu);
    
    liberar_memoria(lines_exm,lines_stu,matriz_exm,matriz_stu);
    return 0;

}
//sudo apt-get install build-essential
//gcc ETP.c -o etp