#include <stdio.h>
#include <string.h>

#define MAX_PAKET 100
#define MAX_TRACKING 100

// ==============================
// STRUCT TRACKING
// ==============================
struct Tracking {
    char tanggal[30];
    char waktu[20];
    char deskripsi[200];
    char lokasi[100];
    char kurir[100];
    char plat[20];
    char status[50];
    char rute[100];
};

// ==============================
// STRUCT PAKET
// ==============================
struct Paket {
    char resi[30];
    char pengirim[100];
    char penerima[100];
    char layanan[50];
    float berat;
    char tujuan[100];
    char statusSekarang[200];

    int jumlahTracking;

    struct Tracking tracking[MAX_TRACKING];
};

// ==============================
// FUNCTION TAMBAH PAKET
// ==============================
void tambahPaket(struct Paket paket[], int *jumlahPaket) {

    int i = *jumlahPaket;

    printf("\n==============================\n");
    printf("INPUT DATA PAKET\n");
    printf("==============================\n");

    getchar();

    printf("No Resi : ");
    fgets(paket[i].resi, sizeof(paket[i].resi), stdin);
    paket[i].resi[strcspn(paket[i].resi, "\n")] = 0;

    printf("Pengirim : ");
    fgets(paket[i].pengirim, sizeof(paket[i].pengirim), stdin);
    paket[i].pengirim[strcspn(paket[i].pengirim, "\n")] = 0;

    printf("Penerima : ");
    fgets(paket[i].penerima, sizeof(paket[i].penerima), stdin);
    paket[i].penerima[strcspn(paket[i].penerima, "\n")] = 0;

    printf("Layanan : ");
    fgets(paket[i].layanan, sizeof(paket[i].layanan), stdin);
    paket[i].layanan[strcspn(paket[i].layanan, "\n")] = 0;

    printf("Berat Paket : ");
    scanf("%f", &paket[i].berat);

    getchar();

    printf("Tujuan : ");
    fgets(paket[i].tujuan, sizeof(paket[i].tujuan), stdin);
    paket[i].tujuan[strcspn(paket[i].tujuan, "\n")] = 0;

    printf("Status Saat Ini : ");
    fgets(paket[i].statusSekarang,
          sizeof(paket[i].statusSekarang), stdin);
    paket[i].statusSekarang[
        strcspn(paket[i].statusSekarang, "\n")] = 0;

    // INPUT TRACKING
    printf("\nJumlah Tracking : ");
    scanf("%d", &paket[i].jumlahTracking);

    getchar();

    for(int j = 0; j < paket[i].jumlahTracking; j++) {

        printf("\nTRACKING KE-%d\n", j + 1);

        printf("Tanggal : ");
        fgets(paket[i].tracking[j].tanggal,
              sizeof(paket[i].tracking[j].tanggal),
              stdin);
        paket[i].tracking[j].tanggal[
            strcspn(paket[i].tracking[j].tanggal, "\n")] = 0;

        printf("Waktu : ");
        fgets(paket[i].tracking[j].waktu,
              sizeof(paket[i].tracking[j].waktu),
              stdin);
        paket[i].tracking[j].waktu[
            strcspn(paket[i].tracking[j].waktu, "\n")] = 0;

        printf("Deskripsi : ");
        fgets(paket[i].tracking[j].deskripsi,
              sizeof(paket[i].tracking[j].deskripsi),
              stdin);
        paket[i].tracking[j].deskripsi[
            strcspn(paket[i].tracking[j].deskripsi, "\n")] = 0;

        printf("Lokasi : ");
        fgets(paket[i].tracking[j].lokasi,
              sizeof(paket[i].tracking[j].lokasi),
              stdin);
        paket[i].tracking[j].lokasi[
            strcspn(paket[i].tracking[j].lokasi, "\n")] = 0;

        printf("Kurir : ");
        fgets(paket[i].tracking[j].kurir,
              sizeof(paket[i].tracking[j].kurir),
              stdin);
        paket[i].tracking[j].kurir[
            strcspn(paket[i].tracking[j].kurir, "\n")] = 0;

        printf("Plat Nomor : ");
        fgets(paket[i].tracking[j].plat,
              sizeof(paket[i].tracking[j].plat),
              stdin);
        paket[i].tracking[j].plat[
            strcspn(paket[i].tracking[j].plat, "\n")] = 0;

        printf("Status : ");
        fgets(paket[i].tracking[j].status,
              sizeof(paket[i].tracking[j].status),
              stdin);
        paket[i].tracking[j].status[
            strcspn(paket[i].tracking[j].status, "\n")] = 0;

        printf("Rute : ");
        fgets(paket[i].tracking[j].rute,
              sizeof(paket[i].tracking[j].rute),
              stdin);
        paket[i].tracking[j].rute[
            strcspn(paket[i].tracking[j].rute, "\n")] = 0;
    }

    (*jumlahPaket)++;

    printf("\nData paket berhasil ditambahkan!\n");
}

