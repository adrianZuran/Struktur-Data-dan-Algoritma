#include <stdio.h>
#include <string.h>

#define MAX_NAMA 50
#define MAX_RESI 20
#define MAX_ALAMAT 100
#define MAX_SIZE 6

typedef struct {
    char nama[MAX_NAMA];
    char resi[MAX_RESI];
    char alamat[MAX_ALAMAT];
    int estimasi;
} Paket;

/* ================= DATA DUMMY ================= */

Paket paket[MAX_SIZE] = {
    {"Budi",  "RESI006", "Surabaya", 3},
    {"Andi",  "RESI002", "Sidoarjo", 1},
    {"Caca",  "RESI004", "Malang", 5},
    {"Doni",  "RESI001", "Gresik", 2},
    {"Eka",   "RESI005", "Mojokerto", 4},
    {"Fajar", "RESI003", "Lamongan", 2}
};

/* ================= TAMPIL DATA ================= */

void tampil()
{
    printf("\n====================================================\n");
    printf("Nama\tResi\t\tAlamat\t\tEstimasi\n");
    printf("====================================================\n");

    for (int i = 0; i < MAX_SIZE; i++)
    {
        printf("%s\t%s\t%s\t\t%d Hari\n",
               paket[i].nama,
               paket[i].resi,
               paket[i].alamat,
               paket[i].estimasi);
    }
}

/* ================= SWAP ================= */

void swap(Paket *a, Paket *b)
{
    Paket temp = *a;
    *a = *b;
    *b = temp;
}

/* ================= QUICK SORT ================= */

int partition(int low, int high)
{
    char pivot[MAX_NAMA];
    strcpy(pivot, paket[high].nama);

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (strcmp(paket[j].nama, pivot) < 0)
        {
            i++;
            swap(&paket[i], &paket[j]);
        }
    }

    swap(&paket[i + 1], &paket[high]);

    return i + 1;
}

void quickSort(int low, int high)
{
    if (low < high)
    {
        int pi = partition(low, high);

        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

/* ================= SHELL SORT ================= */

void shellSort()
{
    for (int gap = MAX_SIZE / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < MAX_SIZE; i++)
        {
            Paket temp = paket[i];

            int j;

            for (j = i;
                 j >= gap &&
                 strcmp(paket[j - gap].nama, temp.nama) > 0;
                 j -= gap)
            {
                paket[j] = paket[j - gap];
            }

            paket[j] = temp;
        }
    }
}

/* ================= MERGE SORT ================= */

void merge(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Paket L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = paket[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = paket[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (strcmp(L[i].nama, R[j].nama) < 0)
        {
            paket[k] = L[i];
            i++;
        }
        else
        {
            paket[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        paket[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        paket[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        merge(left, mid, right);
    }
}

/* ================= MAIN ================= */

int main()
{
    printf("DATA AWAL:\n");
    tampil();

    /* PILIH SALAH SATU */

    // QUICK SORT
    quickSort(0, MAX_SIZE - 1);

    // SHELL SORT
    // shellSort();

    // MERGE SORT
    // mergeSort(0, MAX_SIZE - 1);

    printf("\nSETELAH SORTING:\n");
    tampil();

    return 0;
}