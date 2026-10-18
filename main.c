#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
#define ROOM_EMPTY 0
#define ROOM_BOOKED 1

typedef struct {
    int roomId;
    char roomType[20];
    long pricePerDay;
    int maxGuests;
    int status;
    char guestName[51];
    char checkInDate[11];
    char checkOutDate[11];
} Room;

Room rooms[MAX];
int roomCount = 0;
long totalRevenue = 0;

void readString(const char *prompt, char *buffer, int size) {
    printf("%s", prompt);
    if (!fgets(buffer, size, stdin)) { buffer[0] = '\0'; return; }
    buffer[strcspn(buffer, "\n")] = '\0';
}

int readInt(const char *prompt, int *value) {
    int c;
    printf("%s", prompt);
    if (scanf("%d", value) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    while ((c = getchar()) != '\n' && c != EOF);
    return 1;
}

int readLong(const char *prompt, long *value) {
    int c;
    printf("%s", prompt);
    if (scanf("%ld", value) != 1) {
        while ((c = getchar()) != '\n' && c != EOF);
        return 0;
    }
    while ((c = getchar()) != '\n' && c != EOF);
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

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month - 1];
}

int isValidDate(const char *date) {
    int d, m, y;
    if (strlen(date) != 10 || date[2] != '/' || date[5] != '/') return 0;
    if (sscanf(date, "%d/%d/%d", &d, &m, &y) != 3) return 0;
    if (y < 1900 || y > 2100) return 0;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > daysInMonth(m, y)) return 0;
    return 1;
}

long dateToDays(const char *date) {
    int d, m, y;
    sscanf(date, "%d/%d/%d", &d, &m, &y);
    long total = 0;
    for (int yy = 1900; yy < y; yy++)
        total += isLeapYear(yy) ? 366 : 365;
    for (int mm = 1; mm < m; mm++)
        total += daysInMonth(mm, y);
    return total + d;
}

void printHeader(void) {
    printf("%-8s|%-8s|%-12s|%-11s|%-10s|%-20s|%-10s|%-10s\n",
           "Ma phong", "Loai", "Gia/ngay", "Khach toi da",
           "Trang thai", "Ten khach", "Ngay vao", "Ngay ra");
}

void printRoom(const Room *room) {
    printf("%-8d|%-8s|%-12ld|%-11d|%-10s|%-20s|%-10s|%-10s\n",
           room->roomId, room->roomType, room->pricePerDay, room->maxGuests,
           getStatusString(room->status), room->guestName,
           room->checkInDate[0] ? room->checkInDate : "-",
           room->checkOutDate[0] ? room->checkOutDate : "-");
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
