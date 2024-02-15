#include <stdio.h>
//#include <windows.h>
#include <time.h>

#define SIZE 10000

int datos(double datos[]) {
    FILE *file;

    // Abre el archivo en modo de escritura (w)
    file = fopen("archivo.dat", "w");

    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return 1;
    }

    // Escribe datos en el archivo

    for(int i = 0; i<10;i++){

        fprintf(file, "%d %f \n", 10 * (i+1), datos[i]);

    }

    // Cierra el archivo
    fclose(file);
}


void swap(double *xp, double *yp)
{
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(double arr[], int n)
{
    int i, j;
    double min;

    for (i = 0; i < n - 1; i++)
    {
        min = arr[i];
        int min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < min)
            {
                min = arr[j];
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}

int main()
{
    // LARGE_INTEGER frequency;
    // LARGE_INTEGER start;
    // LARGE_INTEGER end;
    double interval;
    double mediciones[10];
    clock_t begin, end;
    

    double sum = 0; // Cambio de tipo de variable a double

    for (int i = 1; i <= 10; i++)
    {
        time(&begin);

        for (int j = 0; j < 10; j++)
        {

            //CASO PROMEDIO
            double arr[SIZE * i]; // Cambio de tipo de arreglo a double
            int n = sizeof(arr) / sizeof(arr[0]);
            srand(time(0));
            for (int k = 0; k < SIZE * i; k++)
            {
                arr[k] = rand(); // Genera un n�mero aleatorio y lo guarda en el arreglo
            }
            selectionSort(arr, n);
        }

        time(&end);

        clock_t interval = end-begin; // Cambio de tipo de variable a double
        mediciones[i-1] = interval;
        //sum = sum + interval;
        printf("Tiempo de ejecucion para la corrida %d: %ld segundos, con tamano %d\n", i, interval,SIZE * i);
    }
    datos(mediciones);
    //printf("Tiempo promedio en segundos: %f\n", sum / 10); // Divisi�n por 10 para obtener el promedio
    return 0;
}

//CASO PROMEDIO
/*for(int i = 0; i < SIZE; i++)
{
    arr[i] = rand(); // Genera un n�mero aleatorio y lo guarda en el arreglo
}*/

//MEJOR DE LOS CASOS
/*for(int i = 0; i < SIZE; i++)
{
    arr[i] = i; // Genera un n�mero aleatorio y lo guarda en el arreglo
}*/

//PEOR DE LOS CASOS
/*for(int i = 0; i < SIZE; i++)
{
    arr[i] = SIZE-i; // Genera un n�mero aleatorio y lo guarda en el arreglo
}*/
