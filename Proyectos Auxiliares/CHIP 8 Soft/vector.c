#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INIT_CAPACITY 6
#define UNDEFINED -1
#define SUCCESS 0

//Asigna la memoria inicialmente
#define VECTOR_INIT(vec) vector vec;\
vector_init(&vec)

//Estructura que almacena y trackea los datos
typedef struct sVectorList {
    void **items;
    int capacity;
    int total;
} sVectorList;

//Estructura que contiene los punteros a función
typedef struct sVector vector;
struct sVector {
    sVectorList vectorList;
    //Punteros a funcion
    int   (*pfVectorTotal)  (vector *);
    int   (*pfVectorResize) (vector *, int);
    int   (*pfVectorAdd)    (vector *, void *);
    int   (*pfVectorSet)    (vector *, int, void *);
    void *(*pfVectorGet)    (vector *, int);
    int   (*pfVectorDelete) (vector *, int);
    int   (*pfVectorFree)   (vector *);
};

//Inicializacion del vector
void vector_init(vector *v) {
    //Inicializacion de los punteros a funcion
    v->pfVectorTotal  = vectorTotal;
    v->pfVectorResize = vectorResize;
    v->pfVectorAdd    = vectorPushBack;
    v->pfVectorSet    = vectorSet;
    v->pfVectorGet    = vectorGet;
    v->pfVectorFree   = vectorFree;
    v->pfVectorDelete = vectorDelete;
    //Inicializa la capacidad y asigna la memoria
    v->vectorList.capacity = VECTOR_INIT_CAPACITY;
    v->vectorList.total    = 0;
    v->vectorList.items    = malloc(sizeof(void *) * v->vectorList.capacity);
}

//Función que devuelve el tamaño del vector
int vectorTotal (vector *v) {
    int totalCount = UNDEFINED;
    if (v) {
        totalCount = v->vectorList.total;
    }

    return totalCount;
}

//Función que asigna un nuevo tamaño de memoria y actualiza el trackeo de datos
int vectorResize (vector *v, int capacity) {
    int status = UNDEFINED;
    if(v) {
        void **items = realocc(v->vectorList.items, sizeof(void*) * capacity);
        if (items) {
            v->vectorList.items = items;
            v->vectorList.capacity = capacity;
            status = SUCCESS;
        }
    }

    return status;
}

//Función que inserta los datos al final del vector. Si no hay suficiente memoria disponible, cambia el tamaño de la memoria
int vectorPushBack (vector *v, void *item) {
    int status = UNDEFINED;
    if (v) {
        if (v->vectorList.capacity == v->vectorList.total) {
            status = vectorResize(v, v->vectorList.capacity * 2);
            if (status != UNDEFINED) {
                v->vectorList.items[v->vectorList.total++] = item;
            }
        }

        else {
            v->vectorList.items[v->vectorList.total++] = item;
            status = SUCCESS;
        }
    }

    return status;
}

//Función que establece los datos en un índice si el mismo es válido. Si el índice no es válido, no hace nada.
int vectorSet (vector *v, int index, void *item) {
    int status = UNDEFINED;
    if (v) {
        if ((index >= 0) && (index < v->vectorList.total)) {
            v->vectorList.items[index] = item;
            status = SUCCESS;
        }
    }

    return status;
}

//Función que devuelve el dato de un indice determinado
void *vectorGet (vector *v, int index) {
    void *readData = NULL;
    if (v) {
        if ((index >= 0) && (index < v->vectorList.total))
            readData = v->vectorList.items[index];
    }

    return readData;
}

//Función que libera la memoria del vector
int vectorFree (vector *v) {
    int status = UNDEFINED;
    if (v) {
        free(v->vectorList.items);
        v->vectorList.items = NULL;
        status = SUCCESS;
    }

    return status;
}

//Función que asigna NULL a un índice dado y shiftea todos los elementos del vector una posición
int vectorDelete (vector *v, int index) {
    int status = UNDEFINED;
    int i = 0;
    if (v) {
        if ((index < 0) || (index > v->vectorList.total))
            return status;

        v->vectorList.items[index] = NULL;

        for (i = index; (i < v->vectorList.total); ++i) {
            v->vectorList.items[i] = v->vectorList.items[i+1];
            v->vectorList.items[i+1] = NULL;
        }

        v->vectorList.total--;

        if ((v->vectorList.total > 0 ) && (v->vectorList.total) == (v->vectorList.capacity / 4)) {
            vectorResize(v, v->vectorList.capacity / 2);
        }

        status = SUCCESS;
    }

    return status;
}

//Ejemplo de uso de vector

int main (int argc, char *argv[]) {
    int i = 0;

    //Iniciar vector
    VECTOR_INIT(v);
    //Agregar data en el vector
    v.pfVectorAdd(&v, "Que onda pa?");
    v.pfVectorAdd(&v, "Soy un vector en c");
    v.pfVectorAdd(&v, "Bien piola");

    //imprimir los datos
    for (i = 0; i < v.pfVectorTotal(&v); i++)
        printf("%s", (char *)v.pfVectorGet(&v, i));

    //Setear la data del inidice 0
    v.pfVectorSet(&v, 0, "Cambiando la datita pa");

    printf("\n\n\nVector despues del cambio\n\n\n");

    for (i = 0; i < v.pfVectorTotal(&v); i++)
        printf("%s", (char *)v.pfVectorGet(&v, i));

    return 0;
}