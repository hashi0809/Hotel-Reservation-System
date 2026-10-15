#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define ROOM_EMPTY 0
#define ROOM_BOOKED 1

typedef struct {
    int roomId;
    char roomType[20];
    float pricePerDay;
    int maxGuests;
    int status;
    char guestName[51];
    int daysStayed;
} Room;

Room rooms[MAX];
int roomCount = 0;
float totalRevenue = 0;

void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (!fgets(buffer, size, stdin)) { buffer[0] = '\0'; return; }
    buffer[strcspn(buffer, "\n")] = '\0';
}

int readInt(const char *prompt, int *value) {
    char buffer[256];
    readString(prompt, buffer, sizeof(buffer));
    char *end;
    long v = strtol(buffer, &end, 10);
    if (*end != '\0' || end == buffer) return 0;
    *value = (int)v;
    return 1;
}

int readFloat(const char *prompt, float *value) {
    char buffer[256];
    readString(prompt, buffer, sizeof(buffer));
    char *end;
    float v = strtof(buffer, &end);
    if (*end != '\0' || end == buffer) return 0;
    *value = v;
    return 1;
}

void waitEnter(void) {
    int c;
    printf("Nhan Enter de tiep tuc...");
    while ((c = getchar()) != '\n' && c != EOF);
}

void clearScreen(void) {
    for (int i = 0; i < 40; i++) printf("\n");
}

int findRoomIndex(int roomId) {
    for (int i = 0; i < roomCount; i++)
        if (rooms[i].roomId == roomId) return i;
    return -1;
}

int isValidRoomType(const char *type) {
    return strcmp(type, "Don") == 0 ||
           strcmp(type, "Doi") == 0 ||
           strcmp(type, "VIP") == 0 ||
           strcmp(type, "TongThong") == 0;
}

const char* getStatusString(int status) {
    return status == ROOM_BOOKED ? "Da dat" : "Trong";
}

void printHeader(void) {
    printf("%-8s|%-8s|%-12s|%-11s|%-10s|%-20s|%-8s\n",
           "Ma phong", "Loai", "Gia/ngay", "Khach toi da",
           "Trang thai", "Ten khach", "So ngay");
}

void printRoom(const Room *room) {
    printf("%-8d|%-8s|%-12.0f|%-11d|%-10s|%-20s|%-8d\n",
           room->roomId, room->roomType, room->pricePerDay, room->maxGuests,
           getStatusString(room->status), room->guestName, room->daysStayed);
}

void addRoom(void) {
    printf("[TV2] Chuc nang addRoom dang phat trien.\n");
}

void displayRooms(void) {
    printf("[TV2] Chuc nang displayRooms dang phat trien.\n");
}

void updateRoom(void) {
    printf("[TV2] Chuc nang updateRoom dang phat trien.\n");
}

void deleteRoom(void) {
    printf("[TV2] Chuc nang deleteRoom dang phat trien.\n");
}

void saveToFile(void) {
    printf("[TV2] Chuc nang saveToFile dang phat trien.\n");
}

void loadFromFile(void) {
    printf("[TV2] Chuc nang loadFromFile dang phat trien.\n");
}

void searchRooms(void) {
    printf("[TV3] Chuc nang searchRooms dang phat trien.\n");
}

void bookRoom(void) {
    printf("[TV3] Chuc nang bookRoom dang phat trien.\n");
}

void checkoutRoom(void) {
    printf("[TV3] Chuc nang checkoutRoom dang phat trien.\n");
}

void showStatistics(void) {
    printf("[TV3] Chuc nang showStatistics dang phat trien.\n");
}

void sortByPrice(void) {
    printf("[TV3] Chuc nang sortByPrice dang phat trien.\n");
}

int main(void) {
    int choice = -1;
    while (choice != 0) {
        printf("--- QUAN LY DAT PHONG KHACH SAN ---\n");
        printf("1. Them phong moi\n");
        printf("2. Hien thi danh sach phong\n");
        printf("3. Tim kiem phong\n");
        printf("4. Dat phong\n");
        printf("5. Tra phong + tinh tien\n");
        printf("6. Cap nhat thong tin phong\n");
        printf("7. Xoa phong\n");
        printf("8. Thong ke doanh thu\n");
        printf("9. Sap xep phong theo gia\n");
        printf("10. Luu danh sach ra file\n");
        printf("11. Doc danh sach tu file\n");
        printf("0. Thoat\n");

        if (!readInt("Nhap lua chon: ", &choice)) {
            printf("Lua chon khong hop le!\n");
            waitEnter(); clearScreen(); continue;
        }
        switch (choice) {
            case 0: printf("Tam biet!\n"); break;
            case 1: addRoom(); break;
            case 2: displayRooms(); break;
            case 3: searchRooms(); break;
            case 4: bookRoom(); break;
            case 5: checkoutRoom(); break;
            case 6: updateRoom(); break;
            case 7: deleteRoom(); break;
            case 8: showStatistics(); break;
            case 9: sortByPrice(); break;
            case 10: saveToFile(); break;
            case 11: loadFromFile(); break;
            default: printf("Lua chon khong hop le!\n");
        }
        if (choice != 0) waitEnter();
        clearScreen();
    }
    return 0;
}
