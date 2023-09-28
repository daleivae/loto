#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAXIMO_NUMERO_BOLAS 6
#define NRO_MASREPETIDOCOL1_DESDE 1
#define NRO_MASREPETIDOCOL1_HASTA 41
#define NRO_PARES_DESDE 2
#define NRO_PARES_HASTA 4
#define NRO_MAX_COINCIDENCIAS_SORTEO_ANTERIOR 1
#define MAX_CANTIDAD_NUMEROS_UN_DIGITO 2
#define MIN_CANTIDAD_NUMEROS_UN_DIGITO 1
#define CANTIDAD_COINCIDENCIA_ULTIMO_DIGITO 1
#define SUMA_MINIMA 106 /*83*/
#define SUMA_MAXIMA 151 /*148*/
#define MAX_PAR_NUMERO_CONSECUTIVOS 1
#define RESTA_MINIMA 1
#define RESTA_MAXIMA 13
#define NRO_PRIMOS_DESDE 1
#define NRO_PRIMOS_HASTA 3
#define FALSE 0
#define TRUE 1
#define MAX_INTENTOS 1000
#define MAX_SORTEOS 100	/* Acá la cantidad de sorteos a jugar */
#define NUMERO_APUESTAS 1
#define SELECCION_TODOS_LOS_NUMEROS TRUE

int numerosMasRepiten[] = {1,2,4,5,6,7,8,9,10,11,12,15,16,17,18,20,21,22,23,25,26,29,31,32,33,34,37,38,39};
int tamNumMasRepiten=29;

int arregloSorteoAnterior[]={3,9,11,28,34,36};

void ObtenerBola(int numeroBola, int *arregloBolas, int *arregloSorteoAnterior,
                int *nroCoincidentesSa, int *cantidadUnDigito, int *nroPares, int *nroPrimos);
void OrdenarVector(int *vNumeros, int tamano);
void ImprimirVector(int *vNum);
int esPrimo(int numero);
void CalcularParesConsecutivosyRestas(int *arregloBolas, int *nroConsecutivo, int *restasFueraRango, int *suma6Numeros, int *nroUltDigitos,int *cantidadUnDigito);
int AnalizarResultado(int nroPares, int suma6Numeros, int nroPrimos, int cantidadParesConsecutivos, int restasFueraRango, int nroUltDigitos,int cantidadUnDigito);
int aleatorio_en_rango(int minimo, int maximo);
void InicializarMatriz(int (*matriz)[MAXIMO_NUMERO_BOLAS]);
void CargarMatriz(int (*matriz)[MAXIMO_NUMERO_BOLAS], int numeroSorteo, int *arregloBolas);
void SeleccionarApuesta(int (*apuestas)[MAXIMO_NUMERO_BOLAS]);

int main(int argc, char *argv[])
{
    int indice=0;
    int intentos=0;
    int numeroSorteo=0;
//int numeroBola=0;
    int nroPares=0;
    int nroPrimos=0;
    int cantidadUnDigito=0;
    int suma6Numeros=0;
    int nroCoincidentesSa=0;
    int nroUltDigitos=0;
    int cantidadParesConsecutivos=0;
    int restasFueraRango=0;
    int arregloBolas[]={0,0,0,0,0,0};
    int terminar=FALSE;
    int apuestas[MAX_SORTEOS][MAXIMO_NUMERO_BOLAS];
    int apuestasValidas=0;

    InicializarMatriz(apuestas);

    do
    {
        numeroSorteo++;

        do
        {
            intentos++;
            /*printf("INTENTO NRO. %i\n", intentos);*/
            nroPares=0;
            nroPrimos=0;
            nroCoincidentesSa=0;
            cantidadUnDigito=0;
            cantidadParesConsecutivos=0;
            restasFueraRango=0;
            suma6Numeros=0;
            nroUltDigitos=0;

            arregloBolas[0] = 0;
            arregloBolas[1] = 0;
            arregloBolas[2] = 0;
            arregloBolas[3] = 0;
            arregloBolas[4] = 0;
            arregloBolas[5] = 0;

            for (indice=1; indice <= MAXIMO_NUMERO_BOLAS; indice++)
                ObtenerBola(indice, arregloBolas, arregloSorteoAnterior, &nroCoincidentesSa, &cantidadUnDigito,
                &nroPares, &nroPrimos);

            CalcularParesConsecutivosyRestas(arregloBolas,&cantidadParesConsecutivos,&restasFueraRango,&suma6Numeros,&nroUltDigitos,&cantidadUnDigito);

            /*ImprimirVector(arregloBolas);*/

            /* An�lisis del vector*/
            terminar=AnalizarResultado(nroPares,suma6Numeros,nroPrimos,cantidadParesConsecutivos,restasFueraRango,nroUltDigitos,cantidadUnDigito);

        } while (terminar == FALSE && intentos < MAX_INTENTOS);

        if (terminar)
        {
            CargarMatriz(apuestas, numeroSorteo, arregloBolas);
            apuestasValidas++;
        }

    } while (numeroSorteo < MAX_SORTEOS);

    if (apuestasValidas > 0)
        SeleccionarApuesta(apuestas);
    else
        printf("Sin resultado\n");
}

