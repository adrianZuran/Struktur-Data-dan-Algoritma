    /**
    * Sistem Tracking Paket - Jawa Timur
    * Struktur Data: Array, BST, Graph (Adjacency Matrix), Shell Sort, BFS
    */

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    #define MAX_PAKET     100
    #define MAX_TRACKING  50
    #define JUMLAH_KOTA   11
    // Struktur Data

    typedef struct {
        char tanggal[30];
        char deskripsi[200];
        char lokasi[100];
        char kurir[100];
        char plat[20];
        char rute[100];
    } Tracking;

    typedef struct {
        char resi[30];
        char pengirim[100];
        char penerima[100];
        char layanan[50];
        float berat;
        char kotaAsal[100];
        char tujuan[100];
        char statusSekarang[50];
        int estimasi;
        int jumlahTracking;
        Tracking tracking[MAX_TRACKING];
    } Paket;

    typedef struct TreeNode {
        Paket *paket;
        struct TreeNode *left;
        struct TreeNode *right;
    } TreeNode;


    // Cara Tambah Kota tambah kota:

    // Tambah JUMLAH_KOTA
    // Tambah nama di array KOTA
    // Tambah kolom baru di semua baris GRAPH
    // Tambah 1 baris baru GRAPH
    // Pastikan koneksi simetris
    // Update tulisan (1-11) menjadi jumlah terbaru

    static const char KOTA[JUMLAH_KOTA][50] = {
        "Surabaya", "Malang", "Sidoarjo", "Gresik", "Mojokerto",
        "Pasuruan", "Probolinggo", "Kediri", "Madiun", "Jember", "Banyuwangi"
    };

    // Graf ketetanggaan kota Jawa Timur (simetris, undirected)
    static const int GRAPH[JUMLAH_KOTA][JUMLAH_KOTA] = {
        //Sby Mal Sda Gre Moj Pas Pro Ked Mad Jem Bwi
        { 0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0 }, // Surabaya
        { 0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0 }, // Malang
        { 1,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0 }, // Sidoarjo
        { 1,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0 }, // Gresik
        { 0,  0,  1,  1,  0,  0,  0,  1,  1,  0,  0 }, // Mojokerto
        { 0,  1,  1,  0,  0,  0,  1,  0,  0,  0,  0 }, // Pasuruan
        { 0,  0,  0,  0,  0,  1,  0,  0,  0,  1,  0 }, // Probolinggo
        { 0,  1,  0,  0,  1,  0,  0,  0,  1,  0,  0 }, // Kediri
        { 0,  0,  0,  0,  1,  0,  0,  1,  0,  0,  0 }, // Madiun
        { 0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  1 }, // Jember
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0 }, // Banyuwangi
    };


    static void bersihkanBuffer(void) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    static void hilangkanEnter(char *str) {
        str[strcspn(str, "\n")] = '\0';
    }

    static void tanggalOffset(int offsetHari, char *buf, size_t bufSize) {
        time_t t = time(NULL) + (time_t)(offsetHari * 86400);
        struct tm *tm_info = localtime(&t);
        strftime(buf, bufSize, "%d %b", tm_info);
    }

    static int inputPilihanKota(const char *prompt) {
        int pilihan;
        printf("%s", prompt);
        while (scanf("%d", &pilihan) != 1 || pilihan < 1 || pilihan > JUMLAH_KOTA) {
            printf("Masukkan angka 1-%d: ", JUMLAH_KOTA);
            bersihkanBuffer();
        }
        bersihkanBuffer();
        return pilihan - 1; // kembalikan index (0-based)
    }


    // Mengembalikan jumlah node dalam path, atau 0 jika tidak ditemukan
    static int cariBFS(int asal, int tujuan, int path[JUMLAH_KOTA]) {
        if (asal == tujuan) {
            path[0] = asal;
            return 1;
        }

        int queue[JUMLAH_KOTA], front = 0, rear = 0;
        int visited[JUMLAH_KOTA] = {0};
        int parent[JUMLAH_KOTA];
        for (int i = 0; i < JUMLAH_KOTA; i++) parent[i] = -1;

        queue[rear++] = asal;
        visited[asal] = 1;

        int ditemukan = 0;
        while (front < rear && !ditemukan) {
            int curr = queue[front++];
            for (int i = 0; i < JUMLAH_KOTA; i++) {
                if (GRAPH[curr][i] && !visited[i]) {
                    visited[i] = 1;
                    parent[i] = curr;
                    if (i == tujuan) { ditemukan = 1; break; }
                    queue[rear++] = i;
                }
            }
        }

        if (!ditemukan) return 0;

        // Rekonstruksi path dari tujuan ke asal, lalu balik
        int temp[JUMLAH_KOTA], count = 0;
        for (int curr = tujuan; curr != -1; curr = parent[curr])
            temp[count++] = curr;
        for (int i = 0; i < count; i++)
            path[i] = temp[count - 1 - i];

        return count;
    }

    static TreeNode *bstInsert(TreeNode *node, Paket *pkt) {
        if (!node) {
            TreeNode *baru = malloc(sizeof(TreeNode));
            if (!baru) { perror("malloc BST"); exit(EXIT_FAILURE); }
            baru->paket = pkt;
            baru->left = baru->right = NULL;
            return baru;
        }
        int cmp = strcmp(pkt->resi, node->paket->resi);
        if      (cmp < 0) node->left  = bstInsert(node->left,  pkt);
        else if (cmp > 0) node->right = bstInsert(node->right, pkt);
        return node;
    }

    static Paket *bstCari(TreeNode *node, const char *resi) {
        if (!node) return NULL;
        int cmp = strcmp(resi, node->paket->resi);
        if      (cmp == 0) return node->paket;
        else if (cmp  < 0) return bstCari(node->left,  resi);
        else               return bstCari(node->right, resi);
    }

    static void bstFree(TreeNode *node) {
        if (!node) return;
        bstFree(node->left);
        bstFree(node->right);
        free(node);
    }

    static void initTracking(Tracking *t) {
        memset(t, 0, sizeof(Tracking));
    }

    static void tambahTracking(Paket *pkt, const char *tgl,
                            const char *deskripsi, const char *lokasi,
                            const char *kurir, const char *plat, const char *rute) {
        int idx = pkt->jumlahTracking;
        if (idx >= MAX_TRACKING) return;

        initTracking(&pkt->tracking[idx]);
        strncpy(pkt->tracking[idx].tanggal,   tgl       ? tgl       : "", 29);
        strncpy(pkt->tracking[idx].deskripsi, deskripsi ? deskripsi : "", 199);
        strncpy(pkt->tracking[idx].lokasi,    lokasi    ? lokasi    : "", 99);
        strncpy(pkt->tracking[idx].kurir,     kurir     ? kurir     : "", 99);
        strncpy(pkt->tracking[idx].plat,      plat      ? plat      : "", 19);
        strncpy(pkt->tracking[idx].rute,      rute      ? rute      : "", 99);
        pkt->jumlahTracking++;
    }

    static void bangunRiwayatTracking(Paket *pkt, int pathCount, const int path[]) {
        char tglAwal[30], tglAkhir[30];
        int estimasiHari = pkt->estimasi;

        tanggalOffset(0, tglAwal, sizeof(tglAwal));
        tanggalOffset(estimasiHari > 1 ? estimasiHari - 1 : 0, tglAkhir, sizeof(tglAkhir));

        char buf[200];

        tambahTracking(pkt, tglAwal, "Pesanan Dibuat. Pengirim telah mengatur pengiriman.",
                    NULL, NULL, NULL, NULL);

        tambahTracking(pkt, tglAwal, "Kurir ditugaskan untuk menjemput pesanan.",
                    NULL, "Pak Budi (Pickup)", "W 1122 AA", NULL);

        snprintf(buf, sizeof(buf), "Pesanan telah diserahkan ke jasa kirim untuk diproses di %s.", pkt->kotaAsal);
        tambahTracking(pkt, tglAwal, buf, pkt->kotaAsal, NULL, NULL, NULL);

        snprintf(buf, sizeof(buf), "Paket telah tiba di fasilitas MH %s.", pkt->kotaAsal);
        tambahTracking(pkt, tglAwal, buf, pkt->kotaAsal, NULL, NULL, NULL);

        for (int p = 0; p < pathCount - 1; p++) {
            char tglTransit[30];
            tanggalOffset(p + 1, tglTransit, sizeof(tglTransit));
            char rute[110];
            snprintf(rute, sizeof(rute), "%s -> %s", KOTA[path[p]], KOTA[path[p + 1]]);
            tambahTracking(pkt, tglTransit, "Paket sedang dalam perjalanan / transit.",
                        NULL, NULL, NULL, rute);
        }

        snprintf(buf, sizeof(buf), "Paket telah tiba di fasilitas DC %s.", pkt->tujuan);
        tambahTracking(pkt, tglAkhir, buf, pkt->tujuan, NULL, NULL, NULL);

        snprintf(buf, sizeof(buf), "Pesanan tiba di alamat tujuan. Paket diterima oleh %s.", pkt->penerima);
        tambahTracking(pkt, tglAkhir, buf, NULL, "Andi (Delivery)", "W 6835 FU", NULL);
    }

    // Tambah Paket
    static void tambahPaket(Paket *paket[], int *jumlahPaket, TreeNode **root) {
        if (*jumlahPaket >= MAX_PAKET) {
            printf("Kapasitas paket penuh!\n");
            return;
        }

        Paket *pkt = paket[*jumlahPaket];
        memset(pkt, 0, sizeof(Paket));

        printf("\n=== INPUT DATA PAKET ===\n");

        printf("No Resi    : "); fgets(pkt->resi,     sizeof(pkt->resi),     stdin); hilangkanEnter(pkt->resi);
        printf("Pengirim   : "); fgets(pkt->pengirim, sizeof(pkt->pengirim), stdin); hilangkanEnter(pkt->pengirim);
        printf("Penerima   : "); fgets(pkt->penerima, sizeof(pkt->penerima), stdin); hilangkanEnter(pkt->penerima);
        printf("Layanan    : "); fgets(pkt->layanan,  sizeof(pkt->layanan),  stdin); hilangkanEnter(pkt->layanan);

        printf("Berat (Kg) : ");
        while (scanf("%f", &pkt->berat) != 1) {
            printf("Input tidak valid! Masukkan angka: ");
            bersihkanBuffer();
        }
        bersihkanBuffer();

        printf("\nDaftar Kota Jawa Timur:\n");
        for (int k = 0; k < JUMLAH_KOTA; k++)
            printf("  %2d. %s\n", k + 1, KOTA[k]);

        int asalIdx  = inputPilihanKota("\nPilih Kota Asal   (1-11): ");
        int tujuanIdx = inputPilihanKota("Pilih Kota Tujuan (1-11): ");

        strncpy(pkt->kotaAsal, KOTA[asalIdx],   sizeof(pkt->kotaAsal) - 1);
        strncpy(pkt->tujuan,   KOTA[tujuanIdx], sizeof(pkt->tujuan)   - 1);

        int path[JUMLAH_KOTA];
        int pathCount = cariBFS(asalIdx, tujuanIdx, path);

        int estimasiHari = (asalIdx == tujuanIdx) ? 1 : (pathCount > 0 ? pathCount : 3);
        pkt->estimasi = estimasiHari;

        strcpy(pkt->statusSekarang, "Terkirim");
        bangunRiwayatTracking(pkt, pathCount, path);

        *root = bstInsert(*root, pkt);
        (*jumlahPaket)++;

        printf("\nPaket berhasil ditambahkan!\n");
    }

    static void tampilkanPaket(Paket *paket[], int jumlahPaket) {
        if (jumlahPaket == 0) {
            printf("\nBelum ada data paket.\n");
            return;
        }

        printf("\n%-12s %-22s %-22s %-12s %8s  %-12s %-15s\n",
            "No. Resi", "Pengirim", "Penerima",
            "Layanan", "Berat", "Estimasi", "Status");
        printf("%s\n", "------------------------------------------------------------------------------------------------------");

        for (int i = 0; i < jumlahPaket; i++) {
            char pengirim[210], penerima[210];
            char estimasiStr[20];
            snprintf(pengirim, sizeof(pengirim), "%s (%s)", paket[i]->pengirim, paket[i]->kotaAsal);
            snprintf(penerima, sizeof(penerima), "%s (%s)", paket[i]->penerima, paket[i]->tujuan);
            snprintf(estimasiStr, sizeof(estimasiStr), "%d Hari", paket[i]->estimasi);

            printf("%-12.12s %-22.22s %-22.22s %-12.12s %6.2f Kg  %-12.12s %-15.15s\n",
                paket[i]->resi, pengirim, penerima,
                paket[i]->layanan, paket[i]->berat,
                estimasiStr, paket[i]->statusSekarang);
        }
    }

    // Shell Sort generik menggunakan function pointer
    static void shellSort(Paket *paket[], int n, int (*cmp)(const Paket *, const Paket *)) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                Paket *temp = paket[i];
                int j = i;
                while (j >= gap && cmp(paket[j - gap], temp) > 0) {
                    paket[j] = paket[j - gap];
                    j -= gap;
                }
                paket[j] = temp;
            }
        }
    }

    static int cmpNama(const Paket *a, const Paket *b) {
        return strcmp(a->penerima, b->penerima);
    }

    static int cmpEstimasi(const Paket *a, const Paket *b) {
        return (a->estimasi > b->estimasi) - (a->estimasi < b->estimasi);
    }

    static void cariPaket(TreeNode *root) {
        char resi[30];
        printf("\nMasukkan Nomor Resi: ");
        fgets(resi, sizeof(resi), stdin);
        hilangkanEnter(resi);

        Paket *hasil = bstCari(root, resi);
        if (!hasil) {
            printf("\nPaket dengan resi \"%s\" tidak ditemukan.\n", resi);
            return;
        }

        printf("\n=== DETAIL PAKET ===\n");
        printf("No. Resi   : %s\n",       hasil->resi);
        printf("Pengirim   : %s (%s)\n",  hasil->pengirim, hasil->kotaAsal);
        printf("Penerima   : %s (%s)\n",  hasil->penerima, hasil->tujuan);
        printf("Layanan    : %s\n",       hasil->layanan);
        printf("Berat      : %.2f Kg\n",  hasil->berat);
        printf("Estimasi   : %d Hari\n",  hasil->estimasi);
        printf("Status     : %s\n",       hasil->statusSekarang);

        printf("\n=== RIWAYAT PENGIRIMAN ===\n");
        for (int j = hasil->jumlahTracking - 1; j >= 0; j--) {
            Tracking *t = &hasil->tracking[j];
            printf("%-10s | %s\n", t->tanggal, t->deskripsi);
            if (strlen(t->lokasi) > 0) printf("           | Lokasi : %s\n", t->lokasi);
            if (strlen(t->kurir)  > 0) printf("           | Kurir  : %s\n", t->kurir);
            if (strlen(t->plat)   > 0) printf("           | Plat   : %s\n", t->plat);
            if (strlen(t->rute)   > 0) printf("           | Rute   : %s\n", t->rute);
            if (j > 0) printf("           |\n");
        }
        printf("\n");
    }

    int main(void) {
        Paket *paket[MAX_PAKET];
        for (int i = 0; i < MAX_PAKET; i++) {
            paket[i] = malloc(sizeof(Paket));
            if (!paket[i]) { perror("malloc paket"); return EXIT_FAILURE; }
        }

        TreeNode *root = NULL;
        int jumlahPaket = 0;
        int pilih;

        do {
            printf("\n=== SISTEM TRACKING PAKET ===\n");
            printf("1. Input Data Paket\n");
            printf("2. Lihat Paket (Sort Nama)\n");
            printf("3. Lihat Paket (Sort Estimasi)\n");
            printf("4. Cari Paket (BST)\n");
            printf("5. Keluar\n");
            printf("Pilih: ");

            if (scanf("%d", &pilih) != 1) {
                printf("Input tidak valid!\n");
                bersihkanBuffer();
                pilih = 0;
                continue;
            }
            bersihkanBuffer();

            switch (pilih) {
                case 1: tambahPaket(paket, &jumlahPaket, &root);                       break;
                case 2: shellSort(paket, jumlahPaket, cmpNama);  tampilkanPaket(paket, jumlahPaket); break;
                case 3: shellSort(paket, jumlahPaket, cmpEstimasi); tampilkanPaket(paket, jumlahPaket); break;
                case 4: cariPaket(root);                                                break;
                case 5: printf("Program selesai.\n");                                  break;
                default: printf("Menu tidak tersedia!\n");
            }
        } while (pilih != 5);

        // Bersihkan memori
        bstFree(root);
        for (int i = 0; i < MAX_PAKET; i++) free(paket[i]);

        return EXIT_SUCCESS;
    }