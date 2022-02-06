import random
# random.seed(42)

def leer_txt(nombre_archivo):
    archivo = open(nombre_archivo, 'r')
    i = 0
    objetos = []
    for linea in archivo:
        go,po = linea.split(" ")
        go = int(go.strip())
        po = int(po.strip())
        if(i == 0):
            n = go
            cmax = po
        else:
            objetos.append((go,po,i-1))
        i += 1
    return (n,cmax,objetos)

def ordenar_objetos(objetos,version):
    if(version == 1):#Ordenar por peso
        objetos.sort(key=lambda x: x[1])
    elif(version == 2):#Ordenar por ganancia
        objetos.sort(key=lambda x: x[0], reverse = True)
    elif(version == 3):#Ordenar por ratio
        objetos.sort(key=lambda x: x[0]/x[1], reverse = True)
    return objetos

def greedy(n,cmax,objetos,aleatorio = 0, alpha = 0):
    solucion = []
    peso = 0
    ganancia = 0
    if(aleatorio == 1):
        n -= 1
        objeto_random = objetos[random.randint(0, n)]
        solucion.append(objeto_random)
        peso += objeto_random[1]
        ganancia += objeto_random[0]
        objetos.remove(objeto_random)
        print("Se ha agregado el objeto: ", objeto_random)
    if(alpha == 0):
        for i in range(n):
            objeto = objetos[i]
            if(peso + objeto[1] <= cmax):
                solucion.append(objeto)
                peso += objeto[1]
                ganancia += objeto[0]
    else:
        flag = 1
        while(flag):
            lista_candidatos = []
            for i in range(n):
                objeto = objetos[i]
                if(peso + objeto[1] <= cmax):
                    lista_candidatos.append(objeto)
                if(len(lista_candidatos) == alpha):
                    break
            if(len(lista_candidatos) == 0):
                flag = 0
                break
            objeto_random = lista_candidatos[random.randint(0, len(lista_candidatos)-1)]
            solucion.append(objeto_random)
            peso += objeto_random[1]
            ganancia += objeto_random[0]
            objetos.remove(objeto_random)
            n -= 1
            print("(Alpha) Se ha agregado el objeto: ", objeto_random)
    return solucion,peso,ganancia

def lista_binaria(objetos,n):
    lista_bin = []
    objetos.sort(key=lambda x: x[2])
    for i in range(n):
        flag = 0
        for j in range(len(objetos)):
            if(objetos[j][2] == i):
                lista_bin.append(1)
                flag = 1
            if(objetos[j][2] > i):
                break
        if(flag == 0):
            lista_bin.append(0)
    return lista_bin
    
#------------------------------------------------------------------------------

archivo = "Inst02.txt"

n,cmax,objetos = leer_txt(archivo)
# print("Objetos:",objetos)

objetos = ordenar_objetos(objetos,2)
# print("Objetos:",objetos)

solucion_greedy,peso,ganancia = greedy(n,cmax,objetos,aleatorio = 0 , alpha = 10)
print("Peso",peso)
print("Ganancia",ganancia)
# print("Objetos:",objetos)
# print("Greedy:",solucion_greedy)

solucion = lista_binaria(solucion_greedy,n)
print("Lista binaria:",solucion)

