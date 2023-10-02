#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
///ESTRUCTURAS:

typedef struct jugador{
    int dni;
    char nombre_apellido[30];
    int edad;
    char equipo[30];
} jugador;

typedef struct{
    jugador UnJugador;
    struct nodoJugador * siguiente;
} nodoJugador;

typedef struct{
    jugador unJugador;
    struct nodoJugadorDoble * siguiente;
    struct nodoJugadorDoble * anterior;
} nodoJugadorDoble;

///PROTOTIPADO:
nodoJugador *inicLista();
nodoJugadorDoble *inicListaDoble();
nodoJugador *crearNodo(jugador jugadorr);
nodoJugador *insertarPrincipio(nodoJugador *lista, nodoJugador *nodoInsertar);
nodoJugador *agregarNodoJugador(nodoJugador *lista, nodoJugador *nodoInsertar);
void mostrarUnJugadorArchi(jugador unJugador);
void mostrarArchi(char nombreArchi[]);
nodoJugador *armaListaJugadores(char nombreArchi[], nodoJugador *lista);
void mostrarUnSoloJugadorLista(nodoJugador *lista);
void mostrarListaRecursiva(nodoJugador *lista);
int contadorEquipos(nodoJugador *lista, char boca[],char riber[]);
jugador *restoEquipos(nodoJugador *lista, jugador *arregloResto);
nodoJugador *armarJugadoresSeleccionados(nodoJugador *lista, nodoJugador *listaSeleccionados);
nodoJugadorDoble *insertarPrincipioDoble(nodoJugadorDoble *lista, nodoJugadorDoble *nodoInsertar);
nodoJugadorDoble *armaSeleccion(nodoJugador *lista, nodoJugadorDoble *listaSeleccion);
void muestraEquipos(jugador *arregloResto, int dim);
void guardarSeleccion(char nombreArchi, nodoJugadorDoble *listaSeleccion);

int main(){
    char nombreArchi[] = {"jugadores.dat"};
    nodoJugador *listaJugadores = inicLista();
    mostrarArchi(nombreArchi); ///PARA DEBUGG

    listaJugadores = armaListaJugadores(nombreArchi,listaJugadores);
    mostrarListaRecursiva(listaJugadores);

    char riber[30] = {"River Plate"};
    char boca[30] = {"Boca Juniors"};

    nodoJugador *listaSeleccionados = inicLista();
    listaSeleccionados = armarJugadoresSeleccionados(listaJugadores,listaSeleccionados);

    printf("\nMOSTRANDO LISTA SELECCIONADOS: \n");
    mostrarListaRecursiva(listaSeleccionados);

    int dim = contadorEquipos(listaJugadores,boca,riber); ///cuenta los que tienen que estar en el arreglo para no tener memoria de mas
    jugador *arregloResto = (jugador *)malloc(dim * sizeof(jugador));
    arregloResto = restoEquipos(listaJugadores,arregloResto);

    nodoJugadorDoble *listaDobles = inicListaDoble();
    listaDobles = armaSeleccion(listaJugadores,listaDobles);
    mostrarListaRecursiva(listaDobles);

    char nombreSeleccion[] = {"seleccion.dat"};


/// TENGO UN ERROR CUANDO DIGO LISTA != NULL LA CONSOLA ME QUEDA LATIENDO.
}

///FUNCIONES:
nodoJugador *inicLista(){
    return NULL;
}
nodoJugadorDoble *inicListaDoble(){
    return NULL;
}
nodoJugador *crearNodo(jugador jugadorr){
    nodoJugador *aux = (nodoJugador*)malloc(sizeof(nodoJugador));
    aux->UnJugador = jugadorr;
    aux->siguiente = NULL;
    return aux;
}

nodoJugador *insertarPrincipio(nodoJugador *lista, nodoJugador *nodoInsertar){
    if(lista == NULL) lista = nodoInsertar;
    else{
        nodoInsertar->siguiente = lista;
        lista = nodoInsertar;
    }
    return lista;
}

nodoJugador *agregarNodoJugador(nodoJugador *lista, nodoJugador *nodoInsertar){
    nodoJugador *anteDeAux;
    nodoJugador *aux;
    if(lista == NULL) lista = nodoInsertar;
    else{
        if(nodoInsertar->UnJugador.dni < lista->UnJugador.dni) lista = insertarPrincipio(lista, nodoInsertar);
        else{
            anteDeAux = lista;
            aux = lista->siguiente;

            while(aux != NULL && (nodoInsertar->UnJugador.dni > aux->UnJugador.dni)){
                anteDeAux = aux;
                aux = aux->siguiente;
            }
            ///ARRANCAMOS CON LA INSERCION:
            anteDeAux->siguiente = nodoInsertar;
            nodoInsertar->siguiente = aux;
        }
    }
    return lista;
}
void mostrarUnJugadorArchi(jugador unJugador){
    printf("\n...................................\n");
    printf("Nombre: %s\n", unJugador.nombre_apellido);
    printf("Edad: %i\n", unJugador.edad);
    printf("DNI: %i\n", unJugador.dni);
    printf("Equipo: %s", unJugador.equipo);
    printf("\n...................................\n");
}
void mostrarArchi(char nombreArchi[]){
    FILE *punteroArchi = fopen(nombreArchi, "rb");
    jugador unJugador;
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&unJugador, sizeof(jugador),1,punteroArchi);
            if(!feof(punteroArchi)){
                mostrarUnJugadorArchi(unJugador);
            }
        }
        fclose(punteroArchi);
    }else printf("\nERRROR al abrir el archivo.\n");
}

