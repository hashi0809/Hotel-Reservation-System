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
    if (scanf("%d", &r.roomId) != 1 || (r.roomId < 101 || r.roomId > 200))
    {
        printf("Ma phong khong hop le!\n");
        printf("Nhan enter de nhap lai");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].roomId == r.roomId)
        {
            printf("Ma phong da ton tai!\n");
            scanf("%[^\n]");
            printf("Nhan enter de nhap lai");
        	scanf("%*[^\n]");
        	getchar();
            return;
        }
    }

    printf("Nhap loai phong (Don/Doi/Vip/TongThong): ");
    if (scanf("%19s", r.roomType) != 1)
        return;

    char firstChar = r.roomType[0];
    
    if (firstChar == 'V' || firstChar == 'v') 
    {
        strcpy(r.roomType, "VIP");
    } 
    else if (firstChar == 'T' || firstChar == 't') 
    {
        strcpy(r.roomType, "TongThong");
    } 
    else if (firstChar == 'D' || firstChar == 'd') 
    {
        int len = strlen(r.roomType);
        char lastChar = r.roomType[len - 1];

        if (len == 1 || lastChar == 'n' || lastChar == 'N') 
        {
            strcpy(r.roomType, "Don");
        } 
        else if (lastChar == 'i' || lastChar == 'I') 
        {
            strcpy(r.roomType, "Doi");
        } 
        else 
        {
            printf("Loai phong khong hop le!\n");
            scanf("%*[^\n]");
        	getchar();
            return;
        }
    } 
    else 
    {
        printf("Loai phong khong hop le!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    printf("-> Da ghi nhan loai phong: %s\n", r.roomType); 

    printf("Nhap gia phong: ");
    if (scanf("%ld", &r.pricePerDay) != 1 || r.pricePerDay <= 0)
    {
        printf("Gia phong khong hop le!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    printf("Nhap so khach toi da (1-10): ");
    if (scanf("%d", &r.maxGuests) != 1 || r.maxGuests < 1 || r.maxGuests > 10)
    {
        printf("So khach phai tu 1 den 10!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    scanf("%*[^\n]");
    getchar();

    r.status = ROOM_EMPTY;
    strcpy(r.guestName, "");
    strcpy(r.checkInDate, "");
    strcpy(r.checkOutDate, "");

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

    printf("\n=================================================================================================================\n");
    printf("%-10s %-12s %-12s %-10s %-12s %-20s %-12s %-12s\n",
           "Ma phong", "Loai", "Gia/ngay", "Max Khach", "Trang thai", "Ten khach hang", "Ngay vao", "Ngay ra");
    printf("=================================================================================================================\n");

    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].status == ROOM_BOOKED)
        {
            printf("%-10d %-12s %-12ld %-10d %-12s %-20s %-12s %-12s\n",
                   rooms[i].roomId,
                   rooms[i].roomType,
                   rooms[i].pricePerDay,
                   rooms[i].maxGuests,
                   "Da dat",
                   rooms[i].guestName,
                   rooms[i].checkInDate,
                   strlen(rooms[i].checkOutDate) > 0 ? rooms[i].checkOutDate : "Chua tra");
        }
        else
        {
            printf("%-10d %-12s %-12ld %-10d %-12s %-20s %-12s %-12s\n",
                   rooms[i].roomId,
                   rooms[i].roomType,
                   rooms[i].pricePerDay,
                   rooms[i].maxGuests,
                   "NULL",
                   "NULL",
                   "NULL",
                   "NULL");
        }
    }
    printf("=================================================================================================================\n\n");
}



void searchRooms(void) {
    if (roomCount == 0) {
        printf("Chua co phong nao trong he thong!\n");
        return;
    }
    int choice;
    printf("--- TIM KIEM PHONG ---\n");
    printf("1. Tim theo ma phong\n");
    printf("2. Tim theo loai phong\n");
    printf("Nhap lua chon: ");
    if (scanf("%d", &choice) != 1) {
    	scanf("%*[^\n]");
        getchar();
        printf("Lua chon khong hop le!\n");
        return;
    }
    
	scanf("%*[^\n]");
    getchar();
    
    switch (choice) {
        case 1: {
            int id;
            printf("Nhap ma phong can tim: ");
            scanf("%d", &id);
            scanf("%*[^\n]");
            getchar();
            
            int found = 0;
            for (int i = 0; i < roomCount; i++) {
                if (rooms[i].roomId == id) {
                    printf("Da tim thay phong:\n");
                    printf("Ma phong: %d | Loai: %s | Gia: %ld | Toi da: %d khach | Trang thai: %s\n", 
                        rooms[i].roomId, rooms[i].roomType, rooms[i].pricePerDay, rooms[i].maxGuests,
                        rooms[i].status == ROOM_EMPTY ? "Con trong" : "Da dat");
                    found = 1;
                    break;
                }
            }
            if (!found) printf("Khong tim thay phong co ma %d!\n", id);
            break;
        }
        case 2: {
            char type[20];
            printf("Nhap loai phong can tim: ");
            fgets(type, sizeof(type), stdin);
            type[strcspn(type, "\n")] = 0;

            int found = 0;
            printf("Ket qua tim kiem loai '%s':\n", type);
            for (int i = 0; i < roomCount; i++) {
                if (strcasecmp(rooms[i].roomType, type) == 0) {
                    printf("Ma phong: %d | Loai: %s | Gia: %ld | Toi da: %d khach | Trang thai: %s\n", 
                        rooms[i].roomId, rooms[i].roomType, rooms[i].pricePerDay, rooms[i].maxGuests,
                        rooms[i].status == ROOM_EMPTY ? "Con trong" : "Da dat");
                    found = 1;
                }
            }
            if (!found) printf("Khong tim thay phong loai '%s'!\n", type);
            break;
        }
        default:
            printf("Lua chon khong hop le!\n");
            break;
    }
}


	

void bookRoom(void) { 
	int id;
    printf("--- DAT PHONG ---\n");
    printf("Nhap ma phong can dat: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomId == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay phong!\n");
        return;
    }

    if (rooms[index].status == ROOM_BOOKED) {
        printf("Phong nay da duoc dat roi!\n");
        return;
    }
	scanf("%*[^\n]");
    getchar();
    
    printf("Nhap ten khach hang: ");
    fgets(rooms[index].guestName, sizeof(rooms[index].guestName), stdin);
    rooms[index].guestName[strcspn(rooms[index].guestName, "\n")] = 0;

    int guests;
    while (1) {
        printf("Nhap so luong khach (Toi da %d khach): ", rooms[index].maxGuests);
        if (scanf("%d", &guests) == 1 && guests > 0 && guests <= rooms[index].maxGuests) {
            break;
        }
        printf("So luong khach khong hop le! Vui long nhap lai.\n");
        scanf("%*[^\n]");
    	getchar();
    }
    
	scanf("%*[^\n]");
    getchar();

    printf("Nhap ngay vao: ");
    fgets(rooms[index].checkInDate, sizeof(rooms[index].checkInDate), stdin);
    rooms[index].checkInDate[strcspn(rooms[index].checkInDate, "\n")] = 0;

    rooms[index].status = ROOM_BOOKED;
    strcpy(rooms[index].checkOutDate, "Chua xac dinh");
    printf("Dat phong thanh cong cho khach hang %s!\n", rooms[index].guestName);
    
}




void checkoutRoom(void) { 
	int id;
    printf("--- TRA PHONG VA TINH TIEN ---\n");
    printf("Nhap ma phong can tra: ");
    scanf("%d", &id);

    int index = -1;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomId == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Khong tim thay phong!\n");
        return;
    }

    if (rooms[index].status == ROOM_EMPTY) {
        printf("Phong nay dang trong, chua duoc dat!\n");
        return;
    }

    scanf("%*[^\n]");
    getchar();

    char checkOut[11];
    printf("Ngay vao cua khach la: %s\n", rooms[index].checkInDate);
    printf("Nhap ngay ra: ");
    fgets(checkOut, sizeof(checkOut), stdin);
    checkOut[strcspn(checkOut, "\n")] = 0;

    long days;
    printf("Nhap so ngay o: ");
    while (1) {
        if (scanf("%ld", &days) == 1 && days > 0) {
            break;
        }
        printf("So ngay khong hop le! Vui long nhap lai: ");
        scanf("%*[^\n]");
        getchar();
    }

    long bill = days * rooms[index].pricePerDay;
    totalRevenue += bill;

    printf("\n========= HOA DON THANH TOAN =========\n");
    printf("Ma phong: %d\n", rooms[index].roomId);
    printf("Khach hang: %s\n", rooms[index].guestName);
    printf("So ngay o: %ld ngay\n", days);
    printf("Don gia: %ld VND/ngay\n", rooms[index].pricePerDay);
    printf("Tong tien thanh toan: %ld VND\n", bill);
    printf("=======================================\n");

    rooms[index].status = ROOM_EMPTY;
    strcpy(rooms[index].guestName, "");
    strcpy(rooms[index].checkInDate, "");
    strcpy(rooms[index].checkOutDate, "");

    printf("Tra phong thanh cong!\n");
    while (getchar() != '\n');
}

