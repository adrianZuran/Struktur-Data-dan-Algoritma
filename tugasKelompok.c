#include <stdio.h>
#include <string.h>

#define MAX_SIZE 20
#define MAX_RESI 20
#define MAX_NAMA 20

char nama[MAX_SIZE][MAX_NAMA] = {
    "Budi",
    "Andi",
    "Caca",
    "Doni",
    "Eka",
    "Fajar"
};

char resi[MAX_SIZE][MAX_RESI] = {
    "RESI006",
    "RESI002",
    "RESI004",
    "RESI001",
    "RESI005",
    "RESI003"
};

int jumlah = 6;

/* ================= TAMPIL DATA ================= */

void tampil()
{
    printf("\nNama\t\tResi\n");
    for (int i = 0; i < jumlah; i++)
    {
        printf("%s\t\t%s\n", nama[i], resi[i]);
    }
}

/* ================= SWAP ================= */

void swap(int a, int b)
{
    char tempNama[MAX_NAMA];
    char tempResi[MAX_RESI];

    strcpy(tempNama, nama[a]);
    strcpy(nama[a], nama[b]);
    strcpy(nama[b], tempNama);

    strcpy(tempResi, resi[a]);
    strcpy(resi[a], resi[b]);
    strcpy(resi[b], tempResi);
}

/* ================= QUICK SORT ================= */

int partition(int low, int high)
{
    char pivot[MAX_NAMA];
    strcpy(pivot, nama[high]);

    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (strcmp(nama[j], pivot) < 0)
        {
            i++;
            swap(i, j);
        }
    }

    swap(i + 1, high);
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
    for (int gap = jumlah / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < jumlah; i++)
        {
            char tempNama[MAX_NAMA];
            char tempResi[MAX_RESI];

            strcpy(tempNama, nama[i]);
            strcpy(tempResi, resi[i]);

            int j;

            for (j = i; j >= gap &&
                 strcmp(nama[j - gap], tempNama) > 0; j -= gap)
            {
                strcpy(nama[j], nama[j - gap]);
                strcpy(resi[j], resi[j - gap]);
            }

            strcpy(nama[j], tempNama);
            strcpy(resi[j], tempResi);
        }
    }
}

/* ================= MERGE SORT ================= */

void merge(int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char Lnama[n1][MAX_NAMA];
    char Rnama[n2][MAX_NAMA];

    char Lresi[n1][MAX_RESI];
    char Rresi[n2][MAX_RESI];

    for (int i = 0; i < n1; i++)
    {
        strcpy(Lnama[i], nama[left + i]);
        strcpy(Lresi[i], resi[left + i]);
    }

    for (int j = 0; j < n2; j++)
    {
        strcpy(Rnama[j], nama[mid + 1 + j]);
        strcpy(Rresi[j], resi[mid + 1 + j]);
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (strcmp(Lnama[i], Rnama[j]) < 0)
        {
            strcpy(nama[k], Lnama[i]);
            strcpy(resi[k], Lresi[i]);
            i++;
        }
        else
        {
            strcpy(nama[k], Rnama[j]);
            strcpy(resi[k], Rresi[j]);
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        strcpy(nama[k], Lnama[i]);
        strcpy(resi[k], Lresi[i]);
        i++;
        k++;
    }

    while (j < n2)
    {
        strcpy(nama[k], Rnama[j]);
        strcpy(resi[k], Rresi[j]);
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

    // PILIH SALAH SATU SORTING

    // QUICK SORT
    quickSort(0, jumlah - 1);

    // SHELL SORT
    // shellSort();

    // MERGE SORT
    // mergeSort(0, jumlah - 1);

    printf("\nSETELAH SORTING:\n");
    tampil();

    return 0;
}