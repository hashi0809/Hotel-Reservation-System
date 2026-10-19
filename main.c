#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10000
#define ROOM_EMPTY 0
#define ROOM_BOOKED 1

typedef struct
{
    int roomId;
    char roomType[20];
    long pricePerDay;
    int maxGuests;
    int status;
    char guestName[51];
    char checkInDate[9];
    char checkOutDate[9];
} Room;

Room rooms[MAX];
int roomCount = 0;
long totalRevenue = 0;

/* 11 ham chuc nang: TV2, TV3 dien code vao than ham */
void addRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void displayRooms(void) { printf("Chuc nang dang phat trien.\n"); }
void searchRooms(void) { printf("Chuc nang dang phat trien.\n"); }
void bookRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void checkoutRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void updateRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void deleteRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void showStatistics(void) { printf("Chuc nang dang phat trien.\n"); }
void sortByPrice(void) { printf("Chuc nang dang phat trien.\n"); }
void saveToFile(void) { printf("Chuc nang dang phat trien.\n"); }
void loadFromFile(void) { printf("Chuc nang dang phat trien.\n"); }

/* 4 ham ngay thang dung chung (ngay dang DDMMYYYY, vd "10102026") */
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int daysInMonth(int month, int year)
{
    int d[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month < 1 || month > 12) return 0;
    if (month == 2 && isLeapYear(year)) return 29;
    return d[month - 1];
}

int isValidDate(char *date)
{
    int d, m, y;
    if (strlen(date) != 8) return 0;
    if (sscanf(date, "%2d%2d%4d", &d, &m, &y) != 3) return 0;
    if (y < 1900 || m < 1 || m > 12) return 0;
    return d >= 1 && d <= daysInMonth(m, y);
}

long dateToDays(char *date)
{
    int d, m, y, i;
    long total = 0;
    sscanf(date, "%2d%2d%4d", &d, &m, &y);
    for (i = 1900; i < y; i++)
        total += isLeapYear(i) ? 366 : 365;
    for (i = 1; i < m; i++)
        total += daysInMonth(i, y);
    return total + d;
}

int main(void)
{
    int choice = -1;
    while (choice != 0)
    {
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

        printf("Nhap lua chon: ");
        if (scanf("%d", &choice) != 1)
        {
            scanf("%*[^\n]");
            getchar();
            system("cls||clear");
            continue;
        }
        getchar();

        switch (choice)
        {
        case 0:
            printf("Tam biet!\n");
            break;
        case 1:
            addRoom();
            break;
        case 2:
            displayRooms();
            break;
        case 3:
            searchRooms();
            break;
        case 4:
            bookRoom();
            break;
        case 5:
            checkoutRoom();
            break;
        case 6:
            updateRoom();
            break;
        case 7:
            deleteRoom();
            break;
        case 8:
            showStatistics();
            break;
        case 9:
            sortByPrice();
            break;
        case 10:
            saveToFile();
            break;
        case 11:
            loadFromFile();
            break;
        default:
            system("cls||clear");
            continue;
        }
        if (choice != 0)
        {
            printf("Nhan Enter de tiep tuc...");
            scanf("%*[^\n]");
            getchar();
        }
        system("cls||clear");
    }
    return 0;
}
