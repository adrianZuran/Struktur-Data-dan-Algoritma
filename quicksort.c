#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMA 30
#define MAX_RESI 10
#define MAX_ALAMAT 50
#define MAX_ESTIMASI 20
#define MAX_STATUS 15
#define MAX_DATA 100

#define SORT_NAMA 0
#define SORT_ESTIMASI 1

typedef struct
{
    char nama[MAX_NAMA];
    char resi[MAX_RESI];
    char alamat[MAX_ALAMAT];
    char estimasi[MAX_ESTIMASI];
    char status[MAX_STATUS];
} Paket;

Paket dummy[] = {
    {"Budi Santoso", "RS001", "Jl. Merpati No.1, Surabaya", "2024-12-20", "Dikirim"},
    {"Ani Rahayu", "RS002", "Jl. Kenari No.5, Bandung", "2024-12-18", "Dalam Proses"},
    {"Zara Dewi", "RS003", "Jl. Flamboyan No.3, Jakarta", "2024-12-22", "Terkirim"},
    {"Candra Putra", "RS004", "Jl. Melati No.7, Medan", "2024-12-19", "Dikirim"},
    {"Mega Wulandari", "RS005", "Jl. Mawar No.2, Yogyakarta", "2024-12-17", "Pending"},
    {"Hendra Kusuma", "RS006", "Jl. Anggrek No.9, Semarang", "2024-12-25", "Dalam Proses"},
    {"Fitri Handayani", "RS007", "Jl. Dahlia No.4, Malang", "2024-12-15", "Terkirim"},
    {"Rizky Pratama", "RS008", "Jl. Teratai No.6, Makassar", "2024-12-23", "Dikirim"},
    {"Siti Aisyah", "RS009", "Jl. Cempaka No.11, Palembang", "2024-12-16", "Pending"},
    {"Doni Firmansyah", "RS010", "Jl. Bougenville No.8, Depok", "2024-12-21", "Dalam Proses"},
    {"Laras Setiawati", "RS011", "Jl. Kamboja No.13, Bekasi", "2024-12-14", "Terkirim"},
    {"Agus Wijaya", "RS012", "Jl. Tulip No.3, Tangerang", "2024-12-26", "Dikirim"},
    {"Nadia Permata", "RS013", "Jl. Seruni No.17, Solo", "2024-12-13", "Pending"},
    {"Fahrul Hidayat", "RS014", "Jl. Edelweis No.5, Balikpapan", "2024-12-24", "Dalam Proses"},
    {"Yuni Astuti", "RS015", "Jl. Sakura No.20, Denpasar", "2024-12-12", "Terkirim"},
};
int n = sizeof(dummy) / sizeof(dummy[0]);

void cetakdata(Paket arr[], int n)
{
    printf("%-3s | %-20s | %-7s | %-32s | %-12s | %-15s\n", 
           "NO", "Nama", "Resi", "Alamat", "Estimasi", "Status");
    printf("--------------------------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("%-3d | %-20s | %-7s | %-32s | %-12s | %-15s\n",
               i + 1,
               arr[i].nama,
               arr[i].resi,
               arr[i].alamat,
               arr[i].estimasi,
               arr[i].status
            );
    }
}

void swap(Paket *a, Paket *b)
{
    Paket t = *a;
    *a = *b;
    *b = t;
}

int partition(Paket arr[], int low, int high, int key)
{
    Paket pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        int far;
        if (key == SORT_NAMA)
        {
            far = strcmp(arr[j].nama, pivot.nama);
        }
        else
        {
            far = strcmp(arr[j].estimasi, pivot.estimasi);
        }
        if (far <= 0)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Paket arr[], int low, int high, int key)
{
    printf("\nquickSort(arr, %d, %d)\n", low, high);
    if (low < high)
    {
        int pi = partition(arr, low, high, key);
        printf("partition = %d\n", pi);
        quickSort(arr, low, pi - 1, key);
        quickSort(arr, pi + 1, high, key);
    }
}

int main()
{
    cetakdata(dummy, n);

    quickSort(dummy, 0, n - 1, SORT_NAMA);
    cetakdata(dummy, n);

    quickSort(dummy, 0, n - 1, SORT_ESTIMASI);
    cetakdata(dummy, n);

    return 0;
};