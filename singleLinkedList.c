#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAMA 30
#define MAX_RESI 10
#define MAX_ALAMAT 50
#define MAX_ESTIMASI 20

typedef struct {
    char nama[MAX_NAMA];
    char resi[MAX_RESI];
    char alamat[MAX_ALAMAT];
    char estimasi[MAX_ESTIMASI];
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

void initList(LinkedList *l) {
    l->head = NULL;
    l->size = 0;
}

void tambahPaket(LinkedList *l) {
    Node *baru = (Node *) malloc(sizeof(Node));
    if (baru == NULL) {
        printf("Gagal mengalokasi memori!\n");
        return;
    }

    printf("Masukan nama penerima  : ");
    scanf(" %[^\n]", baru->data.nama);
    printf("Masukan resi paket     : ");
    scanf("%s", baru->data.resi);
    printf("Masukan alamat         : ");
    scanf(" %[^\n]", baru->data.alamat);
    printf("Masukan estimasi tiba  : ");
    scanf(" %[^\n]", baru->data.estimasi);

    strcpy(baru->status, "Mengantri");
    baru->next = NULL;

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
    printf("PAKET BERHASIL DITAMBAHKAN\n");
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

    printf("\n===== DAFTAR PAKET =====\n");
    printf("%-4s %-15s %-10s %-20s %-12s %-10s\n",
           "No", "Nama", "Resi", "Alamat", "Estimasi", "Status");
    printf("------------------------------------------------------------------\n");

    while (current != NULL) {
        printf("%-4d %-15s %-10s %-20s %-12s %-10s\n",
               no++,
               current->data.nama,
               current->data.resi,
               current->data.alamat,
               current->data.estimasi,
               current->status);
        current = current->next;
    }
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
        printf("1. Tambah Paket\n");
        printf("2. Kirim Paket\n");
        printf("3. Tampilkan Paket\n");
        printf("4. Keluar\n");
        printf("Pilih: ");

        if (scanf("%d", &pilih) != 1) {
            pilih = -1; 
        }
        while (getchar() != '\n'); // Bersihkan sisa buffer

        switch (pilih) {
            case 1: tambahPaket(&list); break;
            case 2: kirimPaket(&list); break;
            case 3: tampilPaket(&list); break;
            case 4: printf("Keluar...\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }

    } while (pilih != 4);

    hapusSemua(&list);
    return 0;
}