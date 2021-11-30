#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Exm {
   int   id_examen;
   int   cant_alumnos;
};

struct Stu {
   int   id_examen;
   char  id_estudiante[50];
};

struct Conf {
    int cant_conflictos;
    char id_estudiante[50];
};

struct CBJ {
    int *id_examenes;
    int id_examen;
};

struct Orden {
    int id_examen;
    int cant_conflictos;
};

struct Node {
    int timeslot;
    int id_examen;
    struct Node* child;
    struct Node* parent;
};

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

struct Exm** leer_exm(char* path, int *lines_exm){
    FILE *fp;
    int i = 0;
    int id_examen, cant_alumnos;
    *lines_exm = largo_archivo(path);
    struct Exm **matriz_exm = (struct Exm **)malloc(*lines_exm * sizeof(struct Exm*));
    fp = fopen(path, "r");
    while(!feof(fp)){
        struct Exm *arreglo_exm = (struct Exm *)malloc(sizeof(struct Exm));
        fscanf(fp, "%d %d", &id_examen,&cant_alumnos);
        arreglo_exm->id_examen = id_examen;
        arreglo_exm->cant_alumnos = cant_alumnos;
        matriz_exm[i] = arreglo_exm;
        i++;
    }
    fclose(fp);
    // printf("%d %d\n",matriz_exm[0]->id_examen, matriz_exm[0]->cant_alumnos);
    // printf("%d %d\n",matriz_exm[1]->id_examen,matriz_exm[1]->cant_alumnos);
    // printf("%d %d\n",matriz_exm[2]->id_examen,matriz_exm[2]->cant_alumnos);
    return matriz_exm;
}

struct Stu** leer_stu(char* path, int *lines_stu){
    FILE *fp;
    int i = 0;
    *lines_stu = largo_archivo(path);
    char id_estudiante[50];
    int id_examen;
    struct Stu **matriz_stu = (struct Stu **)malloc(*lines_stu * sizeof(struct Stu*));
    fp = fopen(path, "r");
    while(!feof(fp)){
        struct Stu *arreglo_stu = (struct Stu *)malloc(sizeof(struct Stu));
        fscanf(fp, "%s %d", id_estudiante, &id_examen);
        arreglo_stu->id_examen = id_examen;
        strcpy(arreglo_stu->id_estudiante, id_estudiante);
        matriz_stu[i] = arreglo_stu;
        i++;
    }
    fclose(fp);
    // printf("%s %d\n",matriz_stu[0]->id_estudiante, matriz_stu[0]->id_examen);
    // printf("%s %d\n",matriz_stu[1]->id_estudiante,matriz_stu[1]->id_examen);
    // printf("%s %d\n",matriz_stu[2]->id_estudiante,matriz_stu[2]->id_examen);
    // printf("%s %d\n",matriz_stu[3]->id_estudiante,matriz_stu[3]->id_examen);
    // printf("%s %d\n",matriz_stu[4]->id_estudiante,matriz_stu[4]->id_examen);
    return matriz_stu;
}

char** estudiantes(struct Stu **matriz_stu, int lines_stu, int *cant_alumnos){
    int i, j, flag;
    *cant_alumnos = 1;
    char *estudiante;
    char **arreglo_solo_stu = (char **)malloc(lines_stu * sizeof(char*));
    char *id_estudiante = (char *)malloc(50 * sizeof(char));
    id_estudiante = matriz_stu[0]->id_estudiante;
    arreglo_solo_stu[0] = id_estudiante;
    for(i=0 ; i<lines_stu ; i++){
        estudiante = matriz_stu[i]->id_estudiante;
        flag = 0;
        for(j=0 ; j<(*cant_alumnos) ; j++){
            if(strcmp(estudiante,arreglo_solo_stu[j]) == 0){
                flag = 1;
                break;
            }
        }
        if(flag == 0){
            char *id_estudiante = (char *)malloc(50 * sizeof(char));
            id_estudiante = estudiante;
            arreglo_solo_stu[*cant_alumnos] = id_estudiante;
            *cant_alumnos = *cant_alumnos + 1;
        }
    }
    return arreglo_solo_stu;
}


