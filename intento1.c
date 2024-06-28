#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DTot 5
#define turnos 11
#define Valores 6
#define bar printf("\n");

void tirarDados();                                        // lanza los dados por primera vez
void mostrarTirada();                                     // muestra los resultados de los dados
void ordenarMayorAmenor(int arr[DTot]);                   // ordena los dados para reconocerlos facilmente
void repetirTirada(int arrOriginal[DTot], int cantDados); // repite las tiradas puedondo seleccionar cuales se desea cambiar
void inicializarArrays(int arr[], int capacidad);
void contarFrecuencias(int dados[], int frecuencias[]);                                // cuenta la cantidad de veces que cayo un dado en el turno
void subirPuntaje(int puntajes[], int dados[], int frecuencias[], int primerGenerala); // suma los puntajes a cada jugador en su respectivo array
void mostrarPuntaje(int puntaje[]);                                                    // muestra los puntajes de cada jugador
void verificacionDeRepetir(int *rep);                                                  // verifica que los usuarios no hagan macanas
int SacarPuntosFinales(int arr[]);                                                     // suma los valores del array
void funcionAuxArr(int arr[]);                                                         // esto es para probar q todo ande bien x detras luego hay q borrarlo
void reset1Jugador(int *t, int arrPuntajeJ1[], double arrTiempo[], int cantJugadores);
void reset2Jugadores(int *t, int arrPuntajeJ1[], int arrPuntajeJ2[], double arrTiempo[], int cantJugadores);
void finalizarTurno(int jugador, clock_t inicio, double tiempos[/*aca va la cant jugadores */]);