// ==============================
// FUNCTION TAMPILKAN PAKET
// ==============================
void tampilkanPaket(struct Paket paket[], int jumlahPaket) {

    for(int i = 0; i < jumlahPaket; i++) {

        printf("\n==============================\n");
        printf("TRACKING PAKET\n");
        printf("==============================\n");

        printf("\nNo. Resi : %s\n", paket[i].resi);
        printf("Pengirim : %s\n", paket[i].pengirim);
        printf("Penerima : %s\n", paket[i].penerima);
        printf("Layanan : %s\n", paket[i].layanan);
        printf("Berat Paket : %.2f Kg\n", paket[i].berat);
        printf("Tujuan : %s\n", paket[i].tujuan);

        printf("\nStatus Saat Ini :\n");
        printf("%s\n", paket[i].statusSekarang);

        printf("\n=========================================\n");
        printf("LIHAT SELENGKAPNYA\n");
        printf("=========================================\n");

        for(int j = 0; j < paket[i].jumlahTracking; j++) {

            printf("\n%s - %s\n",
                   paket[i].tracking[j].tanggal,
                   paket[i].tracking[j].waktu);

            printf("%s\n",
                   paket[i].tracking[j].deskripsi);

            if(strlen(paket[i].tracking[j].lokasi) > 0)
                printf("Lokasi : %s\n",
                       paket[i].tracking[j].lokasi);

            if(strlen(paket[i].tracking[j].kurir) > 0)
                printf("Kurir : %s\n",
                       paket[i].tracking[j].kurir);

            if(strlen(paket[i].tracking[j].plat) > 0)
                printf("Plat Nomor : %s\n",
                       paket[i].tracking[j].plat);

            if(strlen(paket[i].tracking[j].status) > 0)
                printf("Status : %s\n",
                       paket[i].tracking[j].status);

            if(strlen(paket[i].tracking[j].rute) > 0)
                printf("Rute : %s\n",
                       paket[i].tracking[j].rute);
        }

        printf("\n");
    }
}

// ==============================
// SORT BY NAMA PENERIMA
// ==============================
void sortNama(struct Paket paket[], int jumlahPaket) {

    struct Paket temp;

    for(int i = 0; i < jumlahPaket - 1; i++) {

        for(int j = i + 1; j < jumlahPaket; j++) {

            if(strcmp(paket[i].penerima,
                      paket[j].penerima) > 0) {

                temp = paket[i];
                paket[i] = paket[j];
                paket[j] = temp;
            }
        }
    }

    printf("\nData berhasil di sorting berdasarkan nama!\n");
}

// ==============================
// SORT BERDASARKAN ESTIMASI
// ==============================
void sortEstimasi(struct Paket paket[], int jumlahPaket) {

    struct Paket temp;

    for(int i = 0; i < jumlahPaket - 1; i++) {

        for(int j = i + 1; j < jumlahPaket; j++) {

            if(paket[i].berat > paket[j].berat) {

                temp = paket[i];
                paket[i] = paket[j];
                paket[j] = temp;
            }
        }
    }

    printf("\nData berhasil di sorting estimasi!\n");
}

// ==============================
// CARI PAKET
// ==============================
void cariPaket(struct Paket paket[], int jumlahPaket) {

    char cari[30];
    int ditemukan = 0;

    getchar();

    printf("\nMasukkan Nomor Resi : ");
    fgets(cari, sizeof(cari), stdin);

    cari[strcspn(cari, "\n")] = 0;

    for(int i = 0; i < jumlahPaket; i++) {

        if(strcmp(cari, paket[i].resi) == 0) {

            ditemukan = 1;

            printf("\nData ditemukan!\n");

            printf("\nNo Resi : %s\n", paket[i].resi);
            printf("Pengirim : %s\n", paket[i].pengirim);
            printf("Penerima : %s\n", paket[i].penerima);
            printf("Status : %s\n",
                   paket[i].statusSekarang);
        }
    }

    if(!ditemukan) {
        printf("\nData tidak ditemukan!\n");
    }
}

// ==============================
// MAIN
// ==============================
int main() {

    struct Paket paket[MAX_PAKET];

    int jumlahPaket = 0;
    int pilih;

    do {

        printf("\n==============================\n");
        printf(" SISTEM TRACKING PAKET\n");
        printf("==============================\n");

        printf("1. Input Data Paket\n");
        printf("2. Lihat Paket\n");
        printf("3. Sorting by Nama\n");
        printf("4. Sorting by Estimasi\n");
        printf("5. Cari Paket\n");
        printf("6. Keluar\n");

        printf("\nPilih Menu : ");
        scanf("%d", &pilih);

        switch(pilih) {

            case 1:
                tambahPaket(paket, &jumlahPaket);
                break;

            case 2:
                tampilkanPaket(paket, jumlahPaket);
                break;

            case 3:
                sortNama(paket, jumlahPaket);
                break;

            case 4:
                sortEstimasi(paket, jumlahPaket);
                break;

            case 5:
                cariPaket(paket, jumlahPaket);
                break;

            case 6:
                printf("\nProgram selesai.\n");
                break;

            default:
                printf("\nMenu tidak tersedia!\n");
        }

    } while(pilih != 6);

    return 0;
}