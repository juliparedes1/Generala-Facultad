#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N_DADOS 5
#define TURNOS 11
#define VALORES 6
#define BAR printf("\n");

// void tirarDados(int arr[N_DADOS]);                           // lanza los dados por primera vez
void tirarDados(int arrOriginal[N_DADOS], int cantDados); // repite las tiradas puedondo seleccionar cuales se desea cambiar
void mostrarTirada(int arr[N_DADOS]);                     // muestra los resultados de los dados
void ordenarMayorAMenor(int arr[N_DADOS]);                // ordena los dados para reconocerlos facilmente
void inicializarArrays(int arr[], int capacidad);
void contarFrecuencias(int dados[], int frecuencias[]);                                // cuenta la cantidad de veces que cayo un dado en el turno
void subirPuntaje(int puntajes[], int dados[], int frecuencias[], int primerGenerala); // suma los puntajes a cada jugador en su respectivo array
void mostrarPuntaje(int puntaje[]);                                                    // muestra los puntajes de cada jugador
void verificacionDeRepetir(int *rep);                                                  // verifica que los usuarios no hagan macanas
int SacarPuntosFinales(int arr[]);                                                     // suma los valores del array
void funcionAuxArr(int arr[]);                                                         // esto es para probar q todo ande bien x detras luego hay q borrarlo