void SeleccionarApuesta(int (*apuestas)[MAXIMO_NUMERO_BOLAS])
{
    int i=0, j=0, nSorteo=0;
    int sorteoSeleccionado[MAX_SORTEOS]={0};
    int coincide=FALSE;

    for (i=0; i < NUMERO_APUESTAS; i++)
    {
        do
        {
            coincide = FALSE;
            nSorteo = aleatorio_en_rango(0, MAX_SORTEOS-1);
            for (j=0; j < i; j++)
                if (nSorteo == sorteoSeleccionado[j]) coincide=TRUE;

        } while (coincide == TRUE);

        sorteoSeleccionado[i] = nSorteo;

        /*ImprimirVector(apuestas[nSorteo]);*/
    }
}

void CargarMatriz(int (*matriz)[MAXIMO_NUMERO_BOLAS], int numero, int *arregloBolas)
{
    int i=0,j=0;

    i=numero-1;

    for (j=0; j < MAXIMO_NUMERO_BOLAS; j++)
        matriz[i][j]=arregloBolas[j];

    printf("Sorteo Nro.%i: ", numero);
    ImprimirVector(arregloBolas);
}

void InicializarMatriz(int (*matriz)[MAXIMO_NUMERO_BOLAS])
{
    int i=0, j=0;

    for (i=0; i < MAX_SORTEOS; i++)
        for (j=0; j < MAXIMO_NUMERO_BOLAS; j++)
            matriz[i][j] = 0;

}

