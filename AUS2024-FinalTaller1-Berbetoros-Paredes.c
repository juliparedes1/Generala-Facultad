#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N_DADOS 5
#define TURNOS 11
#define VALORES 6
#define MAX_PUNTOS 485

void tirarDados(int arrOriginal[N_DADOS], int cantDados);                                                                       // Lanzamiento de dados (para todos los casos)
void mostrarTirada(int arr[N_DADOS]);                                                                                           // Muestra los resultados de los dados, se ejecuta internamente en tirarDados();
void ordenarMayorAMenor(int arr[N_DADOS]);                                                                                      // Ordena los dados para reconocerlos facilmente. También se ejecuta internamente en tirarDados();
void inicializarArrays(int arr[], int capacidad);                                                                               // Reinicia los arrays de puntajes a 0 en el caso de reiniciar la partida o iniciarla por primera vez
void contarFrecuencias(int dados[], int frecuencias[]);                                                                         // Cuenta la cantidad de veces que cayo un dado en el turno, sirve para detectar puntuaciones
void subirPuntaje(int puntajes[], int dados[], int frecuencias[], int primerGenerala);                                          // Suma los puntajes a cada jugador en su respectivo array
void mostrarPuntaje(int puntaje[]);                                                                                             // Muestra los puntajes de cada jugador
int sacarPuntosFinales(int arr[]);                                                                                              // Suma los valores del array f:w
char *mostrarDesempeño(int puntaje);                                                                                            // Determina el desempeño según el puntaje final. Devuelve un puntero de char*, ya que almacena un string. En cada caso de retorno, se asigna el tamano en memoria.
void mostrarAuxArr(int arr[]);                                                                                                  // Muestra como funciona el array auxiliar para asignar puntajes. Para DEMO
void resetGame(int *t, int arrTiempo[], int cantJugadores, int arrPuntajeJ1[], int arrPuntajeJ2[], int *turnoJ1, int *turnoJ2); // Resetea la partida si el jugador lo elige
void timeLogger(int jugador, time_t inicio, int tiempos[]);                                                                     // Muestra el tiempo de juego del turno activo, y el acumulado total