struct Conf** conflicto(struct Stu **matriz_stu, int lines_stu, char **arreglo_solo_stu, int cant_alumnos){
    int i, j, k, flag;
    struct Conf **matriz_conf = (struct Conf **)malloc(cant_alumnos * sizeof(struct Conf*));
    for(i=0 ; i<cant_alumnos ; i++){
        struct Conf *arreglo_conf = (struct Conf *)malloc(sizeof(struct Conf));
        arreglo_conf->cant_conflictos = -1;
        strcpy(arreglo_conf->id_estudiante, arreglo_solo_stu[i]);
        for(j=0 ; j<lines_stu ; j++){
            //for por matriz_stu
            //recorrer hasta que encuentre matriz_exm[j]->cant_alumnos
            //si encuentra una coincidencia, sumar 1 al arreglo_conf->cant_conflictos
            if(strcmp(arreglo_solo_stu[i],matriz_stu[j]->id_estudiante) == 0){
                arreglo_conf->cant_conflictos = arreglo_conf->cant_conflictos + 1;
            }
        }
        matriz_conf[i] = arreglo_conf;
    }
    return matriz_conf;
}

struct Orden** examenes(struct Exm **matriz_exm, int lines_exm){
    int i;
    struct Orden **matriz_orden = (struct Orden **)malloc(lines_exm * sizeof(struct Orden*));
    for(i=0 ; i<lines_exm ; i++){
        struct Orden *arreglo_orden = (struct Orden *)malloc(sizeof(struct Orden));
        arreglo_orden->id_examen = matriz_exm[i]->id_examen;
        arreglo_orden->cant_conflictos = 0;
        matriz_orden[i] = arreglo_orden;
    }
    return matriz_orden;
}

void agregar_conflicto(struct Orden **matriz_orden, struct Conf **matriz_conf,struct Stu **matriz_stu, int lines_exm, int cant_alumnos, int lines_stu){
    int i, j, k;
    for(i=0 ; i<lines_exm ; i++){
        for(j=0 ; j<lines_stu ; j++){
            if(matriz_stu[j]->id_examen == matriz_orden[i]->id_examen){
                for(k=0 ; k<cant_alumnos ; k++){
                    if(strcmp(matriz_stu[j]->id_estudiante,matriz_conf[k]->id_estudiante) == 0){
                        matriz_orden[i]->cant_conflictos = matriz_orden[i]->cant_conflictos + matriz_conf[k]->cant_conflictos;
                    }
                }
            }
        }
    }
}

void sort_inverse(struct Orden **matriz_orden, int lines_exm){
    int counter, counter1;
    struct Orden *swap_var;
    for (counter = 0 ; counter < lines_exm - 1; counter++){
        for (counter1 = 0 ; counter1 < lines_exm - counter - 1; counter1++){
            if (matriz_orden[counter1]->cant_conflictos < matriz_orden[counter1+1]->cant_conflictos) /* For decreasing order use < */{
                swap_var = matriz_orden[counter1];
                matriz_orden[counter1] = matriz_orden[counter1+1];
                matriz_orden[counter1+1] = swap_var;
            }
        }
    }
}

int tope_examenes_aux(int id_examen1, int id_examen2, struct Stu **matriz_stu, int lines_stu){
    //revisa si 2 examenes tienen tope
    int i,j;
    char *id_examen_stu;
    for(i=0 ; i<lines_stu ; i++){
        if(matriz_stu[i]->id_examen == id_examen1){
            id_examen_stu = matriz_stu[i]->id_estudiante;
            for(j=0 ; j<lines_stu ; j++){
                if((matriz_stu[j]->id_examen == id_examen2) && (strcmp(id_examen_stu,matriz_stu[j]->id_estudiante) == 0)){
                    return 1;
                }
            }
        }
    }
    return 0;
}

