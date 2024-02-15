#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 10000
typedef enum {SELECTION_SORT, INSERTION_SORT, MERGE_SORT} SortAlgorithm;
void swap(double *xp, double *yp) {
    double temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(double arr[], int n) {
    int i, j;
    double min;

    for (i = 0; i < n-1; i++) {
        min = arr[i];
        int min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}
void insertionSort(double arr[], int n) {
    int i, j;
    double key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
void merge(double arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    double L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(double arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void datos(double datos[], const char* filename) {
    FILE *file;
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }
    for(int i = 0; i < 10; i++) {
        fprintf(file, "%d %f\n", 10 * (i+1), datos[i]);
    }
    fclose(file);
}

void generarMejorCaso(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void generarPeorCaso(double arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void generarCasoPromedio(double arr[], int n) {
    srand((unsigned)time(NULL)); // Para evitar la misma secuencia en cada ejecución
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n; // Genera un número aleatorio entre 0 y n-1
    }
}

void medirTiempo(double mediciones[], void (*generarCaso)(double[], int), const char* filename, SortAlgorithm algorithm) {
    struct timespec start, end;
    double interval;
    
    for (int i = 1; i <= 10; i++) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int j = 0; j < 10; j++) {
            double arr[SIZE * i];
            int n = sizeof(arr) / sizeof(arr[0]);
            generarCaso(arr, n);
            switch (algorithm) {
            case SELECTION_SORT:
                selectionSort(arr, n);
                break;
            case INSERTION_SORT:
                insertionSort(arr, n);
                break;
            case MERGE_SORT:
                mergeSort(arr, 0, n - 1);
                break;
        }
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        interval = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        mediciones[i-1] = interval;
        printf("Tiempo de ejecución para la corrida %d: %f segundos, con tamaño %d\n", i, interval, SIZE * i);
    }
    datos(mediciones, filename);
}

int main() {
    double medicionesMejor[10], medicionesPeor[10], medicionesPromedio[10];
    
    //Selection
    printf("Selection sort\n");
    printf("Mejor caso:\n");
    medirTiempo(medicionesMejor, generarMejorCaso, "mejor_caso_selec.dat", SELECTION_SORT);
    
    printf("\nPeor caso:\n");
    medirTiempo(medicionesPeor, generarPeorCaso, "peor_caso_selec.dat", SELECTION_SORT);
    
    printf("\nCaso promedio:\n");
    medirTiempo(medicionesPromedio, generarCasoPromedio, "caso_promedio_selec.dat", SELECTION_SORT);

    //Insertion
    printf("Insertion sort\n");
    printf("Mejor caso:\n");
    medirTiempo(medicionesMejor, generarMejorCaso, "mejor_caso_inser.dat", INSERTION_SORT);
    
    printf("\nPeor caso:\n");
    medirTiempo(medicionesPeor, generarPeorCaso, "peor_caso_inser.dat", INSERTION_SORT);
    
    printf("\nCaso promedio:\n");
    medirTiempo(medicionesPromedio, generarCasoPromedio, "caso_promedio_inser.dat", INSERTION_SORT);

    //Merge
    printf("Merge sort\n");
    printf("Mejor caso:\n");
    medirTiempo(medicionesMejor, generarMejorCaso, "mejor_caso_merge.dat", MERGE_SORT);
    
    printf("\nPeor caso:\n");
    medirTiempo(medicionesPeor, generarPeorCaso, "peor_caso_merge.dat", MERGE_SORT);
    
    printf("\nCaso promedio:\n");
    medirTiempo(medicionesPromedio, generarCasoPromedio, "caso_promedio_merge.dat", MERGE_SORT);
    
    return 0;
}
