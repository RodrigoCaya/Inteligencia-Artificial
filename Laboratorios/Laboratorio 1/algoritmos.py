import copy

# sudoku = open("Sudoku01.txt","r")
sudoku = open("SudokuE.txt","r")
matriz = []
for linea in sudoku:
    for valor in linea:
        if (valor != " " and valor != "\n"):
            matriz.append(valor)

arcos = []
restricciones = {}
nodos = ['0','1','3','4','5','6','9','10','11','12','13','15']
dominios = {
    '0': [1, 2, 3, 4],
    '1': [1, 2, 3, 4],
    '2': [1, 2, 3, 4],
    '3': [1, 2, 3, 4],
    '4': [1, 2, 3, 4],
    '5': [1, 2, 3, 4],
    '6': [1, 2, 3, 4],
    '7': [1, 2, 3, 4],
    '8': [1, 2, 3, 4],
    '9': [1, 2, 3, 4],
    '10': [1, 2, 3, 4],
    '11': [1, 2, 3, 4],
    '12': [1, 2, 3, 4],
    '13': [1, 2, 3, 4],
    '14': [1, 2, 3, 4],
    '15': [1, 2, 3, 4]
}

def agregar_arco(lista1,lista2,lista3,lista4,arcos):
    for i1 in range(len(lista1)):
        for i11 in range(i1+1,len(lista1)):
            if((str(lista1[i1]),str(lista1[i11])) not in arcos):
                arcos.append((str(lista1[i1]),str(lista1[i11])))
                arcos.append((str(lista1[i11]),str(lista1[i1])))

    for i1 in range(len(lista2)):
        for i11 in range(i1+1,len(lista2)):
            if((str(lista2[i1]),str(lista2[i11])) not in arcos):
                arcos.append((str(lista2[i1]),str(lista2[i11])))
                arcos.append((str(lista2[i11]),str(lista2[i1])))

    for i1 in range(len(lista3)):
        for i11 in range(i1+1,len(lista3)):
            if((str(lista3[i1]),str(lista3[i11])) not in arcos):
                arcos.append((str(lista3[i1]),str(lista3[i11])))
                arcos.append((str(lista3[i11]),str(lista3[i1])))

    for i1 in range(len(lista4)):
        for i11 in range(i1+1,len(lista4)):
            if((str(lista4[i1]),str(lista4[i11])) not in arcos):
                arcos.append((str(lista4[i1]),str(lista4[i11])))
                arcos.append((str(lista4[i11]),str(lista4[i1])))

def nodo_consistencia(lista1,lista2,lista3,lista4,dominios,l1,l2,l3,l4):
    if(lista1 != None):
        for i1 in l1:
            if(str(i1) in dominios):
                for pista in lista1:
                    if(int(pista) in dominios[str(i1)]):
                        lista_updated = dominios[str(i1)]
                        lista_updated.remove(int(pista))
                        dominios[str(i1)] = lista_updated
    if(lista2 != None):
        for i1 in l2:
            if(str(i1) in dominios):
                for pista in lista2:
                    if(int(pista) in dominios[str(i1)]):
                        lista_updated = dominios[str(i1)]
                        lista_updated.remove(int(pista))
                        dominios[str(i1)] = lista_updated
    if(lista3 != None):
        for i1 in l3:
            if(str(i1) in dominios):
                for pista in lista3:
                    if(int(pista) in dominios[str(i1)]):
                        lista_updated = dominios[str(i1)]
                        lista_updated.remove(int(pista))
                        dominios[str(i1)] = lista_updated
    if(lista4 != None):
        for i1 in l4:
            if(str(i1) in dominios):
                for pista in lista4:
                    if(int(pista) in dominios[str(i1)]):
                        lista_updated = dominios[str(i1)]
                        lista_updated.remove(int(pista))
                        dominios[str(i1)] = lista_updated


def filas(matriz,arcos,dominios):
    variableFila1 = []
    variableFila2 = []
    variableFila3 = []
    variableFila4 = []

    pistaFila1 = []
    pistaFila2 = []
    pistaFila3 = []
    pistaFila4 = []

    for i in range(len(matriz)):
        valor = matriz[i]
        fila = (i)//4
        if(valor == '0'):
            if(fila == 0):
                variableFila1.append(i)
            elif(fila == 1):
                variableFila2.append(i)
            elif(fila == 2):
                variableFila3.append(i)
            else:
                variableFila4.append(i)
        else:
            del dominios[str(i)]
            if(fila == 0):
                pistaFila1.append(valor)
            elif(fila == 1):
                pistaFila2.append(valor)
            elif(fila == 2):
                pistaFila3.append(valor)
            else:
                pistaFila4.append(valor)

    agregar_arco(variableFila1,variableFila2,variableFila3,variableFila4,arcos)
    nodo_consistencia(pistaFila1,pistaFila2,pistaFila3,pistaFila4,dominios,range(4),range(4,8),range(8,12),range(12,16))
    
