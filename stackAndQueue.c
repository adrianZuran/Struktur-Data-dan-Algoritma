#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20
#define MAX_RESI 10
#define MAX_NAMA 10

char resi[MAX_SIZE][MAX_RESI];
char nama[MAX_SIZE][MAX_NAMA];
char stack[MAX_SIZE][MAX_NAMA];
char stack2[MAX_SIZE][MAX_RESI];

int paket[MAX_SIZE];
int top = -1;
int front = -1;
int rear = -1;

int kosong()
{
    return front == -1 || front > rear;
}

int penuh()
{
    return rear == MAX_SIZE - 1;
}

void tambah()
{
    if (penuh())
    {
        printf("Antrean Penuh\n");
    }
    else
    {
        if (front == -1)
        {
            front = 0;
        }

        rear++;
        printf("masukan nama penerima : ");
        scanf("%s", nama[rear]);
        printf("masukan resi paket : ");
        scanf("%s", resi[rear]);
        printf("PAKET BERHASIL DITAMBAHKAN\n");
    }
}

void tampil()
{
    if (kosong())
    {
        printf("Antrean Kosong\n");
    }
    else
    {
        printf("Segera Dikirim\n");
        printf("Nama          Resi\n");
        for (int i = front; i <= rear; i++)
        {
            printf("%s          %s \n", nama[i], resi[i]);
        };
    };
}

void kirim()
{
    if (kosong())
    {
        printf("Antrean Kosong\n");
    }
    else
    {
        top++;
        strcpy(stack[top], nama[front]);
        strcpy(stack2[top], resi[front]);

        front++;
        if (front > rear)
        {
            front = rear = -1;
        }
        printf("PAKET BERHASIL DI KIRIM\n");
    }
}

void tampilriwayat()
{
    if (top == -1)
    {
        printf("Riwayat kosong !\n");
    }
    else
    {
        printf("Riwayat paket :\n");
        printf("Nama          Resi\n");
        for (int i = top; i >= 0; i--)
        {
            printf("-%s          %s \n", stack[i], stack2[i]);
        }
        printf("Paket terakhir dikirim:\n%s          %s \n", stack[top], stack2[top]);
    }
}

void pop()
{
    if (top == -1)
    {
        printf("Riwayat kosong!\n");
    }
    else
    {
        printf("Menghapus paket :%s\n", stack[top]);
        top--;
    }
}

int main()
{
    int pilih;

do {
    printf("\n==== SISTEM ANTREAN PENGIRIMAN BARANG ====\n");
    printf("1. Tambahhkan Paket\n");
    printf("2. Tampilkan Antrean Paket\n");
    printf("3. Kirim Paket\n");
    printf("4. Tampilkan Riwayat paket Terkirim\n");
    printf("5. Hapus Riwayat paket Terkirim\n");
    printf("6. Keluar\n");

    printf("Pilih : ");

    if (scanf("%d", &pilih) != 1) {
        printf("Input tidak valid! Harus angka.\n");
        scanf("%*s"); 
        continue;
    }

    if (pilih < 1 || pilih > 6) {
        printf("Input tidak valid! Pilih 1 - 6.\n");
        continue;
    }

    switch (pilih)
    {
    case 1:
        tambah();
        break;
    case 2:
        tampil();
        break;
    case 3:
        kirim();
        break;
    case 4:
        tampilriwayat();
        break;
    case 5:
        pop();
        break;
    case 6:
        printf("Anda Telah Keluar Dari sistem\n");
        break;
    }

} while (pilih != 6);

    return 0;
}