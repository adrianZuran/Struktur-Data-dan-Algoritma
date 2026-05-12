#include <stdio.h>
#include <string.h>

typedef struct {
    int hari, bulan, tahun;
} Tanggal;

typedef struct {
    char nama[50];
    char resi[20];
    char alamat[100];
    char status[30];
    Tanggal estimasi;
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
                    arr[j + gap].estimasi.hari >= arr[j].estimasi.hari;

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

    printf("\n============================================================================================\n");
    printf("NAMA\t\tRESI\tALAMAT\t\t\t\tESTIMASI\tSTATUS\n");
    printf("============================================================================================\n");

    for (int i = 0; i < size; i++) {

        printf("%-15s %-8s %-30s %02d-%02d-%d\t%-15s\n",

        arr[i].nama,
        arr[i].resi,
        arr[i].alamat,
        arr[i].estimasi.hari,
        arr[i].estimasi.bulan,
        arr[i].estimasi.tahun,
        arr[i].status);
    }

    printf("\n");
}

int main() {

    typeData data[] = {

        {"Budi Santoso", "RS001",
        "Surabaya", "Dikirim",
        20, 12, 2024},

        {"Ani Rahayu", "RS002",
        "Bandung", "Dalam Proses",
        18, 12, 2024},

        {"Zara Dewi", "RS003",
        "Jakarta", "Terkirim",
        22, 12, 2024},

        {"Candra Putra", "RS004",
        "Medan", "Dikirim",
        19, 12, 2024},

        {"Mega Wulandari", "RS005",
        "Yogyakarta", "Pending",
        17, 12, 2024},

        {"Hendra Kusuma", "RS006",
        "Semarang", "Dalam Proses",
        25, 12, 2024},

        {"Fitri Handayani", "RS007",
        "Malang", "Terkirim",
        15, 12, 2024},

        {"Rizky Pratama", "RS008",
        "Makassar", "Dikirim",
        23, 12, 2024},

        {"Siti Aisyah", "RS009",
        "Palembang", "Pending",
        16, 12, 2024},

        {"Doni Firmansyah", "RS010",
        "Depok", "Dalam Proses",
        21, 12, 2024}
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