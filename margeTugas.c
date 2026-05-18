#include <stdio.h>
#include <stdlib.h>
int arr[] = {20, 39, 9, 49, 97, 82, 27, 59, 80, 29};
int arr_size = sizeof(arr) / sizeof(arr[0]);

// Fungsi untuk mencetak array
void printArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// Fungsi untuk mencetak array
void printSubArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

// Fungsi untuk menggabungkan dua subarray L[] dan R[] menjadi arr[]
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Membuat array sementara
    int L[n1], R[n2];

    // Menyalin data ke array sementara L[] dan R[]
    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // Menggabungkan array sementara kembali ke arr[l..r]
    i = 0; j = 0; k = l;
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

    // Menyalin elemen sisa L[], jika ada
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Menyalin elemen sisa R[], jika ada
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Fungsi utama Merge Sort
void mergeSort(int arr[], int l, int r) {
    printf("\n----mergeSort(arr, %d,%d)\n", l, r);
    if (l < r) {
        int m = l + (r - l) / 2;
        printf("m = %d\n", m);
        // Mengurutkan bagian pertama dan kedua
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
        printf("merge(arr, %d, %d, %d)\n",l,m,r);
        printArray(arr,arr_size);
    }
}



int main() {

    printf("Array asal: \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nArray terurut: \n");
    printArray(arr, arr_size);
    return 0;
}
