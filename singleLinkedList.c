#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMA 30
#define MAX_RESI 10
#define MAX_ALAMAT 50

typedef struct {
    char nama[MAX_NAMA];
    char resi[MAX_RESI];
    char alamat[MAX_ALAMAT];
    int estimasi;            
} Paket;

typedef struct Node {
    Paket data;
    char status[15];
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int size;
} LinkedList;

Node *buatNode() {
    Node *baru = (Node *) malloc(sizeof(Node));
    if (baru == NULL) {
        printf("Gagal mengalokasi memori!\n");
        return NULL;
    }

    printf("Masukan nama penerima  : ");
    scanf(" %[^\n]", baru->data.nama);
    printf("Masukan resi paket     : ");
    scanf("%s", baru->data.resi);
    printf("Masukan alamat         : ");
    scanf(" %[^\n]", baru->data.alamat);
    printf("Masukan estimasi tiba  : ");
    scanf("%d", &baru->data.estimasi);   
    while (getchar() != '\n');          

    strcpy(baru->status, "Mengantri");
    baru->next = NULL;
    return baru;
}

void initList(LinkedList *l) {
    l->head = NULL;
    l->size = 0;
}

void sisipAwal(LinkedList *l) {
    Node *baru = buatNode();
    if (baru == NULL) return;

    baru->next = l->head;
    l->head = baru;
    l->size++;
    printf("PAKET BERHASIL DISISIP DI AWAL\n");
}

void sisipAkhir(LinkedList *l) {
    Node *baru = buatNode();
    if (baru == NULL) return;

    if (l->head == NULL) {
        l->head = baru;
    } else {
        Node *temp = l->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }
    l->size++;
    printf("PAKET BERHASIL DISISIP DI AKHIR\n");
}

void hapusAwal(LinkedList *l) {
    if (l->head == NULL) {
        printf("Tidak ada paket!\n");
        return;
    }

    Node *temp = l->head;
    printf("PAKET DIHAPUS: %s (Resi: %s)\n",
           temp->data.nama, temp->data.resi);

    l->head = temp->next;
    free(temp);
    l->size--;
}

void hapusAkhir(LinkedList *l) {
    if (l->head == NULL) {
        printf("Tidak ada paket!\n");
        return;
    }

    if (l->head->next == NULL) {
        printf("PAKET DIHAPUS: %s (Resi: %s)\n",
               l->head->data.nama, l->head->data.resi);
        free(l->head);
        l->head = NULL;
        l->size--;
        return;
    }

    Node *prev = NULL;
    Node *current = l->head;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    printf("PAKET DIHAPUS: %s (Resi: %s)\n",
           current->data.nama, current->data.resi);

    prev->next = NULL;
    free(current);
    l->size--;
}

void kirimPaket(LinkedList *l) {
    if (l->head == NULL) {
        printf("Tidak ada paket!\n");
        return;
    }

    Node *temp = l->head;
    while (temp != NULL && strcmp(temp->status, "Mengantri") != 0) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Semua paket sudah terkirim!\n");
        return;
    }

    strcpy(temp->status, "Terkirim");
    printf("PAKET DIKIRIM: %s (Resi: %s)\n",
           temp->data.nama, temp->data.resi);
}

void tampilPaket(LinkedList *l) {
    if (l->head == NULL) {
        printf("Belum ada paket.\n");
        return;
    }

    Node *current = l->head;
    int no = 1;
    int jumlahMengantri = 0;
    int jumlahTerkirim = 0;

    // Hitung jumlah paket berdasarkan status
    Node *temp = l->head;
    while (temp != NULL) {
        if (strcmp(temp->status, "Mengantri") == 0) {
            jumlahMengantri++;
        } else if (strcmp(temp->status, "Terkirim") == 0) {
            jumlahTerkirim++;
        }
        temp = temp->next;
    }

    // Header dengan informasi statistik
    printf("\n========== DAFTAR PAKET ==========\n");
    printf("Jumlah Paket Keseluruhan : %d\n", l->size);
    printf("Paket Mengantri          : %d\n", jumlahMengantri);
    printf("Paket Terkirim           : %d\n", jumlahTerkirim);
    printf("===================================\n\n");

    // Tabel paket
    printf("%-4s %-15s %-10s %-20s %-12s %-10s\n",
           "No", "Nama", "Resi", "Alamat", "Estimasi", "Status");
    printf("--------------------------------------------------------------------\n");

    while (current != NULL) {
        char estimasiStr[20];
        sprintf(estimasiStr, "%d hari", current->data.estimasi);

        printf("%-4d %-15s %-10s %-20s %-12s %-10s\n",
               no++,
               current->data.nama,
               current->data.resi,
               current->data.alamat,
               estimasiStr,             
               current->status);
        current = current->next;
    }
    printf("--------------------------------------------------------------------\n");
}

void hapusSemua(LinkedList *l) {
    Node *current = l->head;

    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    l->head = NULL;
    l->size = 0;
}

int main() {
    LinkedList list;
    initList(&list);

    int pilih;

    do {
        printf("\n=== SISTEM PENGIRIMAN (SINGLE LINKED LIST) ===\n");
        printf("--- Tambah ---\n");
        printf("1. Sisip Awal\n");
        printf("2. Sisip Akhir\n");
        printf("3. Hapus Awal\n");
        printf("4. Hapus Akhir\n");
        printf("5. Kirim Paket\n");
        printf("6. Tampilkan Paket\n");
        printf("7. Keluar\n");
        printf("Pilih: ");

        if (scanf("%d", &pilih) != 1) {
            pilih = -1;
        }
        while (getchar() != '\n');

        switch (pilih) {
            case 1: sisipAwal(&list);   break;
            case 2: sisipAkhir(&list);  break;
            case 3: hapusAwal(&list);   break;
            case 4: hapusAkhir(&list);  break;
            case 5: kirimPaket(&list);  break;
            case 6: tampilPaket(&list); break;
            case 7: printf("Keluar...\n"); break;
            default: printf("Pilihan tidak valid!\n");

        }

    } while (pilih != 7);

    hapusSemua(&list);
    return 0;
}