void updateRoom(void) 
{
	  int id, index = -1, c;
    Room r;

    printf("Nhap ma phong can cap nhat: ");
    if (scanf("%d", &id) != 1)
    {
        printf("Ma phong khong hop le!\n");
        scanf("%*[^\n]");
        getchar();
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
        scanf("*[^\n]");
        getchar();
        return;
    }

    scanf("%*[^\n]");
    getchar();
        
    r = rooms[index];

    printf("Nhap loai phong moi: ");
    if (scanf("%19s", r.roomType) != 1)
        return;

    char firstChar = r.roomType[0];
    
    if (firstChar == 'V' || firstChar == 'v') 
    {
        strcpy(r.roomType, "VIP");
    } 
    else if (firstChar == 'T' || firstChar == 't') 
    {
        strcpy(r.roomType, "TongThong");
    } 
    else if (firstChar == 'D' || firstChar == 'd') 
    {
        int len = strlen(r.roomType);
        char lastChar = r.roomType[len - 1];

        if (len == 1 || lastChar == 'n' || lastChar == 'N') 
        {
            strcpy(r.roomType, "Don");
        } 
        else if (lastChar == 'i' || lastChar == 'I') 
        {
            strcpy(r.roomType, "Doi");
        } 
        else 
        {
            printf("Loai phong khong hop le!\n");
            while ((c = getchar()) != '\n' && c != EOF);
            return;
        }
    } 

	if(firstChar == 'D' || firstChar == 'd')
	{
		int len = strlen(r.roomType);
        char lastChar = r.roomType[len - 1];
        
		if(lastChar == 'n' || lastChar == 'N')
		{
			printf("so khach toi da moi: 1\n");
			r.maxGuests = 1;
		}
		else if(lastChar == 'i' || lastChar == 'I')
		{
			printf("so khach toi da moi: 2\n");
			r.maxGuests = 2;
		}
	}
	
	else if(firstChar == 'V' || firstChar == 'v') 
	{
		printf("Nhap so khach toi da moi (1-5): ");
		if (scanf("%d", &r.maxGuests) != 1 ||
    	r.maxGuests < 1 || r.maxGuests > 5)
		{	
    	printf("So khach phai tu 1 den 5!\n");
    	scanf("%*[^\n]");
    	getchar();
    	return;
    	}
	}
	else if (firstChar == 'T' || firstChar == 't') 
	{
		printf("Nhap so khach toi da moi (1-10): ");
		if (scanf("%d", &r.maxGuests) != 1 ||
    	r.maxGuests < 1 || r.maxGuests > 10)
		{	
    	printf("So khach phai tu 1 den 10!\n");
    	scanf("%*[^\n]");
    	getchar();
    	return;
    	}
	}
	scanf("%*[^\n]");
    getchar();
		
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
        scanf("%*[^\n]");
        getchar();
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
        scanf("%*[^\n]");
        getchar();
        return;
    }

    if (rooms[index].status == ROOM_BOOKED)
    {
        printf("Phong dang duoc dat, khong the xoa!\n");
        scanf("%*[^\n]");
        getchar();
        return;
    }

    for (int i = index; i < roomCount - 1; i++)
        rooms[i] = rooms[i + 1];

    roomCount--;

    scanf("%*[^\n]");
    getchar();
    printf("Xoa phong thanh cong!\n");
}

