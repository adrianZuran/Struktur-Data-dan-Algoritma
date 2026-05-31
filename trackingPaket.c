#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PAKET 100
#define MAX_TRACKING 100

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

struct Paket {
    char resi[30];
    char pengirim[100];
    char penerima[100];
    char layanan[50];
    float berat;
    char kotaAsal[100];
    char tujuan[100];
    char statusSekarang[200];
    char estimasi[50];
    int jumlahTracking;
    struct Tracking tracking[MAX_TRACKING];
};

struct TreeNode {
    struct Paket *paketPtr; // Menyimpan alamat memori paket
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode* root = NULL; // Root dari BST

// Fungsi Insert ke BST
struct TreeNode* insertBST(struct TreeNode *node, struct Paket *pkt) {
    if (node == NULL) {
        struct TreeNode *newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        newNode->paketPtr = pkt;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }
    // Menggunakan Nomor Resi sebagai Key
    if (strcmp(pkt->resi, node->paketPtr->resi) < 0)
        node->left = insertBST(node->left, pkt);
    else if (strcmp(pkt->resi, node->paketPtr->resi) > 0)
        node->right = insertBST(node->right, pkt);
    
    return node;
}

// Fungsi Cari di BST
struct Paket* searchBST(struct TreeNode *node, char *resi) {
    if (node == NULL) return NULL;
    if (strcmp(resi, node->paketPtr->resi) == 0) return node->paketPtr;
    
    if (strcmp(resi, node->paketPtr->resi) < 0)
        return searchBST(node->left, resi);
    else
        return searchBST(node->right, resi);
}

// ==========================================
// 3. GRAPH DATA STRUCTURE (ADJACENCY MATRIX)
// ==========================================

const char kotaJatim[][50] = {
    "Surabaya", "Malang", "Sidoarjo", "Gresik", "Mojokerto", 
    "Pasuruan", "Probolinggo", "Kediri", "Madiun", "Jember", "Banyuwangi"
};
const int JUMLAH_KOTA = 11;

// Matriks Ketetanggaan (Edge: 1 = Terhubung, 0 = Tidak)
// Peta relasi kota-kota di Jawa Timur
int graph[11][11] = {
    // Sby, Mal, Sda, Gre, Moj, Pas, Pro, Ked, Mad, Jem, Bwi
    {0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0}, // 0. Surabaya
    {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0}, // 1. Malang
    {1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // 2. Sidoarjo
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 3. Gresik
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 4. Mojokerto
    {0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0}, // 5. Pasuruan
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}, // 6. Probolinggo
    {0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0}, // 7. Kediri
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // 8. Madiun
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1}, // 9. Jember
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}  // 10. Banyuwangi
};