int main()
{
  // Se intancian las variables de los datos, repetidor, reseteo final y cantidad de jugadores
  int dados[N_DADOS], a, repetir, cantjugadores = 1;
  // Se crea la semilla para los dados y su aleatoriedad
  srand(time(NULL));

  do
  {
    printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2 > ");
    scanf("%d", &cantjugadores);
  } while (cantjugadores >= 3 || cantjugadores <= 0);

  // Se instancian las variables para los puntajes y turnos de los jugadores
  int puntajeJ1[TURNOS], puntajeJ2[TURNOS], puntajefinalJ1, puntajefinalJ2;
  int turnoJ1 = 1, turnoJ2 = 1;
  char nombreJ1[21], nombreJ2[21];
  int PrimerGeneralaJ1 = 0, PrimerGeneralaJ2 = 0;

  // Total de tiempo transcurrido en segundos para cada jugador
  int tiempos[cantjugadores];

  inicializarArrays(puntajeJ1, TURNOS);

  if (cantjugadores == 2)
  {
    inicializarArrays(puntajeJ2, TURNOS);
  }

  printf("Ingrese el nombre del jugador 1, max 20 caracteres > ");
  scanf("%20s", nombreJ1);

  if (cantjugadores == 2)
  {
    printf("Ingrese el nombre del jugador 2, max 20 caracteres > ");
    scanf("%20s", nombreJ2);
  }

  int turnoActivo;
  for (turnoActivo = 0; turnoActivo < (TURNOS * cantjugadores); turnoActivo++)
  {
    int reset = 1;

    // Array para guardar las frecuencias de cada numero. Es necesario para la inicializacion
    int frecuencias[VALORES];

    inicializarArrays(frecuencias, VALORES);
    int acumTiradas = 1;

    // Operadores ternarios que resumen una estructura de control para imprimir nombre y turno activo
    printf("Turno del Jugador %s:  %d de %d",
           cantjugadores == 1     ? nombreJ1
           : turnoActivo % 2 == 0 ? nombreJ1
                                  : nombreJ2,
           cantjugadores == 1     ? turnoActivo + 1
           : turnoActivo % 2 == 0 ? turnoJ1
                                  : turnoJ2,
           TURNOS);

    tirarDados(dados, N_DADOS);

    // Se instancia time_t inicio con tipo long, y se guarda el tiempo de inicio luego de tirar los dados
    time_t inicio = time(NULL);

    do
    {
      printf("Si desea repetir su tirada (intento 2), presione 1, de lo contrario presione 0 > ");
      scanf("%d", &repetir);
    } while (repetir < 0 || repetir > 1);

    while (repetir != 0 && acumTiradas < 3)
    {
      int cantATirar = 0;

      printf("Ingrese la cantidad de dados a tirar nuevamente > ");
      scanf("%d", &cantATirar);

      while (cantATirar > 5 || cantATirar < 1)
      {
        printf("La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados > ");
        scanf("%d", &cantATirar);
      }
      tirarDados(dados, cantATirar);
      acumTiradas++;

      if (acumTiradas >= 3)
      {
        break;
      }
      else
      {
        printf("Si desea repetir su tirada (intento %d), presione 1, de lo contrario presione 0 > ", acumTiradas + 1);
        scanf("%d", &repetir);
      }
    }

    contarFrecuencias(dados, frecuencias);

    if (cantjugadores == 2)
    {
      if (turnoActivo % 2 == 0)
      {
        turnoJ1++;
        subirPuntaje(puntajeJ1, dados, frecuencias, PrimerGeneralaJ1);
        mostrarPuntaje(puntajeJ1);
        timeLogger(0, inicio, tiempos);
      }
      else
      {
        turnoJ2++;
        subirPuntaje(puntajeJ2, dados, frecuencias, PrimerGeneralaJ2);
        mostrarPuntaje(puntajeJ2);
        timeLogger(1, inicio, tiempos);
      }
    }
    else
    {
      turnoJ1++;
      subirPuntaje(puntajeJ1, dados, frecuencias, PrimerGeneralaJ1);
      mostrarPuntaje(puntajeJ1);
      timeLogger(0, inicio, tiempos);
    }

    do
    {
      printf("Si desea resetear el juego presione 0, de lo contrario presione 1 > ");
      scanf("%d", &reset);
    } while (reset != 1 && reset != 0);

    if (reset == 0)
    {
      resetGame(&turnoActivo, tiempos, cantjugadores, puntajeJ1, puntajeJ2, &turnoJ1, &turnoJ2);
    }

    if (cantjugadores == 2)
    {
      if (turnoActivo % 2 == 0)
      {
        printf("El tiempo transcurrido en total para el J%d es %d segundos\n", 1, tiempos[0]);
      }
      else
      {
        printf("El tiempo transcurrido en total para el J%d es %d segundos\n", 2, tiempos[1]);
      }
    }
    else
    {
      printf("El tiempo transcurrido en total para el J%d es %d segundos\n", 1, tiempos[0]);
    }
  }

  puntajefinalJ1 = sacarPuntosFinales(puntajeJ1);

  if (cantjugadores == 2)
  {
    puntajefinalJ2 = sacarPuntosFinales(puntajeJ2);
    if (puntajefinalJ1 > puntajefinalJ2)
    {
      printf("El jugador %s ha conseguido, %d puntos superando al jugador %s que ha conseguido %d puntos.\n", nombreJ1, puntajefinalJ1, nombreJ2, puntajefinalJ2);
    }
    else if (puntajefinalJ1 < puntajefinalJ2)
    {
      printf("El jugador %s ha conseguido, %d puntos superando al jugador %s que ha conseguido %d puntos.\n", nombreJ2, puntajefinalJ2, nombreJ1, puntajefinalJ1);
    }
    else
    {
      printf("Ambos jugadores han conseguido %d puntos. Es un empate!\n", puntajefinalJ1);
    }
    printf("Desempeño de %s (J1): %s\n", nombreJ1, mostrarDesempeño(puntajefinalJ1));
    printf("Desempeño de %s (J2): %s\n", nombreJ2, mostrarDesempeño(puntajefinalJ2));
  }
  else
  {
    printf("%s tu puntaje final ha sido %d\n", nombreJ1, puntajefinalJ1);
    printf("Desempeño: %s\n", mostrarDesempeño(puntajefinalJ1));
  }
  printf("Presione cualquier tecla para cerrar el juego > ");
  scanf("%d", &a);
  return 0;
}

// Funciones

