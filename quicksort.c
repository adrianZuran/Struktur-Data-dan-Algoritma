#include <stdio.h>

int data[] = {57,17,14,84,21,18,48,32,22,23};
int n = sizeof(data) / sizeof(data[0]);

// Fungsi untuk menukar dua elemen
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Fungsi untuk mencetak array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void printArray2(int arr[], int size, int partition) {
    for (int i = 0; i < size; i++){
        if(i == partition){
            printf("-%d- ", arr[i]);
        }else{
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

void printSubArray(int arr[], int low, int high, int partition) {
    printf("Print Sub Array(%d, %d)\n", low, high);
    for (int i = low; i <= high; i++){
        if(i == partition){
            printf("-%d- ", arr[i]);
        }else{
            printf("%d ", arr[i]);
        }
        
    }
        
    printf("\n");
}

// Fungsi partisi: mengambil elemen terakhir sebagai pivot, 
// menempatkan pivot di posisi yang benar, dan memindahkan
// elemen lebih kecil ke kiri dan lebih besar ke kanan
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // pivot untuk nrp 21-30
    printf("Pivot = arr[%d]\n", high);
    printf("Pivot = %d\n", pivot);
    int i = (low - 1); // Indeks elemen lebih kecil

    for (int j = low; j <= high - 1; j++) {
        // Jika elemen saat ini lebih kecil dari pivot
        if (arr[j] < pivot) {
            i++; // tingkatkan indeks elemen lebih kecil
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// Fungsi utama QuickSort
void quickSort(int arr[], int low, int high) {
    printf("\n-----quickSort(arr, %d, %d)\n", low, high);
    if (low < high) {
        // pi adalah indeks partisi, arr[pi] sekarang di posisi yang benar
        int pi = partition(arr, low, high);
        printf("partition = %d\n", pi);
        printSubArray(arr, low, high, pi);
        printArray2(arr, n, pi );
        printf("Masuk Stack:\n");
        printf("quickSort (arr, %d, %d)\n", low, pi -1);
        printf("quickSort (arr, %d, %d)\n", pi + 1, high);

        // Urutkan elemen secara terpisah sebelum dan sesudah partisi
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    printf("Array awal: \n");
    printArray(data, n);
    
    quickSort(data, 0, n - 1);
    
    printf("Array terurut: \n");
    printArray(data, n);
    return 0;
}