// Algoritma BFS (Breadth-First Search) untuk mencari rute terpendek
int findShortestPathBFS(int start, int target, int path[]) {
    int queue[100], front = 0, rear = 0;
    int visited[11] = {0};
    int parent[11];
    
    for(int i = 0; i < 11; i++) parent[i] = -1;
    
    queue[rear++] = start;
    visited[start] = 1;
    
    int found = 0;
    while(front < rear) {
        int curr = queue[front++];
        if (curr == target) {
            found = 1;
            break;
        }
        for(int i = 0; i < 11; i++) {
            if(graph[curr][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = curr;
                queue[rear++] = i;
            }
        }
    }
    
    if(!found) return 0;
    
    int tempPath[11], count = 0;
    int curr = target;
    while(curr != -1) {
        tempPath[count++] = curr;
        curr = parent[curr];
    }
    
    // Balik array agar urutannya dari start -> target
    for(int i = 0; i < count; i++) {
        path[i] = tempPath[count - 1 - i];
    }
    return count; // mengembalikan jumlah node yang dilewati
}


// ==========================================
// UTILITIES
// ==========================================

void bersihkanBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void hilangkanEnter(char *str) {
    str[strcspn(str, "\n")] = 0;
}

// ==========================================
// CORE FUNCTIONS
// ==========================================

void tambahPaket(struct Paket *paket[], int *jumlahPaket) {

    int i = *jumlahPaket;

    printf("\n==============================\n");
    printf("INPUT DATA PAKET (OTOMATIS)\n");
    printf("==============================\n");

    printf("No Resi : ");
    fgets(paket[i]->resi, sizeof(paket[i]->resi), stdin);
    hilangkanEnter(paket[i]->resi);

    printf("Penerima : ");
    fgets(paket[i]->penerima, sizeof(paket[i]->penerima), stdin);
    hilangkanEnter(paket[i]->penerima);

    printf("Layanan : ");
    fgets(paket[i]->layanan, sizeof(paket[i]->layanan), stdin);
    hilangkanEnter(paket[i]->layanan);

    printf("Berat Paket : ");
    while (scanf("%f", &paket[i]->berat) != 1) {
        printf("Input tidak valid! Masukkan angka untuk berat: ");
        bersihkanBuffer();
    }
    bersihkanBuffer();

    printf("\nDaftar Kota Jawa Timur:\n");
    for(int k = 0; k < JUMLAH_KOTA; k++) {
        printf("%d. %s\n", k + 1, kotaJatim[k]);
    }

    int asalIdx, tujuanIdx;
    printf("\nPilih Kota Asal (1-%d): ", JUMLAH_KOTA);
    while (scanf("%d", &asalIdx) != 1 || asalIdx < 1 || asalIdx > JUMLAH_KOTA) {
        printf("Pilih angka 1-%d: ", JUMLAH_KOTA);
        bersihkanBuffer();
    }
    bersihkanBuffer();
    strcpy(paket[i]->kotaAsal, kotaJatim[asalIdx - 1]);

    printf("Pilih Kota Tujuan (1-%d): ", JUMLAH_KOTA);
    while (scanf("%d", &tujuanIdx) != 1 || tujuanIdx < 1 || tujuanIdx > JUMLAH_KOTA) {
        printf("Pilih angka 1-%d: ", JUMLAH_KOTA);
        bersihkanBuffer();
    }
    bersihkanBuffer();
    strcpy(paket[i]->tujuan, kotaJatim[tujuanIdx - 1]);

    // Mencari rute dengan Graph BFS
    int path[11];
    int pathCount = findShortestPathBFS(asalIdx - 1, tujuanIdx - 1, path);

    int estimasiHari;
    if (asalIdx == tujuanIdx) {
        estimasiHari = 1;
    } else if (pathCount > 0) {
        estimasiHari = pathCount;
    } else {
        estimasiHari = 3;
    }
    sprintf(paket[i]->estimasi, "%d Hari", estimasiHari);

    // Generate Tanggal Dinamis berdasarkan input estimasiHari
    char tgl[7][30];
    for (int k = 0; k < 7; k++) {
        int daysToAdd = 0;
        if (k <= 3) {
            daysToAdd = 0; 
        } else if (k == 4) {
            daysToAdd = (estimasiHari > 1) ? (estimasiHari / 2) : 0; 
        } else {
            daysToAdd = (estimasiHari > 1) ? (estimasiHari - 1) : 0; 
        }
        
        time_t t_curr = time(NULL);
        t_curr += (daysToAdd * 24 * 3600);
        struct tm *tm_curr = localtime(&t_curr);
        strftime(tgl[k], sizeof(tgl[k]), "%d %b", tm_curr);
    }

    int trk = 0;
    strcpy(paket[i]->statusSekarang, "Terkirim");

    #define INIT_TRACKING(idx) \
        strcpy(paket[i]->tracking[idx].tanggal, ""); \
        strcpy(paket[i]->tracking[idx].waktu, ""); \
        strcpy(paket[i]->tracking[idx].deskripsi, ""); \
        strcpy(paket[i]->tracking[idx].lokasi, ""); \
        strcpy(paket[i]->tracking[idx].kurir, ""); \
        strcpy(paket[i]->tracking[idx].plat, ""); \
        strcpy(paket[i]->tracking[idx].status, ""); \
        strcpy(paket[i]->tracking[idx].rute, "");

    // 0. Dibuat
    INIT_TRACKING(trk);
    strcpy(paket[i]->tracking[trk].tanggal, tgl[0]);
    strcpy(paket[i]->tracking[trk].deskripsi, "Pesanan Dibuat. Pengirim telah mengatur pengiriman.");
    trk++;

    // 1. Pickup
    INIT_TRACKING(trk);
    strcpy(paket[i]->tracking[trk].tanggal, tgl[1]);
    strcpy(paket[i]->tracking[trk].deskripsi, "Kurir ditugaskan untuk menjemput pesanan.");
    strcpy(paket[i]->tracking[trk].kurir, "Pak Budi (Pickup)");
    strcpy(paket[i]->tracking[trk].plat, "W 1122 AA");
    trk++;

    // 2. Diserahkan ke jasa kirim
    INIT_TRACKING(trk);
    strcpy(paket[i]->tracking[trk].tanggal, tgl[2]);
    strcpy(paket[i]->tracking[trk].deskripsi, "Pesanan telah diserahkan ke jasa kirim untuk diproses.");
    strcpy(paket[i]->tracking[trk].lokasi, paket[i]->kotaAsal);
    trk++;

    // 3. MH Asal
    INIT_TRACKING(trk);
    strcpy(paket[i]->tracking[trk].tanggal, tgl[3]);
    sprintf(paket[i]->tracking[trk].deskripsi, "Paket telah tiba di fasilitas MH %s", paket[i]->kotaAsal);
    strcpy(paket[i]->tracking[trk].lokasi, paket[i]->kotaAsal);
    trk++;

    // 4. Perjalanan via Graph Path
    for(int p = 0; p < pathCount - 1; p++) {
        INIT_TRACKING(trk);
        strcpy(paket[i]->tracking[trk].tanggal, tgl[4]);
        strcpy(paket[i]->tracking[trk].deskripsi, "Paket sedang dalam perjalanan / transit.");
        sprintf(paket[i]->tracking[trk].rute, "%s -> %s", kotaJatim[path[p]], kotaJatim[path[p+1]]);
        trk++;
    }

    // 5. DC Tujuan
    INIT_TRACKING(trk);
    strcpy(paket[i]->tracking[trk].tanggal, tgl[5]);
    sprintf(paket[i]->tracking[trk].deskripsi, "Paket telah tiba di fasilitas DC %s", paket[i]->tujuan);
    strcpy(paket[i]->tracking[trk].lokasi, paket[i]->tujuan);
    trk++;

    // 6. Terkirim
    INIT_TRACKING(trk);
    strcpy(paket[i]->tracking[trk].tanggal, tgl[6]);
    sprintf(paket[i]->tracking[trk].deskripsi, "Pesanan tiba di alamat tujuan. Paket diterima oleh %s.", paket[i]->penerima);
    strcpy(paket[i]->tracking[trk].kurir, "Andi (Delivery)");
    strcpy(paket[i]->tracking[trk].plat, "W 6835 FU");
    trk++;

    paket[i]->jumlahTracking = trk;

    // INSERT KE BST UNTUK PENCARIAN CEPAT
    root = insertBST(root, paket[i]);

    (*jumlahPaket)++;
    printf("\nData paket berhasil ditambahkan ke Array dan BST!\n");
}

void tampilkanPaket(struct Paket *paket[], int jumlahPaket) {

    printf("\n=======================================================================================================================\n");
    printf("| %-10s | %-20s | %-20s | %-12s | %-9s | %-15s | %-15s |\n", 
           "No. Resi", "Pengirim (Asal)", "Penerima (Tujuan)", "Layanan", "Berat", "Estimasi Tiba", "Status Saat Ini");
    printf("=======================================================================================================================\n");

    for(int i = 0; i < jumlahPaket; i++) {
        char pengirimFull[150];
        char penerimaFull[150];
        sprintf(pengirimFull, "%s (%s)", paket[i]->pengirim, paket[i]->kotaAsal);
        sprintf(penerimaFull, "%s (%s)", paket[i]->penerima, paket[i]->tujuan);

        printf("| %-10.10s | %-20.20s | %-20.20s | %-12.12s | %6.2f Kg | %-15.15s | %-15.15s |\n", 
               paket[i]->resi, 
               pengirimFull, 
               penerimaFull, 
               paket[i]->layanan, 
               paket[i]->berat, 
               paket[i]->estimasi, 
               paket[i]->statusSekarang);
    }
    printf("=======================================================================================================================\n");
}

void sortNama(struct Paket *paket[], int jumlahPaket) {

    struct Paket *temp;

    for (int gap = jumlahPaket / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jumlahPaket; i++) {
            temp = paket[i];
            int j;
            for (j = i; j >= gap && strcmp(paket[j - gap]->penerima, temp->penerima) > 0; j -= gap) {
                paket[j] = paket[j - gap];
            }
            paket[j] = temp;
        }
    }
    printf("\nData berhasil di sorting berdasarkan nama!\n");
    // Pointer di-swap, BST tetap aman karena BST menunjuk ke alamat memori yang konstan.
}