int aleatorio_en_rango(int minimo, int maximo)
{
  return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

int AnalizarResultado(int nroPares, int suma6Numeros, int nroPrimos, int cantidadParesConsecutivos, int restasFueraRango, int nroUltDigitos, int cantidadUnDigito)
{
    int resultado=TRUE;

    /*printf("* Estad�stica NroPares:%i NroPrimos:%i Suma:%i CantParConsec.:%i\n",nroPares, nroPrimos,
    suma6Numeros,cantidadParesConsecutivos);*/

    if (nroPares < NRO_PARES_DESDE || nroPares > NRO_PARES_HASTA)
    {
        /*printf("* Resultado falla en Dato 2: N�meros pares [%i]\n", nroPares);*/
        resultado=FALSE;
    }

    if (cantidadParesConsecutivos > MAX_PAR_NUMERO_CONSECUTIVOS)
    {
        /*printf("* Resultado falla en Dato 6: Par de n�meros consecutivos [%i]\n", cantidadParesConsecutivos);*/
        resultado=FALSE;
    }

    if (suma6Numeros < SUMA_MINIMA || suma6Numeros > SUMA_MAXIMA) resultado=FALSE;

    if (restasFueraRango > 0)
    {
        /*printf("* Resultado falla en Dato 8: Resta fuera de rango entre dos n�meros consecutivos [%i]\n", restasFueraRango);*/
        resultado=FALSE;
    }

    if (nroPrimos < NRO_PRIMOS_DESDE || nroPrimos > NRO_PRIMOS_HASTA)
    {
        /*printf("* Resultado falla en Dato 9: N�meros primos [%i]\n", nroPrimos);*/
        resultado=FALSE;
    }

    if (nroUltDigitos != CANTIDAD_COINCIDENCIA_ULTIMO_DIGITO)
    {
        /*printf("* Resultado falla en Dato 3: Dos n�meros misma terminaci�n [%i]\n", nroUltDigitos);*/
        resultado=FALSE;
    }

    if (cantidadUnDigito < MIN_CANTIDAD_NUMEROS_UN_DIGITO || cantidadUnDigito > MAX_CANTIDAD_NUMEROS_UN_DIGITO)
    {
        /*printf("* Resultado falla en Dato 5: Cantidad de n�meros con 1 d�gito [%i]\n", cantidadUnDigito);*/
        resultado=FALSE;
    }

    return resultado;
}

void ObtenerBola(int numeroBola, int *arregloBolas, int *arregloSorteoAnterior,
                int *nroCoincidentesSa, int *cantidadUnDigito, int *nroPares, int *nroPrimos)
{
    int bola=0;
    int i=0;
    int repetir=FALSE;
    int coincidenciaSa=0;
    int unDigito=0;
//    int resta=0;

    do
    {
        coincidenciaSa=0;
        unDigito=0;

        do
        {
            repetir=FALSE;

            /* Se verifica el Dato 1: N�meros que m�s se repiten */
            if (SELECCION_TODOS_LOS_NUMEROS == TRUE)
                bola = rand () % (NRO_MASREPETIDOCOL1_HASTA-NRO_MASREPETIDOCOL1_DESDE+1) + NRO_MASREPETIDOCOL1_DESDE;
            else
                bola = numerosMasRepiten[aleatorio_en_rango(0, (tamNumMasRepiten - 1))];
            /*printf("Seleccionando Bola:%i N�mero:%i\n", numeroBola, bola);*/

            for (i=0; i < numeroBola - 1; i++)
            {
                /* Se verifica que no haya n�meros repetidos */
                if (bola == arregloBolas[i])
                {
                    /*printf("Anomalia - N�mero repetido [%i]\n", bola);*/
                    repetir=TRUE;
                    break;
                }
            }
        } while (repetir==TRUE);

        /* Se verifica el Dato 4: N�meros repetidos del sorteo anterior */
        for (i=0; i < MAXIMO_NUMERO_BOLAS; i++)
        {
            if (bola == arregloSorteoAnterior[i])
            {
                coincidenciaSa++;
                break;
            }
        }

        /* Se verifica el Dato 5: Cantidad de n�meros con 1 d�gito */
        if (bola < 10) unDigito++;

        if (((*nroCoincidentesSa + coincidenciaSa) > NRO_MAX_COINCIDENCIAS_SORTEO_ANTERIOR)
            || ((*cantidadUnDigito + unDigito) > MAX_CANTIDAD_NUMEROS_UN_DIGITO)) repetir = TRUE;

    } while (repetir);

    arregloBolas[numeroBola-1]=bola;
    OrdenarVector(arregloBolas,numeroBola);

    *nroCoincidentesSa+=coincidenciaSa;
    *cantidadUnDigito+=unDigito;

    if (bola % 2==0) (*nroPares)++;
    if (esPrimo(bola)==TRUE) (*nroPrimos)++;
}

void OrdenarVector(int *vNumeros, int tamano)
{
    int temp=0;
    int i=0, j=0;

    for (i = 0; i < (tamano - 1); i++)
    {
        for (j = i + 1; j < tamano; j++)
        {
            if (vNumeros[j] < vNumeros[i])
            {
                temp = vNumeros[j];
                vNumeros[j] = vNumeros[i];
                vNumeros[i] = temp;
            }
        }
    }
}

void ImprimirVector(int *vNum)
{
    printf("Apuesta [%i] [%i] [%i] [%i] [%i] [%i]\n",vNum[0],vNum[1],vNum[2],vNum[3],vNum[4],vNum[5]);
}

int esPrimo(int numero)
{
    //int x=0;

    if (numero == 0 || numero == 1) return FALSE;
    /*
          El n�mero 4 es un caso especial, pues al dividirlo entre
          2 el resultado es 2, y el ciclo nunca se cumple, indicando que
          el 4 S� es primo, pero realmente NO lo es, as� que si el n�mero es 4
                        inmediatamente indicamos que no es primo (regresando 0)
          Nota: solo es para el 4, los dem�s funcionan bien
    */
    if (numero == 4) return FALSE;
    for (int x = 2; x < numero / 2; x++)
    {
        /* Si es divisible por cualquiera de estos n�meros, no
        // es primo*/
        if (numero % x == 0) return FALSE;
    }
    /* Si no se pudo dividir por ninguno de los de arriba, s� es primo*/
    return TRUE;
}

void CalcularParesConsecutivosyRestas(int *arregloBolas, int *nroConsecutivo, int *restasFueraRango, int *suma6Numeros,
                                    int *nroUltDigitos,int *cantidadUnDigito)
{
    int i=0,j=0;
    int resta=0;
    int ultimosDigitos[]={0,0,0,0,0,0};

    *cantidadUnDigito=0;

    for (i=MAXIMO_NUMERO_BOLAS-1; i > 0; i--)
    {
        /* Se verifica el Dato 6: Par de n�meros consecutivos */
        if (arregloBolas[i] == arregloBolas[i-1]+1) (*nroConsecutivo)++;

        /* Se verifica el Dato 8: Resta entre dos n�meros consecutivos */
        resta = arregloBolas[i] - arregloBolas[i-1];

        if (resta > RESTA_MAXIMA) (*restasFueraRango)++;

        *suma6Numeros+=arregloBolas[i];
    }

    /* Se verifica el Dato 3: Dos n�meros con igual terminaci�n */
    for (i=0; i < MAXIMO_NUMERO_BOLAS; i++)
    {
         if (arregloBolas[i] < 10) (*cantidadUnDigito)++;

        ultimosDigitos[i] = arregloBolas[i] % 10;

        for (j=i+1; j < MAXIMO_NUMERO_BOLAS; j++)
            if (ultimosDigitos[i] == (arregloBolas[j] % 10)) (*nroUltDigitos)++;
    }
}


