#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

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

/* Prototype */
int isLeapYear(int year);
int daysInMonth(int month, int year);
int isValidDate(char *date);
long dateToDays(char *date);
void clearInput(void);

/* Ham tien ich: xoa bo ky tu thua trong stdin */
void clearInput(void)
{
    scanf("%*[^\n]");
    getchar();
}
/* Ham tien ich: nhap ma phong 101-200 co kiem tra */
int inputRoomId(const char *prompt)
{
    int roomId;
    do
    {
        printf("%s", prompt);
        if (scanf("%d", &roomId) != 1)
        {
            clearInput();
            roomId = 0;
        }
        if (roomId < 101 || roomId > 200)
            printf("Vui long nhap lai ma phong (101-200)!\n");
    } while (roomId < 101 || roomId > 200);
    return roomId;
}

/* 11 ham chuc nang: TV2, TV3 dien code vao than ham */
void addRoom(void)
{
    if (roomCount >= MAX)
    {
        printf("Danh sach phong da day!\n");
        return;
    }

    Room r = {0};

    while (1)
    {
        printf("Nhap ma phong: ");
        if (scanf("%d", &r.roomId) != 1 || r.roomId < 101 || r.roomId > 200)
        {
            printf("Ma phong khong hop le (chi tu 101 den 200)!\n");
            clearInput();
            continue;
        }
        int trung = 0;
        for (int i = 0; i < roomCount; i++)
            if (rooms[i].roomId == r.roomId)
                trung = 1;
        if (trung)
        {
            printf("Ma phong da ton tai!\n");
            clearInput();
            continue;
        }
        break;
    }

    while (1)
    {
        printf("Nhap loai phong (Don/Doi/Vip/TongThong): ");
        if (scanf("%19s", r.roomType) != 1)
        {
            clearInput();
            continue;
        }

        char firstChar = r.roomType[0];
        if (firstChar == 'V' || firstChar == 'v')
        {
            strcpy(r.roomType, "VIP");
            break;
        }
        else if (firstChar == 'T' || firstChar == 't')
        {
            strcpy(r.roomType, "TongThong");
            break;
        }
        else if (firstChar == 'D' || firstChar == 'd')
        {
            int len = strlen(r.roomType);
            char lastChar = r.roomType[len - 1];
            if (len == 1 || lastChar == 'n' || lastChar == 'N')
            {
                strcpy(r.roomType, "Don");
                break;
            }
            else if (lastChar == 'i' || lastChar == 'I')
            {
                strcpy(r.roomType, "Doi");
                break;
            }
        }
        printf("Loai phong khong hop le!\n");
    }

    printf("-> Da ghi nhan loai phong: %s\n", r.roomType);

    while (1)
    {
        printf("Nhap gia phong: ");
        if (scanf("%ld", &r.pricePerDay) == 1 && r.pricePerDay > 0)
            break;
        printf("Gia phong khong hop le!\n");
        clearInput();
    }

    while (1)
    {
        printf("Nhap so khach toi da (1-10): ");
        if (scanf("%d", &r.maxGuests) == 1 && r.maxGuests >= 1 && r.maxGuests <= 10)
            break;
        printf("So khach phai tu 1 den 10!\n");
        clearInput();
    }

    clearInput();

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
        int booked = (rooms[i].status == ROOM_BOOKED);
        const char *trangThai = booked ? "Da dat" : "Trong";
        const char *tenKhach = booked ? rooms[i].guestName : "-";
        const char *ngayVao = booked ? rooms[i].checkInDate : "-";
        const char *ngayRa = "-";
        if (booked)
            ngayRa = strlen(rooms[i].checkOutDate) > 0 ? rooms[i].checkOutDate : "Chua tra";

        printf("%-10d %-12s %-12ld %-10d %-12s %-20s %-12s %-12s\n",
               rooms[i].roomId,
               rooms[i].roomType,
               rooms[i].pricePerDay,
               rooms[i].maxGuests,
               trangThai,
               tenKhach,
               ngayVao,
               ngayRa);

        if ((i + 1) % 20 == 0 && i + 1 < roomCount)
        {
            printf("Nhan Enter de xem tiep...");
            getchar();
        }
    }
    printf("=================================================================================================================\n\n");
}

void updateRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void deleteRoom(void) { printf("Chuc nang dang phat trien.\n"); }

int findRooms(int room)
{
    for (int i = 0; i < roomCount; i++)
    {
        if (room == rooms[i].roomId)
            return i; /* co */
    }
    return -1; /* kh */
}

int findRoomsGuest(int guest)
{
    for (int i = 0; i < roomCount; i++)
    {
        if (guest == rooms[i].maxGuests)
            return i; /* co */
    }
    return -1; /* kh */
}

void searchRooms(void)
{
    int guest;
    printf("------TIM KIEM PHONG------\n");
    printf("Nhap so nguoi thue: ");
    if (scanf("%d", &guest) != 1 || guest <= 0)
    {
        clearInput();
        printf("So nguoi khong hop le!\n");
        return;
    }
    if (findRoomsGuest(guest) == -1)
    {
        printf("Phong khong ton tai!\n");
        return;
    }

    char loai[20];
    long money = 0;
    if (guest == 1){
        strcpy(loai, "DON");
        money = 350000;
    }
    else if (guest == 2){
        strcpy(loai, "DOI");
        money = 550000;
    }
    else if (guest >= 2 && guest <= 5){
        strcpy(loai, "VIP");
        money = 1500000;
    }
    else{
        strcpy(loai, "TONGTHONG");
        money = 3500000;
    }
        
    int dem = 0;
    for (int i = 0; i < roomCount; i++){
        if (strcasecmp(rooms[i].roomType, loai) == 0 && rooms[i].status == ROOM_EMPTY && rooms[i].maxGuests >= guest)
            dem++;
    }
    printf("Hien tai co %d phong %s danh cho ban voi gia %ld VND\n", dem, loai, money);

    for (int i = 0; i < roomCount; i++){
        if (strcasecmp(rooms[i].roomType, loai) == 0 && rooms[i].status == ROOM_EMPTY && rooms[i].maxGuests >= guest)
        printf("Phong %d - Gia: %ld VND/ngay - Toi da %d khach\n",
                   rooms[i].roomId, rooms[i].pricePerDay, rooms[i].maxGuests);
    }      
}

void bookRoom(void)
{
    char yourName[51];
    char inDate[32];
    char outDate[32];

    printf("------DAT PHONG------\n");
    int index = findRooms(inputRoomId("Nhap so phong ban muon dat: "));
    if (index == -1)
    {
        printf("Khong tim thay phong!\n");
        return;
    }
    if (rooms[index].status == ROOM_BOOKED)
    {
        printf("Phong nay da duoc dat roi!\n");
        return;
    } 

    clearInput();
    printf("Nhap ho & ten cua ban: ");
    gets(yourName);

    while (1)//lặp vô tận
    {
        printf("Nhap ngay vao (DDMMYYYY): ");
        gets(inDate);
        if (isValidDate(inDate)){
            break;
        }
    printf("Ngay khong hop le! Vui long nhap lai.\n");
    }
    while (1)
    {
        printf("Nhap ngay ra (DDMMYYYY): ");
        gets(outDate);
        if (!isValidDate(outDate))
        {
            printf("Ngay khong hop le! Vui long nhap lai.\n");
            continue;
        }
        if (dateToDays(outDate) < dateToDays(inDate))
        {
            printf("Ngay ra phai tu ngay vao tro di! Vui long nhap lai.\n");
            continue;
        }
        break;
    }

    printf("Da dat phong cho anh/chi: %s \n", yourName);
    rooms[index].status = ROOM_BOOKED;
    strcpy(rooms[index].guestName, yourName);
    strcpy(rooms[index].checkInDate, inDate);
    strcpy(rooms[index].checkOutDate, outDate);
    printf("---DAT PHONG THANH CONG---\n");
}