void showStatistics(void) { 
	int bookedCount = 0;
    int emptyCount = 0;
    
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].status == ROOM_BOOKED) {
            bookedCount++;
        } else {
            emptyCount++;
        }
    }

    printf("--- THONG KE KHACH SAN ---\n");
    printf("Tong so phong hien co: %d\n", roomCount);
    printf("So phong dang trong: %d\n", emptyCount);
    printf("So phong dang duoc dat: %d\n", bookedCount);
    printf("Tong doanh thu tich luy: %ld VND\n", totalRevenue);
	
}
void sortByPrice(void) { 
if (roomCount < 2) {
        printf("Khong du phong de sap xep!\n");
        return;
    }

    int choice;
    printf("--- SAP XEP PHONG THEO GIA ---\n");
    printf("1. Tang dan theo gia\n");
    printf("2. Giam dan theo gia\n");
    printf("Nhap lua chon: ");
    
    if (scanf("%d", &choice) != 1) {
        scanf("%*[^\n]");
        getchar();
        printf("Lua chon khong hop le!\n");
        return;
    }
    scanf("%*[^\n]");
    getchar();

    for (int i = 0; i < roomCount - 1; i++) {
        for (int j = i + 1; j < roomCount; j++) {
            int condition = 0;
            switch (choice) {
                case 1:
                    condition = (rooms[i].pricePerDay > rooms[j].pricePerDay);
                    break;
                case 2:
                    condition = (rooms[i].pricePerDay < rooms[j].pricePerDay);
                    break;
                default:
                    printf("Lua chon khong hop le!\n");
                    return;
            }

            if (condition) {
                Room temp = rooms[i];
                rooms[i] = rooms[j];
                rooms[j] = temp;
            }
        }
    }

    printf("Sap xep phong thanh cong! Hay chon chuc nang 2 de xem lai danh sach.\n");
}