int tope_examenes(struct Node *nodo_aux, struct Node *nodo, struct Stu **matriz_stu, int lines_stu){
    // printf("id_aux id : %d %d\n",nodo_aux->id_examen, nodo->id_examen);
    if(nodo_aux->timeslot == nodo->timeslot && nodo_aux->id_examen != nodo->id_examen){
        // printf("comparando nodo_aux y nodo: %d %d\n",nodo_aux->id_examen,nodo->id_examen);
        if(tope_examenes_aux(nodo_aux->id_examen, nodo->id_examen, matriz_stu, lines_stu) == 1){
            // printf("hay tope\n");
            //retorna la más vieja en conflicto
            return nodo->id_examen;
        }
    }
    if(nodo->child != NULL){
    // printf("xd\n");
        return tope_examenes(nodo_aux, nodo->child, matriz_stu, lines_stu);
    }
    return 0;
}

void insertar(struct Node *nodo, struct Node *nodo_aux){
    if(nodo->child == NULL){
        nodo_aux->parent = nodo;
        nodo->child = nodo_aux;
    }
    else insertar(nodo->child, nodo_aux);
}

int backtracking(struct Node *nodo){
    if(nodo->child == NULL){
        int timeslott = nodo->timeslot;
        printf("nodo borrado\n");
        nodo->parent = NULL;
        free(nodo);
        return timeslott;
    }
    else{
        if(nodo->child->child == NULL){
            int timeslott = nodo->child->timeslot;
            printf("nodo hijo borrado\n");
            nodo->child->parent = NULL;
            free(nodo->child);
            nodo->child = NULL;
            return timeslott;
        }
        else{
            backtracking(nodo->child);
        }
        
    }
}

int cant_saltos(struct Node *nodo, int timeslots, int contador){
    if(nodo == NULL){
        return contador;
    }
    else{
        // printf("lines_exm , timeslot = %d , %d\n",lines_exm,nodo->timeslot);
            
        contador = contador + nodo->timeslot/timeslots;
        contador = contador*nodo->timeslot/timeslots;
        printf("contador = %d\n",contador);
       
        cant_saltos(nodo->child, timeslots, contador);
    }
}

// int salto_atras()

struct CBJ** crear_conf_cbj(struct Exm **matriz_exm, int lines_exm){
    // struct Exm **matriz_exm = (struct Exm **)malloc(*lines_exm * sizeof(struct Exm*));
    struct CBJ **matriz_cbj = (struct CBJ **)malloc(lines_exm * sizeof(struct CBJ*));
    int i,j;
    for(i=0 ; i<lines_exm ; i++){
        // printf("%d\n",matriz_exm[i]->id_examen);
        struct CBJ *arreglo_cbj = (struct CBJ *)malloc(sizeof(struct CBJ));
        arreglo_cbj->id_examenes = (int *)malloc(lines_exm * sizeof(int));
        for(j=0 ; j<lines_exm ; j++){
            arreglo_cbj->id_examenes[j] = 0;
        }
        // printf("mori\n");
        arreglo_cbj->id_examen = matriz_exm[i]->id_examen;
        matriz_cbj[i] = arreglo_cbj;
    }
    return matriz_cbj;
}

void agregar_conf_cbj(struct CBJ **matriz_cbj, int lines_exm, int id_examen1, int id_examen2){
    int i;
    for(i=0 ; i<lines_exm ; i++){
        if(matriz_cbj[i]->id_examen == id_examen1){
            matriz_cbj[i]->id_examenes[id_examen2-1] = 1;
            // printf("agregando %d %d\n",id_examen1,id_examen2);
        }
    }
}

int retorno_cbj(struct CBJ **matriz_cbj, struct Orden **matriz_orden, int lines_exm, int id_examen){
    int i,j,k;
    for(i=0 ; i<lines_exm ; i++){
        if(matriz_cbj[i]->id_examen == id_examen){
            for(j=lines_exm-1 ; j>-1 ; j--){
                for(k=0 ; k<lines_exm ; k++){
                    if(matriz_cbj[i]->id_examenes[matriz_orden[j]->id_examen-1] == 1){
                        // return matriz_orden[j]->id_examen;
                        return j;
                    }
                }
            }
        }
    }
}