nodoJugador *armaListaJugadores(char nombreArchi[], nodoJugador *lista){
    FILE *punteroArchi = fopen(nombreArchi, "rb");
    jugador unJugador;
    nodoJugador *nodoNuevo;
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&unJugador, sizeof(jugador),1,punteroArchi);
            nodoNuevo = crearNodo(unJugador);
            if(!feof(punteroArchi)){
               lista = agregarNodoJugador(lista,nodoNuevo);
            }
        }
        fclose(punteroArchi);
    }else printf("\nERRROR al abrir el archivo.\n");
    return lista;
}

void mostrarUnSoloJugadorLista(nodoJugador *lista){
    printf("\n...................................\n");
    printf("Nombre: %s\n", lista->UnJugador.nombre_apellido);
    printf("Edad: %i\n", lista->UnJugador.edad);
    printf("DNI: %i\n", lista->UnJugador.dni);
    printf("Equipo: %s", lista->UnJugador.equipo);
    printf("\n...................................\n");
}

void mostrarListaRecursiva(nodoJugador *lista){
    if(lista == NULL) printf("\nLa lista llego a su fin\n");
    else{
        mostrarUnSoloJugadorLista(lista);
        mostrarListaRecursiva(lista->siguiente);
    }
}

nodoJugador *armarJugadoresSeleccionados(nodoJugador *lista, nodoJugador *listaSeleccionados){
    char riber[] = {"River Plate"};
    char boca[] = {"Boca Juniors"};
    nodoJugador *nodoInsertar;
    if(lista == NULL) printf("\nLa lista esta vacia no hay nada que eliminar\n");
    else{
        while(lista != NULL){
            if(strcmpi(lista->UnJugador.equipo,riber) == 0){
                nodoInsertar = lista;
                listaSeleccionados = insertarPrincipio(listaSeleccionados, nodoInsertar);

            }
            if(strcmpi(lista->UnJugador.equipo,boca) == 0){
                nodoInsertar = lista;
                listaSeleccionados = insertarPrincipio(listaSeleccionados, nodoInsertar);
            }

            lista = lista->siguiente;
        }
    }
    return listaSeleccionados;
}

int contadorEquipos(nodoJugador *lista, char boca[],char riber[]){
    int i = 0;
    while(lista != NULL){
        if(strcmpi(lista->UnJugador.equipo, riber) != 0){
                i++;
            }
        if(strcmpi(lista->UnJugador.equipo, boca) != 0){
                i++;
        }
        lista = lista->siguiente;
    }
    return i;
}

jugador *restoEquipos(nodoJugador *lista, jugador *arregloResto){
    char riber[30] = {"River Plate"};
    char boca[30] = {"Boca Juniors"};
    int i = 0;

    while(lista != NULL){
        if(strcmpi(lista->UnJugador.equipo,riber) != 0){
            arregloResto[i] = lista->UnJugador;
            i++;
        }
        if(strcmpi(lista->UnJugador.equipo,boca) != 0){
            arregloResto[i] = lista->UnJugador;
            i++;
        }
        lista = lista->siguiente;
    }
    return arregloResto;
}

nodoJugadorDoble *insertarPrincipioDoble(nodoJugadorDoble *lista, nodoJugadorDoble *nodoInsertar){
    if(lista == NULL) lista = nodoInsertar;
    else{
        nodoInsertar->siguiente = lista;
        lista->anterior = nodoInsertar;
    }
    return lista;
}

nodoJugadorDoble *armaSeleccion(nodoJugador *lista, nodoJugadorDoble *listaSeleccion){
    char riber[30] = {"River Plate"};
    char boca[30] = {"Boca Juniors"};
    nodoJugadorDoble *nodoInsertar;
    if(lista == NULL) printf("\nLa lista esta vacia no hay nada que eliminar\n");
    else{
        while(lista != NULL){
            if(lista->UnJugador.edad <= 30 && (strcmpi(lista->UnJugador.equipo, riber) == 0)){
                nodoInsertar->unJugador.dni = lista->UnJugador.dni;
                nodoInsertar->unJugador.edad = lista->UnJugador.edad;
                strcpy(nodoInsertar->unJugador.equipo, lista->UnJugador.equipo);
                strcpy(nodoInsertar->unJugador.nombre_apellido, lista->UnJugador.nombre_apellido);

                listaSeleccion = insertarPrincipioDoble(listaSeleccion,nodoInsertar);
            }
        }
    }
    return listaSeleccion;
}

void muestraEquipos(jugador *arregloResto, int dim){
    for(int i = 0; i< dim; i++){
    printf("\n...................................\n");
    printf("Nombre: %s\n", arregloResto[i].nombre_apellido);
    printf("Edad: %i\n", arregloResto[i].edad);
    printf("DNI: %i\n", arregloResto[i].dni );
    printf("Equipo: %s", arregloResto[i].equipo);
    printf("\n...................................\n");
    }
}

void guardarSeleccion(char nombreArchi, nodoJugadorDoble *listaSeleccion){
    FILE *punteroArchi = fopen(nombreArchi, "ab");
    jugador unJugador;
    if(punteroArchi != NULL){
        while(listaSeleccion != NULL){
            unJugador = listaSeleccion->unJugador;
            fwrite(&unJugador, sizeof(jugador),1,punteroArchi);
            listaSeleccion = listaSeleccion->siguiente;
        }
        fclose(punteroArchi);
    }
}
