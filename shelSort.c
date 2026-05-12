#include <stdio.h>
#include <string.h>

#define MAX_NAMA 30
#define MAX_RESI 10
#define MAX_ALAMAT 50
#define MAX_ESTIMASI 20
#define MAX_STATUS 15
#define MAX_DATA 100

typedef struct {
    char nama[MAX_NAMA];
    char resi[MAX_RESI];
    char alamat[MAX_ALAMAT];
    int estimasi;
    char status[MAX_STATUS];
} Paket;

typedef Paket typeData;

// Function swap
void swap(typeData *a, typeData *b) {
    typeData temp = *a;
    *a = *b;
    *b = temp;
}

// Shell Sort
void shellSort_Swap(typeData arr[], int n, int menu) {

    for (int gap = n / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < n; i++) {

            for (int j = i - gap; j >= 0; j -= gap) {

                int kondisi = 0;

                // Sorting berdasarkan tanggal estimasi
                if(menu == 1){

                    kondisi =
                    arr[j + gap].estimasi >= arr[j].estimasi;

                }
                // Sorting berdasarkan nama
                else{

                    kondisi =
                    strcmpi(arr[j + gap].nama, arr[j].nama) >= 0;
                }

                if(kondisi == 1){

                    break;

                } else {

                    swap(&arr[j], &arr[j + gap]);
                }
            }
        }
    }
}

// Menu
int menu(){

    int pilih;

    printf("=========== MENU SORTING ===========\n");
    printf("1. Sorting Tanggal Estimasi\n");
    printf("2. Sorting Nama Penerima\n");
    printf("Pilih Menu : ");
    scanf("%d", &pilih);

    return pilih;
}

// Print Data Paket
void printArrayPaket(typeData arr[], int size) {

    printf("\n========================================================================================================\n");
    printf("%-3s | %-20s | %-7s | %-32s | %-12s | %-15s\n", 
           "NO", "Nama", "Resi", "Alamat", "Estimasi", "Status");
    printf("========================================================================================================\n");

    for (int i = 0; i < size; i++) {

        printf("%-3d | %-20s | %-7s | %-32s | %-12d | %-15s\n",
               i + 1,
               arr[i].nama,
               arr[i].resi,
               arr[i].alamat,
               arr[i].estimasi,
               arr[i].status);
    }

    printf("\n");
}

int main() {

    typeData data[] = {
        {"Budi Santoso", "RS001", "Jl. Merpati No.1, Surabaya", 2, "Dikirim"},
        {"Ani Rahayu", "RS002", "Jl. Kenari No.5, Bandung", 4, "Dalam Proses"},
        {"Zara Dewi", "RS003", "Jl. Flamboyan No.3, Jakarta", 1, "Terkirim"},
        {"Candra Putra", "RS004", "Jl. Melati No.7, Medan", 3, "Dikirim"},
        {"Mega Wulandari", "RS005", "Jl. Mawar No.2, Yogyakarta", 5, "Pending"},
        {"Hendra Kusuma", "RS006", "Jl. Anggrek No.9, Semarang", 6, "Dalam Proses"},
        {"Fitri Handayani", "RS007", "Jl. Dahlia No.4, Malang", 1, "Terkirim"},
        {"Rizky Pratama", "RS008", "Jl. Teratai No.6, Makassar", 4, "Dikirim"},
        {"Siti Aisyah", "RS009", "Jl. Cempaka No.11, Palembang", 5, "Pending"},
        {"Doni Firmansyah", "RS010", "Jl. Bougenville No.8, Depok", 3, "Dalam Proses"},
        {"Laras Setiawati", "RS011", "Jl. Kamboja No.13, Bekasi", 1, "Terkirim"},
        {"Agus Wijaya", "RS012", "Jl. Tulip No.3, Tangerang", 2, "Dikirim"},
        {"Nadia Permata", "RS013", "Jl. Seruni No.17, Solo", 7, "Pending"},
        {"Fahrul Hidayat", "RS014", "Jl. Edelweis No.5, Balikpapan", 6, "Dalam Proses"},
        {"Yuni Astuti", "RS015", "Jl. Sakura No.20, Denpasar", 2, "Terkirim"}
    };

    int n = sizeof(data) / sizeof(data[0]);

    printf("=========== DATA SEBELUM SORTING ===========\n");

    printArrayPaket(data, n);

    int pilih = menu();

    if(pilih == 1){

        shellSort_Swap(data, n, 1);

    } else {

        shellSort_Swap(data, n, 2);
    }

    printf("\n=========== DATA SETELAH SORTING ===========\n");

    printArrayPaket(data, n);

    return 0;
}