void sortEstimasi(struct Paket *paket[], int jumlahPaket) {

    struct Paket *temp;

    for (int gap = jumlahPaket / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < jumlahPaket; i++) {
            temp = paket[i];
            int j;
            for (j = i; j >= gap && paket[j - gap]->berat > temp->berat; j -= gap) {
                paket[j] = paket[j - gap];
            }
            paket[j] = temp;
        }
    }
    printf("\nData berhasil di sorting estimasi!\n");
}

void cariPaket() {

    char cari[30];

    printf("\nMasukkan Nomor Resi : ");
    fgets(cari, sizeof(cari), stdin);
    hilangkanEnter(cari);

    // MENGGUNAKAN BST UNTUK PENCARIAN
    struct Paket *hasil = searchBST(root, cari);

    if(hasil != NULL) {
        printf("\nData ditemukan dari struktur Binary Search Tree (BST)!\n");
        
        // Tampilkan Detail Lengkap
        printf("\nNo. Resi : %s\n", hasil->resi);
        printf("Pengirim : %s (%s)\n", hasil->pengirim, hasil->kotaAsal);
        printf("Penerima : %s (%s)\n", hasil->penerima, hasil->tujuan);
        printf("Layanan : %s\n", hasil->layanan);
        printf("Berat Paket : %.2f Kg\n", hasil->berat);
        printf("Estimasi Tiba : %s\n", hasil->estimasi);

        printf("\nStatus Saat Ini :\n");
        printf("%s\n", hasil->statusSekarang);

        printf("\n=========================================\n");
        printf("LIHAT SELENGKAPNYA\n");
        printf("=========================================\n");

        for(int j = hasil->jumlahTracking - 1; j >= 0; j--) {

            // Tanggal dan Deskripsi Utama
            printf("%-12s | %s\n", hasil->tracking[j].tanggal, hasil->tracking[j].deskripsi);
            
            if(strlen(hasil->tracking[j].lokasi) > 0) {
                printf("             | Lokasi: %s\n", hasil->tracking[j].lokasi);
            }
            if(strlen(hasil->tracking[j].kurir) > 0) {
                printf("             | Kurir: %s\n", hasil->tracking[j].kurir);
            }
            if(strlen(hasil->tracking[j].plat) > 0) {
                printf("             | Plat Nomor: %s\n", hasil->tracking[j].plat);
            }
            if(strlen(hasil->tracking[j].rute) > 0) {
                printf("             | Rute: %s\n", hasil->tracking[j].rute);
            }
            
            // Garis penghubung ke titik selanjutnya
            if(j > 0) {
                printf("             |\n");
            }
        }
        printf("\n");
    } else {
        printf("\nData tidak ditemukan di dalam BST!\n");
    }
}

