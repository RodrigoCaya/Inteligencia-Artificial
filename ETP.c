#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char** estudiantes(char*** matriz_stu, int lines_stu, int *cant_arreglo_solo_stu){
    int i, j, flag;
    *cant_arreglo_solo_stu = 1;
    char *estudiante;
    char **arreglo_solo_stu = (char **)malloc(lines_stu * sizeof(char*));
    char *id_estudiante = (char *)malloc(255 * sizeof(char));
    id_estudiante = matriz_stu[0][0];
    arreglo_solo_stu[0] = id_estudiante;
    for(i=0 ; i<lines_stu ; i++){
        estudiante = matriz_stu[i][0];
        flag = 0;
        for(j=0 ; j<(*cant_arreglo_solo_stu) ; j++){
            if(strcmp(estudiante,arreglo_solo_stu[j]) == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            char *id_estudiante = (char *)malloc(255 * sizeof(char));
            id_estudiante = estudiante;
            arreglo_solo_stu[*cant_arreglo_solo_stu] = id_estudiante;
            *cant_arreglo_solo_stu = *cant_arreglo_solo_stu + 1;
        }
    }
    return arreglo_solo_stu;
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
    int lines_exm, lines_stu, cant_arreglo_solo_stu;
    int **matriz_exm;
    char ***matriz_stu;
    char **arreglo_solo_stu;

    matriz_exm = leer_exm(exm, &lines_exm);
    matriz_stu = leer_stu(stu, &lines_stu);
    

    arreglo_solo_stu = estudiantes(matriz_stu, lines_stu, &cant_arreglo_solo_stu);
    
    liberar_memoria(lines_exm,lines_stu,matriz_exm,matriz_stu);
    return 0;
    //hacer una funcion que te devuelva una lista con todos los estudiantes
    //hacer una funcion que te devuelva los estudiantes que van a dar el examen X
    //hacer una funcion para ver si el estudiante Y se encuentra en esa lista

}
//sudo apt-get install build-essential
//gcc ETP.c -o etp