struct Orden** ordenar(struct Stu **matriz_stu, struct Exm **matriz_exm, struct Conf **matriz_conf, struct Orden **matriz_orden, char **arreglo_solo_stu, int lines_stu, int lines_exm, int cant_alumnos, int tipo_orden){
    matriz_orden = examenes(matriz_exm,lines_exm);
    if(tipo_orden == 1){
        arreglo_solo_stu = estudiantes(matriz_stu, lines_stu, &cant_alumnos);
        matriz_conf = conflicto(matriz_stu, lines_stu, arreglo_solo_stu, cant_alumnos);
        agregar_conflicto(matriz_orden, matriz_conf, matriz_stu, lines_exm, cant_alumnos, lines_stu);
        sort_inverse(matriz_orden, lines_exm);
    }
    return matriz_orden;
}

void grafo(struct Orden **matriz_orden, struct Stu **matriz_stu, struct CBJ **matriz_cbj, int lines_exm, int lines_stu, int timeslots, int printear){
    int i = 0, j, k, it, tope, cont, flag = 1, ultimo_tope = 0, soluciones = 0, look_back = 1, fallo = 0;
    int xd = 0;
    struct Node *nodo = (struct Node *)malloc(sizeof(struct Node));
    j = 1;
    //inicializar nodo
    nodo->id_examen = 0;
    nodo->timeslot = 0;
    nodo->child = NULL;
    while(flag){
        cont = 0;
        for(i ; i<lines_exm ; i++){
            printf("(1) i,j = %d , %d\n",i,j);
            // printf("aaa\n");
            struct Node *nodo_aux = (struct Node *)malloc(sizeof(struct Node));
            nodo_aux->id_examen = matriz_orden[i]->id_examen;
            nodo_aux->timeslot = j;
            nodo_aux->child = NULL;
            insertar(nodo, nodo_aux);
            tope = tope_examenes(nodo_aux,nodo,matriz_stu,lines_stu);
            if(tope != 0 || j>timeslots){
                // printf("hay tope\n");
                agregar_conf_cbj(matriz_cbj,lines_exm,nodo_aux->id_examen,tope);
                if(j <= timeslots){
                    cont++;
                    // printf("cont = %d\n",cont);
                    if(cont == timeslots && look_back == 1){
                        printf("FALLO\n");
                        // printf("id examen %d\n",nodo_aux->id_examen);
                        printf("retorno cbj: %d\n",retorno_cbj(matriz_cbj,matriz_orden,lines_exm,nodo_aux->id_examen));
                        fallo = lines_exm - retorno_cbj(matriz_cbj,matriz_orden,lines_exm,nodo_aux->id_examen) - 1;
                        printf("fallo: %d\n",fallo);
                        look_back = 0;
                    }
                }
                if(j > timeslots){
                    if(ultimo_tope < lines_exm - i){
                        ultimo_tope = lines_exm - i;
                        printf("ultimo tope = %d\n",ultimo_tope);
                        j=1;
                    }
                }else{
                    //ver si hay que usar bt o cbj
                    printf("entree\n");
                    // printf("nodo: %d\n", nodo_aux->id_examen);

                    // if(look_back){
                        // agregar_conf_cbj(matriz_cbj,lines_exm,nodo_aux->id_examen,tope);
                    // }else{
                    if(fallo == 0){
                        printf("entree2\n");
                        backtracking(nodo);
                        i--;
                        j++;

                    }

                    // }
                }
            }else{
                // printf("no hay tope\n");
                cont = 0;
                if(i != lines_exm-1) j=1;
            }
        }
        // if(j == lines_exm) it++;
        xd++;
        soluciones++;

        if(printear){
            printf("--------------------------------------------------------\n");
            printf("Solución número %d:\n",soluciones);
            printf("Id examen | Timeslot | Matriz de conflicto\n");
            printf("   %d      |    %d     | %d %d %d %d %d\n",nodo->child->id_examen, nodo->child->timeslot,matriz_cbj[0]->id_examenes[0],matriz_cbj[0]->id_examenes[1],matriz_cbj[0]->id_examenes[2],matriz_cbj[0]->id_examenes[3],matriz_cbj[0]->id_examenes[4]);
            printf("   %d      |    %d     | %d %d %d %d %d\n",nodo->child->child->id_examen, nodo->child->child->timeslot,matriz_cbj[1]->id_examenes[0],matriz_cbj[1]->id_examenes[1],matriz_cbj[1]->id_examenes[2],matriz_cbj[1]->id_examenes[3],matriz_cbj[1]->id_examenes[4]);
            printf("   %d      |    %d     | %d %d %d %d %d\n",nodo->child->child->child->id_examen, nodo->child->child->child->timeslot,matriz_cbj[2]->id_examenes[0],matriz_cbj[2]->id_examenes[1],matriz_cbj[2]->id_examenes[2],matriz_cbj[2]->id_examenes[3],matriz_cbj[2]->id_examenes[4]);
            printf("   %d      |    %d     | %d %d %d %d %d\n",nodo->child->child->child->child->id_examen, nodo->child->child->child->child->timeslot,matriz_cbj[3]->id_examenes[0],matriz_cbj[3]->id_examenes[1],matriz_cbj[3]->id_examenes[2],matriz_cbj[3]->id_examenes[3],matriz_cbj[3]->id_examenes[4]);
            printf("   %d      |    %d     | %d %d %d %d %d\n",nodo->child->child->child->child->child->id_examen, nodo->child->child->child->child->child->timeslot,matriz_cbj[4]->id_examenes[0],matriz_cbj[4]->id_examenes[1],matriz_cbj[4]->id_examenes[2],matriz_cbj[4]->id_examenes[3],matriz_cbj[4]->id_examenes[4]);
        }
        
        if(j >= timeslots){
            // printf("????\n");
            if(fallo != 0){
                printf("fallllloooooo\n");
                it = fallo;
                soluciones--;
                // fallo = 0;
            }
            // else 
            // flag = 0;
            else{
                printf("entree3\n");

                it = cant_saltos(nodo, timeslots, 0);

            }
        } 
        // else{
            // printf("XDDDDD\n");
        if(ultimo_tope != 0){
            // printf("ultimo tope\n");
            it = ultimo_tope;
            ultimo_tope = 0;
            soluciones--;
        }else{
            if(fallo == 0){
                // it = 0;
            }
            else fallo = 0;
        }
        // } 
        printf("it = %d \n",it);
        // break;
        backtracking(nodo);
        i--;
        j++;
        for(k = 0 ; k< it ; k++){
            if(k == lines_exm-1){
                // printf("SALI \n");
                // soluciones--;
                flag = 0;
                printf("CANTIDAD DE SOLUCIONES: %d\n",soluciones);
            }else{
                j = backtracking(nodo);
                // printf("j = %d\n",j);
                i--;
                j++;
                printf("i = %d\n",i);
            }
        }
        // printf("(2) i,j = %d , %d\n", i, j);
        // if(soluciones == 2) break;
        if(xd == 11) break;
    }
}