int main()
{

  int dados[N_DADOS], a, repetir, cantjugadores = 1;
  srand(time(NULL));

  // Variante Do While

  do
  {
    printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2 >");
    scanf("%d", &cantjugadores);
  } while (cantjugadores >= 3 || cantjugadores <= 0);

  // printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2 >");
  // scanf("%d", &cantjugadores);
  // while (cantjugadores >= 3 || cantjugadores <= 0)
  // {
  //   printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2 >");
  //   scanf("%d", &cantjugadores);
  // }

  // cantjugadores--;

  if (cantjugadores == 2)
  {
    int puntajeJ1[TURNOS], puntajeJ2[TURNOS], puntajefinalJ1, puntajefinalJ2;
    int turnoJ1 = 1, turnoJ2 = 1;
    char nombreJ1[21], nombreJ2[21];
    int PrimerGeneralaJ1 = 0, PrimerGeneralaJ2 = 0;

    inicializarArrays(puntajeJ1, TURNOS);
    inicializarArrays(puntajeJ2, TURNOS);

    BAR
        printf("Ingrese el nombre del jugador 1, max 20 caracteres");
    BAR
        scanf("%20s", nombreJ1);
    BAR
        printf("Ingrese el nombre del jugador 2. max 20 caracteres");
    BAR
        scanf("%20s", nombreJ2);

    for (int t = 0; t < TURNOS * 2; t++)
    {
      // Array para guardar las frecuencias de cada numero
      int frecuencias[VALORES];

      inicializarArrays(frecuencias, VALORES);

      int acumTiradas = 1;

      // Turno del Jugador 1
      if (t % 2 == 0)
      {

        printf("Turno Del Jugador %s:  %d de %d", nombreJ1, turnoJ1, TURNOS);

        // Lanzamiento de dados
        // tirarDados(dados);
        tirarDados(dados, N_DADOS);

        BAR
            // mostrarTirada(dados);
            BAR
                printf("Si desea repetir su tirada Presione 1, de lo contrario presione 0 >");
        scanf("%d", &repetir);
        // verificacion de repetir tirada
        verificacionDeRepetir(&repetir);
        BAR while (repetir != 0 && acumTiradas < 3)
        {
          int cantATirar = 0;

          printf("Ingrese la cantidad de dados a tirar >");
          BAR
              scanf("%d", &cantATirar);
          while (cantATirar > 5 || cantATirar < 1)
          {
            printf("La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados");
            BAR
                scanf("%d", &cantATirar);
          }
          BAR
              tirarDados(dados, cantATirar);
          BAR
              // mostrarTirada(dados);
              BAR
                  acumTiradas++;
          if (acumTiradas >= 3)
          {
            break;
          }

          printf("presione 1 si desea volver a realizar una ultima tirada, de lo contrario presione 0 >");
          scanf("%d", &repetir);
          // verificacion de repetir tirada
          verificacionDeRepetir(&repetir);
        }
        turnoJ1++;
        contarFrecuencias(dados, frecuencias);
        subirPuntaje(puntajeJ1, dados, frecuencias, PrimerGeneralaJ1);
        mostrarPuntaje(puntajeJ1);

        // aca va lo q sigue
      }
      else
      // Turno del Jugador 2
      {
        printf("Turno Del Jugador %s: %d de %d", nombreJ2, turnoJ2, TURNOS);
        // tirarDados(dados);
        tirarDados(dados, N_DADOS);

        BAR
            // mostrarTirada(dados);
            BAR
                printf("Si desea repetir su tirada Presione 1, de lo contrario presione 0 >");
        scanf("%d", &repetir);
        BAR

            // Verificador de repetición
            verificacionDeRepetir(&repetir);
        while (repetir != 0 && acumTiradas < 3)
        {
          int cantATirar = 0;
          printf("Ingrese la cantidad de dados a tirar >");
          BAR
              scanf("%d", &cantATirar);
          while (cantATirar > 5 || cantATirar < 1)
          {
            printf("La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados");
            BAR
                scanf("%d", &cantATirar);
          }
          BAR
              tirarDados(dados, cantATirar);
          BAR
              // mostrarTirada(dados);
              BAR
                  acumTiradas++;
          if (acumTiradas >= 3)
          {
            break;
          }

          printf("presione 1 si desea volver a realizar una ultima tirada");
          BAR
              scanf("%d", &repetir);
          // verificacion de repetir tirada
          verificacionDeRepetir(&repetir);
        }
        turnoJ2++;
        contarFrecuencias(dados, frecuencias);
        subirPuntaje(puntajeJ2, dados, frecuencias, PrimerGeneralaJ2);
        mostrarPuntaje(puntajeJ2);

        // aca va lo q sigue
      }
    } // aca continua luego de los turnos
    puntajefinalJ1 = SacarPuntosFinales(puntajeJ1);
    puntajefinalJ2 = SacarPuntosFinales(puntajeJ2);
    if (puntajefinalJ1 > puntajefinalJ2)
    {
      printf("El jugador %s ha conseguido, %d puntos superando al jugador %s que ha conseguido %d puntos ", nombreJ1, puntajefinalJ1, nombreJ2, puntajefinalJ2);
    }
    else
    {
      printf("El jugador %s ha conseguido, %d puntos superando al jugador %s que ha conseguido %d puntos ", nombreJ2, puntajefinalJ1, nombreJ1, puntajefinalJ2);
    }
  }
  // Modo 1 Jugador
  else
  {
    char nombreJ1[21];
    int PrimerGeneralaJ1 = 0, puntajeJ1[TURNOS], puntajefinalJ1;
    inicializarArrays(puntajeJ1, TURNOS);
    BAR
        printf("Ingrese el nombre del jugador 1, max 20 caracteres");
    BAR
        scanf("%20s", nombreJ1);
    BAR for (int t = 0; t < TURNOS; t++)
    {
      int frecuencias[VALORES];
      inicializarArrays(frecuencias, VALORES);
      int acuTiradas = 1;
      printf("Turno %d de %d", t + 1, TURNOS);
      BAR
          // tirarDados(dados);
          tirarDados(dados, N_DADOS);
      BAR
          // mostrarTirada(dados);
          BAR
              printf("%s, deseas repetir su tirada? Presione 1, de lo contrario presione 0 >", nombreJ1);
      scanf("%d", &repetir);
      verificacionDeRepetir(&repetir);
      BAR while (repetir != 0 && acuTiradas < 3)
      {
        int cantATirar = 0;
        printf("Ingrese la cantidad de dados a tirar >");
        BAR
            scanf("%d", &cantATirar);
        while (cantATirar > 5 || cantATirar < 1)
        {
          printf("La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados");
          BAR
              scanf("%d", &cantATirar);
        }
        BAR
            tirarDados(dados, cantATirar);
        BAR
            // mostrarTirada(dados);
            BAR
                acuTiradas++;
        if (acuTiradas >= 3)
        {
          break;
        }

        printf("presione 1 si desea volver a realizar una ultima tirada de lo contrario presione 0 >");
        scanf("%d", &repetir);
        BAR
            verificacionDeRepetir(&repetir);
      }
      contarFrecuencias(dados, frecuencias);
      subirPuntaje(puntajeJ1, dados, frecuencias, PrimerGeneralaJ1);
      mostrarPuntaje(puntajeJ1);
    }

    // sigue aca
    puntajefinalJ1 = SacarPuntosFinales(puntajeJ1);
    BAR
        printf("%s tu puntaje final ha sido %d ", nombreJ1, puntajefinalJ1);
    BAR
        printf("Presione cualquier tecla para cerrar el juego");
  }

  scanf("%d", &a);

  return 0;
}

/////////////////////////////////////////////////////////////////////////////////
///

// Refactorizada para los dos usos, tirada de 5 o menos
// void tirarDados(int arr[N_DADOS])
// {
//   printf("Rodando! ⚄\n");
//   int a = 0;
//   for (int i = 0; i < N_DADOS; i++)
//   {
//     a = (rand() % 6) + 1;
//     arr[i] = a;
//   }
//   ordenarMayorAMenor(arr);
//   mostrarTirada(arr);
// }

