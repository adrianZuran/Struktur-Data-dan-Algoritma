#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 20
#define MAX_RESI 10
#define MAX_NAMA 30
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

typedef struct {
    Paket data[MAX_SIZE];
    int front;
    int rear;
} Queue;

typedef struct {
    Paket data[MAX_SIZE];
    int top;
} Stack;

void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

void initStack(Stack *s) {
    s->top = -1;
}

void initList(LinkedList *l) {
    l->head = NULL;
    l->size = 0;
}

int kosong(Queue *q) {
    return q->front == -1 || q->front > q->rear;
}

int penuh(Queue *q) {
    return q->rear == MAX_SIZE - 1;
}

void insertList(LinkedList *l, Paket p, char *status) {
    Node *baru = (Node *)malloc(sizeof(Node));
    baru->data = p;
    strcpy(baru->status, status);
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
}

void updateStatus(LinkedList *l, char *resi) {
    Node *current = l->head;
    while (current != NULL) {
        if (strcmp(current->data.resi, resi) == 0) {
            strcpy(current->status, "Terkirim");
            break;
        }
        current = current->next;
    }
}

void tampilLinkedList(LinkedList *l) {
    if (l->head == NULL) {
        printf("Linked List kosong, belum ada paket apapun.\n");
        return;
    }
    printf("\n===== SEMUA PAKET (Antrean + Terkirim) =====\n");
    printf("%-4s %-15s %-10s %-20s %-12s %-10s\n",
           "No", "Nama", "Resi", "Alamat", "Estimasi", "Status");
    printf("-----------------------------------------------------------------------\n");
    Node *current = l->head;
    int no = 1;
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
    printf("-----------------------------------------------------------------------\n");
    printf("Total paket: %d\n", l->size);
}

void tambah(Queue *q, LinkedList *l) {
    if (penuh(q)) {
        printf("Antrean Penuh\n");
        return;
    }
    if (q->front == -1) q->front = 0;
    q->rear++;
    printf("Masukan nama penerima  : ");
    scanf(" %[^\n]", q->data[q->rear].nama);
    printf("Masukan resi paket     : ");
    scanf("%s", q->data[q->rear].resi);
    printf("Masukan alamat         : ");
    scanf(" %[^\n]", q->data[q->rear].alamat);
    printf("Masukan estimasi tiba  : ");
    scanf(" %[^\n]", q->data[q->rear].estimasi);
    insertList(l, q->data[q->rear], "Mengantri");
    printf("PAKET BERHASIL DITAMBAHKAN\n");
}

void tampil(Queue *q) {
    if (kosong(q)) {
        printf("Antrean Kosong\n");
        return;
    }
    printf("\n===== Daftar Antrean =====\n");
    printf("%-4s %-15s %-10s %-20s %-12s\n",
           "No", "Nama", "Resi", "Alamat", "Estimasi");
    printf("------------------------------------------------------\n");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%-4d %-15s %-10s %-20s %-12s\n",
               i - q->front + 1,
               q->data[i].nama,
               q->data[i].resi,
               q->data[i].alamat,
               q->data[i].estimasi);
    }
}

void kirim(Queue *q, Stack *s, LinkedList *l) {
    if (kosong(q)) {
        printf("Antrean Kosong\n");
        return;
    }
    s->top++;
    s->data[s->top] = q->data[q->front];
    updateStatus(l, q->data[q->front].resi);
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    printf("PAKET BERHASIL DIKIRIM\n");
}

void tampilRiwayat(Stack *s) {
    if (s->top == -1) {
        printf("Riwayat kosong!\n");
        return;
    }
    printf("\n===== Riwayat Paket Terkirim =====\n");
    printf("%-4s %-15s %-10s %-20s %-12s\n",
           "No", "Nama", "Resi", "Alamat", "Estimasi");
    printf("------------------------------------------------------\n");
    for (int i = s->top; i >= 0; i--) {
        printf("%-4d %-15s %-10s %-20s %-12s\n",
               s->top - i + 1,
               s->data[i].nama,
               s->data[i].resi,
               s->data[i].alamat,
               s->data[i].estimasi);
    }
    printf("\nPaket TERAKHIR dikirim: %s (Resi: %s)\n",
           s->data[s->top].nama, s->data[s->top].resi);
}

void pop(Stack *s) {
    if (s->top == -1) {
        printf("Riwayat kosong!\n");
        return;
    }
    printf("Menghapus riwayat: %s (Resi: %s)\n",
           s->data[s->top].nama, s->data[s->top].resi);
    s->top--;
}

void bebaskanList(LinkedList *l) {
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
    Queue antrean;
    Stack riwayat;
    LinkedList semuaPaket;

    initQueue(&antrean);
    initStack(&riwayat);
    initList(&semuaPaket);

    int pilih;
    do {
        printf("\n==== SISTEM ANTREAN PENGIRIMAN BARANG ====\n");
        printf("1. Tambahkan Paket\n");
        printf("2. Tampilkan Antrean Paket (Queue)\n");
        printf("3. Kirim Paket\n");
        printf("4. Tampilkan Riwayat Paket Terkirim (Stack)\n");
        printf("5. Hapus Riwayat Terakhir\n");
        printf("6. Tampilkan Semua Paket (Linked List)\n");
        printf("7. Keluar\n");
        printf("Pilih: ");

        if (scanf("%d", &pilih) != 1) {
            printf("Input tidak valid! Harus angka.\n");
            scanf("%*s");
            continue;
        }
        if (pilih < 1 || pilih > 7) {
            printf("Input tidak valid! Pilih 1 - 7.\n");
            continue;
        }
        switch (pilih) {
            case 1: tambah(&antrean, &semuaPaket);           break;
            case 2: tampil(&antrean);                         break;
            case 3: kirim(&antrean, &riwayat, &semuaPaket);  break;
            case 4: tampilRiwayat(&riwayat);                  break;
            case 5: pop(&riwayat);                            break;
            case 6: tampilLinkedList(&semuaPaket);            break;
            case 7: printf("Anda Telah Keluar Dari Sistem\n"); break;
        }
    } while (pilih != 7);

    bebaskanList(&semuaPaket);
    return 0;
}