void checkoutRoom(void)
{
    printf("------TRA PHONG------\n");
    int index = findRooms(inputRoomId("Nhap so phong cua ban: "));
    if (index == -1)
    {
        printf("Khong tim thay phong!\n");
        return;
    }
    if (rooms[index].status == ROOM_EMPTY)
    {
        printf("Phong nay dang trong, chua duoc dat!\n");
        return;
    }

    int acp = -1;
    do
    {
        printf("Xac nhan tra phong nay (co & khong <1|0>): ");
        if (scanf("%d", &acp) != 1){
            clearInput();  /* hot sach "abc" khoi bo dem */
            acp = -1;
        }
    if (acp != 0 && acp != 1)
        printf("Vui long nhap dung dinh dang!\n");
    } while (acp != 0 && acp != 1);

    if (acp == 0)
    {
        printf("Ban da huy thanh toan!\n");
        return;
    }

    printf("----HOA DON THANH TOAN----\n");
    long days = dateToDays(rooms[index].checkOutDate) - dateToDays(rooms[index].checkInDate);
    if (days < 1)
        days = 1; /* Đã đặt phòng là tính 1 ngày */
    long bill = days * rooms[index].pricePerDay;
    totalRevenue += bill;
    printf("Ma phong: %d\n", rooms[index].roomId);
    printf("Khach hang: %s\n", rooms[index].guestName);
    printf("So ngay o: %ld ngay\n", days);
    printf("Thanh tien: %ld VND\n", bill);
    printf("Thanh toan thanh cong!\n");

    rooms[index].status = ROOM_EMPTY;
    strcpy(rooms[index].guestName, "");
    strcpy(rooms[index].checkInDate, "");
    strcpy(rooms[index].checkOutDate, "");
}

void showStatistics(void)
{
    int roomBooked = 0;
    int roomEmpty = 0;
    printf("------THONG KE DOANH THU------\n");
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i].status == ROOM_EMPTY)
            roomEmpty++;
        else if (rooms[i].status == ROOM_BOOKED)
            roomBooked++;
    }
    printf("So phong dang trong: %d\n", roomEmpty);
    printf("So phong da co nguoi: %d\n", roomBooked);
    printf("Tong doanh thu cua khach san la: %ld VND\n", totalRevenue);
}

void sortByPrice(void)
{

    if (roomCount < 2)
    {
        printf("Khong du phong de sap xep!\n");
        return;
    }

    int choice;
    printf("--- SAP XEP PHONG THEO GIA ---\n");
    printf("1. Tang dan theo gia\n");
    printf("2. Giam dan theo gia\n");

    do
    {
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        if(choice != 1 && choice != 2)
            printf("Lua chon khong hop le!\n");

    } while (choice != 1 && choice != 2);
    
    clearInput();

    for (int i = 0; i < roomCount - 1; i++)
    {
        for (int j = i + 1; j < roomCount; j++)
        {
            int swap;
            if(choice == 1){
                swap = (rooms[i].pricePerDay > rooms[j].pricePerDay);
            }
            else{
                swap = (rooms[i].pricePerDay < rooms[j].pricePerDay);
            }

            if (swap)
            {
                Room temp = rooms[i];
                rooms[i] = rooms[j];
                rooms[j] = temp;
            }
        }
    }

    printf("Sap xep phong thanh cong! Hay chon chuc nang 2 de xem lai danh sach.\n");
}

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



/* 11 ham chuc nang: TV2, TV3 dien code vao than ham */
void addRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void displayRooms(void) { printf("Chuc nang dang phat trien.\n"); }
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
void updateRoom(void) { printf("Chuc nang dang phat trien.\n"); }
void deleteRoom(void) { printf("Chuc nang dang phat trien.\n"); }
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
	//printf("Chuc nang dang phat trien.\n"); 
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

            clearInput();
            //system("cls||clear");

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

            //system("cls||clear");
            printf("\n");

            system("cls||clear");
            continue;
        }
        if (choice != 0)
        {

            printf("Nhan Enter de tiep tuc...\n");
            printf("\n");
            clearInput();
        }
        //system("cls||clear");

            printf("Nhan Enter de tiep tuc...");
            scanf("%*[^\n]");
            getchar();
        }
        system("cls||clear");

    return 0;
}
    
