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
	printf("Nhap ma phong: ");
	if(scanf("%d", &r.roomId) != 1)
	{
		printf("Phong khong hop le");
		printf("Nhan enter de nhap lai");
		scanf("%[^\n]");
		return;
	}
}

int main(void)
{
    int choice = -1;
    while (choice != 0)
    {
        printf("--- QUAN LY DAT PHONG KHACH SAN ---\n");
        printf("1. Them phong moi\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            printf("Tam biet!\n");
            break;
        case 1:
            addRoom();
            break;
    	}
	}
	return 0;
}