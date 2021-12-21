Rodrigo Cayazaya Marín 2021-2

Descripción:
El siguiente código resuelve el problema de Examination Timetabling Problem, el cual consiste en encontrar la cantidad mínima de timeslots asignados a exámenes sin que exista tope de horario y reduciendo la penalización promedio por estudiante.
El código esta hecho en el lenguaje C y fue probado en el sistema operativo linux.

Para poder correr el código es necesario:
-C
-Librerias: stdio, stdlib, string y math
-gcc

Comando para correr el código:
-Make run

Input:
-El input debe encontrarse en la misma carpeta que el código.
-Al correr el código le va a pedir el nombre de los archivos ".exm" y ".stu", el nombre debe incluir su extensión. Por ejemplo: "ejemplo.exm".
-También existe la opción de ingresar de forma manual la cantidad máxima de timeslots y el orden de instanciación.

Instanciaciones:
-Dentro de esta carpeta se encuentran 3 instanciaciones con el nombre de instanciacion1, instanciacion2 y instanciacion3.
-Estas instanciaciones corresponden a las presentadas en la sección de "experimentos" del escrito.

Formato entrada:
-El archivo ".exm" debe tener la siguiente estructura: id del exámen, seguido de un espacio y la cantidad de estudiantes que van a rendir ese exámen.
-El archivo ".stu" debe tener la siguiente estructura: id del estudiante, seguido de un espacio y la id del exámen que debe rendir.

Output:
-etp: es el archivo ejecutable que genera el código.
-PENALIZACION.pen: penalización promedio por estudiante.
-PROBLEM.res: la cantidad mínima de timeslots utilizados.
-SOLUCION.sol: las id de los exámenes y sus timeslots asignados.