void liberar_memoria(int lines_exm, int lines_stu, struct Exm **matriz_exm, struct Stu **matriz_stu){
    int i;
    for(i = 0 ; i<lines_exm ; i++){
        free(matriz_exm[i]);
    }
    free(matriz_exm);
    for(i = 0 ; i<lines_stu ; i++){
        free(matriz_stu[i]);
    }
    free(matriz_stu);
    printf("Memoria liberada.\n");
}

int main() {
    int lines_exm, lines_stu, cant_alumnos;
    struct Exm **matriz_exm;
    struct Stu **matriz_stu;
    struct Conf **matriz_conf;
    struct Orden **matriz_orden;
    struct CBJ **matriz_cbj;
    char **arreglo_solo_stu;

    //-------------------inputs del usuario-------------------

    char exm[] = "ejemplo5.exm";
    char stu[] = "ejemplo5.stu";
    int cant_timeslots = 2;
    int tipo_orden = 0; //0 = sin orden, 1 = más conflicto primero
    int printear_pasos = 1; //0 = no, 1 = si

    //--------------------------------------------------------

    matriz_exm = leer_exm(exm, &lines_exm);
    matriz_stu = leer_stu(stu, &lines_stu);
    
    // arreglo_solo_stu = estudiantes(matriz_stu, lines_stu, &cant_alumnos);
    // matriz_conf = conflicto(matriz_stu, lines_stu, arreglo_solo_stu, cant_alumnos);
    // matriz_orden = examenes(matriz_exm,lines_exm);
    // agregar_conflicto(matriz_orden, matriz_conf, matriz_stu, lines_exm, cant_alumnos, lines_stu);
    // sort_inverse(matriz_orden, lines_exm);
    matriz_orden = ordenar(matriz_stu,matriz_exm,matriz_conf,matriz_orden,arreglo_solo_stu,lines_stu,lines_exm,cant_alumnos,tipo_orden);

    matriz_cbj = crear_conf_cbj(matriz_exm, lines_exm);
    // printf("%d %d %d %d\n",matriz_cbj[0]->id_examen,matriz_cbj[0]->id_examenes[0],matriz_cbj[0]->id_examenes[1],matriz_cbj[0]->id_examenes[2]);
    // printf("%d %d %d %d\n",matriz_cbj[1]->id_examen,matriz_cbj[1]->id_examenes[0],matriz_cbj[1]->id_examenes[1],matriz_cbj[1]->id_examenes[2]);
    // printf("%d %d %d %d\n",matriz_cbj[2]->id_examen,matriz_cbj[2]->id_examenes[0],matriz_cbj[2]->id_examenes[1],matriz_cbj[2]->id_examenes[2]);
    // printf("%d %d %d %d\n",matriz_cbj[3]->id_examen,matriz_cbj[3]->id_examenes[0],matriz_cbj[3]->id_examenes[1],matriz_cbj[3]->id_examenes[2]);
    
    printf("%d %d\n",matriz_orden[0]->id_examen,matriz_orden[0]->cant_conflictos);
    printf("%d %d\n",matriz_orden[1]->id_examen,matriz_orden[1]->cant_conflictos);
    printf("%d %d\n",matriz_orden[2]->id_examen,matriz_orden[2]->cant_conflictos);
    printf("%d %d\n",matriz_orden[3]->id_examen,matriz_orden[3]->cant_conflictos);
    


    // printf("%s %d\n",matriz_conf[0]->id_estudiante,matriz_conf[0]->cant_conflictos);
    // printf("%s %d\n",matriz_conf[1]->id_estudiante,matriz_conf[1]->cant_conflictos);
    // printf("%s %d\n",matriz_conf[2]->id_estudiante,matriz_conf[2]->cant_conflictos);
    // printf("%s %d\n",matriz_conf[3]->id_estudiante,matriz_conf[3]->cant_conflictos);
    // printf("%s %d\n",matriz_conf[4]->id_estudiante,matriz_conf[4]->cant_conflictos);
    // printf("%s %d\n",matriz_conf[5]->id_estudiante,matriz_conf[5]->cant_conflictos);
    // printf("%s %d\n",matriz_conf[6]->id_estudiante,matriz_conf[6]->cant_conflictos);

    // printf("%d\n",tope_examenes(1, 2,matriz_stu,lines_stu));

    grafo(matriz_orden, matriz_stu, matriz_cbj, lines_exm, lines_stu,cant_timeslots,printear_pasos);
    
    liberar_memoria(lines_exm,lines_stu,matriz_exm,matriz_stu);
    return 0;
    //todo:
    //-struct y grafo CHECK
    //-heuristica de más conflictos primero CHECK
        //hacer una funcion que te devuelva una lista con todos los estudiantes CHECK
        //lista de conflictos CHECK
    //-backtracking CHECK
    //-CBJ
        //-crear matriz de CBJ CHECK
        //-crear un caso de prueba con fallo
        //-probar la matriz de CBJ
    //-output

}
//sudo apt-get install build-essential
//gcc ETP.c -o etp