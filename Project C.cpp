#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100
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
    char checkInDate[11];
    char checkOutDate[11];
} Room;

Room rooms[MAX];
int roomCount = 0;
long totalRevenue = 0;
void addRoom(void) 
{
  if (roomCount >= MAX)
    {
        printf("Danh sach phong da day!\n");
        return;
    }

    Room r = {0};
    int c;

    printf("Nhap ma phong: ");
    if (scanf("%d", &r.roomId) != 1 || r.roomId <= 0)
    {
        printf("Ma phong khong hop le!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == r.roomId)
        {
            printf("Ma phong da ton tai!\n");
            while ((c = getchar()) != '\n' && c != EOF);
            return;
        }
    }

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Nhap loai phong (Don/Doi/VIP/TongThong): ");
    if (scanf("%19s", r.roomType) != 1)
        return;

    if (strcmp(r.roomType, "Don") != 0 &&
        strcmp(r.roomType, "Doi") != 0 &&
        strcmp(r.roomType, "VIP") != 0 &&
        strcmp(r.roomType, "TongThong") != 0)
    {
        printf("Loai phong khong hop le!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    printf("Nhap gia phong: ");
    if (scanf("%ld", &r.pricePerDay) != 1 ||
        r.pricePerDay <= 0)
    {
        printf("Gia phong khong hop le!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    printf("Nhap so khach toi da (1-10): ");
	if (scanf("%d", &r.maxGuests) != 1 ||
    r.maxGuests < 1 || r.maxGuests > 10)
	{
    printf("So khach phai tu 1 den 10!\n");
    while ((c = getchar()) != '\n' && c != EOF);
    return;
	}

    while ((c = getchar()) != '\n' && c != EOF);

    r.status = ROOM_EMPTY;
    rooms[roomCount] = r;
    roomCount++;

    printf("Them phong thanh cong!\n");
}
 
 
void displayRooms(void) 
{
  if (roomCount == 0)
    {
        printf("Danh sach phong dang trong!\n");
        return;
    }

    printf("%-10s %-12s %-12s %-12s %-12s\n",
           "Ma phong", "Loai", "Gia/ngay",
           "Khach toi da", "Trang thai");

    for (int i = 0; i < roomCount; i++)
    {
        printf("%-10d %-12s %-12ld %-12d %-12s\n",
               rooms[i].roomId,
               rooms[i].roomType,
               rooms[i].pricePerDay,
               rooms[i].maxGuests,
               rooms[i].status == ROOM_BOOKED
                   ? "Da dat" : "Trong");
    }
}
void searchRooms(void) 
{ 
 printf("Chuc nang dang phat trien.\n"); 
}
void bookRoom(void) 
{ 
  printf("Chuc nang dang phat trien.\n"); 
}
void checkoutRoom(void) 
{
 printf("Chuc nang dang phat trien.\n"); 
}
void updateRoom(void) 
{
	  int id, index = -1, c;
    Room r;

    printf("Nhap ma phong can cap nhat: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Ma phong khong hop le!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Khong tim thay phong!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    while ((c = getchar()) != '\n' && c != EOF);

    r = rooms[index];

    printf("Nhap loai phong moi: ");
    if (scanf("%19s", r.roomType) != 1)
        return;

    if (strcmp(r.roomType, "Don") != 0 &&
        strcmp(r.roomType, "Doi") != 0 &&
        strcmp(r.roomType, "VIP") != 0 &&
        strcmp(r.roomType, "TongThong") != 0)
    {
        printf("Loai phong khong hop le!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    printf("Nhap gia phong moi: ");
    if (scanf("%ld", &r.pricePerDay) != 1 ||
        r.pricePerDay <= 0)
    {
        printf("Gia phong khong hop le!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

 	printf("Nhap so khach toi da moi (1-10): ");
	if (scanf("%d", &r.maxGuests) != 1 ||
    r.maxGuests < 1 || r.maxGuests > 10)
	{	
    printf("So khach phai tu 1 den 10!\n");
    while ((c = getchar()) != '\n' && c != EOF);
    return;
	}

    while ((c = getchar()) != '\n' && c != EOF);

    rooms[index] = r;
    printf("Cap nhat phong thanh cong!\n"); 
}

void deleteRoom(void) 
{
int id, index = -1, c;

    printf("Nhap ma phong can xoa: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Ma phong khong hop le!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        printf("Khong tim thay phong!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    if (rooms[index].status == ROOM_BOOKED)
    {
        printf("Phong dang duoc dat, khong the xoa!\n");
        while ((c = getchar()) != '\n' && c != EOF);
        return;
    }

    for (int i = index; i < roomCount - 1; i++)
        rooms[i] = rooms[i + 1];

    roomCount--;

    while ((c = getchar()) != '\n' && c != EOF);
    printf("Xoa phong thanh cong!\n");
}

void showStatistics(void) {printf("Chuc nang dang phat trien.\n"); }
void sortByPrice(void) { printf("Chuc nang dang phat trien.\n"); }

void saveToFile(void)
{
    FILE *f = fopen("rooms.txt", "w");

    if (f == NULL)
    {
        printf("Khong mo duoc file!\n");
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        fprintf(f, "%d|%s|%ld|%d|%d",
                rooms[i].roomId,
                rooms[i].roomType,
                rooms[i].pricePerDay,
                rooms[i].maxGuests,
                rooms[i].status);

        if (rooms[i].status == ROOM_BOOKED)
        {
            fprintf(f, "|%s|%s|%s",
                    rooms[i].guestName,
                    rooms[i].checkInDate,
                    rooms[i].checkOutDate);
        }

        fprintf(f, "\n");
    }

    fclose(f);
    printf("Luu file rooms.txt thanh cong!\n");
}
void loadFromFile(void)
{
    FILE *f = fopen("rooms.txt", "r");
    Room temp[MAX];
    int count = 0;
    char line[256];

    if (f == NULL)
    {
        printf("Khong tim thay file rooms.txt!\n");
        return;
    }

    while (fgets(line, sizeof(line), f) != NULL)
    {
        Room r = {0};
        int n = sscanf(line, "%d|%19[^|]|%ld|%d|%d|%50[^|]|%10[^|]|%10s",
                       &r.roomId,
                       r.roomType,
                       &r.pricePerDay,
                       &r.maxGuests,
                       &r.status,
                       r.guestName,
                       r.checkInDate,
                       r.checkOutDate);

        if (n < 5 || count >= MAX)
        {
            printf("Du lieu file khong hop le!\n");
            fclose(f);
            return;
        }

        if (r.status == ROOM_EMPTY)
        {
            r.guestName[0] = '\0';
            r.checkInDate[0] = '\0';
            r.checkOutDate[0] = '\0';
        }
        else if (n != 8)
        {
            printf("Thieu thong tin khach!\n");
            fclose(f);
            return;
        }

        temp[count] = r;
        count++;
    }

    fclose(f);

    for (int i = 0; i < count; i++)
        rooms[i] = temp[i];

    roomCount = count;

    printf("Doc file thanh cong!\n");
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
        scanf("%*[^\n]");
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