int main() {

    // Alokasi pointer array untuk menyimpan alamat-alamat paket
    struct Paket *paket[MAX_PAKET];
    for(int i = 0; i < MAX_PAKET; i++) {
        paket[i] = (struct Paket *)malloc(sizeof(struct Paket));
    }

    int jumlahPaket = 0;
    int pilih;

    do {
        printf("\n==============================\n");
        printf(" SISTEM TRACKING PAKET\n");
        printf("==============================\n");

        printf("1. Input Data Paket\n");
        printf("2. Lihat Paket Berdasarkan nama\n");
        printf("3. Lihat Paket berdasarkan estimasi\n");
        printf("4. Cari Paket (BST Search)\n");
        printf("5. Keluar\n");

        printf("\nPilih Menu : ");
        if (scanf("%d", &pilih) != 1) {
            printf("\nInput tidak valid!\n");
            bersihkanBuffer();
            continue;
        }
        bersihkanBuffer();

        switch(pilih) {
            case 1:
                tambahPaket(paket, &jumlahPaket);
                break;
            case 2:
                sortNama(paket, jumlahPaket);
                tampilkanPaket(paket, jumlahPaket);
                break;
            case 3:
                sortEstimasi(paket, jumlahPaket);
                tampilkanPaket(paket, jumlahPaket);
                break;
            case 4:
                cariPaket(); // Tidak butuh passing array karena pakai BST global
                break;
            case 5:
                printf("\nProgram selesai.\n");
                break;
            default:
                printf("\nMenu tidak tersedia!\n");
        }

    } while(pilih != 5);

    // Free memori
    for(int i = 0; i < MAX_PAKET; i++) {
        free(paket[i]);
    }
    
    // Note: Idealnya free BST juga dilakukan secara rekursif sebelum exit
    return 0;
}

