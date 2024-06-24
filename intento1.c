#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DTot 5
#define bar printf("\n");

void tirarDados(); // lanza los dados por primera vez
void mostrarTirada(); // muestra los resultados de los dados
void ordenarMayorAmenor(int arr[DTot]); // ordena los dados para reconocerlos facilmente 
void repetirTirada(int arrOriginal[DTot] ,int cantDados ); // repite las tiradas puedondo seleccionar cuales se desea cambiar


/*  SE DEBEN REALIZAR VERIFICACIONES SOBRE LA CANTIDAD MAXIMA DE DADOS QUE SE PUEDEN SELECCIONAR EN EL REPETIR TIRADA; SE DEBE REALIZAR  LA  POSIBILIDAD DE JUGAR DE A 2, SE DEBE REALIZAR LA CANTIDAD TOTAL DE TURNOS (11), SE DEBE REALIZAR LA POSIBILIDAD DE CANCELAR CATEGORIAS Y DE ASIGNAR LOS PUNTAJES, SE DEBE DAR LA POSIBILIDAD DE ANOTAR SEGUN LOS ELEMENTOS DEL ARRAY LOS NUMEROS POSIBLES EN ACADA OPCION E IR ELIMINANDOA  LOS QUE YA SE LES HA ASIGNADO VALOR   */
int main (){

    int dados[DTot], a, repetir, acuTiradas = 1, cantjugadores;
    srand(time(NULL));

    printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2");
    scanf("%d", &cantjugadores);
    while (cantjugadores > 3 && cantjugadores <0)
    {
        printf("Ingrese 1 si desea jugar solo o 2 si desea jugar de a 2");
        scanf("%d", &cantjugadores);
    }
    
    cantjugadores--;

    if (cantjugadores)
    {
        for (int t = 0; t < 22; t++)
        {
            
        }
        
    }
    


    tirarDados(dados);
    bar
    mostrarTirada(dados);
    bar
    printf("Si desea repetir su tirada Presione 1, de lo contrario presione 0");
    bar
    scanf("%d", &repetir);
    bar
    while (repetir != 0 && acuTiradas<3 )
    {
        int cantATirar = 0;
        printf("ingrese la cantidad de dados a tirar");
        bar
        scanf("%d", &cantATirar);
        while (cantATirar > 6)
        {
            "La cantidad maxima de dados a tirar es 5, por favor elija de 1 a 5 dados";
            bar
            scanf("%d", &cantATirar);
        }
        bar
        repetirTirada(dados, cantATirar);
        bar
        mostrarTirada(dados);
        acuTiradas++;
        if (acuTiradas >= 3)
        {
            break;
        }
        
        printf("presione 1 si desea volver a realizar una ultima tirada");
        bar
        
    }
    
    
        
        
    
    
    
    
    



    scanf("%d", &a);




    return 0;
}

void tirarDados(int arr[DTot]){
    int a = 0;
    for (int i = 0; i < DTot ; i++)
    {
        a = (rand() % 6) +1;
        arr[i] = a;
    }
    ordenarMayorAmenor(arr);
}

void mostrarTirada(int arr[DTot]){
    for (int i = 0; i < DTot; i++)
    {
        printf("|%d|", arr[i]);
    }
}

void ordenarMayorAmenor(int arr[DTot]){
    int aux = 0;
    for (int i = 0; i < DTot; i++)
    {
        for ( int k = 0; k < DTot-1; k++)
        {
            if (arr[k+1]>arr[k])
            {
                aux = arr[k];
                arr[k] = arr[k+1];
                arr[k+1] = aux;
            }
            
        }
        
    }
}

void repetirTirada(int arrOriginal[DTot], int cantDados ){

    
    int arrSeleccionador[cantDados];
    
    for (int i = 0; i < cantDados; i++)
    {   int num;
        printf("seleccione la posicion del elemento %d de %d que ha elegido ", i+1, cantDados  );
        bar
        scanf("%d", &num);
        arrSeleccionador[i] = num-1;
    }

    for (int i = 0; i < cantDados; i++)
    {
        for (int j = 0; j < DTot; j++)
        {
            if (arrSeleccionador[i] == j)
            {
                int a = (rand() % 6) +1;
                arrOriginal[j] = a;
                
            }    
        }
        
        
        
    }
    
    


}