void tirarDados(int arr[N_DADOS], int cantDados)
{
  if (cantDados == N_DADOS)
  {
    printf("Rodando! ⚄\n");
    int a = 0;
    for (int i = 0; i < N_DADOS; i++)
    {
      a = (rand() % 6) + 1;
      arr[i] = a;
    }
    ordenarMayorAMenor(arr);
    mostrarTirada(arr);
    return;
  }

  int arrSeleccionador[cantDados];

  for (int i = 0; i < cantDados; i++)
  {
    int num;
    printf("Seleccione la posicion del elemento %d de %d que ha elegido >", i + 1, cantDados);
    BAR
        scanf("%d", &num);
    while (num > 5 || num < 1)
    {
      printf("Posición Incorrecta. Las posiciones de los dados son del 1 al 5. Ingrese una posición valida >");
      BAR
          scanf("%d", &num);
    }

    arrSeleccionador[i] = num - 1;
  }

  for (int i = 0; i < cantDados; i++)
  {
    for (int j = 0; j < N_DADOS; j++)
    {
      if (arrSeleccionador[i] == j)
      {
        int a = (rand() % 6) + 1;
        arr[j] = a;
      }
    }
  }
  printf("Rodando! ⚄\n");
  mostrarTirada(arr);
  return;
}

void ordenarMayorAMenor(int arr[N_DADOS])
{
  int aux = 0;
  for (int i = 0; i < N_DADOS; i++)
  {
    for (int k = 0; k < N_DADOS - 1; k++)
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

void mostrarTirada(int arr[N_DADOS])
{
  for (int i = 0; i < N_DADOS; i++)
  {
    printf("|%d|", arr[i]);
  }
}

void subirPuntaje(int puntajes[], int dados[], int frecuencias[], int primerGenerala)
{
  int arrAux[TURNOS];
  inicializarArrays(arrAux, TURNOS);
  printf("Opciones de Puntuacion");
  BAR

      for (int i = 0; i < VALORES; i++)
  {
    if (puntajes[i] == 0)
    {
      printf("%d) Anotar %d al %d ", i + 1, (frecuencias[i] * (i + 1)), i + 1);
      BAR
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
    for (int i = 0; i < VALORES - 1; i++)
    {
      if (frecuencias[i] == 0)
      {
        escalera = 0;
        break;
      }
    }
    for (int i = 1; i < VALORES; i++)
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
      BAR
    }
    else
    {
      printf("7) Tacharse Escalera");
      BAR
          arrAux[6] = -1;
    }
  }

  // full

  if (puntajes[7] == 0)
  {

    int trio = 0, par = 0;
    for (int i = 0; i < VALORES; i++)
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
      BAR
    }
    else
    {
      printf("8) Tacharse Full ");
      arrAux[7] = -1;
      BAR
    }
  }

  // poker
  if (puntajes[8] == 0)
  {
    int poker = 0;
    for (int i = 0; i < VALORES; i++)
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
      BAR
    }
    else
    {
      printf("9) Tacharse Poker ");
      arrAux[8] = -1;
      BAR
    }
  }

  if (puntajes[9] == 0)
  {
    int generala = 0;
    for (int i = 0; i < VALORES; i++)
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
      BAR
    }
    else
    {
      printf("10) Tacharse Generala ");
      arrAux[9] = -1;
      BAR
    }
  }

  if (puntajes[10] == 0)
  {
    if (primerGenerala == 1)
    {
      printf("11) Anotarse Generala doble");
      arrAux[10] = 120;
      BAR
    }
    else
    {
      printf("11) Tacharse Generala Doble");
      arrAux[10] = -1;
      BAR
    }
  }

  // funcionAuxArr(arrAux); // ESTO HAY Q BORRRLo
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
  for (int i = 0; i < N_DADOS; i++)
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
  for (int i = 0; i < TURNOS; i++)
  {
    printf("----------------");
    if (puntaje[i] == -1)
    {
      printf("Los puntajes son %d) ---------", i + 1);
      BAR
    }
    else
    {
      printf("Los puntajes son %d) %d", i + 1, puntaje[i]);
      BAR
    }
  }
}

void verificacionDeRepetir(int *rep)
{
  while (*rep > 1 || *rep < 0)
  {
    printf("Si desea repetir su tirada Presione 1, de lo contrario presione 0 >");
    scanf("%d", rep);
  }
  // lo que quiero hacer es que despues de verificar cuanto vale rep, lo ponga en el valor la variable que se ingreso a la funcion
}

int SacarPuntosFinales(int arr[])
{
  int puntuacion = 0;
  for (int i = 0; i < TURNOS; i++)
  {
    if (arr[i] != -1)
    {
      puntuacion += arr[i];
    }
  }
  return puntuacion;
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
  for (int i = 0; i < TURNOS; i++) /// ESTO HAY Q BORRARLO primero del codigo luego la funcion
  {
    BAR
        printf("valores del array aux en este momento %d) %d", i + 1, arr[i]);
    BAR
  }
}