int main()
{

    int dados[DTot], a, repetir, cantjugadores;
    srand(time(NULL));

    printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2");
    scanf("%d", &cantjugadores);
    while (cantjugadores >= 3 || cantjugadores <= 0)
    {
        printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2");
        scanf("%d", &cantjugadores);
    }

    cantjugadores--;

    if (cantjugadores)
    {
        int puntajeJ1[turnos], puntajeJ2[turnos], puntajefinalJ1, puntajefinalJ2;
        int turnoJ1 = 1, turnoJ2 = 1;
        char nombreJ1[21], nombreJ2[21];
        double tiempos[cantjugadores + 1];
        int PrimerGeneralaJ1 = 0, PrimerGeneralaJ2 = 0;
        for (int i = 0; i < cantjugadores + 1; i++)
        {
            tiempos[i] = 0;
        }

        inicializarArrays(puntajeJ1, turnos);
        inicializarArrays(puntajeJ2, turnos);
        bar
            printf("Ingrese el nombre del jugador 1, max 20 caracteres");
        bar
            scanf("%20s", nombreJ1);
        bar
            printf("Ingrese el nombre del jugador 2. max 20 caracteres");
        bar
            scanf("%20s", nombreJ2);

        for (int t = 0; t < turnos * 2; t++)
        {
            clock_t inicio = clock();
            int reset = 1;
            int frecuencias[Valores];
            inicializarArrays(frecuencias, Valores);
            int acuTiradas = 1;
            if (t % 2 == 0)
            {

                printf("Turno Del Jugador %s:  %d de %d", nombreJ1, turnoJ1, turnos);
                tirarDados(dados);
                bar
                    mostrarTirada(dados);
                bar
                    printf("Si desea repetir su tirada Presione 1, de lo contrario presione 0");
                bar
                    scanf("%d", &repetir);
                // verificacion de repetir tirada
                verificacionDeRepetir(&repetir);
                bar while (repetir != 0 && acuTiradas < 3)
                {
                    int cantATirar = 0;
                    printf("ingrese la cantidad de dados a tirar");
                    bar
                        scanf("%d", &cantATirar);
                    while (cantATirar > 5 || cantATirar < 1)
                    {
                        printf("La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados");
                        bar
                            scanf("%d", &cantATirar);
                    }
                    bar
                        repetirTirada(dados, cantATirar);
                    bar
                        mostrarTirada(dados);
                    bar
                        acuTiradas++;
                    if (acuTiradas >= 3)
                    {
                        break;
                    }

                    printf("presione 1 si desea volver a realizar una ultima tirada, de lo contrario presione 0");
                    bar
                        scanf("%d", &repetir);
                    // verificacion de repetir tirada
                    verificacionDeRepetir(&repetir);
                }
                turnoJ1++;
                contarFrecuencias(dados, frecuencias);
                subirPuntaje(puntajeJ1, dados, frecuencias, PrimerGeneralaJ1);
                mostrarPuntaje(puntajeJ1);
                bar
                    printf("Si desea resetear el juego presione 0, de lo contrario presione 1");
                bar
                    scanf("%d", &reset);
                while (reset != 1 && reset != 0)
                {
                    bar
                        printf("Si desea resetear el juego presione 0, Para continuar presione 1");
                    bar
                        scanf("%d", &reset);
                }

                if (reset == 0)
                {
                    reset2Jugadores(&t, puntajeJ1, puntajeJ2, tiempos, cantjugadores+1);
                }

                finalizarTurno(cantjugadores, inicio, tiempos);

                // aca va lo q sigue
            }
            else
            {
                clock_t inicio = clock();
                printf("Turno Del Jugador %s: %d de %d", nombreJ2, turnoJ2, turnos);
                tirarDados(dados);
                bar
                    mostrarTirada(dados);
                bar
                    printf("Si desea repetir su tirada Presione 1, de lo contrario presione 0");
                bar
                    scanf("%d", &repetir);
                bar
                    // verificacion de repetir tirada
                    verificacionDeRepetir(&repetir);
                while (repetir != 0 && acuTiradas < 3)
                {
                    int cantATirar = 0;
                    printf("ingrese la cantidad de dados a tirar");
                    bar
                        scanf("%d", &cantATirar);
                    while (cantATirar > 5 || cantATirar < 1)
                    {
                        printf("La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados");
                        bar
                            scanf("%d", &cantATirar);
                    }
                    bar
                        repetirTirada(dados, cantATirar);
                    bar
                        mostrarTirada(dados);
                    bar
                        acuTiradas++;
                    if (acuTiradas >= 3)
                    {
                        break;
                    }

                    printf("presione 1 si desea volver a realizar una ultima tirada");
                    bar
                        scanf("%d", &repetir);
                    // verificacion de repetir tirada
                    verificacionDeRepetir(&repetir);
                }
                turnoJ2++;
                contarFrecuencias(dados, frecuencias);
                subirPuntaje(puntajeJ2, dados, frecuencias, PrimerGeneralaJ2);
                mostrarPuntaje(puntajeJ2);
                bar
                    printf("Si desea resetear el juego presione 0, de lo contrario presione 1");
                bar
                    scanf("%d", &reset);
                while (reset != 1 && reset != 0)
                {
                    bar
                        printf("Si desea resetear el juego presione 0, Para continuar presione 1");
                    bar
                        scanf("%d", &reset);
                }

                if (reset == 0)
                {
                    reset2Jugadores(&t, puntajeJ1, puntajeJ2, tiempos, cantjugadores+1);
                }
                finalizarTurno(cantjugadores + 1, inicio, tiempos);
                // aca va lo q sigue
            }
        } // aca continua luego de los turnos
        puntajefinalJ1 = SacarPuntosFinales(puntajeJ1);
        puntajefinalJ2 = SacarPuntosFinales(puntajeJ2);
        if (puntajefinalJ1 > puntajefinalJ2)
        {
            printf("El jugador %s ha conseguido, %d puntos, ha conseguido finalizar el juego en %.2f segundos, superando al jugador %s que ha conseguido %d puntos ", nombreJ1, puntajefinalJ1, tiempos[0], nombreJ2, puntajefinalJ2);
        }
        else
        {
            printf("El jugador %s ha conseguido, %d puntos, ha conseguido finalizar el juego en %.2f segundos, superando al jugador %s que ha conseguido %d puntos ", nombreJ2, puntajefinalJ1, tiempos[1], nombreJ1, puntajefinalJ2);
        }

    } // DE ACA PARA ABAJO ES UN JUGADOR
    else
    {
        char nombreJ1[21];
        int PrimerGeneralaJ1 = 0, puntajeJ1[turnos], puntajefinalJ1;
        double tiempo[1] = {0};
        inicializarArrays(puntajeJ1, turnos);
        bar
            printf("Ingrese el nombre del jugador 1, max 20 caracteres");
        bar
            scanf("%20s", nombreJ1);
        bar for (int t = 0; t < turnos; t++)
        {
            clock_t inicio = clock();
            int reset = 1;
            int frecuencias[Valores];
            inicializarArrays(frecuencias, Valores);
            int acuTiradas = 1;
            printf("turno %d de %d", t + 1, turnos);
            tirarDados(dados);
            bar
                mostrarTirada(dados);
            bar
                printf("%s deseas repetir su tirada Presione 1, de lo contrario presione 0", nombreJ1);
            bar
                scanf("%d", &repetir);
            verificacionDeRepetir(&repetir);
            bar while (repetir != 0 && acuTiradas < 3)
            {
                int cantATirar = 0;
                printf("ingrese la cantidad de dados a tirar");
                bar
                    scanf("%d", &cantATirar);
                while (cantATirar > 5 || cantATirar < 1)
                {
                    printf("La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados");
                    bar
                        scanf("%d", &cantATirar);
                }
                bar
                    repetirTirada(dados, cantATirar);
                bar
                    mostrarTirada(dados);
                bar
                    acuTiradas++;
                if (acuTiradas >= 3)
                {
                    break;
                }

                printf("presione 1 si desea volver a realizar una ultima tirada de lo contrario presione 0");
                bar
                    scanf("%d", &repetir);
                bar
                    verificacionDeRepetir(&repetir);
            }
            contarFrecuencias(dados, frecuencias);
            subirPuntaje(puntajeJ1, dados, frecuencias, PrimerGeneralaJ1);
            mostrarPuntaje(puntajeJ1);
            bar
                printf("Si desea resetear el juego presione 0, de lo contrario presione 1");
            bar
                scanf("%d", &reset);
            while (reset != 1 && reset != 0)
            {
                bar
                    printf("Si desea resetear el juego presione 0, Para continuar presione 1");
                bar
                    scanf("%d", &reset);
            }

            if (reset == 0)
            {
                reset1Jugador(&t, puntajeJ1, tiempo, cantjugadores );
            }
            finalizarTurno(cantjugadores, inicio, tiempo);
        }

        // sigue aca
        puntajefinalJ1 = SacarPuntosFinales(puntajeJ1);
        bar
            printf("%s tu puntaje final ha sido %d y has tardado %.2f segundos en completarlo ", nombreJ1, puntajefinalJ1, tiempo[0]);
        bar
            printf("Presione cualquier tecla para cerrar el juego");
    }

    scanf("%d", &a);

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
///
void tirarDados(int arr[DTot])
{
    int a = 0;
    for (int i = 0; i < DTot; i++)
    {
        a = (rand() % 6) + 1;
        arr[i] = a;
    }
    ordenarMayorAmenor(arr);
}

void mostrarTirada(int arr[DTot])
{
    for (int i = 0; i < DTot; i++)
    {
        printf("|%d|", arr[i]);
    }
}

void ordenarMayorAmenor(int arr[DTot])
{
    int aux = 0;
    for (int i = 0; i < DTot; i++)
    {
        for (int k = 0; k < DTot - 1; k++)
        {
            if (arr[k + 1] > arr[k])
            {
                aux = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = aux;
            }
        }
    }
}

void repetirTirada(int arrOriginal[DTot], int cantDados)
{

    int arrSeleccionador[cantDados];

    for (int i = 0; i < cantDados; i++)
    {
        int num;
        printf("seleccione la posicion del elemento %d de %d que ha elegido ", i + 1, cantDados);
        bar
            scanf("%d", &num);
        while (num > 5 || num < 1)
        {
            printf("Las posiciones de los dados son del 1 al 5");
            bar
                scanf("%d", &num);
        }

        arrSeleccionador[i] = num - 1;
    }

    for (int i = 0; i < cantDados; i++)
    {
        for (int j = 0; j < DTot; j++)
        {
            if (arrSeleccionador[i] == j)
            {
                int a = (rand() % 6) + 1;
                arrOriginal[j] = a;
            }
        }
    }
}

void subirPuntaje(int puntajes[], int dados[], int frecuencias[], int primerGenerala)
{
    int arrAux[turnos];
    inicializarArrays(arrAux, turnos);
    printf("Opciones de Puntuacion");
    bar

        for (int i = 0; i < Valores; i++)
    {
        if (puntajes[i] == 0)
        {
            printf(" %d) Anotar %d al %d ", i + 1, (frecuencias[i] * (i + 1)), i + 1);
            bar
                arrAux[i] = frecuencias[i] * (i + 1);
            if (frecuencias[i] == 0)
            {
                arrAux[i] = -1;
            }
        }
    }

    // escalera

    if (puntajes[6] == 0)
    {
        int escalera = 1;
        for (int i = 0; i < Valores - 1; i++)
        {
            if (frecuencias[i] == 0)
            {
                escalera = 0;
                break;
            }
        }
        for (int i = 1; i < Valores; i++)
        {
            if (frecuencias[i] == 0)
            {
                escalera = 0;
                break;
            }
        }
        if (escalera)
        {
            printf("7) Anotarse Escalera");
            arrAux[6] = 35;
            bar
        }
        else
        {
            printf("7) Tacharse Escalera");
            bar
                arrAux[6] = -1;
        }
    }

    // full

    if (puntajes[7] == 0)
    {

        int trio = 0, par = 0;
        for (int i = 0; i < Valores; i++)
        {
            if (frecuencias[i] == 3)
            {
                trio = 1;
            }
            if (frecuencias[i] == 2)
            {
                par = 1;
            }
        }

        if (trio && par)
        {
            printf("8) Anotarse Full ");
            arrAux[7] = 50;
            bar
        }
        else
        {
            printf("8) Tacharse Full ");
            arrAux[7] = -1;
            bar
        }
    }

    // poker
    if (puntajes[8] == 0)
    {
        int poker = 0;
        for (int i = 0; i < Valores; i++)
        {
            if (frecuencias[i] == 4)
            {
                poker = 1;
            }
        }

        if (poker)
        {
            printf("9) Anotarse Pocker ");
            arrAux[8] = 75;
            bar
        }
        else
        {
            printf("9) Tacharse Poker ");
            arrAux[8] = -1;
            bar
        }
    }

    if (puntajes[9] == 0)
    {
        int generala = 0;
        for (int i = 0; i < Valores; i++)
        {
            if (frecuencias[i] == 5)
            {
                generala = 1;
                primerGenerala = 1;
            }
        }

        if (generala && !primerGenerala)
        {
            printf("10) Anotarse Generala ");
            arrAux[9] = 100;
            bar
        }
        else
        {
            printf("10) Tacharse Generala ");
            arrAux[9] = -1;
            bar
        }
    }

    if (puntajes[10] == 0)
    {
        if (primerGenerala == 1)
        {
            printf("11) Anotarse Generala doble");
            arrAux[10] = 120;
            bar
        }
        else
        {
            printf("11) Tacharse Generala Doble");
            arrAux[10] = -1;
            bar
        }
    }

    /* funcionAuxArr(arrAux); */ // ESTO HAY Q BORRRLo
    int seleccionador = 0;
    scanf("%d", &seleccionador);
    while ((seleccionador > 12 || seleccionador < 0) || arrAux[seleccionador - 1] == 0)
    {
        printf("Elija un numero en el rango de opciones dadas \n ->");
        scanf("%d", &seleccionador);
    }
    puntajes[seleccionador - 1] = arrAux[seleccionador - 1];
}

void contarFrecuencias(int dados[], int frecuencias[])
{
    for (int i = 0; i < DTot; i++)
    {
        frecuencias[dados[i] - 1]++;
    }
}

void inicializarArrays(int arr[], int capacidad)
{
    for (int i = 0; i < capacidad; i++)
    {
        arr[i] = 0;
    }
}

void mostrarPuntaje(int puntaje[])
{
    for (int i = 0; i < turnos; i++)
    {
        printf("----------------");
        if (puntaje[i] == -1)
        {
            printf("Los puntajes son %d) ---------", i + 1);
            bar
        }
        else
        {
            printf("Los puntajes son %d) %d", i + 1, puntaje[i]);
            bar
        }
    }
}

void verificacionDeRepetir(int *rep)
{
    while (*rep > 1 || *rep < 0)
    {
        printf("Si desea repetir su tirada Presione 1, de lo contrario presione 0");
        bar
            scanf("%d", rep);
    }
    // lo que quiero hacer es que despues de verificar cuanto vale rep, lo ponga en el valor la variable que se ingreso a la funcion
}

int SacarPuntosFinales(int arr[])
{
    int puntuacion = 0;
    for (int i = 0; i < turnos; i++)
    {
        if (arr[i] != -1)
        {
            puntuacion += arr[i];
        }
    }
    return puntuacion;
}

void reset1Jugador(int *t, int arrPuntajeJ1[], double arrTiempo[], int cantJugadores)
{
    *t = -1;
    inicializarArrays(arrPuntajeJ1, turnos);

    if (cantJugadores == 2)
    {
        for (int i = 0; i < 2; i++)
        {
            arrTiempo[i] = 0;
        }
    }else{
        arrTiempo[0] = 0;
    }
}

void reset2Jugadores(int *t, int arrPuntajeJ1[], int arrPuntajeJ2[], double arrTiempo[], int cantJugadores)
{
    *t = -1;
    inicializarArrays(arrPuntajeJ1, turnos);
    inicializarArrays(arrPuntajeJ2, turnos);
    if (cantJugadores == 2)
    {
        for (int i = 0; i < cantJugadores; i++)
        {
            arrTiempo[i] = 0;
        }
    }else{
        arrTiempo[0] = 0;
    }
}

void finalizarTurno(int jugador, clock_t inicio, double tiempos[/*aca va la cant jugadores */])
{
    clock_t fin = clock();                                               // Obtiene el tiempo actual al finalizar el turno
    double tiempoTranscurrido = (double)(fin - inicio) / CLOCKS_PER_SEC; // Calcula el tiempo transcurrido en segundos
    tiempos[jugador] += tiempoTranscurrido;                              // Agrega el tiempo transcurrido al total del jugador
}
// 25/6
/*  SE DEBEN REALIZAR VERIFICACIONES SOBRE LA CANTIDAD MAXIMA DE DADOS QUE SE PUEDEN SELECCIONAR EN EL REPETIR TIRADA; SE DEBE REALIZAR  LA  POSIBILIDAD DE JUGAR DE A 2, SE DEBE REALIZAR LA CANTIDAD TOTAL DE TURNOS (11), SE DEBE REALIZAR LA POSIBILIDAD DE CANCELAR CATEGORIAS Y DE ASIGNAR LOS PUNTAJES, SE DEBE DAR LA POSIBILIDAD DE ANOTAR SEGUN LOS ELEMENTOS DEL ARRAY LOS NUMEROS POSIBLES EN ACADA OPCION E IR ELIMINANDOA  LOS QUE YA SE LES HA ASIGNADO VALOR   */

// 26/6 se agrego funcionalidad de verificacion de repetidos
// se agrego funcionalidad de sumar puntos
// se completo el juego falta mejorar el codigo y verificar lo q pide para 2 programadores

// verificar que algo anda mal con la generala doble (creo que ya lo arregle)
// mejorar el codigo q esto es horrible
// eliminar funcion de array aux
// mejorar la interface grafica ahre q es la consola

void funcionAuxArr(int arr[])
{
    for (int i = 0; i < turnos; i++) /// ESTO HAY Q BORRARLO primero del codigo luego la funcion
    {
        bar
            printf("valores del array aux en este momento %d) %d", i + 1, arr[i]);
        bar
    }
}