void tirarDados(int arr[N_DADOS], int cantDados)
{
  if (cantDados == N_DADOS)
  {
    printf("\nRodando! ⚄\n");
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
    printf("Seleccione la posicion del elemento %d de %d que ha elegido > ", i + 1, cantDados);
    scanf("%d", &num);
    while (num > 5 || num < 1)
    {
      printf("Posición Incorrecta. Las posiciones de los dados son del 1 al 5. Ingrese una posición valida > ");
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
    printf("|%d| ", arr[i]);
  }
  printf("\n");
}

void subirPuntaje(int puntajes[], int dados[], int frecuencias[], int primerGenerala)
{
  // Este array se utiliza para llevar la cuenta de que puntajes se anotaron y cuales no (independiente del valor)
  // Se checkea referenciando mediante indices comparados
  int arrAux[TURNOS];
  inicializarArrays(arrAux, TURNOS);
  printf("Opciones de Puntuacion:\n");

  for (int i = 0; i < VALORES; i++)
  {
    if (puntajes[i] == 0)
    {
      printf("%d) Anotar %d al %d\n", i + 1, (frecuencias[i] * (i + 1)), i + 1);
      arrAux[i] = frecuencias[i] * (i + 1);
      if (frecuencias[i] == 0)
      {
        arrAux[i] = -1;
      }
    }
  }

  // Escalera


  if (puntajes[6] == 0)
  {
    int escalera = 0;
    int acuEscalera = 0;
    for (int i = 0; i < VALORES - 1; i++)
    {
      if (frecuencias[i] == 1)
      {
        acuEscalera++;
      }
      
    }
    if (acuEscalera == 5)
      {
        escalera = 1;
      }else{
        acuEscalera = 0;
        for (int i = 1; i < VALORES; i++)
        {
          if (frecuencias[i]==1)
          {
            acuEscalera++;
          }
          
        }
        
      }
      if (acuEscalera == 5)
      {
        escalera = 1;
      }
      

      if (escalera)
      {
        printf("7) Anotarse Escalera\n");
        arrAux[6] = 35;
      }
      else
      {
        printf("7) Tacharse Escalera\n");
        arrAux[6] = -1;
      }
  }

  // Full
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
      printf("8) Anotarse Full\n");
      arrAux[7] = 50;
    }
    else
    {
      printf("8) Tacharse Full\n");
      arrAux[7] = -1;
    }
  }

  // Poker
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
      printf("9) Anotarse Poker\n");
      arrAux[8] = 75;
    }
    else
    {
      printf("9) Tacharse Poker\n");
      arrAux[8] = -1;
    }
  }

  // Generala
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
      printf("10) Anotarse Generala\n");
      arrAux[9] = 100;
    }
    else
    {
      printf("10) Tacharse Generala\n");
      arrAux[9] = -1;
    }
  }

  // Generala doble
  if (puntajes[10] == 0)
  {
    if (primerGenerala == 1)
    {
      printf("11) Anotarse Generala Doble\n");
      arrAux[10] = 120;
    }
    else
    {
      printf("11) Tacharse Generala Doble\n");
      arrAux[10] = -1;
    }
  }

  // Opcional: Ejecutar para mostrar el array auxiliar que se utiliza para calcular
  // mostrar(arrAux);

  int seleccionador = 0;
  printf("\nElija una opción > ");
  scanf("%d", &seleccionador);

  // El valor en arrAux[seleccionador - 1] sera 0 si ya el puntaje fue anotado
  while ((seleccionador > 12 || seleccionador < 0) || arrAux[seleccionador - 1] == 0)
  {
    printf("Elija un numero en el rango de opciones dadas > ");
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
  printf("\n----------------\n");
  printf("Los puntajes son:\n");
  for (int i = 0; i < TURNOS; i++)
  {
    if (puntaje[i] == -1)
    {
      printf("%d) \n", i + 1);
    }
    else
    {
      printf("%d) %d\n", i + 1, puntaje[i]);
    }
  }
  printf("\n----------------\n");
}

int sacarPuntosFinales(int arr[])
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

char *mostrarDesempeño(int puntaje)
{
  if (puntaje < 0 || puntaje > MAX_PUNTOS)
  {
    return "Puntaje fuera de rango";
  }

  if (puntaje >= 0 && puntaje <= 121)
  {
    return "Pobre";
  }
  else if (puntaje >= 122 && puntaje <= 242)
  {
    return "Regular";
  }
  else if (puntaje >= 243 && puntaje <= 363)
  {
    return "Bueno";
  }
  else
  {
    return "Excelente";
  }
}

void resetGame(int *t, int arrTiempo[], int cantJugadores, int arrPuntajeJ1[], int arrPuntajeJ2[], int *turnoJ1, int *turnoJ2)
{
  // Se configura en -1 porque el bucle ejecuta el aumento de la variable turnoActivo, para que quede en 0
  *t = -1;
  inicializarArrays(arrPuntajeJ1, TURNOS);
  if (cantJugadores == 2)
  {
    *turnoJ1 = 1;
    *turnoJ2 = 1;
    inicializarArrays(arrPuntajeJ2, TURNOS);
  }
  for (int i = 0; i < cantJugadores; i++)
  {
    arrTiempo[i] = 0;
  }
}

void timeLogger(int jugador, time_t inicio, int tiempos[])
{
  // Instanciamos el instante de ejecucion final
  time_t fin = time(NULL);
  // Utilizando difftime calculamos la diferencia de tiempo entre el final y el inicio
  int tiempoTranscurridoSegundos = difftime(fin, inicio);
  // Sumamos al tiempo total de cada jugador
  tiempos[jugador] += tiempoTranscurridoSegundos;
}

// Funcion opcional para mostrar el array auxiliar utilizado para puntuar (calculo paso a paso)

void mostrarAuxArr(int arr[])
{
  for (int i = 0; i < TURNOS; i++)
  {
    printf("\nValores del array aux en este momento %d) %d\n", i + 1, arr[i]);
  }
}