void saveToFile(void)
{
    char fileName[100];
    char fullPath[120];
    int c;

    printf("Nhap ten file muon luu (khong can .txt): ");
    if (scanf("%99s", fileName) != 1)
    {
        printf("Ten file khong hop le!\n");
        return;
    }
   	scanf("%*[^\n]");
    getchar();

    sprintf(fullPath, "%s.txt", fileName);
    FILE *f = fopen(fullPath, "w");

    if (f == NULL)
    {
        printf("Khong mo duoc file để ghi!\n");
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
            fprintf(f, "|%s|%s|%s\n",
                    rooms[i].guestName,
                    rooms[i].checkInDate,
                    rooms[i].checkOutDate);
        }
        else
        {
            fprintf(f, "|NULL|NULL|NULL\n");
        }
    }

    fclose(f);
    printf("Luu file %s thanh cong!\n", fullPath);
}

void loadFromFile(void)
{
    char fileName[100];
    char fullPath[120];
    Room temp[MAX];
    int count = 0;
    char line[256];
    int c;

    printf("Nhap ten file muon doc (khong can .txt): ");
    if (scanf("%99s", fileName) != 1)
    {
        printf("Ten file khong hop le!\n");
        return;
    }
    scanf("%*[^\n]");
    getchar();

    sprintf(fullPath, "%s.txt", fileName);
    FILE *f = fopen(fullPath, "r");

    if (f == NULL)
    {
        printf("Khong tim thay file %s!\n", fullPath);
        return;
    }

    while (fgets(line, sizeof(line), f) != NULL)
    {
        line[strcspn(line, "\r\n")] = '\0';
        
        if (strlen(line) == 0) continue;

        Room r = {0};
        char gName[51] = {0};
        char cIn[11] = {0};
        char cOut[11] = {0};

        int n = sscanf(line, "%d|%19[^|]|%ld|%d|%d|%50[^|]|%10[^|]|%10s",
                       &r.roomId,
                       r.roomType,
                       &r.pricePerDay,
                       &r.maxGuests,
                       &r.status,
                       gName,
                       cIn,
                       cOut);

        if (n != 8 || count >= MAX)
        {
            printf("Du lieu file khong dung dinh dang 8 truong!\n");
            fclose(f);
            return;
        }

        if (r.status == ROOM_EMPTY)
        {
            r.guestName[0] = '\0';
            r.checkInDate[0] = '\0';
            r.checkOutDate[0] = '\0';
        }
        else
        {
            strcpy(r.guestName, gName);
            strcpy(r.checkInDate, cIn);
            strcpy(r.checkOutDate, cOut);
        }

        temp[count] = r;
        count++;
    }

    fclose(f);

    for (int i = 0; i < count; i++)
        rooms[i] = temp[i];

    roomCount = count;
    printf("Doc file %s va cap nhat danh sach thanh cong!\n", fullPath);
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

