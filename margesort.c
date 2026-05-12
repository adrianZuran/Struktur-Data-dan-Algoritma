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

int totalData = 15;

// Fungsi untuk menampilkan data paket
void tampilkanData(Paket data[], int n) {
    printf("\n");
    printf("================================================================================\n");
    printf("%-4s %-20s %-10s %-35s %-12s %-15s\n", 
           "No", "Nama", "Resi", "Alamat", "Estimasi", "Status");
    printf("================================================================================\n");
    
    for (int i = 0; i < n; i++) {
        printf("%-4d %-20s %-10s %-35s %-12s %-15s\n",
               i + 1,
               data[i].nama,
               data[i].resi,
               data[i].alamat,
               data[i].estimasi,
               data[i].status);
    }
    printf("================================================================================\n");
    printf("Total Data: %d paket\n\n", n);
}

// Fungsi merge untuk Merge Sort
void merge(Paket arr[], int left, int mid, int right, int sortBy) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Paket *L = (Paket *)malloc(n1 * sizeof(Paket));
    Paket *R = (Paket *)malloc(n2 * sizeof(Paket));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        int compare;
        
        if (sortBy == SORT_NAMA) {
            compare = strcmp(L[i].nama, R[j].nama);
        } else {
            compare = strcmp(L[i].estimasi, R[j].estimasi);
        }
        
        if (compare <= 0) {
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
    
    free(L);
    free(R);
}

// Fungsi Merge Sort
void mergeSort(Paket arr[], int left, int right, int sortBy) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, sortBy);
        mergeSort(arr, mid + 1, right, sortBy);
        merge(arr, left, mid, right, sortBy);
    }
}

void copyData(Paket dest[], Paket src[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    Paket paket[MAX_DATA];
    int pilihan;
    
    printf("==========================================================\n");
    printf("       SISTEM PENGURUTAN DATA PAKET - MERGE SORT         \n");
    printf("==========================================================\n");
    
    do {
        printf("\n=== MENU PENGURUTAN ===\n");
        printf("1. Urutkan Berdasarkan Nama\n");
        printf("2. Urutkan Berdasarkan Estimasi Tiba\n");
        printf("3. Keluar Program\n");
        printf("Pilihan Anda: ");
        
        if (scanf("%d", &pilihan) != 1) {
            pilihan = -1;
            while (getchar() != '\n'); 
        }
        
        switch (pilihan) {
            case 1:
                printf("\n>>> Mengurutkan berdasarkan NAMA (A-Z) <<<\n");
                
                copyData(paket, dummy, totalData);
                
                printf("\n--- DATA SEBELUM DIURUTKAN ---");
                tampilkanData(paket, totalData);
                
                mergeSort(paket, 0, totalData - 1, SORT_NAMA);
                
                printf("\n--- DATA SETELAH DIURUTKAN (BERDASARKAN NAMA) ---");
                tampilkanData(paket, totalData);
                break;
                
            case 2:
                printf("\n>>> Mengurutkan berdasarkan ESTIMASI TIBA (Tanggal) <<<\n");
                
                // Copy data dummy ke array kerja
                copyData(paket, dummy, totalData);
                
                printf("\n--- DATA SEBELUM DIURUTKAN ---");
                tampilkanData(paket, totalData);
                
                // Lakukan Merge Sort berdasarkan estimasi
                mergeSort(paket, 0, totalData - 1, SORT_ESTIMASI);
                
                printf("\n--- DATA SETELAH DIURUTKAN (BERDASARKAN ESTIMASI) ---");
                tampilkanData(paket, totalData);
                break;
                
            case 3:
                printf("\n==========================================================\n");
                printf("       Terima kasih telah menggunakan program ini!       \n");
                printf("==========================================================\n");
                break;
                
            default:
                printf("\n[ERROR] Pilihan tidak valid! Silakan pilih 1-3.\n");
        }
        
    } while (pilihan != 3);
    
    return 0;
}