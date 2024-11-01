#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct Node {
    char date[11];
    char description[100];
    float amount;
    struct Node* prev;
    struct Node* next;
} Node;


Node* createNode(char date[], char description[], float amount) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->date, date);
    strcpy(newNode->description, description);
    newNode->amount = amount;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}


void addExpense(Node** head, char date[], char description[], float amount) {
    Node* newNode = createNode(date, description, amount);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;


        newNode->prev = temp;
    }
}


void deleteExpense(Node** head, char date[]) {
    Node* temp = *head;
    while (temp != NULL && strcmp(temp->date, date) != 0) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Pengeluaran dengan tanggal %s tidak ditemukan.\n", date);
        return;
    }
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    free(temp);
    printf("Pengeluaran dengan tanggal %s berhasil dihapus.\n", date);
}


void displayExpenses(Node* head) {
    Node* temp = head;
    printf("\nDaftar Pengeluaran Harian:\n");
    printf("------------------------------------------------------------\n");
    printf("|     Tanggal     |        Deskripsi        |    Jumlah    |\n");
    printf("------------------------------------------------------------\n");
    while (temp != NULL) {
        printf("| %15s | %20s | RP.%12.3f |\n", temp->date, temp->description, temp->amount);
        temp = temp->next;
    }
    printf("------------------------------------------------------------\n");
}


void searchExpenseByDate(Node* head, char date[]) {
    Node* temp = head;
    int found = 0;
    printf("\nHasil Pencarian Pengeluaran Berdasarkan Tanggal:\n");
    printf("------------------------------------------------------------\n");
    printf("|     Tanggal     |        Deskripsi        |    Jumlah    |\n");
    printf("------------------------------------------------------------\n");
    while (temp != NULL) {
        if (strcmp(temp->date, date) == 0) {
            printf("| %15s | %20s | %12.2f |\n", temp->date, temp->description, temp->amount);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("| Tidak ada pengeluaran dengan tanggal %s                 |\n", date);
    }
    printf("------------------------------------------------------------\n");
}


void searchExpenseByDescription(Node* head, char description[]) {
    Node* temp = head;
    int found = 0;
    printf("\nHasil Pencarian Pengeluaran Berdasarkan Deskripsi:\n");
    printf("------------------------------------------------------------\n");
    printf("|     Tanggal     |        Deskripsi        |    Jumlah    |\n");
    printf("------------------------------------------------------------\n");
    while (temp != NULL) {
        if (strstr(temp->description, description) != NULL) {
            printf("| %15s | %20s | %12.2f |\n", temp->date, temp->description, temp->amount);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("| Tidak ada pengeluaran dengan deskripsi '%s'             |\n", description);
    }
    printf("------------------------------------------------------------\n");
}


int compareDates(char date1[], char date2[]) {
    return strcmp(date1, date2);
}

void searchExpensesByDateRange(Node* head, char startDate[], char endDate[]) {
    Node* temp = head;
    int found = 0;
    printf("\nPengeluaran dari %s hingga %s:\n", startDate, endDate);
    printf("------------------------------------------------------------\n");
    printf("|     Tanggal     |        Deskripsi        |    Jumlah    |\n");
    printf("------------------------------------------------------------\n");
    while (temp != NULL) {
        if (compareDates(temp->date, startDate) >= 0 && compareDates(temp->date, endDate) <= 0) {
            printf("| %15s | %20s | %12.2f |\n", temp->date, temp->description, temp->amount);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("| Tidak ada pengeluaran dalam rentang tanggal tersebut      |\n");
    }
    printf("------------------------------------------------------------\n");
}


int main() {
    Node* head = NULL;
    int choice;
    char date[11];
    char description[100];
    char startDate[11], endDate[11];
    float amount;

    while (1) {

        system(CLEAR);

        printf("\n============================================================\n");
        printf("|                     Aplikasi Catatan Pengeluaran          |\n");
        printf("============================================================\n");
        printf("| 1. Lihat daftar pengeluaran                               |\n");
        printf("| 2. Tambah daftar pengeluaran                              |\n");
        printf("| 3. Hapus daftar pengeluaran                               |\n");
        printf("| 4. Cari pengeluaran berdasarkan tanggal                   |\n");
        printf("| 5. Cari pengeluaran berdasarkan deskripsi                 |\n");
        printf("| 6. Cari pengeluaran berdasarkan rentang tanggal           |\n");
        printf("| 7. Keluar                                                 |\n");
        printf("============================================================\n");
        printf("Pilihan: ");
        scanf("%d", &choice);


        system(CLEAR);

        switch (choice) {
            case 1:
                displayExpenses(head);
                break;
            case 2:
                printf("Masukkan tanggal (YYYY-MM-DD): ");
                scanf("%s", date);
                printf("Masukkan deskripsi: ");
                scanf(" %[^\n]s", description);
                printf("Masukkan jumlah: ");
                scanf("%f", &amount);
                addExpense(&head, date, description, amount);
                printf("Pengeluaran berhasil ditambahkan.\n");
                break;
            case 3:
                printf("Masukkan tanggal pengeluaran yang ingin dihapus (YYYY-MM-DD): ");
                scanf("%s", date);
                deleteExpense(&head, date);
                break;
            case 4:
                printf("Masukkan tanggal (YYYY-MM-DD) yang ingin dicari: ");
                scanf("%s", date);
                searchExpenseByDate(head, date);
                break;
            case 5:
                printf("Masukkan deskripsi yang ingin dicari: ");
                scanf(" %[^\n]s", description);
                searchExpenseByDescription(head, description);
                break;
            case 6:
                printf("Masukkan tanggal mulai (YYYY-MM-DD): ");
                scanf("%s", startDate);
                printf("Masukkan tanggal akhir (YYYY-MM-DD): ");
                scanf("%s", endDate);
                searchExpensesByDateRange(head, startDate, endDate);
                break;
            case 7:
                printf("Keluar dari program.\n");
                exit(0);
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }

        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
        getchar();
    }

    return 0;
}