def columnas(matriz,arcos):
    variableColumna1 = []
    variableColumna2 = []
    variableColumna3 = []
    variableColumna4 = []

    pistaColumna1 = []
    pistaColumna2 = []
    pistaColumna3 = []
    pistaColumna4 = []

    for i in range(len(matriz)):
        valor = matriz[i]
        columna = (i)%4
        if(valor == '0'):
            if(columna == 0):
                variableColumna1.append(i)
            elif(columna == 1):
                variableColumna2.append(i)
            elif(columna == 2):
                variableColumna3.append(i)
            else:
                variableColumna4.append(i)
        else:
            if(columna == 0):
                pistaColumna1.append(valor)
            elif(columna == 1):
                pistaColumna2.append(valor)
            elif(columna == 2):
                pistaColumna3.append(valor)
            else:
                pistaColumna4.append(valor)
   
    agregar_arco(variableColumna1,variableColumna2,variableColumna3,variableColumna4,arcos)
    nodo_consistencia(pistaColumna1,pistaColumna2,pistaColumna3,pistaColumna4,dominios,[0,4,8,12],[1,5,9,13],[2,6,10,14],[3,7,11,15])


def submatrices(matriz,arcos):
    variableSubMatriz1 = []
    variableSubMatriz2 = []
    variableSubMatriz3 = []
    variableSubMatriz4 = []

    pistaSubMatriz1 = []
    pistaSubMatriz2 = []
    pistaSubMatriz3 = []
    pistaSubMatriz4 = []

    for i in range(len(matriz)):
        valor = matriz[i]
        subMatriz = 2*(i//8) + (i%4)//2
        if(valor == '0'):
            if(subMatriz == 0):
                variableSubMatriz1.append(i)
            elif(subMatriz == 1):
                variableSubMatriz2.append(i)
            elif(subMatriz == 2):
                variableSubMatriz3.append(i)
            else:
                variableSubMatriz4.append(i)
        else:
            if(subMatriz == 0):
                pistaSubMatriz1.append(valor)
            elif(subMatriz == 1):
                pistaSubMatriz2.append(valor)
            elif(subMatriz == 2):
                pistaSubMatriz3.append(valor)
            else:
                pistaSubMatriz4.append(valor)
    nodo_consistencia(pistaSubMatriz1,pistaSubMatriz2,pistaSubMatriz3,pistaSubMatriz4,dominios,[0,1,4,5],[2,3,6,7],[8,9,12,13],[10,11,14,15])
    agregar_arco(variableSubMatriz1,variableSubMatriz2,variableSubMatriz3,variableSubMatriz4,arcos)


def definir_restricciones(restricciones,arcos):
    for arco in arcos:
        restricciones[arco] = lambda a, b: a != b

filas(matriz,arcos,dominios)
# print(arcos)
# print("LARGO: ",len(arcos))
columnas(matriz,arcos)
# print(arcos)
# print("LARGO: ",len(arcos))
submatrices(matriz,arcos)
# print(arcos)
# print("LARGO: ",len(arcos))
definir_restricciones(restricciones,arcos)
print("Dominio Original:",dominios)

#################################### AC3 ####################################

#Se utilizó el código sacado de https://medium.com/swlh/how-to-solve-constraint-satisfaction-problems-csps-with-ac-3-algorithm-in-python-f7a9be538cfe

def revise(x, y,chequeo):
    """
    Make variable `x` arc consistent with variable `y`.
    To do so, remove values from `domains[x]` for which there is no
    possible corresponding value for `y` in `domains[y]`.
    Return True if a revision was made to the domain of `x`; return
    False if no revision was made.
    """
    revised = False

    # Get x and y domains
    x_domain = dominiosAC3[x]
    y_domain = dominiosAC3[y]

    # Get all arc (x, y) constraints
    all_constraints = [
        constraint for constraint in restricciones if constraint[0] == x and constraint[1] == y]

    for x_value in x_domain:
        satisfies = False
        for y_value in y_domain:
            for constraint in all_constraints:
                constraint_func = restricciones[constraint]
                chequeo += 1
                # print("Chequeo")
                if constraint_func(x_value, y_value):
                    satisfies = True
        if not satisfies:
            x_domain.remove(x_value)
            revised = True

    return revised,chequeo


def ac3(arcos):
    """
    Update `domains` such that each variable is arc consistent.
    """
    # Add all the arcs to a queue.
    queue = arcos[:]
    #print(queue)
    chequeo = 0
    instanciacion = 0
    # Repeat until the queue is empty
    while queue:
        # Take the first arc off the queue (dequeue)
        (x, y) = queue.pop(0)
        x = str(x)
        y = str(y)
        instanciacion += 1
        # print("Instanciaciones")

        # Make x arc consistent with y
        revised,chequeo = revise(x, y, chequeo)

        # If the x domain has changed
        if revised:
            # Add all arcs of the form (k, x) to the queue (enqueue)
            neighbors = [neighbor for neighbor in arcos if neighbor[1] == x]
            queue = queue + neighbors
    # print(chequeo)
    # print(instanciacion)


dominiosAC3 = copy.deepcopy(dominios)
ac3(arcos)
print("RESULTADO AC3:",dominiosAC3)
# Instanciaciones: 74
# Saltos: ?
# Chequeos: 110

#################################### GBJ ####################################

def GBJ_aux(nodos,arcos,restricciones,dominiosGBJ,n1,n2,d1,d2,resultado):
    print("nodos",nodos)
    # print("------------------")
    # print("n1",n1)
    if(len(nodos) <= n1):
        # print("MORI")
        return resultado
    nodoActual = nodos[n1]
    print("resultado",resultado)
    print("nodo actual",nodoActual)
    print("d1",d1)
    print("dominios",dominiosGBJ)
    resultado[nodoActual] = dominiosGBJ[nodoActual][d1]
    if(len(nodos) == n2): 
        resultado[nodoActual] = dominiosGBJ[nodoActual][d1]
        # print(resultado)
        return resultado
    # print("instanciación")
    nodoSiguiente = nodos[n2]
    arco = (nodoActual,nodoSiguiente)
    # print("N2",n2)
    if(len(dominiosGBJ[nodoSiguiente]) == d2): #GBJ
        print("GBJ")
        for i in range(n2, -1, -1):
            print("for")
            # print("VALOR:",str(i))
            # print("DEBUG",resultado)
            arco = (str(i),str(nodos[n2]))
            flag = True
            flag2 = True
            if(arco in arcos):
                flag = False
                if(i == 0):
                    return resultado
                n1_aux = nodos[i-1]
                n2_aux = nodos[i]
                d1_aux = dominiosGBJ[n1_aux].index(resultado[n1_aux])
                # print("d1_aux",d1_aux)
                print("n1_aux",n1_aux)
                print("resultado",resultado)
                print("dom",dominiosGBJ)

                if(resultado[n2_aux]+1 not in dominiosGBJ[n2_aux]):
                    print("entre")
                    print(dominiosGBJ[nodos[n1_aux]])
                    if(d1_aux +1 in dominiosGBJ[nodos[n1_aux]]):
                        d1_aux = d1_aux + 1
                        d2_aux = 0
                    else:
                        print("entre 2")
                        flag2 = False
                else:
                    d2_aux = dominiosGBJ[n2_aux].index(resultado[n2_aux]+1)
                if(nodos[i] in resultado):
                    del resultado[nodos[i]]
                # print("XDDDD 3")
                print("d1_aux",d1_aux)
                if(flag2):
                    GBJ_aux(nodos,arcos,restricciones,dominiosGBJ,int(n1_aux),int(n2_aux),int(d1_aux),int(d2_aux),resultado)
            if(nodos[i] in resultado and flag):
                    del resultado[nodos[i]]
        # return resultado
    siguiente = True
    flag = True
    for res,dom in resultado.items():
        arcoOtro = (res,nodoSiguiente)
        if(arcoOtro in arcos):
            # print("Chequeo")
            siguiente = restricciones[arcoOtro](dom,dominiosGBJ[nodoSiguiente][d2])
            if(siguiente == False):
                flag = False
    if(flag):
        # print("XDDDD")
        GBJ_aux(nodos,arcos,restricciones,dominiosGBJ,n2,n2+1,d2,0,resultado)
    else:
        # print("XDDDD 2")
        GBJ_aux(nodos,arcos,restricciones,dominiosGBJ,n1,n2,d1,d2+1,resultado)
    return resultado


def GBJ(nodos,arcos,restricciones,dominiosGBJ):
    resultado = {}
    return GBJ_aux(nodos,arcos,restricciones,dominiosGBJ,0,1,0,0,resultado)


# nodos = ['0','1','3','4','5','6','9','10','13','15']

# print("Arcos:",arcos)

arcosx0 = 0
arcosx1 = 0
arcosx3 = 0
arcosx4 = 0
arcosx5 = 0
arcosx6 = 0
arcosx9 = 0
arcosx10 = 0
arcosx11 = 0
arcosx12 = 0
arcosx13 = 0
arcosx15 = 0

for arc in arcos:
    for node in arc:
        if(node == '0'):
            arcosx0 += 1
        elif(node == '1'):
            arcosx1 += 1
        elif(node == '3'):
            arcosx3 += 1
        elif(node == '4'):
            arcosx4 += 1
        elif(node == '5'):
            arcosx5 += 1
        elif(node == '6'):
            arcosx6 += 1
        elif(node == '9'):
            arcosx9 += 1
        elif(node == '10'):
            arcosx10 += 1
        elif(node == '11'):
            arcosx11 += 1
        elif(node == '12'):
            arcosx12 += 1
        elif(node == '13'):
            arcosx13 += 1
        elif(node == '15'):
            arcosx15 += 1

lista_nodos = [(arcosx0,'0'),(arcosx1,'1'),(arcosx3,'3'),(arcosx4,'4'),(arcosx5,'5'),(arcosx6,'6'),(arcosx9,'9'),(arcosx10,'10'),(arcosx11,'11'),(arcosx12,'12'),(arcosx13,'13'),(arcosx15,'15')]

# print(lista_nodos)

lista_nodos.sort(reverse=True)

# print(lista_nodos)


dominiosGBJ = copy.deepcopy(dominios)
# dominiosGBJ = GBJ(nodos,arcos,restricciones,dominiosGBJ)
# print("RESULTADO GBJ:",dominiosGBJ)
# Instanciaciones: 16
# Saltos: 2
# Chequeos: 28


#################################### FC ####################################

def revisar(nodos,arcos,restricciones,dominiosFC,n1,d1,dominiosModificados,instanciacion,chequeos):
    # print("DOMINIO ORIGINAL",dominiosModificados)
    # flag = 1
    nodoActual = nodos[n1]
    valorN1 = dominiosFC[nodoActual][d1]
    # print("Nodo actual = ",nodoActual,valorN1)
    for i in range(n1+1,len(nodos)):
        # print(dominiosFC[nodos[i]])
        # print("nueva iteracion")
        for dominio in dominiosModificados[nodos[i]]:
            # print("DOMINIOOO",dominiosModificados[nodos[i]])
            arco = (nodoActual,nodos[i])
            # print("arco:",arco)
            # print("dominio,valorn1",dominio,valorN1)
            if(arco in arcos):
                # print("Chequeo")
                # chequeos += 1
                # print("arco:",nodoActual,nodos[i])
                # print("valores:",valorN1,dominio)
                if(not restricciones[arco](dominio,valorN1)):
                    updated_lista = copy.deepcopy(dominiosModificados[nodos[i]])
                    updated_lista.remove(int(dominio))
                    # print("updated_lista",updated_lista)
                    dominiosModificados[nodos[i]] = updated_lista
                    # print("DOMINIO MODIFICADO",dominiosModificados[nodos[i]])
                    if(updated_lista == []):
                        print("Dominio vacío")
                        return 0,chequeos
    # print(dominiosModificados)
    return 1,chequeos


def FC(nodos,arcos,restricciones,dominiosFC,n1,n2,d1,d2,resultado,dominiosModificados,instanciacion,chequeos):
    if(len(nodos) == n1):
        return dominiosModificados,chequeos
    instanciacion += 1
    # print("Instanciación")
    nodoActual = nodos[n1]
    valorN1 = dominiosFC[nodoActual][d1]
    resultado[nodoActual] = valorN1
    resul,chequeos = revisar(nodos,arcos,restricciones,dominios,n1,d1,dominiosModificados,instanciacion,chequeos)
    if(resul):
        l = []
        l.append(valorN1)
        dominiosModificados[nodoActual] = l
        dominiosFC = dominiosModificados
        FC(nodos,arcos,restricciones,dominiosFC,n2,n2+1,0,d2,resultado,dominiosModificados,instanciacion,chequeos)
    else:
        dominiosModificados = dominiosFC
        FC(nodos,arcos,restricciones,dominiosFC,n1,n2,d1+1,d2,resultado,dominiosModificados,instanciacion,chequeos)
    return dominiosModificados,chequeos


dominiosFC = copy.deepcopy(dominios)
resultado = {}
dominiosModificados = copy.deepcopy(dominios)
chequeos = 0
dominiosModificados,chequeos = FC(nodos,arcos,restricciones,dominiosFC,0,1,0,0,resultado,dominiosModificados,0,chequeos)
print("RESULTADO FC:",dominiosModificados)
# print(chequeos)
# Instanciaciones: 11
# Saltos: 0
# Chequeos: 32